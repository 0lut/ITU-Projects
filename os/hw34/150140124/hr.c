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
typedef struct Applicant {
  int applicantNum;
  int ni;
  int nt;
  int statusHr;
  int statusTr;

} Applicant;
int nr;
Applicant applicants[1000];
Applicant applicantQue[1000];
int num_applicants=0;
int queue_cnt=0;
int interviewed_cnt = 0;
int flag=0;
sem_t mutex;
sem_t applicantSem;
sem_t interview_mutex;
sem_t *sem;
sem_t *sem_signal_trial;
sem_t *mem_mutex;
FILE *fptr;
void readFile();
void * Receptionist();
void * Interviewer(void *a);
int * shm_ptr;

int main(int argc, char *argv[])
{
  sleep(1);
  sem = sem_open("Applicant_Sem", 0);
  mem_mutex=sem_open("MEM_MUTEX",0);
  sem_signal_trial = sem_open("/Hr_to_Trial2", O_CREAT, 0600, 0);
  sem_init(sem_signal_trial,1,0); //after each successful interview, trainers will be alerted.

  fptr=fopen(argv[1],"r");

  sem_init( & mutex, 1, 1);
  sem_init(&applicantSem,1,0);
  sem_init(&interview_mutex,1,1);

  sem_getvalue(sem,&num_applicants);
  int shm_fd= shm_open("Status",O_RDWR,0666);
  shm_ptr =(int *)mmap(0,sizeof(int)*num_applicants,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);

  pthread_t thread1, thread2, thread3, thread4;
  if (pthread_create( & thread1, NULL, Receptionist, NULL))
    exit(1);
  if (pthread_create( & thread2, NULL, Interviewer, (void * ) 1))
    exit(1);
  if (pthread_create( & thread3, NULL, Interviewer, (void * ) 2))
    exit(1);
  if (pthread_create( & thread4, NULL, Interviewer, (void * ) 3))
    exit(1);

    if (pthread_join(thread2, NULL)) /* wait for the thread 1 to finish */ {
      printf("\n ERROR joining thread1");
      exit(1);
    }

    if (pthread_join(thread3, NULL)) /* wait for the thread 1 to finish */ {
      printf("\n ERROR joining thread2");
      exit(1);
    }
    if (pthread_join(thread4, NULL)) /* wait for the thread 1 to finish */ {
      printf("\n ERROR joining thread3");
      exit(1);
    }


  printf("All applicants have interviewed successfully.\n");


  sem_destroy(sem_signal_trial);
  sem_destroy(&mutex);
  sem_destroy(&applicantSem);
  sem_destroy(&interview_mutex);
  pthread_exit(NULL);
}
void readFile()
{
  int i=0;
  for(;i<num_applicants;i++)
  {
    fscanf(fptr,"%d %d %d %d", (&applicants[i].ni),(&applicants[i].nt), (&applicants[i].statusHr), (&applicants[i].statusTr));
    applicants[i].applicantNum = i;
    printf("Applicant %d applied to the receptionist (status of applicant %d: %d)\n",i+1,i+1,shm_ptr[i]);
  }



}


void *Receptionist()
{
  fscanf(fptr,"%d", &nr);
  printf("Registeration time is: %d seconds\n",nr);
  readFile();

  int i=0;
  for(;i<num_applicants;i++)
  {
    sem_wait(&mutex);
    sleep(nr/5);
    printf("Applicant %d's registeration is done (status of applicant %d: %d)\n", i+1,i+1,shm_ptr[i]);
    applicantQue[queue_cnt++]=applicants[i];
    sem_post(&applicantSem);
    sem_post(&mutex);

  }

  printf("Registeration process is done.\n");

}


void * Interviewer(void *a)
{
  int * _id=(int *) a;

  while(!flag)
  {
    sem_wait(&applicantSem);
    sem_wait(&interview_mutex);
    int success=applicantQue[interviewed_cnt].statusHr;
    int val=applicantQue[interviewed_cnt++].applicantNum;
    if (interviewed_cnt == num_applicants) // All candidates are taken to interview
    {
      flag = 1;
      sem_post( & applicantSem);
      sem_post( & applicantSem);
    }
    printf("Interview %d started inverview with Applicant %d (status of applicant %d: %d)\n", _id, val + 1, val+1,0);
    sem_post(&interview_mutex);
    if (flag && !val) // Candidate queue is empty.
      break;
    sleep(applicantQue[interviewed_cnt - 1].ni / 10);
    if(success)
    {
      sem_wait(mem_mutex);
      *(shm_ptr+val)=2;
      sem_post(mem_mutex);
      sem_post(sem_signal_trial);

    }
    else
    {
      sem_wait(mem_mutex);
      *(shm_ptr+val)=1;
      sem_post(mem_mutex);
    }

    printf("Interviewer %d finished interview with Applicant %d(status of applicant %d: %d)\n", _id, val + 1, val+1,shm_ptr[val]);



  }
 // applicanttan her sinyal geldiğinde num_applicants artacak ve register dosyadan yeni bi şey okuyacak.(gelen sinyal kadar, readfile aslında tek okuma yapacak.)

}
