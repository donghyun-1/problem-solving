// https://www.acmicpc.net/problem/11726
// 2xn 타일링 (실버 3)
// 2025-05-18

#include <iostream>

#define M 10007

using namespace std;

int main()
{
    int n;
    cin >> n;

    long long dp[1001];

    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % M;
    }

    cout << dp[n] % M;

    return 0;
}