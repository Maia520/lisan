#include <stdio.h>
#define MAX 10   // 宏观定义最大数组和矩阵不超过10 

// 简单函数名声明
void cart();       // 计算笛卡尔积
void calc();       // 关系矩阵复合运算
void show();       // 打印矩阵函数 

//定义全局二维数组，三个矩阵 
int m1[MAX][MAX], m2[MAX][MAX], res[MAX][MAX];

int main()
{
    int choose;//一直显示菜单，不退出就能一直用 
    while(1)
    {
        printf("==== 离散数学实验 ====\n");
        printf("1 笛卡尔积运算\n");
        printf("2 关系矩阵复合\n");
        printf("0 退出程序\n");
        printf("请输入选择：");
        scanf("%d",&choose);

        if(choose == 0)
            break;
        else if(choose == 1)
            cart();
        else if(choose == 2)
            calc();
    }
    return 0;
}

// 功能：计算集合笛卡尔积
void cart()
{
    int a[MAX], b[MAX];//定义两个数组存在集合AB元素 
    int len1, len2;
    int i,j;

    // 输入集合A
    printf("\n输入集合A元素个数：");
    scanf("%d",&len1);//len为两元素个数 
    printf("输入A的%d个整数：",len1);
    for(i=0; i<len1; i++)
    {
        scanf("%d",&a[i]);
    }

    // 输入集合B
    printf("输入集合B元素个数：");
    scanf("%d",&len2);
    printf("输入B的%d个整数：",len2);
    for(i=0; i<len2; i++)
    {
        scanf("%d",&b[i]);
    }

    // 输出笛卡尔积结果提示 
    printf("\n笛卡尔积结果：\n");
    for(i=0; i<len1; i++)//外层循环遍历A每个元素 
    {
        for(j=0; j<len2; j++)//内层循环遍历B每个元素 
        {
            printf("<%d,%d>  ",a[i],b[j]);
        }
    }
    printf("\n\n");
}

// 功自定义函数，mat是要打印的矩阵 ，row为行，col为列 
void show(int mat[MAX][MAX], int row, int col)
{
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("%d  ",mat[i][j]);
        }
        printf("\n");
    }
}

// 功能：关系矩阵复合逻辑运算
void calc()
{
    int r, n, c;//r矩阵1行数，n：矩阵1列数，矩阵2行数 ，c：矩阵2列数 
    int i,j,k;

    // 输入矩阵行列
    printf("\n输入矩阵1 行数 列数：");
    scanf("%d%d",&r,&n);
    printf("输入矩阵2 行数 列数：");
    scanf("%d%d",&n,&c);

    // 输入第一个01矩阵
    printf("输入矩阵1（只输0和1）：\n");
    for(i=0; i<r; i++)
        for(j=0; j<n; j++)
            scanf("%d",&m1[i][j]);

    // 输入第二个01矩阵
    printf("输入矩阵2（只输0和1）：\n");
    for(i=0; i<n; i++)
        for(j=0; j<c; j++)
            scanf("%d",&m2[i][j]);

    // 结果矩阵初始化为0
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            res[i][j] = 0;

    // 关系逻辑矩阵乘法
    for(i=0; i<r; i++)//遍历结果每一行 
    {
        for(j=0; j<c; j++)//遍历结果每一列 
        {
            for(k=0; k<n; k++)//中间进行比对 
            {
                // 只要同时为1，结果矩阵该位置为1 
                if(m1[i][k]==1 && m2[k][j]==1)
                {
                    res[i][j] = 1;
                    break;
                }
            }
        }
    }

    // 输出复合矩阵
    printf("\n复合关系矩阵：\n");
    show(res, r, c);
    printf("\n");
}
