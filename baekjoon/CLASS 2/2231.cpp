// https://www.acmicpc.net/problem/2231
// 분해합 (브론즈 2)
// 2025-06-12

#include <iostream>
#include <vector>
#include <string>

#define INF 1000001

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> ans(N+1, INF);

    for (int i = 1; i <= N; i++) {
        string s = to_string(i);
        int div_sum = 0;

        for (int i = 0; i < s.size(); i++) {
            div_sum += s[i] - '0';
        }

        div_sum += i;

        if (div_sum > N) continue;

        ans[div_sum] = min(ans[div_sum], i);
    }

    // 출력
    if (ans[N] == INF) 
        cout << "0";
    else 
        cout << ans[N];

    return 0;
}