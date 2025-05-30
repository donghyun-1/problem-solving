// https://www.acmicpc.net/problem/11279
// 최대 힙 (실버 2)
// 2025-05-31

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    priority_queue<int> maxHeap;
    int x;

    for (int i = 0; i < N; i++) {        
        cin >> x;

        if (x == 0) {
            if (maxHeap.empty()) {
                cout << 0 << "\n";
            }
            else {
                cout << maxHeap.top() << "\n";
                maxHeap.pop();
            }
        }
        else {
            maxHeap.push(x);
        }
    }

    return 0;
}