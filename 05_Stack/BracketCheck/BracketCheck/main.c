#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1

typedef char element;
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

//괄호 검사 함수
int check_matching(char *in)
{
    StackType s;
    char ch, open_ch;
    int i;
    int n = strlen(in);
    init(&s);
    
    for(i=0;i<n;i++){
        ch = in[i];
        switch(ch){
            case '(': case '[': case '{':
                push(&s,ch);
                break;
            case ')': case ']': case '}':
                // 스택이 비어있으면 오류
                if (is_empty(&s))
                    return FALSE;
                else{
                    open_ch = pop(&s);
                    // 괄호의 짝이 맞지않으면 오류
                    if((open_ch == '(' && ch != ')')||
                       (open_ch == '[' && ch != ']')||
                       (open_ch == '{' && ch != '}')){
                        return FALSE;
                    }
                    break;
                }
        }
    }
    // 스택에 뭔가 남아있으면 오류
    if (!is_empty(&s)) return FALSE;
    return TRUE;
}

int main(void)
{
    if (check_matching("{A[(i+1)]=0}") ==TRUE)
        printf("괄호검사 성공\n");
    else
        printf("괄호검사 실패\n");
}
