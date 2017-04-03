#include<stdio.h>
union ele
{
    struct
    {
        int *p;
        int x;
    }e1;
    struct
    {
        int y;
        union ele *next;
    }e2;
};
void proc(union ele *up);
int main()
{
    union ele a,b;
    int m=8;
    a.e2.y=5;
    a.e2.next=&b;
    b.e1.p=&m;
    b.e1.x=0;
    proc(&a);
    printf("%d\n",b.e1.x);
}
void proc(union ele *up)
{
    up->e2.next->e1.x=*(up->e2.next->e1.p)-up->e2.y;
}
