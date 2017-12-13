#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 8
#define L 7

//W[7][8]
float W[L][N]=
{
    {0,0,0,0,0,0,0,0},
    {0,0,0,0.5,-1,0,0,0},
    {0,0,0,1.5,-2,0,0,0},
    {0,0,0,0,0,1,-1,0},
    {0,0,0,0,0,3,-4,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,-3}

};
float alpha=0.1;
float d=1;
float X[3]= {0,2,-1};
float in[L];
float delta[L];
float a[L+1];

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}
void alea(float W[L][N])
{
    int i,j;
    for(i=1; i<L; i++)
    {
        for(j=1; j<N; j++)
        {
            W[i][j]=rand_a_b(-1,1);

        }
    }
}




float g(float x)
{
    return 1/(1+exp(-x));
}


void app_retro_propagation(float X[3],float W[L][N],float delta[L+1])
{

    int i,j;


    for(i=1; i<3; i++)
    {
        a[i]=X[i];
       // printf("a[i]=%f\n",a[i]);
    }


    for(j=3; j<=L; j++)
    {
        for(i=1; i<L; i++)
        {
            in[j]+=W[i][j]*a[i];

        }

        a[j]=g(in[j]);
    }
    for(j=1; j<=L; j++)
    {
        printf("a[%d]=%f\n",j,a[j]);
    }

    delta[L]=1-a[L];

    float sum=0;
    printf("\n\n");
    printf("delta[7]=%f\n",delta[L]);
    for(i=L-1; i>=3; i--)
    {
        for(j=1; j<=L; j++)
        {
            sum+=W[i][j]*delta[j];
        }
        delta[i]=g(in[i])*(1-g(in[i]))*sum;
        printf("delta[%d]=%f\n",i,delta[i]);
        sum=0;
    }

    printf("\n\n");

//modification des poids
    for(i=1; i<L; i++)
    {
        for(j=1; j<=L; j++)
        {
            W[i][j]=W[i][j]+alpha*a[i]*delta[j];

        }

    }
//affichage des poids
    for(i=1; i<L; i++)
    {
        for(j=1; j<=L; j++)
        {
            printf("W[%d][%d]=%f\n",i,j,W[i][j]);

        }

    }

}
int main()
{
    // Valeurs aléatoires entre -1 et 1
    //alea(W);


    // Valeurs du cours
    while(1)
    {
        app_retro_propagation(X,W,delta);
        if(delta[L]<0.1) break;
    }


    return 0;
}
