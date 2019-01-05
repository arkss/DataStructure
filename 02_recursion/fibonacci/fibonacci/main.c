#include <stdio.h>
// 순환적인 fac
int fibo(int n)
{
    if (n==0)
        return 0;
    else if (n==1)
        return 1;
    return fibo(n-1)+fibo(n-2);
}
// 반복적인 fac
int fibo_iter(int n)
{
    if (n<2)
        return n;
    int i,temp, current = 1, last = 0;
    for (i=2;i<=n;i++)
    {
        temp = current;
        current += last;
        last = temp;
    }
    return current;
}

int main(void)
{
    int answer;
    answer = fibo(5);
    printf("%d\n",answer);
    answer = fibo_iter(5);
    printf("%d\n",answer);
    

}
