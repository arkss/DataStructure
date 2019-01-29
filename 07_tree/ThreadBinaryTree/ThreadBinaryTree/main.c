#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FLASE 0

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
    int is_thread;
} TreeNode;

//        G
//    C       F
//   A B     D E

TreeNode n1 = { 'A', NULL, NULL, 1 };// thread이면 1
TreeNode n2 = { 'B', NULL, NULL, 1 };
TreeNode n3 = { 'C', &n1, &n2, 0 };
TreeNode n4 = { 'D', NULL, NULL, 1 };
TreeNode n5 = { 'E', NULL, NULL, 0 };
TreeNode n6 = { 'F', &n4, &n5, 0 };
TreeNode n7 = { 'G', &n3, &n6, 0 };
TreeNode *root = &n7;

// 중위 후속자를 찾는 함수
TreeNode *find_successor(TreeNode *p)
{
    TreeNode *q = p->right;
    // 오른쪽 포인터가 NULL 이거나 쓰레드이면 오른쪽 포인터를 번환
    // 오른쪽 포인터가 NULL 이라는 것은 더 이상 후속자가 없다는 뜻. 오른쪽 서브트리의 맨 밑단
    if( q == NULL || p->is_thread == TRUE){
        return q;
    }
    // 오른쪽 포인터가 NULL이 아니라면, 왼쪽 서브트리가 존재한다는 뜻
    // 왼쪽 서브트리로 이동
    while( q->left != NULL){
        q = q->left;
    }
    return q;
}


void thread_inorder(TreeNode *t)
{
    TreeNode *q;
    // 원래 값은 보존하기 위해서 복사해서 사용
    q = t;
    // 가장 왼쪽으로 이동
    while(q->left != NULL)
        q = q->left;
    do
    {
        printf("%c",q->data);
        // 중위 후속자가 없을 때 까지 계속 반복
        q = find_successor(q);
    }while(q!=NULL);
}


int main(int argc, const char * argv[]) {

    n1.right = &n3;
    n2.right = &n7;
    n4.right = &n6;
    thread_inorder(root);
}

