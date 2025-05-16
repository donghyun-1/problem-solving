// https://www.acmicpc.net/problem/1377
// 버블 소트 (골드 2)
// 2025-05-17

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<pair<int, int>> v(N);     // value, idx 

    for (int i = 0; i < N; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v.begin(), v.end());

    int max = 0;
    for (int i = 0; i < N; i++) {
        if (max < v[i].second - i) {
            max = v[i].second - i;
        }
    }

    cout << max + 1;

    return 0;
}