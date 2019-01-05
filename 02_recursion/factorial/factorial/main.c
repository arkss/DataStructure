#include <stdio.h>

// recursive 한 factorial
int factorial(int n)
{
    if (n==1)
        return 1;
    return n * factorial(n-1);
}

// iterative한 factorial
int factorial_iter(int n)
{
    int answer = 1;
    while (n>0)
    {
        answer *= n;
        n--;
    }
    return answer;
}

int main(void)
{
    int answer;
    answer = factorial(5);
    printf("%d\n",answer);
    answer = factorial_iter(5);
    printf("%d\n",answer);
    
}
