#include <stdio.h>
#include <stdlib.h>


typedef int element;
typedef struct ListNode{
    element data;
    struct ListNode *link;
} ListNode;

// 에러 출력
void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}

// phead : 리스트의 헤드 포인터의 포인터
// p : 선행노드
// new_node : 새로운 노드

// 단순 연결 리스트의 삽입 함수
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
    // 헤드포인터가 NULL 일 경우는 비어있는 리스트이다.
    if (*phead == NULL){
        new_node->link = NULL;
        *phead = new_node;
    }
    // 선행노드가 NULL이면 첫번째 노드로 삽입해야한다.
    else if (p==NULL){
        new_node->link = *phead;
        *phead = new_node;
    }
    // 선행노드 다음에 삽입하는 일반적인 경우
    else{
        new_node->link = p->link;
        p->link = new_node;
    }
}
// 단순 연결 리스트의 삭제 함수
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
    // 선행노드가 NULL이면 제일 앞에 노드를 제거한다.
    if (p==NULL)
        *phead = (*phead)->link;
    // 일반적인 경우
    else
        p->link = removed->link;
    // 삭제된 노드를 더 이상 사용할 필요가 없으므로 반환해준다.
    free(removed);
}

// 반복적인 리스트 방문
void display(ListNode *head)
{
    ListNode *p = head;
    while (p !=NULL){
        printf("%d->",p->data);
        p = p->link;
    }
    printf("\n");
}

// 순환적인 리스트 방문
void display_recur(ListNode *head)
{
    ListNode *p = head;
    if (p != NULL){
        printf("%d->",p->data);
        display_recur(p->link);
    }
}
// 노드 값 탐색
ListNode *search(ListNode *head, int x)
{
    ListNode *p;
    p = head;
    while (p!=NULL){
        if (p->data == x) return p;
        p = p->link;
    }
    return p; // 탐색 실패인 경우 NULL 반환
}
// 두 개의 리스트 합치기
ListNode *concat(ListNode *head1, ListNode *head2)
{
    ListNode *p = NULL;
    // 두 리스트 중 하나가 비어있을 경우를 처리
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    else {
        while (p->link != NULL)
            p=p->link;
        p->link = head2;
        return head1;
    }
}

// 리스트를 역순으로 만들기
ListNode *reverse(ListNode *head)
{
    // 세 변수 r q p가 이 순서대로 이동한다고 생각한다.
    ListNode *p,*q,*r; //
    p = head;
    q = NULL;
    while (p!= NULL){
        r = q;         // r 은 q를 따라가고
        q = p;         // q는 p를 계속 따라간다.
        p = p->link;   // p는 null 을 만날 때까지 list를 순회한다.
        q -> link = r; // link의 연결방향을 바꿔주는 역할
    }
    return q; // q가 마지막에는 head 가 된다.
}

// 노드를 동적으로 생성하는 프로그램
ListNode *create_node(element data, ListNode *link)
{
    ListNode *new_node;
    new_node = (ListNode *)malloc(sizeof(ListNode));
    if (new_node == NULL) error("메모리 할당 에러");
    new_node->data = data;
    new_node->link = link;
    
    return (new_node);
}

int main(void)
{
    ListNode *list1 = NULL, *list2 = NULL;
    ListNode *p;
    
    // list1 = 30->20->10->
    insert_node(&list1,NULL,create_node(10,NULL));
    insert_node(&list1,NULL,create_node(20,NULL));
    insert_node(&list1,NULL,create_node(30,NULL));
    display(list1);
    
    // list1 = 20->10->
    remove_node(&list1,NULL, list1);
    display(list1);
    
    // list2 = 80->70->60->
    insert_node(&list1,NULL,create_node(60,NULL));
    insert_node(&list1,NULL,create_node(70,NULL));
    insert_node(&list1,NULL,create_node(80,NULL));
   
   // list1 = 80->70->60->20->10->
    list1 = concat(list1,list2);
    display(list1);
    
    // list1 = 10->20->60->70->80->
    list1= reverse(list1);
    display(list1);
    
    // 탐색성공 : 20
    p = search(list1,20);
    if (p != NULL) printf("탐색성공 : %d\n",p->data);
    else printf("탐색실패\n");
    
}
