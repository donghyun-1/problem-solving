// https://www.codetree.ai/ko/frequent-problems/problems/destroy-the-turret/description
// 2025-04-12 걸린 시간: 7시 시작

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF (0x7fff0000)
#define MIN 0

using namespace std;

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

// 누가 더 약한가
bool isWeak(RC a, RC b) {
    if (board[a.row][a.col].damage != board[b.row][b.col].damage) {
        return board[a.row][a.col].damage < board[b.row][b.col].damage;
    }

    if (board[a.row][a.col].attack_time != board[b.row][b.col].attack_time) {
        return board[a.row][a.col].attack_time > board[b.row][b.col].attack_time;
    }

    if (a.row + a.col != b.row + b.col) {
        return a.row + a.col > b.row + b.col;
    }

    return a.col > b.col;
}

// 공격자
RC getWeakestTower() {
    RC ret = {0, 0};

    board[0][0].damage = INF;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j].damage == 0) continue;

            RC tmp = {i, j};
            if (isWeak(tmp, ret) == true) {     // tmp가 더 작으면
                ret = tmp;
            }
        }
    }

    return ret;
}

// 방어자
RC getStrongestTower(RC at) {
    RC ret = {0, 0};

    board[0][0].damage = MIN;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j].damage == 0) continue;
            if (i == at.row && j == at.col) continue;   // 공격자 제외

            RC tmp = {i, j};
            if (isWeak(tmp, ret) == false) {     // tmp가 더 크면
                ret = tmp;
            }
        }
    }

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

    for (int i = 1; i <= k; i++) {
        // 1. 공격자 선정
        RC attacker = getWeakestTower();
        RC defender = getStrongestTower(attacker);

        // defender 없음
        if (defender.row == 0 && defender.col == 0)
            break;
        
        // 2. 공격자 버프
        board[attacker.row][attacker.col].damage += (n + m);

        // 2. 공격자의 공격 + 3. 포탑 부서짐
        if (!raserAttack(attacker.row, attacker.col, defender.row, defender.col)) {  // 레이저 공격 실패하면
            // 포탄 공격
            bombardiloCrocodilo(attacker.row, attacker.col, defender.row, defender.col);
        }
        
        // 공격 시간 업데이트
        board[attacker.row][attacker.col].attack_time = i;

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