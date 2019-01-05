#include <stdio.h>
// 반복적인 거듭제곱
double slow_power(double x, int n)
{
    int i;
    double answer = 1;
    for(i=0;i<n;i++)
    {
        answer *= x;
    }
    return answer;
}
// 순환을 사용한 거듭제곱
double power(double x, int n)
{
    if (n==0)
        return 1;
    if ( n%2==0 )
        return power(x*x,n/2);
    else
        return x * power(x*x,(n-1)/2);
}

int main(void)
{
    double answer;
    answer = slow_power(2,3);
    printf("%.1lf\n",answer);
    answer = power(2,3);
    printf("%.1lf",answer);
}
