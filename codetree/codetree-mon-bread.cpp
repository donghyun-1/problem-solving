// https://www.codetree.ai/ko/frequent-problems/problems/codetree-mon-bread/description
// 2025-04-12 걸린 시간: ??

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int row, col, dist;
};

int n, m;
int D[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};       // 상, 좌, 우, 하
vector<vector<int>> board;
vector<Point> player;
vector<Point> store;

// 다음으로 움직일 좌표 구하기 (최단거리로 이동하며 이전 좌표를 저장 -> 거꾸로 탐색 -> 이전 좌표 == 시작 좌표)
Point getNextStep(int num) {      // bfs
    queue<Point> q;
    vector<vector<bool>> visited(n+1, vector<bool>(n+1, false));
    vector<vector<Point>> before(n+1, vector<Point>(n+1));

    int srcRow = player[num].row;
    int srcCol = player[num].col;
    int dstRow = store[num].row;
    int dstCol = store[num].col;

    q.push({srcRow, srcCol, 0});

    before[srcRow][srcCol] = {-1, -1, -1};
    visited[srcRow][srcCol] = true;

    while (!q.empty()) {
        int curr_row = q.front().row;
        int curr_col = q.front().col;
        int curr_dist = q.front().dist;
        q.pop();

        if (curr_row == dstRow && curr_col == dstCol) {
            int tr = dstRow;
            int tc = dstCol;

            while (1) {
                int br = before[tr][tc].row;
                int bc = before[tr][tc].col;

                if (br == srcRow && bc == srcCol) {
                    break;
                }

                tr = br;
                tc = bc;
            }

            return {tr, tc, before[tr][tc].dist + 1};
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr_row + D[i][0], nc = curr_col + D[i][1];
            if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
            if (board[nr][nc] == 2) continue;
            if (visited[nr][nc]) continue;
            visited[nr][nc] = true;
            before[nr][nc] = {curr_row, curr_col, curr_dist};

            q.push({nr, nc, curr_dist + 1});
        }

    }
}

// 시작 베이스캠프 찾기
Point getBaseCamp(int srcRow, int srcCol, int dist) {
    queue<Point> q;
    vector<vector<bool>> visited(n+1, vector<bool>(n+1, false));
    q.push({srcRow, srcCol, dist});

    while(!q.empty()) {
        int curr_row = q.front().row;
        int curr_col = q.front().col;
        int curr_dist = q.front().dist;
        q.pop();

        if (board[curr_row][curr_col] == 1) {
            board[curr_row][curr_col] = 2;
            return {curr_row, curr_col, curr_dist};
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr_row + D[i][0], nc = curr_col + D[i][1];
            if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
            if (board[nr][nc] == 2) continue;   // 막힘
            if (visited[nr][nc]) continue;
            visited[nr][nc] = true;

            q.push({nr, nc, curr_dist + 1});
        }
    }
}


int main()
{
    cin >> n >> m;
    board.resize(n+1, vector<int> (n+1));
    player.resize(m+1);
    store.resize(m+1);
    vector<Point> nextStep(m+1);

    // 보드 입력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }

    // 편의점 위치
    for (int i = 1; i <= m; i++) {
        cin >> store[i].row >> store[i].col;
    }

    int time = 0;
    while (1) {
        // 1. 다음으로 움직 일 좌표
        for (int i = 1; i <= time; i++) {
            if (i > m) {    // 플레이어 다 움직임
                break;
            }    
            if (player[i].row == store[i].row && player[i].col == store[i].col) {   // 이미 도착
                continue;
            }

            nextStep[i] = getNextStep(i);
        }

        // 2.
        int count = 0;
        for (int i = 1; i <= time; i++) {
            if (i > m) {    // 플레이어 다 움직임
                break;
            }    
            if (player[i].row == store[i].row && player[i].col == store[i].col) {   // 이미 도착
                count++;
                continue;
            }

            player[i].row = nextStep[i].row;
            player[i].col = nextStep[i].col;

            if (player[i].row == store[i].row && player[i].col == store[i].col) {   // 도착
                board[player[i].row][player[i].col] = 2;    // block
            }

        }

        if (count == m) {
            cout << time;
            break;
        }

        time++;

        // 3.
        if (time <= m) {
            Point p = getBaseCamp(store[time].row, store[time].col, 0);
            player[time].row = p.row;
            player[time].col = p.col;

            board[p.row][p.col] = 2;        // block
        }
    }

    return 0;
}