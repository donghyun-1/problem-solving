// https://www.acmicpc.net/problem/20056
// 웰컴 키트 (브론즈 3)
// 2025-05-25

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, T, P;
    int t = 0;
    vector<int> tshirt(6, 0);

    // 입력
    cin >> N;
    for (int i = 0; i < 6; i++) {
        cin >> tshirt[i];
    }
    cin >> T >> P;

    // 티셔츠 묶음 구하기
    for (int i = 0; i < 6; i++) {
        if (tshirt[i] % T == 0) {
            t += tshirt[i] / T;
        }
        else {
            t += (tshirt[i] / T) + 1;
        }
    }

    cout << t << "\n";

    // 펜 묶음 구하기
    cout << N / P << " " << N % P;

    return 0;
}