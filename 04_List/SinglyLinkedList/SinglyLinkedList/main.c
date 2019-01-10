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

// 문제13 의 삭제함수
void remove_node_again(ListNode **phead, ListNode *p)
{
    if (p==NULL)
        *phead = (*phead)->link;
    else
        p->link = p->link->link;
    // 위 remove_node 함수에서 removed 는 p->link 와 동일하다.
}

// 반복적인 리스트 방문
void display(ListNode *phead)
{
    ListNode *p = phead;
    while (p !=NULL){
        printf("%d->",p->data);
        p = p->link;
    }
    printf("\n");
}

// 순환적인 리스트 방문
void display_recur(ListNode *phead)
{
    ListNode *p = phead;
    if (p != NULL){
        printf("%d->",p->data);
        display_recur(p->link);
    }
}
// 노드 값 탐색
ListNode *search(ListNode *phead, int x)
{
    ListNode *p;
    p = phead;
    while (p!=NULL){
        if (p->data == x) return p;
        p = p->link;
    }
    return p; // 탐색 실패인 경우 NULL 반환
}
// 두 개의 리스트 합치기
ListNode *concat(ListNode *phead1, ListNode *phead2)
{
    ListNode *p = NULL;
    // 두 리스트 중 하나가 비어있을 경우를 처리
    if (phead1 == NULL) return phead2;
    else if (phead2 == NULL) return phead1;
    else {
        while (p->link != NULL)
            p=p->link;
        p->link = phead2;
        return phead1;
    }
}

// 리스트를 역순으로 만들기
ListNode *reverse(ListNode *phead)
{
    // 세 변수 r q p가 이 순서대로 이동한다고 생각한다.
    ListNode *p,*q,*r; //
    p = phead;
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

// 문제 14번 리스트 내의 모든 원소를 더하는 함수
int sum(ListNode *phead)
{
    ListNode* p;
    p = phead;
    int sum=0;
    while (p != NULL){
        sum += p->data;
        p = p->link;
    }
    return sum;
}
// 문제 15번 특정한 데이터값을 갖는 노드의 개수를 반환하는 함수
int count(ListNode *phead, element x)
{
    ListNode* p = phead;
    int count = 0;
    while (p!=NULL){
        if (p->data == x) count++;
        p = p->link;
    }
    return count;
}

// 문제 16번 특정 데이터값을 가지는 노드를 삭제하는 함수
void search_remove(ListNode **phead, element x)
{
    ListNode* p = *phead;
    ListNode* before = NULL; // 삭제할 노드의 전 노드
    while (p!=NULL){
        if (p->data == x){
            remove_node(phead, before, p);
            // p는 free 된 상태인데 while문이 돌면서 p에 다시 접근하기 때문에 아래 과정을 해서 p를 뒤로 넘겨줘야 한다.
            if(before!=NULL) p = before->link;
            else p = *phead;
        }
        else{
            before = p;
            p = p->link;
        }
    }
}

//문제 17번 첫번째 노드부터 하나씩 건너 뛰어서 삭제하는 함수
void odd_remove(ListNode **phead)
{
    ListNode *p = *phead;
    ListNode *before = NULL;
    int count = 0;
    while (p!=NULL){
        if ((count%2) != 0){
            remove_node(phead,before,p);
            if(before!=NULL) p = before->link;
            else p = *phead;
        }
        else{
            before = p;
            p = p->link;
        }
        count++;
    }
}


// 문제 18번 보조 함수, node의 마지막에 값 대입 함수
void insert_node_last(ListNode **phead, element item)
{
    ListNode *new_node = create_node(item,NULL);
    // list가 비어있을 경우에는 새로 만든 head가 새로 만든 node를 가르키게 해준다.
    if (*phead == NULL) *phead = new_node;
    else{
        ListNode *p = *phead;
        // 비어있지 않을 경우에는 마지막으로 이동한다.
        while (p->link!=NULL)
            p = p->link;
        p->link = new_node;
    }
    
}
//문제 18번 A,B 두 노드로 부터 번갈아가면서 가져와 새로운 노드를 만드는 함수
ListNode *alternate(ListNode *list1, ListNode *list2)
{
    ListNode *list3 = NULL;
    ListNode *p1,*p2;
    if (list1 == NULL) return list2;
    else if (list2 == NULL) return list1;
    else{
        p1 = list1;
        p2 = list2;
        while ((p1!=NULL)||(p2!=NULL)){
            // 안 쪽에서도 NULL을 한 번 더 확인해줌으로서 한 list가 먼저 끝날 경우, 다른 리list 값을 그래도 이어오는 기능을 구현하였다.
            if (p1!=NULL){
                insert_node_last(&list3,p1->data);
                p1 = p1->link;
            }
            if(p2!=NULL){
                insert_node_last(&list3,p2->data);
                p2 = p2-> link;
            }
        }
        return list3;
    }
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
