#include <iostream>
using namespace std;
#define N 3
#define Valume 50
typedef struct
{
    int ID;
    int weight;
    int value;
    float unitvalue;
    int choosedWeight;
} Goods;
typedef struct
{
    int bagValume;
    int remainValume;
    float values;
} Bag;

int Partition(Goods goods[],int low,int high);
void QSort(Goods goods[],int low,int high);
void fractionalKnapsack(Goods goods[],Bag &bag);

int main()
{
    Goods goods[N] = {{1,10,60,0,0},{2,20,100,0,0},{3,30,120,0,0}};
    for(int i=0; i<N; i++)
    {
        goods[i].unitvalue=(float)goods[i].value/goods[i].weight;
        cout<<"goods id:"<<goods[i].ID<<" weight:"<<goods[i].weight<<" value:"<<goods[i].value<<endl;
    }
    Bag bag = {Valume,Valume,0};
    fractionalKnapsack(goods,bag);
    cout<<"fractional knapsack:"<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"goods id: "<<goods[i].ID;
        cout<<" choosed weight: "<<goods[i].choosedWeight<<endl;
    }
    cout<<"bag values: "<<bag.values<<endl;

    char *a;
    cin>>a;
    return 0;
}

int Partition(Goods goods[],int low,int high)
{
    Goods temp=goods[low];

    while(low<high)
    {
        while(low<high&&goods[high].unitvalue<=temp.unitvalue)
            --high;
        goods[low]=goods[high];
        while(low<high&&goods[low].unitvalue>=temp.unitvalue)
            ++low;
        goods[high]=goods[low];
    }
    goods[low]=temp;
    return low;
}
void QSort(Goods goods[],int low,int high)
{
    if(low<high)
    {
        int pivotloc=Partition(goods,low,high);
        QSort(goods,low,pivotloc-1);
        QSort(goods,pivotloc+1,high);
    }
}
void fractionalKnapsack(Goods goods[],Bag &bag)
{
    QSort(goods,0,N-1);
    for(int i=0;i<N;i++)
    {
        if(bag.remainValume>=goods[i].weight)
        {
            goods[i].choosedWeight=goods[i].weight;
            bag.values+=goods[i].value;
            bag.remainValume-=goods[i].weight;
        }
        else
        {
            goods[i].choosedWeight=bag.remainValume;
            bag.values+=goods[i].choosedWeight*goods[i].unitvalue;
            bag.remainValume=0;
            break;
        }
    }
}
