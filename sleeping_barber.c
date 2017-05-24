#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define threadSayisi 5
pthread_t threads[threadSayisi];

int seats = 1;
sem_t mutex;
sem_t customers;
sem_t barber;


  void *berber(void *threadid){
  int haircuts = threadSayisi-1;
  while(haircuts > 0){
    sem_wait(&customers);
    sem_wait(&mutex);
    seats--;
    sem_post(&barber);
    haircuts--;
     printf("Saç kesiliyor..\n");
     sem_post(&mutex);
     sleep(3);
    printf("\n Birol Berber hoşgeldiniz, Thread: kesimler = %d, boş koltuk  = %d \n",haircuts,seats);
  }
  printf("Berber Birol Kapandi!\n");
  pthread_exit(NULL);
}

void *customer(void *threadid)
{
  int haircuts = 1;
  while(haircuts > 0){
    sem_wait(&mutex);
    if(seats > 0){
      seats++;
      printf("Birol uyandiriliyor... \n");
      sem_post(&customers);
      haircuts--;
      sem_post(&mutex);
      sem_wait(&barber);
      printf("Sıhhatler olsun %d \n", (int)threadid);
    }
    else{
      printf("\n Müşteriyi kaybettik. Thread:%d  koltuk = %d\n",(int)threadid, seats);
      sem_post(&mutex);
    }
    sleep(1);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  if(argc < 2 || argc > 3){
    printf("Wrong number of arguments: Usage > barber.exe x \n");
  }
  int x = atoi(argv[1]);
  printf("number of chairs %d \n", seats);
  sem_init(&customers,0,0);
  sem_init(&barber,0,1);
  sem_init(&mutex,0,1);
  int t;
  for(t=0;t<threadSayisi;t++){
    printf("Creating thread %d\n", t);
    if(t==0){
      pthread_create(&threads[t], NULL, berber, (void *)t);
    }
    else{
      pthread_create(&threads[t], NULL, customer, (void *)t);
    }
  }


  //for(t = 0; t < threadSayisi; t++)
    //pthread_join(threads[t],NULL);
  pthread_exit(NULL);
}