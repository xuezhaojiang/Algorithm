#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;
typedef int Status;
#define N 60
Status QuickSort(int A[]);
Status RandomQuickSort(int A[]);
int Partition(int A[],int low,int high);
int RandomPartition(int A[],int low,int high);
void QSort(int A[],int low,int high);
void RandomQSort(int A[],int low,int high);
int main()
{
    int *A=(int *)malloc(N*sizeof(int));
    for(int i=1; i<=N-1; i++)
    {
        A[i]=rand();
    }
    /*
    for(int i=1; i<=N-1; i++)
    {
        cout<<(int)B[i]<<"  ";
        if(i%10==0)
        cout<<endl;
    }
    cout<<endl;
    */
    FILETIME beg,end;
    long dur;
    cout << "排序"<<N<<"个无序数字"<<endl;
    cout << "随机化快速排序";
    GetSystemTimeAsFileTime(&beg);
    RandomQuickSort(A);
    GetSystemTimeAsFileTime(&end);
    dur = (end.dwLowDateTime-beg.dwLowDateTime)/10000;
    cout <<dur<<"ms"<<endl;
    for(int i=1; i<=N-1; i++)
    {
        A[i]=rand();
    }
    cout << "快速排序";
    GetSystemTimeAsFileTime(&beg);
    QuickSort(A);
    GetSystemTimeAsFileTime(&end);
    dur = (end.dwLowDateTime-beg.dwLowDateTime)/10000;
    cout <<dur<<"ms"<<endl;

    cout << "排序"<<N<<"个有序数字"<<endl;
    cout << "随机化快速排序";
    GetSystemTimeAsFileTime(&beg);
    RandomQuickSort(A);
    GetSystemTimeAsFileTime(&end);
    dur = (end.dwLowDateTime-beg.dwLowDateTime)/10000;
    cout <<dur<<"ms"<<endl;

    cout << "快速排序";
    GetSystemTimeAsFileTime(&beg);
    QuickSort(A);
    GetSystemTimeAsFileTime(&end);
    dur = (end.dwLowDateTime-beg.dwLowDateTime)/10000;
    cout <<dur<<"ms"<<endl;

    char *a;
    cin>>a;
    return 0;
}
int Partition(int A[],int low,int high)
{
    A[0]=A[low];
    int key=A[low];
    while(low<high)
    {
        while(low<high&&A[high]>=key)
            --high;
        A[low]=A[high];
        while(low<high&&A[low]<=key)
            ++low;
        A[high]=A[low];
    }
    A[low]=A[0];
    return low;
}
void QSort(int A[],int low,int high)
{
    if(low<high)
    {
        int pivotloc=Partition(A,low,high);
        QSort(A,low,pivotloc-1);
        QSort(A,pivotloc+1,high);
    }
}
Status QuickSort(int A[])
{
    QSort(A,1,N-1);
    return 0;
}

int RandomPartition(int A[],int low,int high)
{
    int r=rand()%(high-low+1)+low;
    A[0]=A[low];
    int key=A[r];
    while(low<high)
    {
        while(low<high&&A[high]>=key)
            --high;
        A[low]=A[high];
        while(low<high&&A[low]<=key)
            ++low;
        A[high]=A[low];
    }
    A[low]=A[0];
    return low;
}
void RandomQSort(int A[],int low,int high)
{
    if(low<high)
    {
        int pivotloc=RandomPartition(A,low,high);
        RandomQSort(A,low,pivotloc);
        RandomQSort(A,pivotloc+1,high);
    }
}
Status RandomQuickSort(int A[])
{
    RandomQSort(A,1,N-1);
    return 0;
}
