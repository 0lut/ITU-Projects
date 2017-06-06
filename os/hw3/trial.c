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
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

typedef struct Applicant {
  int applicantNum;
  int ni;
  int nt;
  int statusHr;
  int statusTr;

} Applicant;
sem_t *sem_hr;
sem_t *sem_applicants;
sem_t trainerSem; // mutex for trainers
sem_t *mem_mutex;
sem_t *signal_to_hr;
sem_t *signal_to_app;
FILE *fptr;
int traniee_cnt;
int trained;
int * shm_ptr;
void readFile();
void * Trainer(void * a);
int num_applicants;
Applicant applicants[1000];
int queue_cnt=0;
int flag=0;
int main(int argc, char *argv[])
{

  sleep(2);

  sem_init(&trainerSem,0,1);

  pthread_t thread1, thread2, thread3, thread4;

  signal_to_app= sem_open("/trial_to_app",0);


  sem_hr=sem_open("/Hr_to_Trial2",0);
  mem_mutex=sem_open("MEM_MUTEX",0);
  sem_applicants=sem_open("Applicant_Sem",0);


  sem_getvalue(sem_applicants,&num_applicants);
  int val;
  sem_getvalue(sem_hr,&val);





  int shm_fd= shm_open("Status",O_RDWR,0666);
  shm_ptr =(int *)mmap(0,sizeof(int)*num_applicants,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
  fptr=fopen(argv[1],"r");
  readFile();

  if (pthread_create( & thread1, NULL, Trainer, (void * ) 1))
    exit(1);
  if (pthread_create( & thread2, NULL, Trainer, (void * ) 2))
    exit(1);
    if (pthread_create( & thread3, NULL, Trainer, (void * ) 3))
      exit(1);
    if (pthread_create( & thread4, NULL, Trainer, (void * ) 4))
      exit(1);

      if (pthread_join(thread1, NULL)) /* wait for the thread 1 to finish */ {
        printf("\n ERROR joining thread41");
        exit(1);
      }

      if (pthread_join(thread2, NULL)) /* wait for the thread 1 to finish */ {
        printf("\n ERROR joining thread4");
        exit(1);
      }
      if (pthread_join(thread3, NULL)) /* wait for the thread 1 to finish */ {
        printf("\n ERROR joining thread5");
        exit(1);
      }
      if (pthread_join(thread4, NULL)) /* wait for the thread 1 to finish */ {
        printf("\n ERROR joining thread6");
        exit(1);
      }

      printf("Training process is done.\n");





}

void * Trainer(void *a)
{
  int * _id=(int *)a;
  while(!flag)
  {

    sem_wait(sem_hr);
    sem_wait(&trainerSem);
    int i=0;
    int val;
    printf("asddddddddd");
    for(;i<num_applicants;i++)
    {

      if(shm_ptr[i]==2)
        {
          sem_wait(mem_mutex);
          printf("Trainer %d started training with Applicant %d (status of applicant %d: %d)\n", _id,i+1,i+1,2);
          *(shm_ptr+i)=-1; //dummy value.
          trained++;
          sem_post(mem_mutex);
          if(trained==traniee_cnt)
          {
            flag=1;
            sem_post(sem_hr);
            sem_post(sem_hr);
            sem_post(sem_hr);
            sem_post(signal_to_app);


          }

          break;

        }

    }


    sem_post(&trainerSem);
    sleep(applicants[i].nt / 10);
    sem_wait(mem_mutex);
    if(applicants[i].statusTr) //successful
      *(shm_ptr+i)=4;
    else
      *(shm_ptr+i)=3;
    sem_post(mem_mutex);
    printf("Trainer %d finished training with Applicant %d (status of applicant %d: %d)\n",_id,i+1,i+1,shm_ptr[i]);



  }

  }








void readFile()
{
  int i;
  fscanf(fptr,"%d",&i);//nr is read
  for(i=0;i<num_applicants;i++)
  {
    fscanf(fptr,"%d %d %d %d", (&applicants[i].ni),(&applicants[i].nt), (&applicants[i].statusHr), (&applicants[i].statusTr));
    applicants[i].applicantNum = i;
    if(applicants[i].statusHr==1)
      traniee_cnt++;
  }



}


/*
sem_wait(sem_hr);
int i=0;
sem_wait(&trainerSem);
  printf("TRAINER CALISTI** %d\n", _id);
if(trained==traniee_cnt)
  break;
for(;i<num_applicants;i++)
{
  sem_wait(mem_mutex);
  if(shm_ptr[i]==2)
  {

    shm_ptr[i]=3;
    break;
  }
  sem_post(mem_mutex);
}
trained++;
int success=applicants[i].statusTr;
sem_post(&trainerSem);
printf("Trainer %d started interview with Traniee %d (status of trainee is: %d )\n", _id,i+1, success+1);
sleep(applicants[i].nt / 10);
printf("Trainer %d finished interview with Traniee %d\n", _id,i+1);
if(trained==traniee_cnt)
  break;
  */
