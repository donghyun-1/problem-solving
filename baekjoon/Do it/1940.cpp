// https://www.acmicpc.net/problem/1940
// 주몽 (실버 4)
// 2025-05-11 

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, m, cnt = 0;
    cin >> n >> m;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    int i = 0;
    int j = v.size() - 1;

    while (i < j) {
        if (v[i] + v[j] == m) {
            cnt++;
            j--;
            i++;
        }
        else if (v[i] + v[j] < m) {
            i++;
        }
        else if (v[i] + v[j] > m) {
            j--;
        }
    }

    cout << cnt;

    return 0;
}