// https://www.acmicpc.net/problem/19236
// 청소년 상어 (골드 1)

/*
    DFS + 백트래킹 사용 (가능한 경우 모두 실행해봐야하기 때문)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int row, col, cost, dir;
};


int total_eat = 0;
vector<vector<Point>> board;

int D[8][2] = {
    {-1, 0},    //  ↑    (1)
    {-1, -1},   //  ↖   (2)
    {0, -1},    //  ←    (3)
    {1, -1},    //  ↙   (4)
    {1, 0},     //  ↓    (5)
    {1, 1},     //  ↘   (6)
    {0, 1},     //  →    (7)
    {-1, 1}     //  ↗   (8)
};

// 물고기 swap 함수
void swap(Point& a, Point& b) {
    int temp_cost = a.cost;
    int temp_dir = a.dir;
    
    a.cost = b.cost;
    a.dir = b.dir;
    
    b.cost = temp_cost;
    b.dir = temp_dir;
}

// 물고기 이동 함수
void moveFishes(int fish, vector<vector<Point>>& board, Point curr_shark) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Point p = board[i][j];

            if (p.cost != 0 && p.cost == fish) {
                for (int k = 0; k < 8; k++) {
                    int dir = (p.dir-1 + k) % 8;                                      // 방향
                    int nr = p.row + D[dir][0], nc = p.col + D[dir][1];             
                    if (nr < 0 || nr > 3 || nc < 0 || nc > 3) continue;               // 범위 오바
                    if (nr == curr_shark.row && nc == curr_shark.col) continue;       // 상어 있음
                    
                    board[i][j].dir = dir + 1;                  // 방향 업뎃
                    swap(board[i][j], board[nr][nc]);           // swap

                    return;
                }
            }
        }
    }
}

void dfs(vector<vector<Point>> board, Point curr_shark, int eat_sum) {
    // 물고기 먹기
    int shark_dir = board[curr_shark.row][curr_shark.col].dir;      // 다음 방향
    eat_sum += board[curr_shark.row][curr_shark.col].cost;          // 물고기 +
    board[curr_shark.row][curr_shark.col].cost = 0;                 // 먹고 0 초기화
    

    // 업데이트
    total_eat = max(eat_sum, total_eat);

    // 1. 물고기 이동
    for (int i = 1; i <= 16; i++) {
        moveFishes(i, board, curr_shark);
    }

    // 2. 상어 이동
    for (int i = 1; i < 4; i++) {
        int nr = curr_shark.row + i * D[shark_dir-1][0], nc = curr_shark.col + i * D[shark_dir-1][1];
        if (nr < 0 || nr > 3 || nc < 0 || nc > 3) continue;
        if (board[nr][nc].cost == 0) continue;

        // 이동 가능한 곳
        dfs(board, {nr, nc, 0, 0}, eat_sum);
    }
}


int main()
{
    int cost, dir;
    board.resize(4, vector<Point>(4));

    // 4x4 board 입력
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> cost >> dir;
            board[i][j] = {i, j, cost, dir};
        }
    }

    // 시작
    dfs(board, {0, 0, 0, 0}, 0);

    cout << total_eat;

    return 0;
}