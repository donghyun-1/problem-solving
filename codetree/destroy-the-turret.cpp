// https://www.codetree.ai/ko/frequent-problems/problems/destroy-the-turret/description
// 2025-04-12 걸린 시간: 7시 시작

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MIN (-1)
#define MAX (0x7fff0000)

using namespace std;

struct Point {
    int ar, ac, dr, dc;
};

struct RC {
    int row, col;
};

struct Info {
    int damage;
    int attack_time;
    bool attacked;
};

int n, m, k;
vector<vector<Info>> board;
int D[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};   // 우, 하, 좌, 상

Point getAD() {
    Point ret;
    int min = MAX;
    int max = MIN;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j].damage != 0) {
                // 가장 약한 포탑
                if (board[i][j].damage < min) {
                    min = board[i][j].damage;
                    ret.ar = i;
                    ret.ac = j;
                }
                else if (board[i][j].damage == min) {
                    if (board[i][j].attack_time > board[ret.ar][ret.ac].attack_time) {  // 가장 최근에 공격한 포탑
                        ret.ar = i;
                        ret.ac = j;
                    }
                    else if (board[i][j].attack_time == board[ret.ar][ret.ac].attack_time) {
                        if (i + j > ret.ar + ret.ac) {      // 열과 행의 합이 가장 큰 포탑
                            ret.ar = i;
                            ret.ac = j;
                        }
                        else if (i + j == ret.ar + ret.ac) {    // 열 값이 가장 큰 포탑
                            if (j > ret.ac) {
                                ret.ar = i;
                                ret.ac = j;
                            }
                        }
                    }
                }

                // 가장 강한 포탑
                if (board[i][j].damage > max) {
                    max = board[i][j].damage;
                    ret.dr = i;
                    ret.dc = j;
                }
                else if (board[i][j].damage == max) {
                    if (board[i][j].attack_time < board[ret.dr][ret.dc].attack_time) {  // 가장 옛날에 공격한 포탑
                        ret.dr = i;
                        ret.dc = j;
                    }
                    else if (board[i][j].attack_time == board[ret.dr][ret.dc].attack_time) {
                        if (i + j < ret.dr + ret.dc) {      // 열과 행의 합이 가장 작은 포탑
                            ret.dr = i;
                            ret.dc = j;
                        }
                        else if (i + j == ret.dr + ret.dc) {    // 열 값이 가장 작은 포탑
                            if (j < ret.dc) {
                                ret.dr = i;
                                ret.dc = j;
                            }
                        }
                    }
                }
            }
        }
    }

    board[ret.ar][ret.ac].damage += n + m;     // 공격자 버프
    return ret;
}

// 레이저 공격
bool raserAttack(int ar, int ac, int dr, int dc) {
    queue<RC> q;
    vector<vector<bool>> visited(n+1, vector<bool> (m+1, false));
    vector<vector<RC>> before(n+1, vector<RC> (m+1));
    q.push({ar, ac});

    visited[ar][ac] = true;

    while (!q.empty()) {
        int curr_row = q.front().row;
        int curr_col = q.front().col;
        q.pop();

        // 경로 도달 (포탑 조지기)
        if (curr_row == dr && curr_col == dc) {
            board[dr][dc].damage = board[dr][dc].damage - board[ar][ac].damage;

            if (board[dr][dc].damage < 0) {
                board[dr][dc].damage = 0;
            }

            board[dr][dc].attacked = true;
            board[ar][ac].attacked = true;      // 공격자도 예외처리

            int tr = dr;
            int tc = dc;

            while (1) {
                int br = before[tr][tc].row;
                int bc = before[tr][tc].col;

                if (br == ar && bc == ac) {
                    break;
                }

                board[br][bc].damage = board[br][bc].damage - (board[ar][ac].damage / 2);     // 경로 포탑 반토막
                board[br][bc].attacked = true;

                if (board[br][bc].damage < 0) {
                    board[br][bc].damage = 0;
                }

                tr = br;
                tc = bc;
            }

            // 공격 성공
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr_row + D[i][0], nc = curr_col + D[i][1];
            // if (nr < 1 || nr > n || nc < 1 || nc > m) continue;
            if (nr == n+1) nr = 1;
            if (nc == m+1) nc = 1;
            if (nr == 0) nr = n;
            if (nc == 0) nc = m;
            if (board[nr][nc].damage == 0) continue;
            if (visited[nr][nc]) continue;
            
            visited[nr][nc] = true;
            before[nr][nc] = {curr_row, curr_col};

            q.push({nr, nc});
        }
    }

    // 레이저 공격 실패
    return false;
}

// 포탄 공격
void bombardiloCrocodilo(int ar, int ac, int dr, int dc) {
    board[dr][dc].damage -= board[ar][ac].damage;

    if (board[dr][dc].damage < 0) {
        board[dr][dc].damage = 0;
    }

    board[dr][dc].attacked = true;
    board[ar][ac].attacked = true;      // 공격자도 예외처리
    
    // 8개 방향
    int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    for (int i = 0; i < 8; i++) {
        int nr = dr + dir[i][0], nc = dc + dir[i][1];
        if (nr == n+1) nr = 1;
        if (nc == m+1) nc = 1;
        if (nr == 0) nr = n;
        if (nc == 0) nc = m;
        if (board[nr][nc].damage == 0) continue;
        if (nr == ar && nc == ac) continue;         // 공격자 제외

        board[nr][nc].damage -= board[ar][ac].damage / 2;
        board[nr][nc].attacked = true;

        if (board[nr][nc].damage < 0) {
            board[nr][nc].damage = 0;
        }
    }

    return;
}



int main()
{
    cin >> n >> m >> k;
    board.resize(n+1, vector<Info>(m+1));

    // board 입력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j].damage;
            board[i][j].attack_time = 0;
            board[i][j].attacked = false;
        }
    }

    int time = 0;
    while (time != k) {
        time++;

        // 1. 공격자 선정
        Point p = getAD();

        // 2. 공격자의 공격 + 3. 포탑 부서짐
        if (!raserAttack(p.ar, p.ac, p.dr, p.dc)) {  // 레이저 공격 실패하면
            // 포탄 공격
            bombardiloCrocodilo(p.ar, p.ac, p.dr, p.dc);
        }
        
        // 공격 시간 업데이트
        board[p.ar][p.ac].attack_time = time;

        // 4. 포탑 정비
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (board[i][j].damage != 0) {
                    if (!board[i][j].attacked) {
                        board[i][j].damage++;
                    }
                    else {
                        board[i][j].attacked = false;   // 다시 초기화
                    }
                }
            }
        }

        // //debug
        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= m; j++) {
        //         cout << board[i][j].damage << " ";
        //     }
        //     cout << "\n";
        // }
    }

    // 최대값 출력
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j].damage != 0 && board[i][j].damage > ans) {
                ans = board[i][j].damage;
            }
        }
    }

    cout << ans;

    return 0;
}