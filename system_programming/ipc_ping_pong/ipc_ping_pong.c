/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   IPC Ping Pong           */
/*   Date:      04/05/23                */
/*   Reviewer:  Ariel Kerner            */
/*                                      */
/****************************************/

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit */
#include <fcntl.h>      /* O_WRONLY */
#include <sys/stat.h>   /* mkfifo */
#include <semaphore.h>  /* sem_t */
#include <unistd.h>     /* sleep */
#include <pthread.h>    /* fdopen */
#include <string.h>     /* strlen */
#include <sys/msg.h>    /* msg key_t */
#include <sys/shm.h>    /* shm key_t */

#define MAX_LEN 10 
#define PING "/ping_sem"
#define PONG "/pong_sem"
#define BUFFER_SIZE 256

struct message_buffer 
{
    long message_type;
    char message_text[100];
} message;

static char *fifo = "/tmp/fifo";
static char *g_buffer1 = "PING\n";
static char g_buffer2[6];

int Ex1Semaphore(void); 

int Ex2Pipe(void);
void Write(const char* message, int counter, FILE* stream);
void Read(FILE* stream);

int Ex3Fifo(void);
void WriteFifo(void);
void ReadFifo(void);

void Ex4MessageQueueWrite(void);
void Ex5SharedMemory(void);

int main(void)
{
	/*Ex1Semaphore();*/
    /*Ex2Pipe();*/
    /*Ex3Fifo();*/
    /*Ex4MessageQueueWrite();*/
    Ex5SharedMemory();

	return 0;
}

/*-------------------------------- Ex1Semaphore ------------------------------*/
int Ex1Semaphore(void) 
{
   	int i = 0;
    sem_t *sem_ping;
    sem_t *sem_pong; 

    sem_ping = sem_open(PING, O_CREAT, 0644, 0);
 	if (SEM_FAILED == sem_ping) 
    {
        perror("open ping failed");
        exit(1);
    }

    sem_pong = sem_open(PONG, O_CREAT, 0644, 0);   
    if (SEM_FAILED == sem_pong) 
    {
        perror("open pong failed");
        exit(1);
    }

    for (i = 0; i < 5; ++i) 
    {
        printf("PING\n");
        sleep(2);

        sem_post(sem_pong);

        sem_wait(sem_ping);
    }

    sem_close(sem_ping);
    sem_close(sem_pong);
    
    sem_unlink(PING);
    sem_unlink(PONG);
    
    return 0;
}

/*---------------------------------- Ex2Pipe ---------------------------------*/
int Ex2Pipe(void)
{
	int i = 0;
	int fds[2];
	pid_t pid;
	int read_fd = 0;
	int write_fd = 0;

	if (-1 == pipe(fds))
	{
	    printf("pipe failed\n");
	    return -1;
	}

	pid = fork();
	if (pid == 0) 
	{
		FILE *stream;
		read_fd = fds[0];

		close(fds[1]);

		stream = fdopen(read_fd, "r");

		for (i = 0; i < 5; ++ i)
		{
			Read(stream);
			printf("PONG\n");
		}
		
	    fclose(stream);
		close(fds[0]);
	}
	else if (0 < pid)
	{
		FILE* stream;
		write_fd = fds[1];

		close (fds[0]);

		stream = fdopen(write_fd, "w");

		Write("PING\n", 5, stream);
		 
		fclose(stream);
		close(write_fd);
	}
	else
	{
		close(fds[0]);
		close(fds[1]);

		perror("Fork failed");
		return -1;
	}
	return 0;
}

void Write(const char* message, int count, FILE* stream)
{
	for (count = 0; count < 5; ++count)
	{
 		fputs(message, stream);	
	}
}

void Read(FILE* stream)
{
	 char buffer[BUFFER_SIZE];
	
	 if (NULL != fgets(buffer ,sizeof(buffer), stream))
	 {
		 printf("%s", buffer); 
	 }
}

/*---------------------------------- Ex3Fifo ---------------------------------*/
int Ex3Fifo(void)
{
    if (-1 == mkfifo(fifo, 0666))
    {
    	perror("mkfifo failed\n");
    	exit(1);
    }
	while (1)
    {
       WriteFifo();
       sleep(1);
       ReadFifo();
    }
    return 0;
}

void WriteFifo(void)
{
	int fd = open(fifo, O_WRONLY);
	if (-1 == fd) 
	{
		perror("Failed to open");
		exit(1);
	}
	if (-1 == write(fd, g_buffer1, 6)) 
    {
        perror("Failed to write");
		exit(1);
    }
    close(fd);
}

void ReadFifo(void)
{
	int fd = open(fifo, O_RDONLY);
	if (-1 == fd) 
	{
		perror("Failed to open");
		exit(1);
	}
	if (-1 == read(fd, g_buffer2, 6)) 
    {
        perror("Failed to write");
		exit(1);
    }
    printf("%s", g_buffer2);
    
    close(fd);
}

/*--------------------------- Ex4MessageQueueWrite ---------------------------*/
void Ex4MessageQueueWrite(void)
{
    key_t key = 0;
    int msg_id = 0;
  
    key = ftok("message queue", 1);
  
    msg_id = msgget(key, 0666 | IPC_CREAT);
    message.message_type = 1;
  
    printf("Write Data: ");
    fgets(message.message_text, MAX_LEN, stdin);
  
    msgsnd(msg_id, &message, sizeof(message), 0);
  
    printf("Data written: %s \n", message.message_text);
  
}

/*------------------------------ Ex5SharedMemory -----------------------------*/ 
void Ex5SharedMemory(void)
{
    key_t key = ftok("shm_file", 1);
    int shmid = 0;
    char *str = NULL;
    
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    str = (char*) shmat(shmid, 0 ,0);
  
    printf("Write Data: ");
    fgets(str, MAX_LEN, stdin);
        
    shmdt(str);
}