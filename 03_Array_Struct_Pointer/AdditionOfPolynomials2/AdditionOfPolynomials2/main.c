#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

struct {
    float coef; //계수
    int expon;  //차수
} terms[MAX_TERMS] = {
    {8,3},{7,1},{1,0},{10,3},{3,2},{1,0}
    // 8x^3+7x+1 과 10x^3+3x^2+1 의 합
};
int avail=6; // 배열에 이미 6개의 원소가 들어와있으므로 6부터 시작한다.

// 두 개의 정수를 비교
char compare(int a, int b)
{
    if (a>b) return '>';
    else if (a==b) return '=';
    else return '<';
}

// 배열에 항을 입력하는 함수
void attach(float coef, int expon)
{
    if (avail > MAX_TERMS){
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
// As : A의 시작 index
// Ae : A의 끝 index
// 나머지도 마찬가지
{
    float tempcoef;
    *Cs = avail; // 다항식의 합이 저장될 새로운 위치 지정
    while (As<=Ae && Bs <= Be)
        switch (compare(terms[As].expon,terms[Bs].expon)){
            case '>': // A의 차수 > B의 차수
                attach(terms[As].coef, terms[As].expon);
                As++;
                break;
            case '=':
                tempcoef = terms[As].coef + terms[Bs].coef;
                if (tempcoef) // 두 수의 합이 0일 경우에는 추가해줄 필요 x
                    attach(tempcoef, terms[As].expon);
                As++;
                Bs++;
                break;
            case '<':
                attach(terms[Bs].coef, terms[Bs].expon);
                Bs++;
                break;
        }
    
    // A항과 B항의 남은 부분들을 뒤에다가 추가해준다.
    for (;As<=Ae;As++)
        attach(terms[As].coef,terms[As].expon);
    for (;Bs<=Be;Bs++)
        attach(terms[Bs].coef,terms[Bs].expon);
    *Ce = avail - 1;
}

int main(void)
{
    int Cs, Ce;
    poly_add2(0,2,3,5,&Cs,&Ce);
    // 두 다항식의 시작값과 끝값, 새로운 다항식이 들어갈 주소를 넘겨준다.
}

