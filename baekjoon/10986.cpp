// https://www.acmicpc.net/problem/10986
// 나머지 합 (골드 3)
// 2025-05-11

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, ans = 0;
    cin >> n >> m;

    vector<long> sum(n, 0);
    vector<long> c(m, 0);

    cin >> sum[0];
    for (int i = 1; i < n; i++) {
        int temp;
        cin >> temp;

        sum[i] = temp + sum[i-1];
    }

    // 구간합 나머지 구하기 
    for (int i = 0; i < n; i++) {
        int remainder = sum[i] % m;

        if (remainder == 0) {
            ans++;
        }

        c[remainder]++;
    }

    // 나머지 같은거 끼리 2개 뽑기 (3개면 3C2)
    // s[i] % m == s[j] % m 이면 (s[j] - s[i]) % m == 0
    for (int i = 0; i < m; i++) {
        if (c[i] > 1) {
            ans += c[i] * (c[i]-1) / 2;
        }
    }

    cout << ans;

    return 0;
}