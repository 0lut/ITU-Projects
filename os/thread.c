#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *printfunc(void *ptr)
{

  char *msg;
  msg=(char *)ptr;
  printf("%s \n",msg);


  pthread_exit(NULL);
  
}

int main()
{

  pthread_t th1,th2,th3;
  char *msg1="Hello";
  char *msg2="Hello2";
  char *msg3="Hello3";


  pthread_create(&th1,NULL,printfunc, (void *)msg1
}
