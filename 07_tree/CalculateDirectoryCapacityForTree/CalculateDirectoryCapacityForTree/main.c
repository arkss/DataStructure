#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
}TreeNode;

int calc_direc_size(TreeNode *root)
{
    int left_size, right_size;
    if(root != NULL){
        left_size = calc_direc_size(root->left);
        right_size = calc_direc_size(root->right);
        return (root->data + left_size + right_size);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    TreeNode n4 = {500,NULL,NULL};
    TreeNode n5 = {200,NULL,NULL};
    TreeNode n3 = {100,&n4,&n5};
    TreeNode n2 = {50,NULL,NULL};
    TreeNode n1 = {0,&n2,&n3};
    
    printf("디렉토리의 크기 = %d\n", calc_direc_size(&n1));
    // 850
}
