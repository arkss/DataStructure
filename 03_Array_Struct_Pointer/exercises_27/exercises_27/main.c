#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20
struct test{
    int num;
    char arr[MAX_SIZE];
};

int main(void)
{
    struct test *p;
    p = (struct test *)malloc(sizeof(struct test));
    if (p==NULL){
        printf("공간을 할당할 수 없습니다.\n");
        exit(1);
    }
    
    p->num = 10;
    strcpy(p->arr,"just testing");
    
    printf("num : %d\narr[MAX_SIZE] : %s\n",p->num,p->arr);
    free(p);
    
    
}
