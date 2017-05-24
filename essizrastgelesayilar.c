#include <stdio.h>
#define boyut 1000
int dizi2[boyut]={0};

int main(){
    int j,r,a,sayac=0;
    srand ( time(NULL) );
    while(sayac<boyut){
        a=rand();
        r=a%boyut;
        if(dizi2[r]==0){
            dizi2[r]=a;
            sayac++;
        }
    }
    for (j = 0; j < boyut; ++j)
    {
        printf("%d. eleman %d\n", j,dizi2[j]);
    }
    return 0;
}