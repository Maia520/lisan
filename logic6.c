#include <stdio.h>

// 辗转相除法求最大公约数
int gcd(int a, int b)
{
    int temp;
    // 转为正数计算，兼容负数输入
    if(a < 0)
        a = -a;
    if(b < 0)
        b = -b;
    // 边界：一数为0，公约数为另一个数
    while(b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 计算最小公倍数
int lcm(int a, int b)
{
    // 存在0则无最小公倍数
    if(a == 0 || b == 0)
    {
        return -1;
    }
    // 先除后乘避免数值溢出
    return a / gcd(a,b) * b;
}

// 输入合法性校验，只接收整数
int getNum()
{
    int num, flag;
    while(1)
    {
        flag = scanf("%d", &num);
        // 输入非数字，清空缓冲区重新输入
        if(flag != 1)
        {
            while(getchar() != '\n');
            printf("输入非法，请输入整数：");
        }
        else
        {
            break;
        }
    }
    return num;
}

int main()
{
    int m, n;
    int resGcd, resLcm;
    printf("====辗转相除法计算最大公约数与最小公倍数====\n");
    printf("请输入第一个整数：");
    m = getNum();
    printf("请输入第二个整数：");
    n = getNum();

    resGcd = gcd(m, n);
    resLcm = lcm(m, n);

    // 规范格式输出
    printf("GCD(%d,%d) = %d\n", m, n, resGcd);
    if(resLcm == -1)
    {
        printf("LCM(%d,%d) 无意义，数值包含0\n", m, n);
    }
    else
    {
        printf("LCM(%d,%d) = %d\n", m, n, resLcm);
    }

    return 0;
}
