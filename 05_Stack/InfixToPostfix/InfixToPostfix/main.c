#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

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

// 연산자의 우선순위를 반환한다.
int prec(char op)
{
    switch(op){
        case '(': case ')': return 0; //
        case '+': case '-': return 1; //
        case '*': case '/': return 2; // 우선순위 최하위
    }
    return -1;
}

// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[])
{
    int i =0;
    char ch, top_op;
    int len = strlen(exp);
    StackType s;
    
    init(&s);
    for(i=0;i<len;i++){
        // 입력받은 문자열에서 값을 하나씩 가져온다.
        ch = exp[i];
        switch(ch){
            // 연산자를 가져 왔을 경우.
            case '+': case '-': case '*': case '/':
                // 스택이 비어있지 않고, 현재 스택 안에 있는 연산자가 우선순위가 더 높을 경우에는
                while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
                    // 스택에 있는 것을 pop 한다.
                    printf("%c",pop(&s));
                // 아닐 경우에는 스택에 넣어준다.
                push(&s, ch);
                break;
            // ( 를 받은 경우에는 무조검 스택에 넣어준다.
            case '(':
                push(&s, ch);
                break;
            // ) 을 받은 경우에는
            case ')':
                top_op = pop(&s);
                // 스택에서 ( 을 만날 때까지 뽑아서 출력한다.
                while(top_op != '('){
                    printf("%c",top_op);
                    top_op = pop(&s);
                }
                break;
            // 숫자를 받으면 바로 출력한다.
            default:
                printf("%c",ch);
                break;
            }
    }
    // 스택이 빌 때까지 남은 것들을 모두 출력한다.
    while(!is_empty(&s))
        printf("%c",pop(&s));
}

int main(void)
{
    infix_to_postfix("(2+3)*4+9");
}

