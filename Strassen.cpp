#include <stdio.h>
#include <stdlib.h>
#define NN 4
using namespace std;

void Strassen(int N,int A[][NN],int B[][NN],int R[][NN]);
void Strassen2(int N,int* A,int* B,int* R);
void Square(int A[][NN],int B[][NN],int R[][NN]);
void PrintMatrix(int M[][NN]);

int main()
{
    int A[NN][NN];
    int B[NN][NN];
    int R[NN][NN];
    int i,j;
    for(i=0; i<NN; i++)
    {
        for(j=0; j<NN; j++)
        {
            A[i][j]=rand()%10;
            B[i][j]=rand()%10;
        }
    }
    Strassen2(NN,(int*)A,(int*)B,(int*)R);
    PrintMatrix(R);
    printf("\n");
    Strassen(NN,A,B,R);
    PrintMatrix(R);
    printf("\n");
    Square(A,B,R);
    PrintMatrix(R);
    return 0;
}

void Strassen(int N,int A[][NN],int B[][NN],int R[][NN])
{
    if(N==1)
        R[0][0]=A[0][0]*B[0][0];
    else
    {
        int i,j;
        int A11[NN][NN],A12[NN][NN],A21[NN][NN],A22[NN][NN];
        int B11[NN][NN],B12[NN][NN],B21[NN][NN],B22[NN][NN];
        for(i=0; i<N/2; i++)
            for(j=0; j<N/2; j++)
            {
                A11[i][j]=A[i][j];
                A12[i][j]=A[i][j+N/2];
                A21[i][j]=A[i+N/2][j];
                A22[i][j]=A[i+N/2][j+N/2];
                B11[i][j]=B[i][j];
                B12[i][j]=B[i][j+N/2];
                B21[i][j]=B[i+N/2][j];
                B22[i][j]=B[i+N/2][j+N/2];
            }
        int S1[NN][NN],S2[NN][NN],S3[NN][NN],S4[NN][NN],
        S5[NN][NN],S6[NN][NN],S7[NN][NN],S8[NN][NN],
        S9[NN][NN],S10[NN][NN];
        int P1[NN][NN],P2[NN][NN],P3[NN][NN],P4[NN][NN],
        P5[NN][NN],P6[NN][NN],P7[NN][NN];
        for(i=0; i<N/2; i++)
            for(j=0; j<N/2; j++)
            {
                S1[i][j]=B12[i][j]-B22[i][j];
                S2[i][j]=A11[i][j]+A12[i][j];
                S3[i][j]=A21[i][j]+A22[i][j];
                S4[i][j]=B21[i][j]-B11[i][j];
                S5[i][j]=A11[i][j]+A22[i][j];
                S6[i][j]=B11[i][j]+B22[i][j];
                S7[i][j]=A12[i][j]-A22[i][j];
                S8[i][j]=B21[i][j]+B22[i][j];
                S9[i][j]=A11[i][j]-A21[i][j];
                S10[i][j]=B11[i][j]+B12[i][j];
            }
        Strassen(N/2,A11,S1,P1);
        Strassen(N/2,S2,B22,P2);
        Strassen(N/2,S3,B11,P3);
        Strassen(N/2,A22,S4,P4);
        Strassen(N/2,S5,S6,P5);
        Strassen(N/2,S7,S8,P6);
        Strassen(N/2,S9,S10,P7);
        for(i=0; i<N/2; i++)
            for(j=0; j<N/2; j++)
            {
                R[i][j]=P5[i][j]+P4[i][j]-P2[i][j]+P6[i][j];
                R[i][j+N/2]=P1[i][j]+P2[i][j];
                R[i+N/2][j]=P3[i][j]+P4[i][j];
                R[i+N/2][j+N/2]=P5[i][j]+P1[i][j]-P3[i][j]-P7[i][j];
            }
    }
}

