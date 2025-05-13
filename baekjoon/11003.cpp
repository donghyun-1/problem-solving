// https://www.acmicpc.net/problem/11003
// 최솟값 찾기 (플레티넘 5)
// 2025-05-13

#include <iostream>
#include <deque>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, L;   // 개수, 길이
    cin >> N >> L;

    deque<pair<int, int>> dq;   // <idx, value>;

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;

        while (dq.size() && dq.back().second > num) {
            dq.pop_back();
        }

        dq.push_back({i, num});

        if (dq.front().first <= i - L) {
            dq.pop_front();
        }

        cout << dq.front().second << " ";
    }

    return 0;
}