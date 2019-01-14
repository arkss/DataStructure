#include <stdio.h>

#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}
// 초기화 함수
void init(QueueType *q)
{
    q->front = q->rear = 0;
}

// 공백상태 검출 함수
int is_empty(QueueType *q)
{
    // front와 rear의 값이 같으면 공백상태이다.
    return (q->front == q->rear);
}
//  포화상태 검출 함수
int is_full(QueueType *q)
{
    // front와 rear가 한 칸 떨어져 있으면 포화 상태이다.
    // queue는 포화상태와 공백상태를 구분해주기 위해서 다음과 같이 하나의 자리는 항상 비워둔다.
    return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        printf("큐가 포화상태입니다.\n");
    q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType *q)
{
    if(is_empty(q))
        printf("큐가 공백상태입니다.\n");
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}
// 피크 함수, 어느 값이 삭제될 차례인지 확인
element peek(QueueType *q)
{
    if(is_empty(q))
        error("큐가 공백상태입니다.\n");
    return q->queue[(q->front+1) % MAX_QUEUE_SIZE];
}

int main(void)
{ 
    QueueType q;
    init(&q);
    printf("front=%d rear=%d\n",q.front, q.rear);
    enqueue(&q,1);
    enqueue(&q,2);
    enqueue(&q,3);
    printf("fdequeue()=%d\n",dequeue(&q));
    printf("fdequeue()=%d\n",dequeue(&q));
    printf("fdequeue()=%d\n",dequeue(&q));
    printf("front=%d rear=%d\n",q.front, q.rear);
    
}
