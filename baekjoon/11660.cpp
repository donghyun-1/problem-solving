// https://www.acmicpc.net/problem/11660
// 구간 합 구하기 5 (실버 1)
// 2025-05-11

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> board(n+1, vector<int>(n+1));
    vector<vector<int>> sum(n+1, vector<int>(n+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
            
            sum[i][j] = sum[i][j-1] + board[i][j];
        }
    }

    int x1, y1, x2, y2;
    for (int i = 0; i < m; i++) {
        int ans = 0;
        cin >> x1 >> y1 >> x2 >> y2;

        for (int i = x1; i <= x2; i++) {
            ans += sum[i][y2] - sum[i][y1-1];
        }

        cout << ans << "\n";
    }

    return 0;
}