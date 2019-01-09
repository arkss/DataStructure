#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

// 이중 연결 리스트 초기화
void init(DlistNode *phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

// 이중 연결 리스트 출력
void display(DlistNode *phead)
{
    DlistNode *p;
    for (p=phead->rlink;p!=phead;p=p->rlink){
        printf("<--|%x|%d|%x|-->\n",p->llink,p->data,p->rlink);
    }
    printf("\n");
}

// 데이터 삽입 함수
void dinsert_node(DlistNode *before, DlistNode *new_node)
{
    // 삽입함수의 link 들 부터 바꿔줘야 한다. 순서 바뀌면 안된다.
    new_node->llink = before;
    new_node->rlink = before->rlink;
    before->rlink->llink = new_node;
    before->rlink = new_node;
    
}
// 데이터 삭제 함수
void dremove_node(DlistNode *phead_node, DlistNode *removed)
{
    if (removed == phead_node) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

int main(void)
{
    DlistNode head_node;
    DlistNode *p[10];
    int i;
    init(&head_node);
    for(i=0;i<5;i++){
        p[i] = (DlistNode *)malloc(sizeof(DlistNode));
        p[i]->data = i;
        dinsert_node(&head_node,p[i]);
    }
    dremove_node(&head_node,p[4]);
    display(&head_node);
//    <--|efbff4c0|3|504780|-->
//    <--|5115d0|2|506570|-->
//    <--|504780|1|508300|-->
//    <--|506570|0|efbff4c0|-->
// 다음과 같이 가장 앞의 node와 가장 뒤의 node가 가르키는 주소는 head_node의 주소로서 동일해야한다.
}
