#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>


#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)


int main(int argc, char * argv[])
{
  int num_applicants=atoi(argv[1]);
  sem_t *sem = sem_open("Applicant_Sem", O_CREAT, 0644, 0); //this semaphore will signal to HR deparment that a new applicant came.(a process forked.)
  sem_init(sem, 1, 0);
  sem_t *mem_mutex = sem_open("MEM_MUTEX", O_CREAT, 0644, 1); //this semaphore will signal to HR deparment that a new applicant came.(a process forked.)
  sem_init(mem_mutex, 1, 1);


  sem_t *signal_to_app= sem_open("/trial_to_app", O_CREAT, 0600, 0);
  sem_init(signal_to_app,1,0);
  int shm_fd = shm_open("Status",O_CREAT | O_RDWR,0666);
  ftruncate(shm_fd,sizeof(int)*num_applicants );
  int *shm_ptr=mmap(0,sizeof(int)*num_applicants , PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  int i=0;
  for(;i<num_applicants;i++)
  {
     sem_wait(mem_mutex);
    * (shm_ptr+i) =0;
      sem_post(mem_mutex);
  }



  for(num_applicants;num_applicants>0;num_applicants--)
  {
      int f=fork();
      if(!f) // if child.
      {
      sem_post(sem);
      int value;
      sem_getvalue(sem, &value);
     // printf("The value of the semaphors is %d\n", value);
      exit(0);
      break;
      }
  }

  sem_wait(signal_to_app);
  sem_unlink("/trial_to_app");
  sem_unlink("Applicant_Sem");
  shm_unlink("Status");
  return 0;
}

/*
*/
