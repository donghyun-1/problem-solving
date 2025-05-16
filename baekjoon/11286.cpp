// https://www.acmicpc.net/problem/11286
// 절댓값 힙 (실버 1)
// 2025-05-17

#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct Compare {
    bool operator()(int a, int b) {
        if (abs(a) == abs(b)) {
            return a > b;               // true면 b가 top, false면 a가 top
        }
        else {
            return abs(a) > abs(b);     // abs(-1) > abs(2) false니깐 a가 top
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    priority_queue<int, vector<int>, Compare> pq;

    for (int i = 0; i < N; i++) {
        int cal;
        cin >> cal;

        if (cal == 0) {
            if (!pq.empty()) {
                cout << pq.top() << "\n";
                pq.pop();
            }
            else 
                cout << "0\n";
        }
        else if (cal != 0) {
            pq.push(cal);
        }
    }

    return 0;
}