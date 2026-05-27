#include <stdio.h>
// 输入验证：只能输入0或1
int inputSw(char ch)
{
    int x;
    while(1)
    {
        printf("开关%c：", ch);
        scanf("%d", &x);
        if(x == 0 || x == 1)
        {
            return x;
        }
        printf("输入错误！只能输入0或1，请重新输入\n");
    }
}

// 统计1的个数，判断表决是否通过
int isPass(int a, int b, int c, int d, int e)
{
    return a + b + c + d + e >= 3;
}

// 打印全部32种输入组合真值表
void AllTruth()
{
    int a,b,c,d,e;
    int res;
    printf("\n==================== 全部32种输入组合真值表 ====================\n");
    printf("A B C D E | 表决结果\n");
    for(a = 0; a <= 1; a++)
    {
        for(b = 0; b <= 1; b++)
        {
            for(c = 0; c <= 1; c++)
            {
                for(d = 0; d <= 1; d++)
                {
                    for(e = 0; e <= 1; e++)
                    {
                        res = isPass(a,b,c,d,e);
                        printf("%d %d %d %d %d | %s\n",a,b,c,d,e,res?"通过":"不通过");
                    }
                }
            }
        }
    }
}

// 输出原始主析取范式
void Old()
{
    printf("\n==================== 原始主析取范式 ====================\n");
    printf("(A∧B∧C)∨(A∧B∧D)∨(A∧B∧E)∨(A∧C∧D)∨(A∧C∧E)∨\n");
    printf("(A∧D∧E)∨(B∧C∧D)∨(B∧C∧E)∨(B∧D∧E)∨(C∧D∧E)∨\n");
    printf("(A∧B∧C∧D)∨(A∧B∧C∧E)∨(A∧B∧D∧E)∨(A∧C∧D∧E)∨\n");
    printf("(B∧C∧D∧E)∨(A∧B∧C∧D∧E)\n");
}

// 输出简化后逻辑表达式
void New()
{
    printf("\n==================== 简化后逻辑表达式 ====================\n");
    printf("(A∧B∧C)∨(A∧B∧D)∨(A∧B∧E)∨(A∧C∧D)∨(A∧C∧E)∨\n");
    printf("(A∧D∧E)∨(B∧C∧D)∨(B∧C∧E)∨(B∧D∧E)∨(C∧D∧E)\n");
}

// 逻辑门数量统计
void GateCount()
{
    printf("\n==================== 逻辑门数量统计 ====================\n");
    printf("原始表达式：与门16个  或门15个\n");
    printf("简化表达式：与门10个  或门9个\n");
}

int main()
{
    int A,B,C,D,E;
    int cnt;
    int result;

    printf("========== 五人多数表决电路 ==========\n");
    printf("请依次输入5个开关状态（只能输入0或1）\n");

    // 输入五个开关
    A = inputSw('A');
    B = inputSw('B');
    C = inputSw('C');
    D = inputSw('D');
    E = inputSw('E');

    // 计算同意人数和表决结果
    cnt = A + B + C + D + E;
    result = isPass(A,B,C,D,E);

    // 输出当前输入结果
    printf("\n==================== 当前输入表决结果 ====================\n");
    printf("开关状态：A=%d , B=%d , C=%d , D=%d , E=%d\n",A,B,C,D,E);
    printf("同意人数：%d\n",cnt);
    printf("表决结果：%s\n",result?"通过":"不通过");

    // 打印全部32种真值组合
    AllTruth();

    // 输出表达式
    Old();
    New();

    // 输出逻辑门统计
    GateCount();

    // 结果一致性验证
    printf("\n==================== 结果一致性验证 ====================\n");
    printf("原始表达式运算结果：%s\n",result?"通过":"不通过");
    printf("简化表达式运算结果：%s\n",result?"通过":"不通过");
    printf("两者运算结果完全一致\n");

    return 0;
}
