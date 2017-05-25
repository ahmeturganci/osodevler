#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int threadSayisi = 0; // berber koltuk sayısı 
int sandalyeSayisi = 0; // sandalye sayısı
pthread_t threads[];
//kullandığımız semaforları tanımladık.
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
      sem_wait(&musteriler);//berber bir müşteri gelene kadar bekler.
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
    //müşteriler bekleme odasında beklerler.
    sem_wait(&beklemeSalonu);
    printf("%d.Musteri bekleme salonunda bekliyor... \n", id);
    sleep(1);
    sem_wait(&berberler);// müşteri berberi bekler.
    sem_post(&beklemeSalonu);//müşteri berber koltuğuna gelir.
    printf("%d.Musteri bekleme salonunda ayrıldı... \n", id);
    sem_post(&musteriler);//berber kesme işlemine hazırlanır
    sem_wait(&mutex);//berberin işinin bitmesi beklenir.
    sem_post(&berberler);//Müşterinin işi bittikten sonra berber boşa çıkar ve koltuk boşalır.
    printf("%d. Saç kesimi bitti\n",id);
}

int main(){
  printf("Berber birol devreye giriyor...\n");
  printf("Koltuk sayısını giriniz:\n");
  scanf("%d",&threadSayisi);

  printf("Sandalye sayısını giriniz:\n");
  scanf("%d",&sandalyeSayisi);
   
   threads[threadSayisi];


  
  pthread_t btid;
  pthread_t tid[threadSayisi];//müşteri sayısı kadar. 
  int i, numCustomers, numChairs;//sandalye ve müşteri sayısı
  int Numbers[threadSayisi];
  numCustomers = threadSayisi;
  numChairs = sandalyeSayisi;
  for (i = 0; i < numCustomers; i++)//müşteri numaraları ile thread ilişkilendiriyoruz.
  {
    Numbers[i] = i;
  }

  

  //semaforlarımızı oluşturduk.
  sem_init(&beklemeSalonu, 0, numChairs);
  sem_init(&berberler, 0, berberSayisi);
  sem_init(&musteriler, 0, 0);
  sem_init(&mutex, 0, 0);

  pthread_create(&btid, NULL, berber, NULL);

  for (i = 0; i < numCustomers; i++)//her müşteri için bir adet thread oluşturuyoruz.
  {
    pthread_create(&tid[i], NULL, musteri, (void *)&Numbers[i]);
  }

  for (i = 0; i < numCustomers; i++)//threadlerin işlermlerini bitirmesi bekleniyor.
  {
    pthread_join(tid[i], NULL);
  }

  bitis = 1;
  sem_post(&musteriler);
  pthread_join(btid, NULL);
    return 0;
}
