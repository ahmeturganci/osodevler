#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define boyut 1000
#define threadBoyut 3
#define rastgeleSayiAraligi 100000

void *Sirala(int arg[]);//Sıralama thread fonksiyonumuz.
void *Birlestir(int arg); //Birleştirme thread fonksiyonumuz.

void diziBirlestir(int dizi[],int sorted[]);//merge için kullanılan fonksiyon.
void essizRastgeleSayiUret();// birbirinden farklı eşşiz sayılar üretmek için.

int dizi[boyut];//sıralanması istenen dizi
int yeniDizi[boyut];//birleştirilmesi istenen yeni dizi
pthread_t threads[3];//threadlerimiz.

int main(){
    int i = 0,j = 0;
    // Dizi de benzersiz sayılar üretmemizi sağlayan fonksiyon
    essizRastgeleSayiUret(dizi);
    //başlama ve bitiş aralıkları için.
    int s[2];
    s[0]=0;
    s[1]=boyut/2;
    int f[2];
    f[0]=boyut/2;
    f[1]=boyut;
    //istenildiği üzere 3 thread oluşturuldu.
    pthread_create(&(threads[0]),NULL,Sirala,s);
    pthread_create(&(threads[1]),NULL,Sirala,f);
    pthread_create(&(threads[2]),NULL,Birlestir,dizi);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);
	
    pthread_exit(NULL);
}

//1000 elemanlı dizimiz için rastgele sayılar üretme fonksiyonumuz.
void essizRastgeleSayiUret(int dizi[]){
	int j,r,a,sayac=0;
    srand ( time(NULL) );//bilgisayarın saatini çekirdek değeri olarak alıyor.
    while(sayac<boyut){
        a=rand()%rastgeleSayiAraligi;
        r=a%boyut;
        if(dizi[r]==0){
            dizi[r]=a;
            sayac++;
        }
    }
}
// işlemlerin sonucunu istenildiği gibi 
void dosyayaYaz(int dizi[]){
    FILE *fp=fopen("sonuc.txt","w");
    int i;
    if(fp!=NULL){
        for ( i = 0;i<boyut;i++){
            fprintf(fp,"%d\n",dizi[i]);
        }
    }
    else{
        printf("Yazmada Bir Hata Oluştu...");
    }
    fclose(fp);
}
//verilen dizide ikiye bölünlenmiş değerleri kendi içerisine sıralamak
void bubbleSort(int dizi[],int baslangicDeger, int bitisDegeri){
    int temp, i, j;
    for (i=1; i<bitisDegeri-1; i++){
        for (j=baslangicDeger; j<bitisDegeri-i; j++){
            if(dizi[j] > dizi[j+1]){
            temp = dizi [j];
            dizi [j] = dizi [j+1];
            dizi [j+1] = temp;
            }
        }
    }
}
//içerisine gönderdiğimiz dizinin  belirlenen aralılardaki halini 
void *Sirala(int arg[]){
    bubbleSort(dizi,arg[0],arg[1]);
}
// bubble sıralama ile 2 ayrı parça halinde sıralanmış olan dizi yi mergelediğimiz kısım.
void *Birlestir(int arg){
    diziBirlestir(dizi,yeniDizi);
    dosyayaYaz(yeniDizi);
    //dosyayaYaz(dizi);
}
// merge işlemi için kullandığımız fonksiyon.
void diziBirlestir(int dizi[],int sorted[]){
    /*birleştirme işlemi sırasında istenilen merge işlemi için öncelikle
    dizimizi 2 ye bölelim. */
    int x, i, j, k, m, n;
    int a[boyut/2],b[boyut/2];
    for (x=0; x<boyut; x++){
        if(x>=boyut/2){
            b[x-boyut/2]=dizi[x];
        }
        else{
            a[x]=dizi[x];
        }
    }

    j = k = 0;//başlangıç değerleri
    m = n = boyut/2;// bitiş değerleri
    
    // ilk dizinin elamanları ike 2. dizinin elemanları arasında bir sıralama işlemi 
    //gerçekleştiriyoruz.
  for (i = 0; i < m + n;) {
    if (j < m && k < n) {
      if (a[j] < b[k]) {
        sorted[i] = a[j];
        j++;
      }
      else {
        sorted[i] = b[k];
        k++;
      }
      i++;
    }
    else if (j == m) {
      for (; i < m + n;) {
        sorted[i] = b[k];
        k++;
        i++;
      }
    }
    else {
      for (; i < m + n;) {
        sorted[i] = a[j];
        j++;
        i++;
      }
    }
  }
}
