/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 25.11.2022                                        */
/* WORKSHEET NAME: word boundary optimization                       */
/* GDB + Valgrind tested                                            */
/* Reviewer: Karin                                                  */
/*------------------------------------------------------------------*/
#include <stddef.h>/*size_t*/

void *Memset(void *ptr, int c, size_t n);
void *Memcpy(void *dest, const void *src, size_t n);
void *Memmove(void *dest, const void *src, size_t n);
