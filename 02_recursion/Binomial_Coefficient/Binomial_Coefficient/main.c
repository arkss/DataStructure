#include <stdio.h>

int bin(int n,int k)
{
    if (k==0 || k== n)
        return 1;
    return bin(n-1,k-1)+bin(n-1,k);
}

int bin_iter(int n,int k)
{
    int i;
    int numerator = 1; // 분자
    int denominator = 1; // 분모
    for (i=1;i<=k;i++)
    {
        denominator *= i;
        numerator *= n+1-i;
    }
    return numerator / denominator;
}

int main(void)
{
    int answer;
    answer = bin(5,3);
    printf("%d\n",answer);
    answer = bin_iter(3, 0);
    printf("%d\n",answer);
    
}
