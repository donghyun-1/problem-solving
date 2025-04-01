// https://school.programmers.co.kr/learn/courses/30/lessons/159993

#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int row, col, cnt;
};

int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int N, M;

Point findStartPoint(char s, vector<string>& maps) {
    for (int i = 0; i < maps.size(); i++) {
        for (int j = 0; j < maps[i].size(); j++) {
            if (maps[i][j] == s)
                return {i, j, 0};
        }
    }
    return {-1, -1, -1};
}

int bfs(char start, char end, vector<string>& maps) {
    bool visited[101][101] = {false};
    queue<Point> q;
    
    Point startPoint = findStartPoint(start, maps);
    q.push(startPoint);
    
    visited[startPoint.row][startPoint.col] = true;
    
    while(!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        if (maps[curr.row][curr.col] == end) {
            return curr.cnt;
        }
    
        for (int i = 0; i < 4; i++) {
            int nr = curr.row + D[i][0], nc = curr.col + D[i][1];
            if (nr < 0 || nr > N-1 || nc < 0 || nc > M-1) continue;
            if (maps[nr][nc] == 'X') continue;
            if (visited[nr][nc]) continue;
            visited[nr][nc] = true;

            q.push({nr, nc, curr.cnt+1});
        }
    }
    return -1;
}

int solution(vector<string> maps) {
    N = maps.size();
    M = maps[0].size();
    
    int lever = bfs('S', 'L', maps);
    if (lever == -1) return -1;
    
    int LeverToEnd = bfs('L', 'E', maps);
    
    return LeverToEnd == -1 ? -1 : lever + LeverToEnd;
}