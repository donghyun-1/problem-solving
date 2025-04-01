// https://school.programmers.co.kr/learn/courses/30/lessons/43162

#include <string>
#include <vector>

using namespace std;

vector<bool> visited;

void dfs(int node, vector<vector<int>> network) {
    visited[node] = true;
    
    for (int i = 0; i < network[node].size(); i++) {
        if (network[node][i] && !visited[i]) {
            dfs(i, network);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    visited = vector<bool> (computers.size(), false);
    
    for (int i = 0; i < computers.size(); i++) {
        if (!visited[i]) {
            dfs(i, computers);
            answer++;
        }
    }
    
    return answer;
}