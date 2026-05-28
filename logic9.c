#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int graph[MAX][MAX];
int res[MAX][MAX];
int temp[MAX][MAX];
int n;

// 矩阵相乘：c = a * b
void mul(int a[][MAX], int b[][MAX], int c[][MAX])
{
    int i, j, k;
    int temp[MAX][MAX] = {0};
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            temp[i][j] = 0;
            for(k = 0; k < n; k++)
            {
                temp[i][j] = temp[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            c[i][j] = temp[i][j];
        }
    }
}

// 矩阵快速幂：计算m的p次幂，结果存在res中
void matrix_pow(int m[][MAX], int p)
{
    int i, j;
    int base[MAX][MAX];
    
    // 初始化结果矩阵为单位矩阵
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
                res[i][j] = 1;
            else
                res[i][j] = 0;
        }
    }
    
    // 复制base矩阵
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            base[i][j] = m[i][j];
        }
    }
    
    // 快速幂核心算法
    while(p > 0)
    {
        if(p % 2 == 1)  // 如果p是奇数
        {
            mul(res, base, res);  // res = res * base
        }
        mul(base, base, base);    // base = base * base
        p = p / 2;                // p右移一位
    }
}

// 输入图
void input_graph()
{
    int i, j;
    
    printf("请输入顶点数 n：");
    scanf("%d", &n);
    
    printf("请输入 %d 行 %d 列的邻接矩阵：\n", n, n);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
}

int main()
{
    int u, v, k;
    int i, j;
    
    // 1. 输入图
    input_graph();
    
    // 2. 输入查询参数
    printf("\n请输入起点u 终点v 长度k：");
    scanf("%d %d %d", &u, &v, &k);
    
    // 3. 验证顶点编号是否有效
    if(u < 0 || u >= n || v < 0 || v >= n)
    {
        printf("\n错误：顶点编号应在0到%d之间！\n", n-1);
        return 1;
    }
    
    // 4. 复制原始矩阵
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            temp[i][j] = graph[i][j];
        }
    }
    
    // 5. 计算矩阵的k次幂
    matrix_pow(temp, k);
    
    // 6. 输出结果
    printf("\n从 %d 到 %d 长度为 %d 的通路数：%d\n", u, v, k, res[u][v]);
    
    // 7. 可选：显示所有顶点对之间的通路数
    printf("\n所有顶点对之间长度为 %d 的通路数矩阵：\n", k);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
