// https://www.acmicpc.net/problem/11399
// ATM (실버 4)
// 2025-05-18

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    vector<int> v(N);
    vector<int> sum(N);
    int ans = 0;

    // 배열 입력
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    // 삽입 정렬
    for (int i = 1; i < N; i++) {
        int insert_idx = i;
        int insert_value = v[i];

        for (int j = i - 1; j >= 0; j--) {
            if (v[j] < v[i]) {
                insert_idx = j + 1;
                break;
            }

            if (j == 0) {
                insert_idx = 0;
            }
        }

        for (int j = i; j > insert_idx; j--) {
            v[j] = v[j-1];
        }

        v[insert_idx] = insert_value;
    }

    // 누적 합
    sum[0] = v[0];

    for (int i = 1; i < N; i++) {
        sum[i] = sum[i-1] + v[i];
    }

    for (int i = 0; i < N; i++) {
        ans += sum[i];
    }

    cout << ans;

    return 0;
}