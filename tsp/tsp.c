#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    float x,y;
}City;

float cal_distance(City A, City B)
{
    float dx = A.x - B.x;
    float dy = A.y - B.y;
    return sqrtf(dx * dx + dy * dy);
}

float total_distance(City *cities,int *path, int n)
{
    float res = 0.0f;
    for(int i = 0; i < n -1 ;i ++)
    {
        res += cal_distance(cities[path[i]],cities[path[i + 1]]);
    }
    res += cal_distance(cities[path[n - 1]],cities[path[0]]);
    return res;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
float min(float a, float b)
{
    if(b > a)
    return a;
    else return b;
}

void dfs(City *cities, int *path, int n, int pos,float *res)
{
    if(pos == n)
    {
        //printf("debug ----%f",*res);
        *res = min(*res,total_distance(cities,path,n));
        return;
    }
    for(int i = pos;i < n;i ++)
    {
        swap(&path[pos],&path[i]);
        dfs(cities,path,n,pos + 1,res);
        swap(&path[pos],&path[i]);
    }
}


int main()
{
    City cities[12];
    int n = 0;
    while(n < 11 && fscanf(stdin, "%f, %f",&cities[n].x,&cities[n].y) == 2)
    {
        n ++;
    }
    if(n < 2)
    {
        printf("0.00\n");
        return 0;
    }
    int path[12];
    for(int i = 0;i < n;i ++)
    {
        path[i] = i;
    }
    float res = 1000000000;
    dfs(cities,path,n,0,&res);
    printf("%.2f\n",res);
    return 0;
}