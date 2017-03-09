#include <iostream>
using namespace std;
#define N 3
#define Valume 50
typedef struct
{
    int weight;
    int value;
    int choose;
} Goods;
typedef struct
{
    int bagValume;
    int currentWeights;
    int values;
} Bag;

int max(int a,int b);
int knapsack(Goods goods[],Bag &bag);

int main()
{
    Goods goods[N+1] = {{0,0,0},{10,60,0},{20,100,0},{30,120,0}};
    for(int i=1;i<=N;i++)
    cout<<"goods id:"<<i<<" weight:"<<goods[i].weight<<" value:"<<goods[i].value<<endl;
    Bag bag = {Valume,0,0};
    bag.values = knapsack(goods,bag);
    cout<<"bag valume: "<<bag.bagValume<<endl;
    cout<<"choose goods: ";
    for(int i=0; i<=N; i++)
    {
        if(goods[i].choose)
            cout<<i<<" ";
    }
    cout<<endl;
    cout<<"current bag weight: "<<bag.currentWeights<<endl;
    cout<<"bag value: "<<bag.values<<endl;

    char *a;
    cin>>a;
    return 0;
}

int max(int a,int b)
{
    if(a>=b)
        return a;
    else
        return b;
}

int knapsack(Goods goods[],Bag &bag)
{
    //在前i个物品中能够装入容量为就j的背包中的物品的最大价值
    int worths[N+1][Valume+1];
    int i,j;
    for(i=0; i<=N; i++)
        worths[i][0]=0;//容量为0
    for(j=0; j<=Valume; j++)
        worths[0][j]=0;//没有物品
    for(i=1; i<=N; i++)
    {
        for(j=1; j<=Valume; j++)
        {
            if(j<goods[i].weight)
            {
                worths[i][j]=worths[i-1][j];
            }
            else
            {
                worths[i][j] = max(worths[i-1][j],worths[i-1][j-goods[i].weight]+goods[i].value);
            }
        }
    }


    j=Valume;
    for(i=N; i>=1; i--)
    {
        if(worths[i][j]>worths[i-1][j])
        {
            goods[i].choose=1;
            j=j-goods[i].weight;
            bag.currentWeights += goods[i].weight;
        }
    }
    return worths[N][Valume];
}
