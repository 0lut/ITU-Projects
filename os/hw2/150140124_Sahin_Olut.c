#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_APP 1000
  /*
  * My code supports up to 1000 applicants, for more applicants, NUM_APP can be replaced with any number+1 desired. Last element of array has special usage.
  * Compiliation command : gcc fileName.c -lrt -lpthread -o outputFile

  */
sem_t interviewSemp; //Mutex for taking a candidate
sem_t applicantSemp; // Signaling interviews to warn there is a candidate waiting
sem_t mutex; //While doing registration, some information has to be preserved.
int count = 0; // Number of applicants
typedef struct Applicants {
  int ni;
  int id;
} Applicants;

Applicants applicants[NUM_APP];
Applicants applicantQue[NUM_APP];
int queue_cnt = 0;
int interviewed_cnt = 0; // Simple queue implementation with array.
int flag = 0;
int nr;
char * inpFile;
void * Receptionist(void * a) {

  FILE * fptr;
  fptr = fopen(inpFile, "r");
  sem_wait( & mutex);
  while (fscanf(fptr, "%d", & (applicants[count].ni))) {
    if (feof(fptr))
      break;
    printf("Applicant %d applied to receptionist\n", count + 1);
    applicants[count].id = count++;

  }

  sem_post( & mutex);

  int i = 0;

  for (i = 0; i < count; i++) {
    sem_wait( & mutex);
    sleep(nr);
    printf("Applicant %d's registeration is done\n", i + 1);
    applicantQue[queue_cnt++] = applicants[i];
    sem_post( & applicantSemp); //sırası degisti
    sem_post( & mutex);

  }

}
void * Interviewer(void * a) {

  int * _id = (int * ) a;
  while (22 && !flag) {

    sem_wait( & applicantSemp);
    sem_wait( & interviewSemp);
    int val = applicantQue[interviewed_cnt++].id;
    if (interviewed_cnt == count) // All candidates are taken to interview
    {
      flag = 1;
      sem_post( & applicantSemp);
      sem_post( & applicantSemp);
    }
    sem_post( & interviewSemp);
    if (flag && !val) // Candidate queue is empty.
      break;

    printf("Interview %d started inverview with Applicant %d\n", _id, val + 1);
    sleep(applicantQue[interviewed_cnt - 1].ni );
    printf("Interviewer %d finished interview with Applicant %d\n", _id, val + 1);

  }

}

int main(int argc, char *argv[]) {
  nr=atoi(argv[2]);
  inpFile=argv[1];
  sem_init( & interviewSemp, 0, 1);
  sem_init( & applicantSemp, 0, 0);
  sem_init( & mutex, 0, 1);
  pthread_t thread1, thread2, thread3, thread4;
  if (pthread_create( & thread2, NULL, Interviewer, (void * ) 1))
    exit(1);
  if (pthread_create( & thread1, NULL, Receptionist, NULL))
    exit(1);
  if (pthread_create( & thread3, NULL, Interviewer, (void * ) 2))
    exit(1);
  if (pthread_create( & thread4, NULL, Interviewer, (void * ) 3))
    exit(1);
  if (pthread_join(thread1, NULL)) /* wait for the thread 1 to finish */ {
    printf("\n ERROR joining thread");
    exit(1);
  }
  if (pthread_join(thread2, NULL)) /* wait for the thread 1 to finish */ {
    printf("\n ERROR joining thread");
    exit(1);
  }

  if (pthread_join(thread3, NULL)) /* wait for the thread 1 to finish */ {
    printf("\n ERROR joining thread");
    exit(1);
  }
  if (pthread_join(thread4, NULL)) /* wait for the thread 1 to finish */ {
    printf("\n ERROR joining thread");
    exit(1);
  }

  printf("All applicants have interviewed successfully.\n");
  sem_destroy(&interviewSemp);
  sem_destroy(&applicantSemp);
  sem_destroy(&mutex);

  pthread_exit(NULL);

}
