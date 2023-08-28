/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   IPC Ping Pong           */
/*   Date:      04/05/23                */
/*   Reviewer:  Ariel Kerner            */
/*                                      */
/****************************************/

#include <stdio.h>      /* printf */
#include <sys/shm.h>    /* key_t */
  
int main(void)
{
    key_t key = ftok("shm_file", 2);  
    int shmid = 0;
    char *str = NULL;
    
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    str = (char*) shmat(shmid, 0 ,0);
  
    printf("Data read: %s\n",str);
      
    shmdt(str);
    
    shmctl(shmid,IPC_RMID,NULL);
    
    return 0; 
}
