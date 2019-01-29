#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef TreeNode *element;


typedef struct QueueNode{
    element item;
    struct QueueNode *link;
}QueueNode;



typedef struct{
    QueueNode *front;
    QueueNode *rear;
}QueueType;

// 오류 함수
void error(char *message)
{
    fprintf(stderr,"%s\n", message);
    exit(1);
}

// 초기화 함수
void init(QueueType *q)
{
    q->front = q->rear = NULL;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
    //큐의 요소가 없는 경우에는 front와 rear이 둘 다 null이다.
    return (q->front==NULL);
}
// 큐에 삽입하는 함수
void enqueue(QueueType *q, element item)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    if ( temp == NULL)
        error("메모리를 할당 할 수 없습니다.\n");
    
    else{
        // 동적할당해서 새로 만든 노드는 맨 뒤로 들어가기 떄문에 link는 NULL이 된다.
        temp->item = item;
        temp->link = NULL;
        // q가 비어있으면 front와 rear 둘다 temp를 가르킨다.
        if(is_empty(q)){
            q->front = temp;
            q->rear = temp;
        }
        // 비어있지 않았으면
        else{
            // temp 노드의 전 노드가 temp를 가르키게 해주고
            q->rear->link = temp;
            // rear를 temp로 바꿔준다.
            q->rear = temp;
        }
    }
}

// 큐에서 제거하는 함수
element dequeue(QueueType *q)
{
    QueueNode *temp = q->front;
    element item;
    if(is_empty(q))
        error("큐가 비었습니다.\n");
    else{
        item = temp->item;
        // front가 다음 노드를 가르키게 한다.
        q->front = q->front->link;
        // front를 다음 노드를 가리키게 한 후에 다시 공백상태이면 rear도 NULL 값을 대입해준다.
        if(q->front == NULL)
        {
            q->rear = NULL;
        }
        free(temp);
        return item;
    }
    return 0;
}
// peek 함수, queue에서 제거될 값이 무엇인지 확인하는 함수
element peek(QueueType *q)
{
    if(is_empty(q))
        error("큐가 비어 있습니다.");
    else {
        return q->front->item;
    }
    return 0;
}

// 트리 레벨 순회
void level_order(TreeNode *ptr)
{
    // 큐 생성
    QueueType q;
    // 큐 초기화
    init(&q);
    // 빈 트리이면 그냥 반환
    if (ptr == NULL) return;
    // 큐 안에 트리 노드를 넣고
    enqueue(&q, ptr);
    // 큐가 빌 때까지 반복
    while(!is_empty(&q)){
        // 하나를 꺼내서
        ptr = dequeue(&q);
        // 그 값을 출력하고
        printf("%d\n",ptr->data);
        // 그 왼쪽 값과 오른쪽 값에도 똑같이 적용
        if(ptr->left)
            enqueue(&q, ptr->left);
        if(ptr->right)
            enqueue(&q, ptr->right);
    }
}

// 임의의 트리 생성
//        15
//    4       20
//1         16  25
TreeNode n1 = {1,NULL,NULL};
TreeNode n2 = {4,&n1,NULL};
TreeNode n3 = {16,NULL,NULL};
TreeNode n4 = {25,NULL,NULL};
TreeNode n5 = {20,&n3,&n4};
TreeNode n6 = {15,&n2,&n5};
TreeNode *root = &n6;


int main(int argc, const char * argv[]) {
    level_order(root);
//    15
//    4
//    20
//    1
//    16
//    25
    
}
