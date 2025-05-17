// https://www.acmicpc.net/problem/2750
// 수 정렬하기 (브론즈 2)
// 2025-05-17

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
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    // 버블 정렬
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-1-i; j++) {
            if (v[j] > v[j+1]) {
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << v[i] << "\n";
    }

    return 0;
}