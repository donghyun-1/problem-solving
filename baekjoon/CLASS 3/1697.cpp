// https://www.acmicpc.net/problem/1697
// 숨박꼭질 (실버 1)
// 2025-05-31

#include <iostream>
#include <queue>

#define MAX 100001

using namespace std;

struct Point {
    int x, sec;
};

int bfs(int src, int dst) {
    bool visited[MAX] = {false};
    queue<Point> q;
    q.push({src, 0});

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == dst) {
            return curr.sec;
        }

        // x - 1
        if (curr.x - 1 >= 0 && !visited[curr.x - 1]) {
            visited[curr.x - 1] = true;
            q.push({curr.x - 1, curr.sec + 1});
        }

        // x + 1
        if (curr.x + 1 < MAX && !visited[curr.x + 1]) {
            visited[curr.x + 1] = true;
            q.push({curr.x + 1, curr.sec + 1});
        }

        // 2 * x
        if (curr.x * 2 < MAX && !visited[curr.x * 2]) {
            visited[curr.x * 2] = true;
            q.push({curr.x * 2, curr.sec + 1});
        }
    }
}

int main()
{
    int N, K;
    cin >> N >> K;

    cout << bfs(N, K);

    return 0;
}