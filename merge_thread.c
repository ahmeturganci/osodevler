#include<stdio.h>
#include<pthread.h>

#define boyut 1000
#define threadBoyut 3
void *Sirala(int arg[]);//Sıralama thread fonksiyonumuz.
void *Birlestir(int arg); //Birleştirme thread fonksiyonumuz.
void diziBirlestir(int dizi[],int sorted[]);
void essizRastgeleSayiUret();
int dizi[boyut];//sıralanması istenen dizi
int yeniDizi[boyut];//birleştirilmesi istenen yeni dizi
pthread_t threads[3];//threadlerimiz.
int main(){
    int i = 0,j = 0;
    /*
    öncelikle 0-1000 arasında sayıları bir dizye alıp ardından bu sayıları kendi içerisinde sıralıyoruz.
    */
    /*for(i=0;i<boyut;i++){ // 0 - 1000 arasındaki değerler dizisi
        dizi[i]=i;
    }
    // 0 - 1000 arasındaki değerler karıştırma
    for(i = 0 ; i < boyut ; i++) {
        int r = (rand()%(boyut-i))+i;
        int temp = dizi[i];
        dizi[i]=dizi[r];
        dizi[r]=temp;
    }*/
    essizRastgeleSayiUret(dizi);
    for (j = 0; j < boyut; ++j)
    {
        printf("%d. eleman %d\n", j,dizi[j]);
    }
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
void essizRastgeleSayiUret(int dizi[]){
	int j,r,a,sayac=0;
    srand ( time(NULL) );
    while(sayac<boyut){
        a=rand();
        r=a%boyut;
        if(dizi[r]==0){
            dizi[r]=a;
            sayac++;
        }
    }
}
void dosyayaYaz(int dizi[]){
    FILE *fp=fopen("sayilar.txt","a");
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

void bubbleSort(int dizi[],int baslangicDeger, int bitisDegeri){
    int temp;
    int i, j;
    

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
void *Sirala(int arg[]){
    bubbleSort(dizi,arg[0],arg[1]);
}


void *Birlestir(int arg){
    //bubbleSort(dizi,0,boyut);
    diziBirlestir(dizi,yeniDizi);
    dosyayaYaz(yeniDizi);
    //dosyayaYaz(dizi);

}
void diziBirlestir(int dizi[],int sorted[]){
    int x,i, j, k,m,n;
    int a[500],b[500];
    for (x=0; x<1000; x++){
        if(x>=500){
            b[x-500]=dizi[x];
        }
        else{
            a[x]=dizi[x];
        }
    }
  m = n = 500;
  j = k = 0;
 
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
