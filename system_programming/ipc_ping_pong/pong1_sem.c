/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   IPC Ping Pong           */
/*   Date:      04/05/23                */
/*   Reviewer:  Ariel Kerner            */
/*                                      */
/****************************************/

#include <stdio.h>      /* printf */
#include <stdlib.h>		/* exit */
#include <fcntl.h>      /* O_CREAT */
#include <semaphore.h>  /* sem_t */
#include <unistd.h>     /* sleep */

#define PING "/ping_sem"
#define PONG "/pong_sem"

int main(void) 
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
        sem_wait(sem_pong);
       
        printf("PONG\n");

        sem_post(sem_ping);
    }

    sem_close(sem_ping);
    sem_close(sem_pong);
   
    return 0;
}


