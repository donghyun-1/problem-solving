// https://www.acmicpc.net/problem/1253
// 좋다 (골드 4)
// 2025-05-11

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, cnt = 0;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        int k = v[i];
        int start_idx = 0;
        int end_idx = n-1;

        while (start_idx < end_idx) {
            if (v[start_idx] + v[end_idx] == k) {
                if (start_idx != i && end_idx != i) {
                    cnt++;
                    break;
                }
                else if (start_idx == i) {
                    start_idx++;
                }
                else if (end_idx == i) {
                    end_idx--;
                }
            }
            else if (v[start_idx] + v[end_idx] < k) {
                start_idx++;
            }
            else if (v[start_idx] + v[end_idx] > k) {
                end_idx--;
            }
        }
    }

    cout << cnt;

    return 0;
}