#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

// 리스트를 위한 구조체
typedef struct{
    ListNode *head; // 헤드포인터
    int length;     // 노드의 개수
} LinkedListType;

// 리스트의 공백여부를 확인하는 함수
int is_empty(LinkedListType *list)
{
    if (list->head == NULL) return 1;
    else return 0;
}

void error(char* message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}
// 삽입함수
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
    if (*phead == NULL){
        new_node->link = NULL;
        *phead = new_node;
    }
    else if ( p ==NULL){
        new_node->link = *phead;
        *phead = new_node;
    }
    else{
        new_node->link = p->link;
        p->link = new_node;
    }
}
// 삭제함수
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
    if (p==NULL){
        *phead = (*phead)->link;
    }
    else{
        p->link = removed->link;
    }
    free(removed);
}

// 리스트의 항목의 개수를 반환하는 함수
int get_length(LinkedListType *list)
{
    return list->length;
}



// 리스트 안에서 pos 위치의 노드를 반환
ListNode *get_node_at(LinkedListType *list, int pos)
{
    int i;
    ListNode *tmp_node = list->head;
    if (pos<0) return NULL;
    for (i=0;i<pos;i++)
        tmp_node = tmp_node->link;
    return tmp_node;
}


// 전에 했던 insert_node 함수를 이용하여 위치를 통해 리스트에 추가하는 함수
void add(LinkedListType *list, int position, element data)
{
    ListNode *p;
    if ((position>=0) && (position <= list->length)){
        ListNode * node = (ListNode *)malloc(sizeof(ListNode));
        if (node == NULL) error("메모리 할당에러\n");
        node->data = data;
        p = get_node_at(list, position-1);
        insert_node(&(list->head),p,node);
        list->length++;
    }
}
// 리스트의 끝에 삽입
void add_last(LinkedListType *list,element data)
{
    add(list,get_length(list),data);
}

// 리스트의 처음에 삽입
void add_first(LinkedListType *list, element data)
{
    add(list,0,data);
}

// 전에 했던 remove_node 함수를 이용하여 위치를 통해 리스트에서 제거하는 함수
void delete(LinkedListType *list, int pos)
{
    // 리스트가 비어있지 않고 list 범위 내에 pos 가 있으면
    if (!is_empty(list) && (pos>=0) && pos<(list->length)){
        ListNode *p = get_node_at(list, pos-1);
        ListNode *removed = get_node_at(list,pos);
        remove_node(&(list->head),p,removed);
        list->length--;
    }
}

// 주어진 위치에 해당하는 데이터를 반환하는 함수
element get_entry(LinkedListType *list,int pos)
{
    ListNode *p;
    if (pos >= list->length) error("위치오류");
    p = get_node_at(list,pos);
    return p->data;
}

// 모든 노드를 지우는 함수
void clear_all(LinkedListType *list)
{
    int i;
    for(i=0;i<list->length;i++)
        delete(list,i);
}

// 리스트 출력하는 함수
void display(LinkedListType *list)
{
    int i;
    ListNode *node = list->head;
    printf("(");
    for (i=0;i<list->length;i++){
        printf("%d ",node->data);
        node = node->link;
    }
    printf(")\n");
}

// 리스트 탐색 함수
int is_in_list(LinkedListType *list, element item)
{
    ListNode *p;
    p = list->head;
    while(p!=NULL){
        if (p->data == item)
            break;
        p = p->link;
    }
    if (p==NULL) return FALSE;
    else return TRUE;
}

void init(LinkedListType *list)
{
    if (list == NULL) return;
    list->length = 0;
    list->head = NULL;
}

int main(void)
{
    LinkedListType list1;
    
    init(&list1);
    add(&list1,0,20);
    add_last(&list1,30);
    add_first(&list1,10);
    add_last(&list1,40);
    // list1 = (10,20,30,40)
    display(&list1);
    
    delete(&list1, 3);
    // list1 = (10,20,30)
    display(&list1);
    
    delete(&list1,0);
    // list1 = (20,30)
    display(&list1);
    
    printf("%s\n", is_in_list(&list1,20) == TRUE ? "성공":"실패"); // 성공
    printf("%d\n",get_entry(&list1,0)); // 20
}
