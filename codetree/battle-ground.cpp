// https://www.codetree.ai/ko/frequent-problems/problems/battle-ground/description
// 2025-04-09 걸린 시간: 약 3시간 30분

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    int row, col, dir, init, gun_attack;
};

struct Gun {
    int p_num;
    vector<int> list;

    Gun() : list(1, 0) {};
};

int n, m, k;
vector<Player> player;
vector<vector<Gun>> board;
int D[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};      // 상 우 하 좌
vector<int> point;

// 플레이어 있는지 체크 함수
bool playerCheck(int r, int c) {
    if (board[r][c].p_num != 0)
        return true;
    else 
        return false;
}

// 총 줍기 함수
void getGun(int num, int r, int c) {
    sort(board[r][c].list.begin(), board[r][c].list.end(), greater<int> ());
    
    if (board[r][c].list[0] > player[num].gun_attack) {     // 땅에 있는게 더 쌔면 swap
        int temp = player[num].gun_attack;
        player[num].gun_attack = board[r][c].list[0];
        board[r][c].list[0] = temp;
    }
}

// 싸우기 함수
int fight(int num, int enemy_num, int r, int c) {
    int enemy_attack = player[enemy_num].init + player[enemy_num].gun_attack;
    int my_attack = player[num].init + player[num].gun_attack;

    if (enemy_attack > my_attack) {
        point[enemy_num] += enemy_attack - my_attack;
        return enemy_num;
    }
    else if (enemy_attack < my_attack) {
        point[num] += my_attack - enemy_attack;
        return num;
    }
    else {
        if (player[enemy_num].init > player[num].init) return enemy_num;
        else return num;
    }
}

// 진 사람 이동 (총 버리고 방향대로 이동)
void moveLooser(int num) {
    int curr_row = player[num].row;
    int curr_col = player[num].col;
    int curr_dir = player[num].dir;

    // 총 버리기
    board[curr_row][curr_col].list.push_back(player[num].gun_attack);
    player[num].gun_attack = 0;

    // 이동
    for (int i = 0; i < 4; i++) {
        int dir = (curr_dir + i) % 4;
        int nr = curr_row + D[dir][0], nc = curr_col + D[dir][1];
        if (nr < 0 || nr > n-1 || nc < 0 || nc > n-1) continue;
        if (playerCheck(nr, nc)) continue;
        
        player[num].row = nr;
        player[num].col = nc;
        player[num].dir = dir;
        board[nr][nc].p_num = num;

        // 총 줍기
        getGun(num, nr, nc);

        return;
    }
}

// 이긴 사람 총 바꾸기, 보드 갱신
void winnerGet(int num) {
    board[player[num].row][player[num].col].p_num = num;
    getGun(num, player[num].row, player[num].col);
}

// 플레이어 1명씩 이동 함수
void movePlayer(int num) {
    int curr_row = player[num].row;
    int curr_col = player[num].col;
    int curr_dir = player[num].dir;

    for (int i = 0; i < 2; i++) {
        int nr = curr_row + D[curr_dir][0], nc = curr_col + D[curr_dir][1];
        if (nr < 0 || nr > n-1 || nc < 0 || nc > n-1) {
            curr_dir = (curr_dir + 2) % 4;
            continue;
        }

        // 위치 업데이트
        player[num].row = nr;
        player[num].col = nc;
        player[num].dir = curr_dir;
        board[curr_row][curr_col].p_num = 0;

        if (!playerCheck(nr, nc)) {     // 플레이어 없으면 총 줍기
            getGun(num, nr, nc);
            
            board[nr][nc].p_num = num;  // 보드 갱신
        }
        else {                          // 있으면 싸우기
            int enemy_num = board[nr][nc].p_num;      // 상대 플레이어 번호
            int winner_num = fight(num, enemy_num, nr, nc);
            int looser_num;
            if (winner_num == num) looser_num = enemy_num;
            else looser_num = num;

            moveLooser(looser_num);
            winnerGet(winner_num);
        }

        return;
    }
}

int main()
{
    cin >> n >> m >> k;
    board.resize(n, vector<Gun>(n));
    player.resize(m+1);
    point.resize(m+1, 0);

    // 총 초기 위치
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v;
            cin >> v;
            board[i][j].list[0] = v;
            board[i][j].p_num = 0;
        }
    }

    // player 정보
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y >> player[i].dir >> player[i].init;
        player[i].row = x - 1;
        player[i].col = y - 1;

        board[x-1][y-1].p_num = i;
    }

    while (k--) {
        for (int i = 1; i <= m; i++) {
            movePlayer(i);
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << point[i] << " ";
    }

    return 0;
}