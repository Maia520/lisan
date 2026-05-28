#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==========================
// 安全乘法：避免int溢出
// 功能：计算 (a*b) % mod，防止中间结果溢出
// ==========================
int mul_mod(int a, int b, int mod)
{
    int ans = 0;
    a = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
            ans = (ans + a) % mod;
        a = (a * 2) % mod;
        b = b / 2;
    }
    return ans;
}

// ==========================
// 快速幂取模（防溢出版）
// 功能：计算 (a^b) % mod
// ==========================
int pow_mod(int a, int b, int mod)
{
    int ans = 1;
    a = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
            ans = mul_mod(ans, a, mod);
        b = b / 2;
        a = mul_mod(a, a, mod);
    }
    return ans;
}

// ==========================
// 最大公约数 gcd(a,b)
// ==========================
int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// ==========================
// 无指针实现模逆元计算
// ==========================
int inv(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1)
    {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

// ==========================
// Miller-Rabin素性检测
// ==========================
int is_prime(int n)
{
    int i, a, m, j, k;
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    m = n - 1;
    k = 0;
    while (m % 2 == 0)
    {
        m /= 2;
        k++;
    }
    for (i = 0; i < 5; i++)
    {
        a = rand() % (n - 3) + 2;
        int x = pow_mod(a, m, n);
        if (x == 1 || x == n - 1) continue;
        for (j = 0; j < k - 1; j++)
        {
            x = pow_mod(x, 2, n);
            if (x == n - 1) break;
        }
        if (j == k - 1) return 0;
    }
    return 1;
}

// ==========================
// 随机生成素数（范围缩小，避免n过大溢出）
// ==========================
int create_prime()
{
    int num;
    while (1)
    {
        num = rand() % 200 + 100; // 生成100~300之间的素数，避免n溢出
        if (is_prime(num))
            return num;
    }
}

// ==========================
// RSA全局参数
// ==========================
int p, q, n, phi, e, d;
int dp, dq, qinv;

// ==========================
// 生成密钥
// ==========================
void rsa_create_key()
{
    p = create_prime();
    q = create_prime();
    n = p * q;
    phi = (p - 1) * (q - 1);
    e = 17; // 改用小e，避免计算溢出
    while (gcd(e, phi) != 1)
        e++;
    d = inv(e, phi);
    // CRT预计算参数
    dp = d % (p - 1);
    dq = d % (q - 1);
    qinv = inv(q, p);
}

// ==========================
// RSA加密函数
// ==========================
int rsa_encrypt(int m)
{
    return pow_mod(m, e, n);
}

// ==========================
// 传统解密函数
// ==========================
int rsa_decrypt(int c)
{
    return pow_mod(c, d, n);
}

// ==========================
// CRT优化解密函数
// ==========================
int rsa_crt(int c)
{
    int m1 = pow_mod(c, dp, p);
    int m2 = pow_mod(c, dq, q);
    int t = (m1 - m2) % p;
    if (t < 0) t += p;
    t = mul_mod(t, qinv, p);
    return m2 + t * q;
}

// ==========================
// 主函数
// ==========================
int main()
{
    srand(time(0));
    rsa_create_key();

    printf("===== RSA性能对比实验 =====\n");
    printf("随机生成素数p = %d\n", p);
    printf("随机生成素数q = %d\n", q);
    printf("模数n = %d\n", n);
    printf("公钥e = %d\n", e);
    printf("私钥d = %d\n\n", d);

    // 手动输入明文
    int plain;
    printf("请输入测试明文（<%d）：", n);
    scanf("%d", &plain);
    int cipher = rsa_encrypt(plain);
    printf("加密得到密文：%d\n\n", cipher);

    // 单次运算循环次数
    int run_cnt = 50000;
    // 整体重复运行次数，用于取平均值
    int test_times = 5;
    int i, j;
    double sum1 = 0.0, sum2 = 0.0;
    double avg1, avg2;

    // 多次重复测试，累加总耗时
    for (j = 0; j < test_times; j++)
    {
        clock_t s1 = clock();
        for (i = 0; i < run_cnt; i++)
            rsa_decrypt(cipher);
        clock_t e1 = clock();
        sum1 += (double)(e1 - s1) / CLOCKS_PER_SEC;

        clock_t s2 = clock();
        for (i = 0; i < run_cnt; i++)
            rsa_crt(cipher);
        clock_t e2 = clock();
        sum2 += (double)(e2 - s2) / CLOCKS_PER_SEC;
    }

    // 计算平均耗时
    avg1 = sum1 / test_times;
    avg2 = sum2 / test_times;

    // 解密结果校验
    int res1 = rsa_decrypt(cipher);
    int res2 = rsa_crt(cipher);
    printf("传统解密结果：%d\n", res1);
    printf("CRT优化解密结果：%d\n", res2);

    if (plain == res1 && plain == res2)
        printf("\n数据校验：解密结果与原始明文一致\n");
    else
        printf("\n数据校验：解密出错\n");

    // 输出平均性能数据
    printf("\n共进行%d轮测试，每轮运算%d次\n", test_times, run_cnt);
    printf("传统解密平均耗时：%.4f 秒\n", avg1);
    printf("CRT解密平均耗时：%.4f 秒\n", avg2);

    if (avg2 > 0)
    {
        double speed_rate = avg1 / avg2;
        printf("CRT解密加速倍数：%.2f 倍\n", speed_rate);
    }
    else
        printf("运算量级较小，理论加速3倍左右\n");

    system("pause");
    return 0;
}
