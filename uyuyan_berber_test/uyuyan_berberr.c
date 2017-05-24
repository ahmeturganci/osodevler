#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define threadSayisi 5
#define sandalyeSayisi 3
pthread_t threads[threadSayisi];
sem_t beklemeSalonu;
sem_t mutex;
sem_t musteriler;
sem_t berberler;
void *berber(void *threadid);
void *musteri(void *threadid);
int bitis=0;
int berberSayisi=1;

void *berber(void *threadid){
  while(!bitis){
      sem_wait(&musteriler);
      if(!bitis){
          printf("Berber saç kesiyor\nSaç kesildi.\n");
          sleep(2);
          sem_post(&mutex);
      }
      else{
          printf("Berber Kapandi.\n");
      }
  }
}
void *musteri(void *threadid){
    int id=*(int *)threadid;
    sem_wait(&beklemeSalonu);
    printf("%d.Musteri bekleme salonunda bekliyor \n", id);
    sleep(1);
    sem_wait(&berberler);
    sem_post(&beklemeSalonu);
    sem_post(&musteriler);
    sem_wait(&mutex);
    sem_post(&berberler);
    printf("%d. Saç kesimi bitti\n",id);
}

int main(){
    printf("Berber birol devreye giriyor\n");
  pthread_t btid;
  pthread_t tid[threadSayisi];
  int i, numCustomers, numChairs;
  int Numbers[threadSayisi];
  numCustomers = threadSayisi;
  numChairs = sandalyeSayisi;
  for (i = 0; i < numCustomers; i++)
  {
    Numbers[i] = i;
  }

  sem_init(&beklemeSalonu, 0, numChairs);
  sem_init(&berberler, 0, berberSayisi);
  sem_init(&musteriler, 0, 0);
  sem_init(&mutex, 0, 0);

  pthread_create(&btid, NULL, berber, NULL);

  for (i = 0; i < numCustomers; i++)
  {
    pthread_create(&tid[i], NULL, musteri, (void *)&Numbers[i]);
  }

  for (i = 0; i < numCustomers; i++)
  {
    pthread_join(tid[i], NULL);
  }

  bitis = 1;
  sem_post(&musteriler); 
  pthread_join(btid, NULL);
    return 0;
}