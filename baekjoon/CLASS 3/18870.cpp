// https://www.acmicpc.net/problem/18870
// 좌표 압축 (실버 2)
// 2025-06-01

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<pair<int, int>> v;   // value, idx
    vector<int> ans(N);

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;

        v.push_back({num, i});
    }

    sort(v.begin(), v.end());

    int start = 0;
    ans[v[0].second] = 0;

    for (int i = 1; i < N; i++) {
        int idx = v[i].second;
        int value = v[i].first;

        if (value == v[i-1].first) {
            ans[idx] = start;
        }
        else if (value > v[i-1].first) {
            start++;
            ans[idx] = start;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}