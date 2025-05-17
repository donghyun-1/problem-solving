// https://www.acmicpc.net/problem/1927
// 최소 힙 (실버 2)
// 2025-05-18

#include <iostream>
#include <queue>

using namespace std;

struct Compare {
    bool operator()(int a, int b) { // true면 b가 top();
        return a > b;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    // priority_queue<int, vector<int>, greater<int>> q;
    priority_queue<int, vector<int>, Compare> q;

    for (int i = 0; i < N; i++) {
        int op;
        cin >> op;

        if (op == 0) {
            if (q.empty()) {
                cout << "0\n";
            }
            else {
                cout << q.top() << "\n";
                q.pop();
            }
        }
        else {
            q.push(op);
        }
    }

    return 0;
}