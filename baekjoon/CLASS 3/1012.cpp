// https://www.acmicpc.net/problem/1012
// 유기농 배추 (실버 2)
// 2025-06-02

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int x, y;
};

int N, M, K;
vector<vector<int>> board;
vector<vector<bool>> visited;
int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void input() {
    cin >> M >> N >> K;

    board.resize(N, vector<int>(M));
    visited.resize(N, vector<bool>(M));
    
    for (int i = 0; i < N; i++) {
        board[i].assign(M, 0);
        visited[i].assign(M, false);
    }

    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;

        board[y][x] = 1;
    }
}

void bfs(int x, int y) {
    queue<Point> q;
    q.push({x, y});

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int dx = curr.x + D[i][0], dy = curr.y + D[i][1];
            if (dx < 0 || dx > M-1 || dy < 0 || dy > N-1) continue;
            if (visited[dy][dx]) continue;
            if (board[dy][dx] == 0) continue;

            visited[dy][dx] = true;
            q.push({dx, dy});
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        int cnt = 0;

        input();

        // bfs
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!visited[i][j] && board[i][j] == 1) {
                    bfs(j, i);
                    cnt++;
                }
            }
        }

        cout << cnt << "\n";
    }
    
    return 0;
}