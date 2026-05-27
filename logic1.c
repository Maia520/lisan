#include <stdio.h>
#include <stdbool.h>
// 清空输入垃圾（防止输错字母卡死）
void clear()
{
    while(getchar() != '\n');
}

// 读取合法的 0 或 1（输错会一直提示重输）
int input(const char* tips)
{
    int num;
    int check;
    do
    {
        printf("%s (0/1): ", tips);
        check = scanf("%d", &num);
        
        // 如果不是数字 0 或 1，提示错误
        if(check != 1 || (num != 0 && num != 1))
        {
            printf("输入无效！请输入 0 或 1。\n");
            clear(); // 清空错误输入
        }
        else
        {
            break; // 输入正确，退出循环
        }
    }while(1);
    
    clear();
    return num;
}

// 打印自动真值表
void table()
{
    printf("\n========== 命题逻辑联结词真值表 ==========\n");
    printf("+-------+-------+-------+-------+-------+-------+-------+\n");
    printf("|   p   |   q   | 合取  | 析取  | 蕴含  | 等价  | 非p   |\n");
    printf("+-------+-------+-------+-------+-------+-------+-------+\n");

    int p, q;
    // 遍历 p = 0,1
    for(p = 0; p <= 1; p++)
    {
        // 遍历 q = 0,1
        for(q = 0; q <= 1; q++)
        {
            int he = p && q;     // 合取 p∧q
            int xi = p || q;     // 析取 p∨q
            int yun = (!p) || q; // 蕴含 p→q
            int deng = (p == q); // 等价 p?q
            int fei = !p;        // 非 p

            // 输出一行结果
            printf("|   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |\n",
            p, q, he, xi, yun, deng, fei);
        }
    }
    printf("+-------+-------+-------+-------+-------+-------+-------+\n");
}

// 手动输入 p、q 计算结果
void check()
{
    printf("\n===== 自定义命题真值验证 =====\n");
    
    // 输入 p 和 q
    int p = input("请输入命题 p 的值");
    int q = input("请输入命题 q 的值");

    // 计算五种运算
    int he = p && q;
    int xi = p || q;
    int yun = (!p) || q;
    int deng = (p == q);
    int fei = !p;

    // 输出结果
    printf("\n运算结果：\n");
    printf("  p合取q  = %d\n", he);
    printf("  p析取q  = %d\n", xi);
    printf("  p蕴含q  = %d\n", yun);
    printf("  p等价q  = %d\n", deng);
    printf("  非p     = %d\n", fei);
}

// 主函数（程序入口）
int main()
{
    printf("=== 离散数学实验：命题逻辑联结词 ===\n");
    
    table();  // 打印自动真值表
    check();  // 手动验证
    
    printf("\n程序结束。\n");
    return 0;
}
