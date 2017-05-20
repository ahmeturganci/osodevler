#include<stdio.h>
#include<pthread.h>

#define boyut 1000
#define threadBoyut 3
void *Sirala(int arg[]);//Sıralama thread fonksiyonumuz.
void *Birlestir(int arg); //Birleştirme thread fonksiyonumuz.
int dizi[boyut];//sıralanması istenen dizi
pthread_t threads[3];//threadlerimiz.
int main(){
    int i = 0,j = 0;
    /*
    öncelikle 0-1000 arasında sayıları bir dizye alıp ardından bu sayıları kendi içerisinde sıralıyoruz.
    */
    for(i=0;i<boyut;i++){ // 0 - 1000 arasındaki değerler dizisi
        dizi[i]=i;
    }
    // 0 - 1000 arasındaki değerler karıştırma
    for(i = 0 ; i < boyut ; i++) {
        int r = (rand()%(boyut-i))+i;
        int temp = dizi[i];
        dizi[i]=dizi[r];
        dizi[r]=temp;
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
    

}
void dosyayaYaz(int dizi[]){
    FILE *fp=fopen("sayilar.txt","w");
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
    bubbleSort(dizi,0,boyut);
    dosyayaYaz(dizi);


}
