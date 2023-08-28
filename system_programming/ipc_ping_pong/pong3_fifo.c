/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   IPC Ping Pong           */
/*   Date:      04/05/23                */
/*   Reviewer:  Ariel Kerner            */
/*                                      */
/****************************************/

#include <stdio.h>      /* printf */
#include <fcntl.h>      /* O_WRONLY */
#include <unistd.h>     /* sleep */
#include <stdlib.h>     /* exit */

void Write(void);
void Read(void);

static char *fifo = "/tmp/fifo";
static char *g_buffer1 = "PONG\n";
static char g_buffer2[6];

int main(void)
{
	while (1)
    {
       sleep(2);
       Read();
       Write();
    }

    return 0;
}

void Write(void)
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

void Read(void)
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
