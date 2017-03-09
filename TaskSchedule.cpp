#include <iostream>
using namespace std;
#define N 7
typedef struct
{
    int id;
    int deadline;
    int weight;
} Task;

int Partition(Task task[],int low,int high);
void QSort(Task task[],int low,int high);
int TaskSchedule(Task task[],Task schedule[]);
int main()
{
    Task task[N+1]= {{0,0,0},{1,4,70},{2,2,60},{3,4,50},{4,3,40},{5,1,30},{6,4,20},{7,6,10}};
    for(int i=1;i<=N;i++)
    {
        cout<<"task id:"<<task[i].id<<" deadline:"<<task[i].deadline<<" weight:"<<task[i].weight<<endl;
    }
    QSort(task,1,N);
    Task schedule[N+1]= {{0,0,0}};
    int punish=TaskSchedule(task,schedule);
    cout<<"task schedule: ";
    for(int i=1; i<=N; i++)
        cout<<schedule[i].id<<" ";
    cout<<endl;
    cout<<"punish: "<<punish<<endl;
    cout<<endl;

    for(int i=1; i<=N; i++)
    {
        task[i].weight=70-task[i].weight;
        schedule[i]= {0};
        cout<<"task id:"<<task[i].id<<" deadline:"<<task[i].deadline<<" weight:"<<task[i].weight<<endl;
    }
    QSort(task,1,N);
    punish=TaskSchedule(task,schedule);
    cout<<"task schedule: ";
    for(int i=1; i<=N; i++)
        cout<<schedule[i].id<<" ";
    cout<<endl;
    cout<<"punish: "<<punish<<endl;

    char *a;
    cin>>a;
    return 0;
}
int Partition(Task task[],int low,int high)
{
    task[0]=task[low];
    int weight=task[low].weight;
    while(low<high)
    {
        while(low<high&&task[high].weight<=weight)
            --high;
        task[low]=task[high];
        while(low<high&&task[low].weight>=weight)
            ++low;
        task[high]=task[low];
    }
    task[low]=task[0];
    return low;
}
void QSort(Task task[],int low,int high)
{
    if(low<high)
    {
        int pivotloc=Partition(task,low,high);
        QSort(task,low,pivotloc-1);
        QSort(task,pivotloc+1,high);
    }
}

int TaskSchedule(Task task[],Task schedule[])
{
    int punish=0;
    for(int i=1,ii,j; i<=N; i++)
    {
        for(ii=task[i].deadline; ii>0; ii--)
        {
            if(schedule[ii].id == 0)
            {
                schedule[ii]=task[i];//属于独立集的，放在deadline的位置或者deadline之前
                break;
            }
        }
        if(ii==0)//不属于独立集的尽量往后放
        {
            punish+=task[i].weight;
            for(j=N; j>0; j--)
            {
                if(schedule[j].id==0)
                {
                    schedule[j]=task[i];
                    break;
                }
            }
        }
    }
    return punish;
}
