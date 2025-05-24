// https://www.acmicpc.net/problem/20056
// 마법사 상어와 파이어볼 (골드 4)
// 2025-05-25

#include <iostream>
#include <vector>

#define MAX_N 55

using namespace std;

struct FireBall {
    int row, col, mass, speed, dir;
};

int N, M, K;
vector<FireBall> board[MAX_N][MAX_N];
vector<FireBall> fire;
int D[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

void input() {
    cin >> N >> M >> K;
    fire.resize(M);

    // 파이어 볼
    for (int i = 0; i < M; i++) {
        cin >> fire[i].row >> fire[i].col >> fire[i].mass >> fire[i].speed >> fire[i].dir;
    }
}

void fireball_move() {
    // 초기화
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            board[i][j].clear();
        }
    }

    for (int i = 0; i < fire.size(); i++) {
        int r = fire[i].row;
        int c = fire[i].col;
        int m = fire[i].mass;
        int s = fire[i].speed;
        int d = fire[i].dir;

        int nr = r + (D[d][0] * s % N), nc = c + (D[d][1] * s % N);
        if (nr > N) nr -= N;
        if (nc > N) nc -= N;
        if (nr < 1) nr += N;
        if (nc < 1) nc += N;

        board[nr][nc].push_back({nr, nc, m, s, d});
    }
}

void fireball_sum() {
    vector<FireBall> temp;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (board[i][j].size() == 0) continue;
            
            if (board[i][j].size() == 1) {
                temp.push_back(board[i][j][0]);
                continue;
            }

            int total_mass = 0;
            int total_speed = 0;
            bool total_odd = true;
            bool total_even = true;

            for (int n = 0; n < board[i][j].size(); n++) {
                total_mass += board[i][j][n].mass;
                total_speed += board[i][j][n].speed;

                if (board[i][j][n].dir % 2 == 0) {
                    total_odd = false;
                }
                else {
                    total_even = false;
                }
            }

            // 4개로 나누기
            total_mass /= 5;
            if (total_mass == 0) continue;

            total_speed /= board[i][j].size();

            if (total_odd || total_even) {
                temp.push_back({i, j, total_mass, total_speed, 0});
                temp.push_back({i, j, total_mass, total_speed, 2});
                temp.push_back({i, j, total_mass, total_speed, 4});
                temp.push_back({i, j, total_mass, total_speed, 6});
            }
            else {
                temp.push_back({i, j, total_mass, total_speed, 1});
                temp.push_back({i, j, total_mass, total_speed, 3});
                temp.push_back({i, j, total_mass, total_speed, 5});
                temp.push_back({i, j, total_mass, total_speed, 7});
            }
        }
    }
    fire = temp;
}

void simulation() {
    int sum = 0;

    for (int i = 0; i < K; i++) {
        fireball_move();

        fireball_sum();
    }

    for (int i = 0; i < fire.size(); i++) {
        sum += fire[i].mass;
    }

    cout << sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();

    simulation();

    return 0;
}