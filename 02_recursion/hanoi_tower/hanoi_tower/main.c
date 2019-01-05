#include <stdio.h>

void hanoi_tower(int n, char from, char temp, char to)
{
    if (n==1)
        printf("1을 %c에서 %c로 옮긴다.\n",from,to);
    else
    {
        hanoi_tower(n-1,from,to,temp);
        printf("%d을 %c에서 %c로 옮긴다.\n",n,from,to);
        hanoi_tower(n-1,temp,from,to);
    }
}

int main(void)
{
    hanoi_tower(3,'A','B','C');
}
