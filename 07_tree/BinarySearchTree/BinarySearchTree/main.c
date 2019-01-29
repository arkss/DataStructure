#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int key;
    struct TreeNode *left, *right;
} TreeNode;

// 순환적인 탐색 함수
TreeNode *recursive_search(TreeNode *node, int key)
{
    if (node == NULL) return NULL;
    if (key == node->key) return node;
    // 작으면 왼쪽에서
    else if (key < node->key)
        return recursive_search(node->left, key);
    // 크면 오른쪽에서
    else
        return recursive_search(node->right,key);
}

// 반복적인 탐색 함수
TreeNode *iterative_search(TreeNode *node, int key)
{
    while(node != NULL){
        if(key == node->key) return node;
        else if (key<node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL; // 탐색에 실패하면 NULL을 반환
}

// 이진 트리 삽입 프로그램
void insert_node(TreeNode **root, int key)
{
    TreeNode *p, *t; // p는 부모 노드, t는 현재 노드
    TreeNode *n; // n은 새로운 노드
    
    t = *root;
    p = NULL;
    
    while(t!=NULL){
        // 탐색이 성공하면 아무것도 하지않고 종료한다.
        if(key == t->key) return;
        // 현재노드가 부모노드가 되고
        p = t;
        // 현재 노드는 key 값의 크기를 비교해 왼쪽 or 오른쪽을 결정
        if ( key < p->key) t = p->left;
        else t = p->right;
    }
    // 트리노드 구성
    n = (TreeNode *)malloc(sizeof(TreeNode));
    if (n==NULL) return;
    
    // 데이터 복사
    n->key = key;
    n->left = n->right = NULL;
    // 부모가 존재한다면 부모를 새로운 노드에 연결해준다.
    if( p!=NULL){
        if(key<n->key)
            p->left = n;
        else
            p->right = n;
    }
    // 부모가 존재하지않으면 root와 연결
    else
        *root = n;
}

// 삭제 함수
void delete_node(TreeNode **root, int key)
{
    TreeNode *p, *child, *succ, *succ_p, *t;
    // succ은 후계자 노드, succ_p는 후계자의 부모 노드
    
    p = NULL; // p는 부모 노드
    t = *root; // t는 현재 노드
    
    while( t!=NULL && t->key!=key){
        p = t;
        t = (key<p->key) ? p->left : p->right;
    }
    // 탐색이 끝난 시점에서 t가 NULL이면 트리 안에 key가 없다.
    if (t==NULL){
        printf("key is not the tree");
        return;
    }
    
    // 첫번째 경우: 단말 노드인 경우
    if((t->left==NULL)&&(t->right==NULL)){
        if(p!=NULL){
            // 연결을 끊어버린다.
            if(p->left == t)
                p->left = NULL;
            else
                p->right = NULL;
        }
        // 부모가 NULL이면 root 노드를 NULL로 바꾼다.
        else
            *root = NULL;
    }
    // 두번째 경우: 하나의 자식만 가지고 있는 경우
    else if((t->left==NULL)||(t->right==NULL)){
        // child 노드에 둘 중 존재하는 값, 자식 노드를 넣어준다.
        child = (t->left != NULL) ? t->left : t->right;
        if (p!=NULL){
            // t의 부모와 t의 자식을 연결해준다.
            if(p->left == t)
                p->left = child;
            else p->right = child;
        }
        // 부모가 없었으면 root가 p의 자식 node를 가르키게 한다.
        else
            *root = child;
    }
    // 세번째 경우: 두 개의 자식을 가지고 있는 경우
    else{
        // 오른쪽 서브트리에서 후계자를 찾는다.
        succ_p = t;
        succ = t->right;
        // 후계자를 찾아서 계속 왼쪽으로 이동한다.
        // 즉 root를 기준으로 오른쪽 노드에서 가장 작은 값을 찾기위한 과정
        while(succ->left != NULL){
            succ_p = succ;
            succ = succ->left;
        }
        // 후속자의 부모와 자식을 연결
        if (succ_p->left == succ)
            succ_p->left = succ-> right;
        // 이런 경우가 언제 있지? /////////////////////////////////
        else
            succ_p->right = succ->right;
        
        // 한 번에 대입이 되지않나? 굳이 따로 해주는 이유는?
        // 여기서 굳이 t에 대입을 해주는 이유는 마지막에 free(t)를 해주는 일관성을 유지하기 위해서이다.
        t->key = succ->key;
        t = succ;
    
    }
    
    
    // 삭제 할 것이므로 free 해준다.
    free(t);
}
int main(int argc, const char * argv[]) {


}
