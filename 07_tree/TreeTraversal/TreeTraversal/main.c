#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode n1 = {1, NULL,NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16,NULL,NULL};
TreeNode n4 = {25,NULL,NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};
TreeNode *root = &n6;

// 중위 순회
void inorders(TreeNode *root)
{
    if (root){
        inorders(root->left);
        printf("%d->",root->data);
        inorders(root->right);
    }
}

// 전위 순회
void preorders(TreeNode *root)
{
    if (root){
        printf("%d->",root->data);
        preorders(root->left);
        preorders(root->right);
    }
}

// 후위 순회
void postorders(TreeNode *root)
{
    if (root){
        postorders(root->left);
        postorders(root->right);
        printf("%d->",root->data);
    }
}


int main(int argc, const char * argv[]) {
    inorders(root); // 1->4->15->16->20->25->
    printf("\n");
    preorders(root); // 15->4->1->20->16->25->
    printf("\n");
    postorders(root); // 1->4->16->25->20->15->
    printf("\n");
}
