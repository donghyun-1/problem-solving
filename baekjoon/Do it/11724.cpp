// https://www.acmicpc.net/problem/11724
// 연결 요소의 개수 (실버 2)
// 2025-05-21

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> visited; 

void DFS(int v) {
    if (visited[v])
        return;

    visited[v] = true;
    // cout << v << "-";

    for (int i = 0; i < graph[v].size(); i++) {
        int n = graph[v][i];
        if (!visited[n]) {
            DFS(n);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, ans = 0;
    cin >> N >> M;

    graph.resize(N+1);
    visited.resize(N+1, false);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;

        // 양방향 그래프
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            ans++;
            DFS(i);
        }
    }

    cout << ans;

    return 0;
}
