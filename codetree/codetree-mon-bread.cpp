// https://www.codetree.ai/ko/frequent-problems/problems/codetree-mon-bread/description
// 2025-04-09 걸린 시간: 20분 + 

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Person {
    int srcRow, srcCol, dstRow, dstCol;
};

struct Point {
    int row, col, dist;

    // bool operator>(const Point& other) const {
    //     if (row == other.row) return col < other.col;
    //     return row < other.row;
    // }
};

int n, m;
vector<vector<int>> board;
vector<Person> person;
int D[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};   // 상, 좌, 우, 하


// 최단 거리 이동
Point bfs(int srcRow, int srcCol, int dstRow, int dstCol) {
    queue<Point> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<int>> dist(n, vector<int>(n, -1));

    q.push({srcRow, srcCol, 0});
    dist[srcRow][srcCol] = 0;
    visited[srcRow][srcCol] = true;

    while (!q.empty()) {
        int curr_row = q.front().row;
        int curr_col = q.front().col;
        int d = q.front().dist;
        q.pop();

        if (curr_row == dstRow && curr_col == dstCol) {
            return {curr_row, curr_col, dist[curr_row][curr_col]};
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr_row + D[i][0], nc = curr_col + D[i][1];
            if (nr < 0 || nr > n-1 || nc < 0 || nc > n-1) continue;
            if (visited[nr][nc]) continue;
            if (board[nr][nc] == -1) continue;
            
            visited[nr][nc] = true;
            dist[nr][nc] = d + 1;

            q.push({nr, nc, d + 1});
        }
    }

    return {-1, -1, -1};
}

// 1. 시작 베이스 캠프 찾기
void findBaseCamp() {

}


int main() 
{
    cin >> n >> m;
    board.resize(n, vector<int>(n));
    person.resize(m+1);

    // 보드 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];         // 1은 편의점
        }
    }

    // 가고 싶은 편의점
    for (int i = 1; i <= m; i++) {
        cin >> person[i].dstRow >> person[i].dstCol;
    }


    Point p = bfs(1, 0, person[1].dstRow, person[1].dstCol);
    cout << p.row << ", " << p.col << ", " << p.dist << "\n";

    Point a = bfs(3, 1, person[2].dstRow, person[2].dstCol);
    cout << a.row << ", " << a.col << ", " << a.dist << "\n";

    Point b = bfs(1, 4, person[3].dstRow, person[3].dstCol);
    cout << b.row << ", " << b.col << ", " << b.dist << "\n";

    Point c = bfs(4, 4, person[4].dstRow, person[4].dstCol);
    cout << c.row << ", " << c.col << ", " << c.dist << "\n";

    return 0;
}