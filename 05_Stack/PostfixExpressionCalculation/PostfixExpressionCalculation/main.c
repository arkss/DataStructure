#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
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

element eval(char exp[])
{
    int op1, op2, value, i=0;
    int len = strlen(exp);
    char ch;
    StackType s;
    
    init(&s);
    for (i=0;i<len;i++){
        ch = exp[i];
        
        // 입력받은 값이 사칙연산이 아니면, 즉 숫자면
        if (ch!='+' && ch!='-' && ch != '*' && ch != '/'){
            // 아스키코드값을 정수로 바꿔주고
            value = ch - '0';
            push(&s, value);
        }
        // 문자일 경우에는, 스택에서 값을 꺼내서 연산을 해준다.
        else{
            op2 = pop(&s);
            op1 = pop(&s);
            switch(ch){
                case '+': push(&s, op1+op2); break;
                case '-': push(&s, op1-op2); break;
                case '*': push(&s, op1*op2); break;
                case '/': push(&s, op1/op2); break;
            }
        }
    }
    return pop(&s);
}

int main(void)
{
    int result;
    printf("후위 표기식은 82/3-32*+\n");
    result = eval("82/3-32*+");
    printf("결과값은 %d\n", result);
}
