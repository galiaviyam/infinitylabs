/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   IPC Ping Pong           */
/*   Date:      04/05/23                */
/*   Reviewer:  Ariel Kerner            */
/*                                      */
/****************************************/

#include <stdio.h>      /* printf */
#include <sys/msg.h>    /* key_t */
  
struct message_buffer 
{
    long message_type;
    char message_text[100];
} message;
  
int main(void)
{
    key_t key = 0;
    int msg_id = 0;
  
    key = ftok("message queue", 2);
  
    msg_id = msgget(key, 0666 | IPC_CREAT);
  
    msgrcv(msg_id, &message, sizeof(message), 1, 0);
  
    printf("Data Received: %s \n", message.message_text);
  
    msgctl(msg_id, IPC_RMID, NULL);
  
    return 0;
}

