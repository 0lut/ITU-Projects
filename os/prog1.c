#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (void)
{
  pid_t f;
  int  myGlobal=5;
  int *myPtr= &myGlobal;
  printf("I point to: %d\n", myPtr);
  printf("Pointed values is: %d\n", *myPtr);
  
  f=fork();
  if (f==-1)
  {
    printf("Error \n");
    exit(1);
  } 
  else if (f==0)
  {
    *myPtr=3;
    printf("   Child: My process ID: %d \n", getpid());
    sleep(1);
    printf("   Child: My parent's process ID: %d \n", getppid());
    printf("   Child: My ptr is: %d \n",*myPtr);
    exit(0);
  }
  else
  {
    wait(NULL);
    printf("Parent: My parent's process ID: %d \n", getppid());
    printf("Parent: My process ID: %d \n", getpid());
    printf("Parent: My child's process ID: %d \n", f);
    printf("Parent: My ptr is: %d \n", *myPtr);
    printf("Parent: Terminating...\n");
    exit(0);
  }
  return (0);
}

