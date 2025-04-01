// https://school.programmers.co.kr/learn/courses/30/lessons/1844

#include <vector>
#include <queue>
using namespace std;

struct Point {
    int row, col, cnt;
};

int N, M;
int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int bfs(int srcRow, int srcCol, int dstRow, int dstCol, vector<vector<int>>& maps) {
    bool visited[101][101] = {false};
    queue<Point> q;
    q.push({srcRow, srcCol, 1});
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        if (curr.row == N-1 && curr.col == M-1) {
            return curr.cnt;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = curr.row + D[i][0], nc = curr.col + D[i][1];
            if (nr < 0 || nr > N-1 || nc < 0 || nc > M-1) continue;
            if (maps[nr][nc] == 0) continue;
            if (visited[nr][nc]) continue;
            visited[nr][nc] = true;
            
            q.push({nr, nc, curr.cnt+1});
        }
    }
    return -1;
}

int solution(vector<vector<int>> maps)
{
    N = maps.size();
    M = maps[0].size();
    
    int answer = bfs(0, 0, N-1, M-1, maps);
    return answer;
}