#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct Point {
    int row, col, dist;
    bool operator<(const Point& other) const {
        if (dist != other.dist) return dist > other.dist;
        if (row != other.row) return row > other.row;
        return col > other.col;
    }
};

int N;
vector<vector<int>> board;
int shark_size = 2;
int eat_count = 0;
int total_time = 0;
Point shark_pos;

// 상, 좌, 우, 하 (위쪽 먼저 보기 위해 순서 주의)
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

bool bfs() {
    queue<Point> q;
    bool visited[20][20] = {false};
    priority_queue<Point> fish_q;

    q.push({shark_pos.row, shark_pos.col, 0});
    visited[shark_pos.row][shark_pos.col] = true;

    while (!q.empty()) {
        Point curr = q.front(); q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = curr.row + dr[i];
            int nc = curr.col + dc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (visited[nr][nc]) continue;
            if (board[nr][nc] > shark_size) continue;

            visited[nr][nc] = true;
            q.push({nr, nc, curr.dist + 1});

            if (board[nr][nc] != 0 && board[nr][nc] < shark_size) {
                fish_q.push({nr, nc, curr.dist + 1});
            }
        }
    }

    // 먹을 수 있는 물고기 없음
    if (fish_q.empty()) return false;

    Point target = fish_q.top();
    board[target.row][target.col] = 0;
    total_time += target.dist;
    shark_pos = {target.row, target.col, 0};

    eat_count++;
    if (eat_count == shark_size) {
        shark_size++;
        eat_count = 0;
    }

    return true;
}

int main() {
    cin >> N;
    board.resize(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 9) {
                shark_pos = {i, j, 0};
                board[i][j] = 0; // 상어 위치 초기화
            }
        }
    }

    while (bfs());

    cout << total_time << '\n';
    return 0;
}
