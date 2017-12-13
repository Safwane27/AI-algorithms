#include <stdio.h>
#include <stdlib.h>
#define N 2
// Déclaration des variables
float E[N];
float W[N];
float D[20]={0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1};
float X[20];
int nb=0;
int nbtest=0;
float teta=0.2;


//Initialisation
void initialiserX(float X[20]){
int i;
for(i=0;i<20;i++){
    X[i]=-1;
}
}
void initialiserE(float e1,float e2){
E[0]=e1;
E[1]=e2;
}
void initialiserW(float w1,float w2){
W[0]=w1;
W[1]=w2;

}

void sortie(float W[N],float E[N],float teta){
    int i;float a=0;
    for( i=0;i<N;i++){
    a=a+W[i]*E[i];
}
    a=a-teta;
    if(a>0){
    X[nb]=1;
    nb++;
    }

    else{
    X[nb]=0;
    nb++;
    }

}

void afficher(float t[20])
{
    int i=0;
    for(i=0;i<20;i++){
        printf("%.2f \n",t[i]);
        if((i+1)%4==0) printf("\n");
    }
}
//modification des poids
void modification (float W[N],float mu){
int i=0;
for(i=0;i<N;i++){
    W[i]=W[i]+mu*((D[nb-1]-X[nb-1])*E[i]);
}

}
//test de modification
void test(float D[20],float X[20]){

if(D[nbtest]!=X[nbtest]){ modification(W,0.1);}
printf("w1:%.2f \t w2:%.2f \n",W[0],W[1]);
nbtest++;
}
//condition d'arret
int arret(float X[20]){
int i,s=0;
for(i=0;i<20;i=i+4){
    if(X[i]==0&&X[i+1]==0&&X[i+2]==0&&X[i+3]==1){s++;}
}
if(s){
    return 1;
}else{
    return 0;
}
}

int main()
{   printf("Poids final :\n");
    initialiserX(X);
    initialiserW(0.3,-0.1);
    while(!arret(X)){
    initialiserE(0,0);
    sortie(W,E,teta);
    test(D,X);
    initialiserE(0,1);
    sortie(W,E,teta);
    test(D,X);
    initialiserE(1,0);
    sortie(W,E,teta);
    test(D,X);
    initialiserE(1,1);
    sortie(W,E,teta);
    test(D,X);
}
   //afficher(D);
    printf("\nX :\n\n");afficher(X);




    return 0;
}
