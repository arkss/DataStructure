// 라인에디터 구현하기

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 1000
#define MAX_NAME 256

void warning(char *);
void error(char *);

#define FALSE 0
#define TRUE 1

typedef struct {
    char a[MAX_CHAR_PER_LINE];
} element;
//노드에 저장될 데이터 타입이 문자열이 된다. 따라서 element를 다음과 같이 정의.

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

void init(LinkedListType *list)
{
    if (list == NULL) return;
    list->length = 0;
    list->head = NULL;
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
void display(LinkedListType *buffer)
{
    int i;
    ListNode *tmp_node;
    tmp_node = buffer->head;
    printf("*****************\n");
    for(i=0;i<buffer->length;i++){
        printf("%s",tmp_node->data.a);
        tmp_node = tmp_node->link;
    }
    printf("*****************\n");
}

// 경고 출력 함수
void warning(char * message)
{
    fprintf(stderr,"%s\n", message);
}

void help()
{
    printf("***************\n");
    printf("i : 입력\n");
    printf("d : 삭제\n");
    printf("r : 파일읽기\n");
    printf("w : 파일쓰기\n");
    printf("q : 종료\n");
    printf("***************\n");
}


// 데이터 읽기
void read_file(LinkedListType *buffer)
{
    char fname[MAX_NAME];
    FILE *fd;
    element p;
    
    if (!is_empty(buffer)){
        clear_all(buffer);
    }
    init(buffer);
    
    printf("파일 이름 :");
    scanf("%s",fname);
    if( (fd= fopen(fname,"r"))==NULL){
        warning("파일을 열 수 없습니다.");
        return;
    }
    while (fgets(p.a, MAX_CHAR_PER_LINE, fd)) {
        add_last(buffer,p);
    }
    fclose(fd);
    display(buffer);
}

// 버퍼에 있는 데이터를 디스크 파일로
void write_file(LinkedListType *buffer)
{
    FILE *fd;
    char fname[MAX_NAME];
    element p;
    int i;
    
    printf("파일 이름 : ");
    scanf("%s",fname);
    if ( (fd= fopen(fname,"w")) == NULL){
        printf("파일을 열 수 없습니다.\n");
        return ;
    }
    for(i=0;i<get_length(buffer);i++)
    {
        p = get_entry(buffer,i);
        fputs(p.a,fd);
    }
    fclose(fd);
    display(buffer);
}

// 라인 하나 삭제
void delete_line(LinkedListType *buffer)
{
    int position;
    
    if (is_empty(buffer))
        printf("지울 라인이 없습니다.\n");
    else
    {
        printf("지우고 싶은 라인 번호를 입력하세요\n");
        scanf("%d", &position);
        delete(buffer, position);
    }
    display(buffer);
}

// 라인 하나 추가
void insert_line(LinkedListType *buffer)
{
    int position;
    char line[MAX_CHAR_PER_LINE];
    element p;
    
    printf("입력행번호를 입력하세요\n");
    scanf("%d",&position);
    
    printf("내용을 입력하세요\n");
    rewind(stdin);
    fgets(line,MAX_CHAR_PER_LINE, stdin);
    strcpy(p.a, line);
    add(buffer, position, p);
    display(buffer);
}

void do_command(LinkedListType *buffer, char command)
{
    switch(command)
    {
        case 'd':
            delete_line(buffer);
            break;
        case 'i':
            insert_line(buffer);
            break;
        case 'r':
            read_file(buffer);
            break;
        case 'w':
            write_file(buffer);
            break;
        case 'q':
            break;
    }
}
int main(void)
{
    char command;
    LinkedListType buffer;
    
    init(&buffer);
    do {
        help();
        command = getchar();
        do_command(&buffer, command);
        rewind(stdin);
    } while (command!= 'q');
   
    
    
        

}
