#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101 // 다항식의 최대차수를 100으로 하고 상수항도 있으니 +1

typedef struct{
    int degree;             //  다항식의 차수
    float coef[MAX_DEGREE]; //  다항식의 계수
} polynomial;

polynomial poly_add1(polynomial A, polynomial B);

int main(void)
{
    polynomial a = {5, {3,6,0,0,0,10}};
    polynomial b = {4,{7,0,5,0,1}};
    polynomial c;
    c = poly_add1(a, b);
}

polynomial poly_add1(polynomial A, polynomial B)
{
    polynomial C;
    int Apos=0, Bpos=0, Cpos=0;
    int degree_a = A.degree;
    int degree_b = B.degree;
    C.degree = MAX(A.degree,B.degree);
    
    while (Apos <= A.degree && Bpos <= B.degree)
    {
        // a의 차수가 더 크면 a의 값이 합 그 자체가 된다.
        if (degree_a > degree_b){
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        // 차수가 같으면 두 개를 더해준다.
        else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--;
            degree_b--;
        }
        // b의 차수가 더 크면 b의 값이 합 그 자체가 된다.
        else{
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}
