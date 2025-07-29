// https://www.acmicpc.net/problem/9085
// 더하기 (브론즈 3)
// 2025-07-30

#include <iostream>

using namespace std;

int main()
{
    int T, N, num;
    
    cin >> T;

    for (int t = 0; t < T; t++) {
        cin >> N;

        int sum = 0;
        for (int i = 0; i < N; i++) {
            cin >> num;

            sum += num;
        }

        cout << sum << "\n";
    }

    return 0;
}