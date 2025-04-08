// https://www.acmicpc.net/problem/19237
// 2025-04-09 걸린 시간: 약 5시간

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    int row, col, dir;
    bool life;
    vector<vector<int>> prio_dir;                   //  방향 우선 순위

    Info() : prio_dir(5, vector<int>(4, 0)) {};     // [방향][우선순위]
};

struct Smell {
    int value;              // 칸에 들어있는 값
    int shark_num;          // 냄새 상어 번호
    int shark_k;            // 냄새 남은 시간
};

int N, K;
int total_second = 0;
vector<vector<Smell>> board;
vector<Info> shark;
int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};   // 상, 하, 좌, 우

// 냄새 뿌리기 함수
void smelling(int num, int curr_row, int curr_col) {    // 상어 번호, row, col
    board[curr_row][curr_col].shark_num = num;
    board[curr_row][curr_col].shark_k = K;
}

// 상어 한마리 이동 함수
void moveShark(int num) {
    int curr_row = shark[num].row;
    int curr_col = shark[num].col;
    int curr_dir = shark[num].dir;

    // 냄새 없는 칸으로 이동
    for (int i = 0; i < 4; i++) {
        int p = shark[num].prio_dir[curr_dir][i];       // 방향 우선 순위 ex) 1이면 D[0]
        int nr = curr_row + D[p-1][0], nc = curr_col + D[p-1][1];
        
        if (nr < 0 || nr > N-1 || nc < 0 || nc > N-1) continue;     // 범위 오바
        if (board[nr][nc].shark_num != 0) continue;     // 이미 냄새 있음 (자기 냄새 포함)

        if (board[curr_row][curr_col].value == num)
            board[curr_row][curr_col].value = 0;        // 이전 위치 초기화 (내꺼면)

        // 이동
        if (board[nr][nc].value == 0) {                 // 아무도 없음
            board[nr][nc].value = num;
        }
        else {   // 다른 상어 있음
            int other = board[nr][nc].value;
            if (other < num) {                  // 다른 상어보다 약한 경우
                shark[num].life = false;        // 죽기
            }
            else if (other > num) {             // 내가 더 쌔면
                board[nr][nc].value = num;      // 값만 변경 (어차피 상대는 이동할 예정)
            }
        }

        if (shark[num].life) {
            shark[num].row = nr;        // 이동 후 row
            shark[num].col = nc;        // 이동 후 col
            shark[num].dir = p;         // 이동 후 dir
        }

        return;
    }

    // 그런 칸 없음 -> 자기 냄새 칸으로 이동
    for (int i = 0; i < 4; i++) {
        int p = shark[num].prio_dir[curr_dir][i];
        int nr = curr_row + D[p-1][0], nc = curr_col + D[p-1][1];
        
        if (nr < 0 || nr > N-1 || nc < 0 || nc > N-1) continue;     // 범위 오바
        if (board[nr][nc].shark_num != num) continue;     // 자기 냄새 아니면 pass

        if (board[curr_row][curr_col].value == num)
            board[curr_row][curr_col].value = 0;

        // 이동
        if (board[nr][nc].value == 0) {          // 아무도 없음
            board[nr][nc].value = num;
        }
        else {   // 다른 상어 있음
            int other = board[nr][nc].value;
            if (other < num) {                  // 다른 상어보다 약한 경우
                shark[num].life = false;        // 죽기
            }
            else if (other > num) {             // 내가 더 쌔면
                board[nr][nc].value = num;      // 값만 변경 (어차피 상대는 이동할 예정)
            }
        }

        if (shark[num].life) {
            shark[num].row = nr;        // 이동 후 row
            shark[num].col = nc;        // 이동 후 col
            shark[num].dir = p;         // 이동 후 dir
        }

        return;
    }
}

// 냄새 업데이트
void updateSmell() {
    // 냄새 처리
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int n = board[i][j].value;
            // 상어 칸 냄새 --
            if (board[i][j].shark_k != 0) {
                board[i][j].shark_k--;
            }

            // 시간 다 되면 없어지기
            if (board[i][j].shark_k == 0) {
                board[i][j].shark_num = 0;
                board[i][j].value = 0;
            }
        }
    }
}


int main()
{
    int M;
    cin >> N >> M >> K;

    board.resize(N, vector<Smell>(N));
    shark.resize(M+1);

    // 보드 입력 + 상어 번호
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int value;
            cin >> value;
            board[i][j].shark_num = 0;
            board[i][j].shark_k = 0;
            board[i][j].value = value;

            if (value != 0) {
                shark[value].row = i;
                shark[value].col = j;
                shark[value].life = true;
            }
        }
    }

    // 초기 방향
    for (int i = 1; i <= M; i++) {
        cin >> shark[i].dir;
    }

    // 각 상어 방향 별 우선 순위
    for (int i = 1; i <= M; i++) {              // 상어 번호
        for (int j = 1; j <= 4; j++) {          // 방향(상, 하, 좌, 우)
            for (int k = 0; k < 4; k++) {       // 우선 순위
                cin >> shark[i].prio_dir[j][k];
            }
        }
    }

    /*
    1. 현재 위치 냄새 뿌리기
    2. 상어 이동 + 죽기
    3. 이전 자리 냄새 --
    */

    while (total_second < 1000) {
        for (int i = 1; i <= M; i++) {
            if (shark[i].life) smelling(i, shark[i].row, shark[i].col);
        }

        for (int i = 1; i <= M; i++) {
            if (shark[i].life) moveShark(i);
        }

        updateSmell();

        total_second++;

        // 1번 빼고 다 죽으면
        int flag = 1;
        for (int i = 2; i <= M; i++) {
            if (shark[i].life == true)
                flag = 0;
        }

        if (flag == 1) {
            cout << total_second;
            
            return 0;
        }
    }

    cout << "-1";

    return 0;
}