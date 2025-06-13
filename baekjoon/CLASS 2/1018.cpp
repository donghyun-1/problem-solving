// https://www.acmicpc.net/problem/1018
// 체스판 다시 칠하기 (실버 4)
// 2025-06-12

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<char>> board;
vector<int> ans;

void input() {
    cin >> N >> M;

    board.resize(N, vector<char>(M));

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < M; j++) {
            board[i][j] = s[j];
        }
    }
}

int check(int row, int col) {
    int cnt1 = 0;
    int cnt2 = 0;

    for (int i = row; i < row+8; i++) {
        for (int j = col; j < col+8; j++) {
            // W로 시작할 때
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] == 'B') cnt1++;
            if (i % 2 == 1 && j % 2 == 1 && board[i][j] == 'B') cnt1++;

            if (i % 2 == 0 && j % 2 == 1 && board[i][j] == 'W') cnt1++;
            if (i % 2 == 1 && j % 2 == 0 && board[i][j] == 'W') cnt1++;

            // B로 시작할 때
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] == 'W') cnt2++;
            if (i % 2 == 1 && j % 2 == 1 && board[i][j] == 'W') cnt2++;

            if (i % 2 == 0 && j % 2 == 1 && board[i][j] == 'B') cnt2++;
            if (i % 2 == 1 && j % 2 == 0 && board[i][j] == 'B') cnt2++;
        }
    }

    return min(cnt1, cnt2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();

    for (int i = 0; i < N-7; i++) {
        for (int j = 0; j < M-7; j++) {
            ans.push_back(check(i, j));
        }
    }

    int min_v = *min_element(ans.begin(), ans.end());

    cout << min_v;

    return 0;
}