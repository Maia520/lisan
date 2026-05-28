#include<stdio.h>
#define MAX_N 10

// 函数名简单
int checkClose(int tab[MAX_N][MAX_N], int n);
int checkCombine(int tab[MAX_N][MAX_N], int n);
int findUnit(int tab[MAX_N][MAX_N], int n, int *unit);
int checkReverse(int tab[MAX_N][MAX_N], int n, int unit);

int main()
{
    int n;
    int table[MAX_N][MAX_N];
    int i,j;
    int closeFlag, combineFlag;
    int unitFlag, unitNum;
    int reverseFlag;

    printf("======== 代数系统群判定程序 ========\n");
    printf("请输入集合元素个数 n：");
    scanf("%d",&n);

    printf("请输入 %d 行 %d 列运算表：\n",n,n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&table[i][j]);
        }
    }

    printf("\n---------- 判定结果 ----------\n");

    // 1. 封闭性检查
    closeFlag = checkClose(table,n);
    if(closeFlag == 0)
    {
        printf("不满足封闭性，不是半群\n");
        return 0;
    }
    printf("1. 封闭性：满足\n");

    // 2. 结合律检查
    combineFlag = checkCombine(table,n);
    if(combineFlag == 0)
    {
        printf("不满足结合律，不是半群\n");
        return 0;
    }
    printf("2. 结合律：满足\n");
    printf("=> 该代数系统是【半群】\n\n");

    // 3. 找幺元
    unitFlag = findUnit(table,n,&unitNum);
    if(unitFlag == 0)
    {
        printf("不存在幺元，不是含幺半群\n");
        return 0;
    }
    printf("3. 幺元：存在，值为 %d\n",unitNum);
    printf("=> 该代数系统是【含幺半群】\n\n");

    // 4. 查逆元
    reverseFlag = checkReverse(table,n,unitNum);
    if(reverseFlag == 0)
    {
        printf("存在元素无逆元，不是群\n");
        return 0;
    }
    printf("4. 逆元：所有元素都存在逆元\n");
    printf("=> 该代数系统是【群】\n");

    return 0;
}

// 封闭性
int checkClose(int tab[MAX_N][MAX_N], int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(tab[i][j]<1 || tab[i][j]>n)
            {
                printf("反例：运算结果 %d 不在集合内\n",tab[i][j]);
                return 0;
            }
        }
    }
    return 1;
}

// 结合律
int checkCombine(int tab[MAX_N][MAX_N], int n)
{
    int a,b,c;
    int left, right;
    int ab, bc;

    for(a=1;a<=n;a++)
    {
        for(b=1;b<=n;b++)
        {
            for(c=1;c<=n;c++)
            {
                ab = tab[a-1][b-1];
                left = tab[ab-1][c-1];

                bc = tab[b-1][c-1];
                right = tab[a-1][bc-1];

                if(left != right)
                {
                    printf("反例：(%d*%d)*%d = %d，%d*(%d*%d) = %d\n",a,b,c,left,a,b,c,right);
                    return 0;
                }
            }
        }
    }
    return 1;
}

// 找幺元
int findUnit(int tab[MAX_N][MAX_N], int n, int *unit)
{
    int e,x;
    int flag;
    for(e=1;e<=n;e++)
    {
        flag=1;
        for(x=1;x<=n;x++)
        {
            if(tab[e-1][x-1]!=x || tab[x-1][e-1]!=x)
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {
            *unit = e;
            return 1;
        }
    }
    return 0;
}

// 查逆元
int checkReverse(int tab[MAX_N][MAX_N], int n, int unit)
{
    int x,y;
    int hasRev;
    for(x=1;x<=n;x++)
    {
        hasRev=0;
        for(y=1;y<=n;y++)
        {
            if(tab[x-1][y-1]==unit && tab[y-1][x-1]==unit)
            {
                hasRev=1;
                break;
            }
        }
        if(hasRev==0)
        {
            printf("反例：元素 %d 没有逆元\n",x);
            return 0;
        }
    }
    return 1;
}
