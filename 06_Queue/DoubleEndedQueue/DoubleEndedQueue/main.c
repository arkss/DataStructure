#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int element;


typedef struct DlistNode{
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
}DlistNode;

typedef struct DequeType {
    DlistNode *head; // 첫번째 노드를 가리키는 변수
    DlistNode *tail; // 마지막 노드를 가리키는 변수
} DequeType;

// 에러 출력함수
void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}
// 초기화 함수
void init(DequeType *dq)
{
    dq->head = dq->tail = NULL;
}
// 공백 확인 함수
int is_empty(DequeType *dq)
{
    if(dq->head==NULL) return TRUE;
    else return FALSE;
}

// 새로운 노드를 생성하는 함수
DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink)
{
    DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
    if (node ==NULL)
        error("메모리 할당 오류");
    node->llink = llink;
    node->data = item;
    node->rlink = rlink;
    return node;
}

// 뒤로 추가하는 함수
void add_rear(DequeType *dq,element item)
{
// 새로운 노드를 형성한다. 새 노드의 llink를 앞쪽을 지금의 tail과 연결, 뒤쪽은 없다.
    DlistNode *new_node = create_node(dq->tail, item, NULL);
    // 빈 노드일 경우에는 head가 새로운 노드를 가리키게 한다.
    if(is_empty(dq))
        dq->head = new_node;
    // 빈 노드가 아닐 경우에는 tail의 rlink에 새로운 노드를 연결 시킨다.
    else
        // 마지막 노드의 rlink를 new_node와 연결
        dq->tail->rlink = new_node;
    // 마지막 노드를 new_node 로 바꿔준다.
    dq->tail = new_node;
}

// 앞으로 추가하는 함수
void add_front(DequeType *dq, element item)
{
// 새로운 노드를 형성한다. 새 노드의 llink를 앞쪽을 지금의 tail과 연결, 앞쪽은 없다.
    DlistNode *new_node = create_node(NULL, item, dq->head);
    
    if (is_empty(dq))
        dq->tail = new_node;
    else
        dq->head->llink = new_node;
    dq->head = new_node;
}

// 앞에서 삭제하는 함수
element delete_front(DequeType *dq)
{
    element item;
    DlistNode * removed_node;
    
    if(is_empty(dq)) error("공백 덱에서 삭제");
    else{
        removed_node = dq->head;    // head가 가르키는 노드,즉 삭제할 노드
        item = removed_node->data;  // 삭제할 값을 item 에 저장
        dq->head = dq->head->rlink; // 헤드포인터를 다음 node로 변경
        free(removed_node);
        
        // 삭제한 후에 덱이 비어있으면 tail도 NULL로
        if(dq->head ==NULL)
            dq->tail = NULL;
        // 삭제한 후에 덱이 아직 안비었으면 첫번째 노드의 왼쪽 연결은 아무것도 없다.
        else
            dq->head->llink = NULL;
    }
    return item;
}

// 뒤에서 삭제하는 함수
element delete_rear(DequeType *dq)
{
    element item=0;
    DlistNode *removed_node;
    // 덱이 비어있으면 에러
    if(is_empty(dq)) error("공백 덱에서의 삭제");
    // 비어있지 않으면
    else{
        removed_node = dq->tail; // tail이 가르키는 노드, 즉 삭제할 노드
        item = removed_node->data;// 삭제할 값을 item에 저장
        dq->tail = dq->tail->llink;// tail포인터를 그 전 node로 변경
        free(removed_node);
        
        // 삭제한 후에 덱이 비어있으면 head도 NULL로
        if(dq->tail==NULL)
            dq->head = NULL;
        // 삭제한 후에 덱이 아직 안 비었으면 마지막 노드의 오른쪽 연결은 아무것도 없다.
        else
            dq->tail->rlink = NULL;
    }
    return item;
}

// 출력하는 함수
void display(DequeType *dq)
{
    DlistNode *p;
    printf("(");
    for(p=dq->head;p!=NULL;p=p->rlink){
        printf("%d ",p->data);
    }
    printf(")\n");
}

int main(void)
{
    DequeType deque;
    init(&deque);
    add_front(&deque,10);
    add_front(&deque,20);
    add_rear(&deque, 30);
    display(&deque);
    
    delete_front(&deque);
    delete_rear(&deque);
    display(&deque);
}
