#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define threadSayisi 5
pthread_t threads[threadSayisi];

int seats = 3;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t customers;
sem_t barber;


  void *berber(void *threadid){
  int haircuts = threadSayisi-1;
  while(haircuts > 0){
    sem_wait(&customers);
    pthread_mutex_lock(&mutex);
    seats++;
    sem_post(&barber);
    haircuts--;
     printf("Saç kes, Sonraki müşteriyi bekleyin.\n");
    pthread_mutex_unlock(&mutex);
    printf("\n Birol Berber Thread: kesimler = %d, boş koltuk  = %d \n",haircuts,seats);
  }
  printf("Dükkan Kapnadı, baybay!\n");
  pthread_exit(NULL);
}

void *customer(void *threadid)
{

  int haircuts = 1;
  while(haircuts > 0){
    pthread_mutex_lock(&mutex);
    if(seats > 0){
      seats--;
      printf("elemanlar ile delirmeceler birol bekleniyor. \n");
      sem_post(&customers);
      haircuts--;
  sleep(1);
      pthread_mutex_unlock(&mutex);
      sem_wait(&barber);
      printf("Sıhatler olsun borcunuz 18TL sen 20 ver 2 tl de elemanlara TİP :D %d \n", (int)threadid);
    }
    else{
      pthread_mutex_unlock(&mutex);
      printf("\n Müşteri Thread:%d abi benim bi işim çıktı yarın traş olrum sıra gelmeyecek bana = %d\n",(int)threadid, seats);
      sleep(1);
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  if(argc < 2 || argc > 3){
    printf("Wrong number of arguments: Usage > barber.exe x \n");
  }
  seats = atoi(argv[1]);
  printf("number of chairs %d \n", seats);
  sem_init(&customers,0,0);
  sem_init(&barber,0,0);
  int t;
  for(t=0;t<threadSayisi;t++){
    printf("Creating thread %d\n", t);
    if(t == 0){
      pthread_create(&threads[t], NULL, berber, (void *)t);
    }
    else{
      pthread_create(&threads[t], NULL, customer, (void *)t);
    }
  }


  for(t = 0; t < threadSayisi; t++)
    pthread_join(threads[t],NULL);
  pthread_exit(NULL);
}