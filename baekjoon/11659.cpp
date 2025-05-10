// https://www.acmicpc.net/problem/11659
// 구간 합 구하기 4 (실버 3)
// 2025-05-10

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> v_sum;
    int n, k;
    cin >> n >> k;

    v_sum.push_back(0);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v_sum.push_back(v_sum[i-1] + a);
    }

    for (int i = 0; i < k; i++) {
        int a, b;
        int sum = 0;
        cin >> a >> b;

        cout << v_sum[b] - v_sum[a-1] << "\n";
    }

    return 0;
}