#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;
//        +
//    *       +
//  1   4  16   25

TreeNode n1 = {1,NULL,NULL};
TreeNode n2 = {4,NULL,NULL};
TreeNode n3 = {'*',&n1,&n2};
TreeNode n4 = {16,NULL,NULL};
TreeNode n5 = {25,NULL,NULL};
TreeNode n6 = {'+',&n4,&n5};
TreeNode n7 = {'+',&n3,&n6};
TreeNode *root = &n7;

int evaluate(TreeNode *root)
{
    // 비어있으면 끝
    if (root == NULL)
        return 0;
    // 자식노드들이 비어있으면 본인의 값을 return
    if(root->left == NULL && root->right == NULL)
        return root->data;
    // 자식노드가 있으면
    else{
        // 자식 노드들의 값을 계산
        int op1 = evaluate(root->left);
        int op2 = evaluate(root->right);
        // 자식노드들의 값을 내 연산자로 이용해서 계산 후 return
        switch(root->data){
            case '+':
                return op1+op2;
            case '-':
                return op1-op2;
            case '*':
                return op1*op2;
            case '/':
                return op1/op2;
                
        }
    }
    return 0;
}
int main(int argc, const char * argv[]) {
    printf("%d", evaluate(root)); // 45
}
