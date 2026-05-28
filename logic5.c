#include <stdio.h>

#define MAX 100

// 检查输入是否合法
int check(int x)
{
    return x >= 2;
}

//质因数分解
void resolve(int n)
{
    int origin = n;
    int fac[MAX];
    int cnt = 0;
    int i = 2;
    int k;  // 变量提前定义，不在for里定义

    // 实验步骤：i*i <= n 循环
    while(i * i <= n)
    {
        if(n % i == 0)
        {
            fac[cnt++] = i;
            n = n / i;
        }
        else
        {
            i++;
        }
    }

    // 最后大于1就加入列表
    if(n > 1)
    {
        fac[cnt++] = n;
    }

    // 输出
    printf("%d = ", origin);
    for(k = 0; k < cnt; k++)
    {
        printf("%d", fac[k]);
        if(k != cnt - 1)
            printf(" × ");
    }
    printf("\n");
}

// 主函数
int main()
{
    int num;
    printf("===== 算术基本定理实验 =====\n");

    while(1)
    {
        printf("请输入>=2的正整数：");
        if(scanf("%d", &num) != 1)
        {
            while(getchar() != '\n');
            printf("输入非法！请重新输入\n");
            continue;
        }

        if(check(num))
        {
            resolve(num);
            break;
        }
        else
        {
            printf("必须>=2，请重输\n");
        }
    }

    return 0;
}
