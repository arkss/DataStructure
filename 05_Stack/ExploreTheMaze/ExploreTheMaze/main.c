#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
// 미로의 크기를 6*6 으로 한정
#define MAZE_SIZE 6

// 미로에서의 위치를 2차원평면으로 생각하여 좌표로 나타냄
typedef struct{
    short r;
    short c;
}element;

// 쥐의 현재 위치 here, 시작하는 위치 entry
element here = {1,0}, entry={1,0};

typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init(StackType *s)
{
    s->top = -1;
}
//공백 상태 확인 함수
int is_empty(StackType *s)
{
    return (s->top == -1);
}
//포화 상태 확인 함수
int is_full(StackType *s)
{
    return (s->top == (MAX_STACK_SIZE-1));
}
// push 함수
void push(StackType *s, element item)
{
    if (is_full(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else s->stack[++(s->top)] = item;
}

// pop 함수
element pop(StackType *s)
{
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->stack[(s->top)--];
}

//peek함수, top에 있는 값만 확인
element peek(StackType *s)
{
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->stack[(s->top)];
}

// 미로, 1은 벽, 0은 길, e는 출발지점, x는 도착지점
char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1','1','1','1','1','1'},
    {'e','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','x'},
    {'1','1','1','1','1','1'}
};

// 위치를 스택에 삽입하는 함수
// 스택과 좌표값을 매개변수로 받는다.
void push_loc(StackType *s, int r, int c)
{
    if(r<0||c<0) return;
    // 벽도 아니고 방문도 하지 않았을 경우에
    if (maze[r][c] != '1' && maze[r][c] != '.'){
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s,tmp);
    }
}

int main(void)
{
    int r,c;
    StackType s;
    
    init(&s);
    here = entry;
    // 도착지점이 아닐 경우에는 계속해서 반복한다.
    while( maze[here.r][here.c] != 'x'){
        r = here.r;
        c = here.c;
        // 현재 위치는 방문 표시를 해주고
        maze[r][c] = '.';
        // 현재 위치의 사방을 다 검사해준다.
        push_loc(&s,r-1,c);
        push_loc(&s,r+1,c);
        push_loc(&s,r,c-1);
        push_loc(&s,r,c+1);
        // 스택이 비어있는 경우, 즉 더 이상 이동할 경로가 없는 경우에는 미로에 출구가 없는 것이고,
        if (is_empty(&s)){
            printf("실패");
            return 0;
        }
        // 스택이 비어있지 않은 경우에는 pop해서 현재위치 here로 넣어준다.
        else
            here = pop(&s);
        
    }
    printf("성공\n");
}
