#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
sem_t interviewSemp;
sem_t applicantSemp;
sem_t mutex;
int count=0;
typedef struct Applicants
{
  int nr;
  int id;
} Applicants;
Applicants applicants[1000];
Applicants applicantQue[1000];
int queue_cnt=0;
int interviewed_cnt=0;
int flag=0;
void * Receptionist(void *a)
{
  
    FILE *fptr;
    fptr=fopen("applicantList.txt","r");
    sem_wait(&mutex);
    while(!feof(fptr))
    {
        
        printf("Applicant %d has entered\n", count);
        fscanf(fptr,"%d", &(applicants[count].nr));
        applicants[count].id=count++;
            
    }

    sem_post(&mutex);
    
    int i=0;
    count--;
    for(i=0;i<count;i++)
      {
        sem_wait(&mutex);    
        sleep(1);
        printf("Applicant %d's registiration is done.\n",i);
        applicantQue[queue_cnt++]=applicants[i];
        sem_post(&applicantSemp);
        sem_post(&mutex);
      }
 
  
}
void * Interviewer(void * a)
{
 
  while(22&&!flag)
    {

  
      
    sem_wait(&applicantSemp);
    sem_wait(&interviewSemp);
    int val=applicantQue[interviewed_cnt++].id;
    if(interviewed_cnt==count)
	{
        flag=1;
	sem_post(&applicantSemp);
	sem_post(&applicantSemp);

	}
    sem_post(&interviewSemp);
	if(flag && !val)
		break;
	
    printf("Interview 1 with Applicant %d is started\n", val);
    sleep(applicantQue[interviewed_cnt-1].nr/10);
    printf("Interviewer 1 finished interview with Applicant %d\n",val);
  
   
    }
  
}

void * Interviewer2(void * a)
{
 
  while(22&& !flag)
    {

     
      sem_wait(&applicantSemp);
      sem_wait(&interviewSemp);
      int val=applicantQue[interviewed_cnt++].id;
      if(interviewed_cnt==count){
        flag=1;
	sem_post(&applicantSemp);
	sem_post(&applicantSemp);

	}
      sem_post(&interviewSemp);
	if(flag && !val)
		break;
      printf("Interview 2 with Applicant %d is started\n", val);
      sleep(applicantQue[interviewed_cnt-1].nr/10);
      printf("Interviewer 2 finished interview with Applicant %d\n",val);
    
  
    }
  
}

void * Interviewer3(void * a)
{

  while(22&&!flag)
    {

     
      sem_wait(&applicantSemp);
      sem_wait(&interviewSemp);
      int val=applicantQue[interviewed_cnt++].id;
      if(interviewed_cnt==count){
        flag=1;
	sem_post(&applicantSemp);
	sem_post(&applicantSemp);

	}
      sem_post(&interviewSemp);
	if(flag && !val)
		break;
      printf("Interview 3 with Applicant %d is started\n", val);
      sleep(applicantQue[interviewed_cnt-1].nr/10);
      printf("Interviewer 3 finished interview with Applicant %d\n",val);
    
  
    }
  
}


int main()
{
	    sem_init(&interviewSemp,0,1);
	    sem_init(&applicantSemp,0,0);
	    sem_init(&mutex,0,1);
	    pthread_t thread1,thread2,thread3,thread4;
	    if(pthread_create(&thread2,NULL,Interviewer,NULL))
		exit(1);
	    if(pthread_create(&thread1,NULL,Receptionist,NULL))
		exit(1);
	    if(pthread_create(&thread3,NULL,Interviewer2,NULL))
	      exit(1);
	   if(pthread_create(&thread4,NULL,Interviewer3,NULL))
	      exit(1);
	    if(pthread_join(thread1, NULL))	/* wait for the thread 1 to finish */
	    {
		printf("\n ERROR joining thread");
		exit(1);
	    }
	    if(pthread_join(thread2, NULL))	/* wait for the thread 1 to finish */
	    {
		printf("\n ERROR joining thread");
		exit(1);
	    }

	    if(pthread_join(thread3, NULL))	/* wait for the thread 1 to finish */
	      {
		printf("\n ERROR joining thread");
		exit(1);
	      }
		if(pthread_join(thread4, NULL))	/* wait for the thread 1 to finish */
	      {
		printf("\n ERROR joining thread");
		exit(1);
	      }
	    
	   
	    printf("All applicants have interviewed successfully.\n");
	    pthread_exit(NULL);


}
