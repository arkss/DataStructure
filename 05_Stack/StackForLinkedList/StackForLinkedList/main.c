#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackNode{
    element item;
    struct StackNode *link;
} StackNode;

typedef struct {
    StackNode *top;
} LinkedStackType;

//초기화 함수
void init(LinkedStackType *s)
{
    s->top = NULL;
}

//공백 상태 확인 함수
int is_empty(LinkedStackType *s)
{
    return (s->top == NULL);
}

// push함수
void push(LinkedStackType *s, element item)
{
    StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp ==NULL){
        fprintf(stderr,"메모리 할당에러\n");
        return;
    }
    else{
        temp->item = item;
        temp->link = s->top;
        s->top = temp;
    }
}
// pop함수
element pop(LinkedStackType *s)
{
    if (is_empty(s)){
        fprintf(stderr,"스택이 비어있음\n");
        exit(1);
    }
    else{
        StackNode *temp = s->top;
        element item = temp->item;
        s->top = s->top->link;
        free(temp);
        return item;
    }
}
// peek 함수
element peek(LinkedStackType *s)
{
    if (is_empty(s)){
        fprintf(stderr,"스택이 비어있음\n");
        exit(1);
    }
    else{
        return s->top->item;
    }
}

int main(void)
{
    LinkedStackType s;
    init(&s);
    push(&s,1);
    push(&s,2);
    push(&s,3);
    printf("%d\n",pop(&s));
    printf("%d\n",pop(&s));
    printf("%d\n",pop(&s));
    printf("%d\n",is_empty(&s));
}
