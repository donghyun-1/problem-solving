// https://www.acmicpc.net/problem/2164
// 카드2 (실버 4)
// 2025-05-17

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int N;
    cin >> N;

    queue<int> q;

    for (int i = 1; i <= N; i++) {
        q.push(i);
    }

    while (q.size() != 1) {
        q.pop();
        
        // 제일 아래로 옮기기
        q.push(q.front());
        q.pop();
    }

    cout << q.front();

    return 0;
}