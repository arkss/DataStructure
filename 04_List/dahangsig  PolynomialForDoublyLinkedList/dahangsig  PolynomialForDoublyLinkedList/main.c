#include <stdio.h>
#include <stdlib.h>

// 연결리스트의 노드
typedef struct ListNode {
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

// 연결 리스트 해더
typedef struct ListHeader {
    int length;
    ListNode *head;
    ListNode *tail;
} ListHeader;

// 초기화 함수
void init(ListHeader *plist)
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
    
}

// 오류 처리 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 다항식의 마지막에 새로운 노드 추가하는 함수
// plist : 연결리스트의 해더를 가르키는 포인터 coef : 계수 expon : 지수
void insert_node_last(ListHeader *plist, int coef, int expon)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if (temp == NULL) error("메모리 할당 에러");
    temp->coef=coef;
    temp->expon=expon;
    temp->link=NULL;
    // 빈 다항식일 경우
    if (plist->tail == NULL)
    {
        plist->head = plist->tail = temp;
    }
    else{
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->length++;
}

// 다항식의 덧셈 함수
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)
{
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    
    int sum;
    while (a && b){
        // a의 차수 = b의 차수
        if (a->expon == b->expon){
            sum = a->coef + b->coef;
            if (sum != 0)
                insert_node_last(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        // a의 차수 > b의 차수
        else if ( a->expon > b->expon){
            insert_node_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        // a의 차수 < b의 차수
        else{
            insert_node_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }
    // 남은 항들 모두 뒤에 추가해줌, 두 반복문 중 하나만 돌아간다.
    for(;a!=NULL;a=a->link)
        insert_node_last(plist3, a->coef, a->expon);
    for(;b!=NULL;b=b->link)
        insert_node_last(plist3, b->coef, b->expon);
}

void poly_print(ListHeader *plist)
{
    ListNode *p = plist->head;
    while (p!=NULL){
        printf("%d %d\n", p->coef, p->expon);
        p = p->link;
    }
}

int main(void)
{
    ListHeader list1, list2, list3;
    
    // 각 리스트들 초기화
    init(&list1);
    init(&list2);
    init(&list3);
    
    // 다항식 1 생성
    insert_node_last(&list1, 3,12);
    insert_node_last(&list1, 2,8);
    insert_node_last(&list1, 1,0);
    
    // 다항식 2 생성
    insert_node_last(&list2, 8,12);
    insert_node_last(&list2, -3,10);
    insert_node_last(&list2, 10,6);
    
    poly_add(&list1, &list2, &list3);
    poly_print(&list3);
}
