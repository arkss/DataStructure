#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int element; // 리스트에 들어갈 자료형이 바뀔 수 한 번에 바꿔주기 위해서
typedef struct {
    element list[MAX_LIST_SIZE];
    int length; // list에 저장된 자료의 개수
} ArrayListType;

// 오류 처리
void error(char * message)
{
    fprintf(stderr, "%s\n",message);
    exit(1);
}

// 리스트 초기화
void init(ArrayListType *L)
{
    L->length = 0;
}

// 리스트 비웠는지 확인 함수
int is_empty(ArrayListType *L)
{
    return L->length == 0; // 비어있으면 1, 아니면 0 반환
}

// 리스트 꽉 찼는지 확인 함수
int is_full(ArrayListType *L)
{
    return L->length == MAX_LIST_SIZE; // 꽉 찼으면 1, 아니면 0 반환
}

// 리스트의 항목을 출력하는 함수
void display(ArrayListType *L)
{
    int i;
    for (i=0;i<L->length;i++)
    {
        printf("%d\n", L->list[i]);
    }
}

// 리스트에 항목을 추가하는 함수
void add(ArrayListType *L, int position, element item)
{
    // 가득 차지 않고, 위치가 0보다 크거나 같고, 리스트의 길이보다 같거나 작을 때
    if (!is_full(L) && (position >=0) && (position <= L->length)){
        int i;
        // 끝에서 부터 하나씩 옮겨준다.
        for (i=L->length-1;i>=position;i--)
            L->list[i+1] = L->list[i];
        L->list[position] = item;
        L->length++;
    }
}

// 맨 앞에 요소를 추가하는 함수
void add_first(ArrayListType *L, element item)
{
    add(L,0,item);
}

// 맨 끝에 요소를 추가하는 함수
void add_last(ArrayListType *L, element item)
{
    add(L,L->length,item);
}

// 리스트의 모든 요소를 제거하는 함수, init함수 동일.
void clear_all(ArrayListType *L)
{
    L->length = 0;
}

// pos 위치이의 요소를 아이템으로 바꾸는 함수
void replace(ArrayListType *L, int position, element item)
{
    L->list[position] = item;
}

//item이 list에 있는지 검사하는 함수
int is_in_list(ArrayListType *L, element item)
{
    int i;
    for(i=0;i<(L->length);i++){
        if (L->list[i] == item) return 1;
    }
    return 0;
}

//pos의 위치의 요소롤 반환하는 함수
element get_entry(ArrayListType *L, int position)
{
    if (position < 0 || position >= L->length)
        error("index 에러\n");
    return L->list[position];
}

// 리스트의 길이를 구하는 함수
int get_length(ArrayListType *L)
{
    return L->length;
}

// 리스트에 항목을 삭제하는 함수
element delete(ArrayListType *L,int position)
{
    int i;
    element item;
    
    if (position < 0 || position >= L->length)
        error("위치 오류");
    item = L->list[position];
    for(i=position;i<(L->length);i++)
        L->list[i] = L->list[i+1];
    L->length--;
    return item;
}

int main(void)
{
    ArrayListType list1;
    ArrayListType *plist;
    
    // 구조체를 정적으로 생성
    init(&list1);
    add(&list1,0,10);
    add(&list1,0,20);
    add(&list1,0,30);
    display(&list1);
    
    // 구조체를 동적으로 생성
    plist = (ArrayListType *)malloc(sizeof(ArrayListType));
    init(plist);
    add(plist,0,10);
    add(plist,0,20);
    add(plist,0,30);
    display(plist);
    free(plist);
    
}
