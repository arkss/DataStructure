#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode{
    element data;
    struct ListNode *link;
} ListNode;

// 에러함수
void error(char* message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}

// 노드를 동적으로 생성하는 프로그램
ListNode *create_node(element data, ListNode *link)
{
    ListNode *new_node;
    new_node = (ListNode *)malloc(sizeof(ListNode));
    if (new_node == NULL) error("메모리 할당 에러\n");
    new_node->data = data;
    new_node->link = link;
    return new_node;
}

// 리스트의 항목 출력
void display(ListNode *head)
{
    ListNode *p;
    
    if (head == NULL) return;
    // 책이랑 조금 다르다. 내가 맞는거 같긴한데 head가 가장 마지막 node를 가르키고 있으니까 출력이 원하는 대로 되지않아서 p=head->link를 통해서 맨 처음으로 이동시켜 주었다.
    p = head->link;
    do {
        printf("%d->",p->data);
        p = p->link;
    } while (p != head->link);
}

//phead : 리스트의 헤드 포인터의 포인터
// node : 삽입될 노드

// 원형 연결 리스트 처음에 삽입하는 함수

// insert 와 delete 에서는 phead를 이중포인터로 받아온다.
// 그 이유는 이 두 경우에는 head 를 바꿀 필요가 있기 때문에
void insert_first(ListNode **phead, ListNode *node)
{
    // list가 비어있을 경우
    if (*phead == NULL) {
        *phead = node;
        node->link = node;
    }
    else{
        node->link = (*phead)->link;
        (*phead)->link = node;
    }
}

// 원형 연결 리스트 삽입 함수
void insert_last(ListNode **phead, ListNode *node)
{
    // list가 비어있는 경우
    if (*phead == NULL){
        *phead = node;
        node->link = node;
    }
    else{
        node->link = (*phead)->link;
        (*phead)->link = node;
        *phead = node;
    }
}

int main(void)
{
    ListNode *list1 =NULL;
    insert_first(&list1,create_node(10,NULL));
    insert_first(&list1,create_node(20,NULL));
    insert_last(&list1,create_node(30,NULL));
    display(list1);
}