void Square(int A[][NN],int B[][NN],int R[][NN])
{
    int i,j,k;
    for(i=0; i<NN; i++)
    {
        for(j=0; j<NN; j++)
        {
            R[i][j]=0;
            for(k=0; k<NN; k++)
            {
                R[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}

void PrintMatrix(int M[][NN])
{
    int i,j;
    for(i=0; i<NN; i++)
    {
        for(j=0; j<NN; j++)
            printf("%4d  ",M[i][j]);
        printf("\n");
    }
}

void Strassen2(int N,int* A,int* B,int* R)
{
    if(N==1)
        *R=(*A)*(*B);
    else
    {
        int i,j;
        int A11[N/2][N/2],A12[N/2][N/2],A21[N/2][N/2],A22[N/2][N/2];
        int B11[N/2][N/2],B12[N/2][N/2],B21[N/2][N/2],B22[N/2][N/2];
        for(i=0; i<N/2; i++)
            for(j=0; j<N/2; j++)
            {
                *(((int*)A11+i*N/2)+j)=*((A+i*N)+j);
                *(((int*)A12+i*N/2)+j)=*((A+i*N)+j+N/2);
                *(((int*)A21+i*N/2)+j)=*((A+(i+N/2)*N)+j);
                *(((int*)A22+i*N/2)+j)=*((A+(i+N/2)*N)+j+N/2);

                *(((int*)B11+i*N/2)+j)=*((B+i*N)+j);
                *(((int*)B12+i*N/2)+j)=*((B+i*N)+j+N/2);
                *(((int*)B21+i*N/2)+j)=*((B+(i+N/2)*N)+j);
                *(((int*)B22+i*N/2)+j)=*((B+(i+N/2)*N)+j+N/2);
            }
        int S1[N/2][N/2],S2[N/2][N/2],S3[N/2][N/2],S4[N/2][N/2],
        S5[N/2][N/2],S6[N/2][N/2],S7[N/2][N/2],S8[N/2][N/2],
        S9[N/2][N/2],S10[N/2][N/2];
        int P1[N/2][N/2],P2[N/2][N/2],P3[N/2][N/2],P4[N/2][N/2],
        P5[N/2][N/2],P6[N/2][N/2],P7[N/2][N/2];
        for(i=0; i<N/2; i++)
            for(j=0; j<N/2; j++)
            {
            	*(((int*)S1+i*N/2)+j)=*(((int*)B12+i*N/2)+j)-*(((int*)B22+i*N/2)+j);
            	*(((int*)S2+i*N/2)+j)=*(((int*)A11+i*N/2)+j)+*(((int*)A12+i*N/2)+j);
            	*(((int*)S3+i*N/2)+j)=*(((int*)A21+i*N/2)+j)+*(((int*)A22+i*N/2)+j);
            	*(((int*)S4+i*N/2)+j)=*(((int*)B21+i*N/2)+j)-*(((int*)B11+i*N/2)+j);
            	*(((int*)S5+i*N/2)+j)=*(((int*)A11+i*N/2)+j)+*(((int*)A22+i*N/2)+j);
            	*(((int*)S6+i*N/2)+j)=*(((int*)B11+i*N/2)+j)+*(((int*)B22+i*N/2)+j);
            	*(((int*)S7+i*N/2)+j)=*(((int*)A12+i*N/2)+j)-*(((int*)A22+i*N/2)+j);
            	*(((int*)S8+i*N/2)+j)=*(((int*)B21+i*N/2)+j)+*(((int*)B22+i*N/2)+j);
            	*(((int*)S9+i*N/2)+j)=*(((int*)A11+i*N/2)+j)-*(((int*)A21+i*N/2)+j);
            	*(((int*)S10+i*N/2)+j)=*(((int*)B11+i*N/2)+j)+*(((int*)B12+i*N/2)+j);
            }
        Strassen2(N/2,(int*)A11,(int*)S1,(int*)P1);
        Strassen2(N/2,(int*)S2,(int*)B22,(int*)P2);
        Strassen2(N/2,(int*)S3,(int*)B11,(int*)P3);
        Strassen2(N/2,(int*)A22,(int*)S4,(int*)P4);
        Strassen2(N/2,(int*)S5,(int*)S6,(int*)P5);
        Strassen2(N/2,(int*)S7,(int*)S8,(int*)P6);
        Strassen2(N/2,(int*)S9,(int*)S10,(int*)P7);
        for(i=0; i<N/2; i++)
            for(j=0; j<N/2; j++)
            {
            	*((R+i*N)+j)=*(((int*)P5+i*N/2)+j)+*(((int*)P4+i*N/2)+j)-*(((int*)P2+i*N/2)+j)+*(((int*)P6+i*N/2)+j);
            	*((R+i*N)+j+N/2)=*(((int*)P1+i*N/2)+j)+*(((int*)P2+i*N/2)+j);
            	*((R+(i+N/2)*N)+j)=*(((int*)P3+i*N/2)+j)+*(((int*)P4+i*N/2)+j);
            	*((R+(i+N/2)*N)+j+N/2)=*(((int*)P5+i*N/2)+j)+*(((int*)P1+i*N/2)+j)-*(((int*)P3+i*N/2)+j)-*(((int*)P7+i*N/2)+j);
            }
    }
}




