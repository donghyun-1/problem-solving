// https://www.acmicpc.net/problem/1436
// 영화감독 숌 (실버 5)
// 2025-06-13

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int N;
    cin >> N;

    int num = 665;

    // N번 찾기
    for (int i = 0; i < N; i++) {
        while(1) {
            num++;

            string temp = to_string(num);

            // 찾았으면
            if (temp.find("666") != -1) {
                break;
            }
        }
    }

    cout << num;

    return 0;
}