#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows; // 행의 개수
    int cols; // 열의 개수
    int terms; // 0아닌 값을 가지는 항의 개수
} SparseMatrix;

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b);

int main(void)
{
    SparseMatrix m1 = {{{1,1,5},{2,2,9}}, 3,3,2};
    SparseMatrix m2 = {{{0,0,5},{2,2,9}}, 3,3,2};
    SparseMatrix m3;
    
    m3 = sparse_matrix_add2(m1, m2);
    
    // m3 = {{{0,0,5},{1,1,5},{2,2,18}}, 3,3,3};
    
    
}

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)
{
    SparseMatrix c;
    int ca=0, cb=0, cc =0;
    
    // a와 b의 행렬 크기 같은지 계산하고 다르면 error
    if (a.rows != b.rows || a.cols != b.cols){
        fprintf(stderr, "희소에러의 크기 에러\n");
        exit(1);
    }
    
    // a와 b의 rows와 cols는 같으므로 두 행렬의 합인 c도 이와 같다.
    c.rows = a.rows;
    c.cols = c.cols;
    c.terms = 0;
    
    while (ca<a.terms && cb < b.terms){
        
        // 현재 값들이 어느 위치에 저장되어있는지 index를 나타낸다.
        int inda = a.data[ca].row * a.cols + a.data[ca].col;
        int indb = b.data[cb].row * b.cols + b.data[cb].col;
        
        // a의 index <  b의 index 이면 a 값을 c에 대입
        if(inda < indb) {
            c.data[cc++] = a.data[ca++];
        }
        
        // a의 index = b의 index 인 경우,
        else if (inda == indb){
            // 두 값의 합이 0이 아니면
            if ((a.data[ca].value+b.data[cb].value)!=0) {
                // 값이 존재하는 row와 col는 a와 b가 동일하므로 a값을 대입해줘도 무방하고
                c.data[cc].row = a.data[ca].row;
                c.data[cc].col = a.data[ca].col;
                // 값 자체는 a와 b를 더해줘야 한다.
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }
            // 두 값의 합이 0이면 다음으로 넘긴다.
            else{
                ca++;
                cb++;
            }
        }
        // a의 index > b의 index 이면 b 값을 c에 대입
        else
            c.data[cc++] = b.data[cb++];
    }
    // a나 b 중 하나의 행렬의 모든 값을 다 사용해 0만 남았을 경우에는 남은 부분을 다 c에 대입한다.
    for (;ca<a.terms;)
        c.data[cc++] = a.data[ca++];
    for (;cb<b.terms;)
        c.data[cc++] = b.data[cb++];
    c.terms = cc;
    return c;
}
