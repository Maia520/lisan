#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// 定义一个最大数组，足够存下 0~2000 的数（满足实验 1000-2000 需求）
#define MAX 2001
// 标记数组：is_prime[i] = true 表示数字 i 是素数
bool is_prime[MAX];

// 函数1：基础埃氏筛法，筛出 0~max 内所有素数
void ai_shai(int max)
{
    int i, j;
    
    // 1. 初始化：先假设所有数都是素数
    for (i = 0; i <= max; i++)
    {
        is_prime[i] = true;
    }
    
    // 2. 0和1不是素数，直接标记
    is_prime[0] = false;
    is_prime[1] = false;
    
    // 3. 埃氏筛核心：从2开始，标记倍数为非素数
    // 优化：只需要循环到 根号max 就够了
    for (i = 2; i <= sqrt(max); i++)
    {
        // 如果 i 是素数，就把它的倍数全部标记为非素数
        if (is_prime[i] == true)
        {
            // 从 i*2 开始，每次加 i，遍历所有倍数
            for (j = i * 2; j <= max; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
}

// 函数2：输出区间 [start, end] 内的素数
void print_shai(int start, int end)
{
    int i;
    int count = 0;    // 素数总数
    int min, max;     // 最小、最大素数
    int hang = 0;     // 每行输出10个
    
    printf("\n===== 区间 [%d, %d] 内的素数 =====\n", start, end);
    
    // 遍历区间，找出素数
    for (i = start; i <= end; i++)
    {
        if (is_prime[i] == true)
        {
            count++;
            // 记录最小素数
            if (count == 1)
                min = i;
            // 记录最大素数
            max = i;
            
            // 输出素数
            printf("%d\t", i);
            hang++;
            
            // 每10个换一行
            if (hang % 10 == 0)
                printf("\n");
        }
    }
    
    // 输出统计信息
    printf("\n\n区间内素数总数：%d 个\n", count);
    printf("最小素数：%d\n", min);
    printf("最大素数：%d\n", max);
}

// 主函数
int main()
{
    int start, end;
    // 默认区间 1000 ~ 2000
    start = 1000;
    end = 2000;
    
    printf("===== 埃氏筛法求区间素数 =====\n");
    printf("默认区间：1000 - 2000\n");
    printf("是否修改区间？(1=修改，0=默认)：");
    
    int xuanze;
    scanf("%d", &xuanze);
    
    // 如果用户选择修改区间
    if (xuanze == 1)
    {
        printf("请输入起始值：");
        scanf("%d", &start);
        printf("请输入结束值：");
        scanf("%d", &end);
    }
    
    // 1. 先筛出 0~2000 所有素数
    ai_shai(2000);
    // 2. 输出指定区间的素数
    print_shai(start, end);
    
    return 0;
}
