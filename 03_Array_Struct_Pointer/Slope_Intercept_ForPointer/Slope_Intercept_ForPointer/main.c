#include <stdio.h>

typedef struct {
    int x;
    int y;
} PointType;

int get_line_parameter(PointType p1, PointType p2, float *slope, float *yintercept);


int main(void)
{
    PointType pt1 = {3,3}, pt2 = {6,6};
    float s,y;
    if (get_line_parameter(pt1, pt2, &s, &y) == -1){
        printf("error\n");
    }
    
    else {
        printf("기울기는 %.1lf, y절편은 %.1lf입니다.", s,y);
    }
}

int get_line_parameter(PointType p1, PointType p2, float *slope, float *yintercept)
{
    if (p1.x == p2.x) return -1;
    
    else{
        // 기울기 = y증가량 / x의 증가량
        *slope = (float)(p2.y - p1.y) / (float) (p2.x - p1.x);
        // y = a*x + b  -> b = y - a*x
        *yintercept = p1.y - (*slope) * p1.x;
        return 0;
    }
    
}
