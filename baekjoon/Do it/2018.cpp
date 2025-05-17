// https://www.acmicpc.net/problem/2018
// 수들의 합 5 (실버 5)
// 2025-05-11

#include <iostream>

using namespace std; 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, ans = 1;
    cin >> n;

    int start_idx = 1;
    int end_idx = 1;
    int sum = 1;

    while (end_idx != n) {
        if (sum == n) {
            ans++;
            end_idx++;
            sum += end_idx;
        }
        else if (sum < n) {
            end_idx++;
            sum += end_idx;
        }
        else if (sum > n) {
            sum -= start_idx;
            start_idx++;
        }
    }

    cout << ans;

    return 0;
}