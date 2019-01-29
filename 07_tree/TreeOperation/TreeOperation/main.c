#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 노드의 전체 개수를 구하는 함수
int get_node_count(TreeNode *node)
{
    int count = 0;
    if( node != NULL)
        count = 1 + get_node_count(node->left) + get_node_count(node->right);
    
    return count;
}
// 단말 노드의 개수를 구하는 함수
int get_leaf_count(TreeNode *node)
{
    int count = 0;
    if (node != NULL){
        if (node->left == NULL && node->right == NULL)
            return 1;
        else
            count = get_leaf_count(node->left)+get_leaf_count(node->right);
    }
    return count;
}
int max(int a,int b)
{
    return a>b ? a:b;
}
// 노드의 높이를 구하는 함수
int get_height(TreeNode *node)
{
    int height = 0;
    if (node != NULL)
        height = 1 + max(get_height(node->left),get_height(node->right));
    
    return height;
}

TreeNode n1 = {1,NULL,NULL};
TreeNode n2 = {2,NULL,NULL};
TreeNode n3 = {3,&n1,&n2};
TreeNode n4 = {4,NULL,NULL};
TreeNode n5 = {5,&n3,&n4};
TreeNode *root = &n5;

int main(int argc, const char * argv[]) {
    
    printf("node의 수 : %d\n",get_node_count(root));
    printf("leaf node의 수 : %d\n",get_leaf_count(root));
    
    printf("node의 높이 : %d\n",get_height(root));
}
