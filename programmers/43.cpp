// https://school.programmers.co.kr/learn/courses/30/lessons/92343

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> tree;
vector<int> comp;   // info랑 같음
vector<bool> visited;

int answer = 0;

void dfs(vector<int> curr) {
    int sheep = 0, wolf = 0;
    
    for (int i : curr) {
        if (comp[i] == 1) wolf++;
        else sheep++;
    }
    
    // wolf가 같거나 크면 종료
    if (sheep <= wolf) return;
    
    // 양 마리 수 업데이트
    answer = max(sheep, answer);
    
    for (int i = 0; i < curr.size(); i++) {
        int node = curr[i];
        
        // 현재 노드랑 인접한 노드 순회
        for (int g : tree[node]) {
            if (visited[g]) continue;
            visited[g] = true;
            curr.push_back(g);
            dfs(curr);
            
            curr.pop_back();      // 백트래킹
            visited[g] = false;
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int n = info.size();
    visited.resize(n, false);
    tree.resize(n);
    comp = info;
    
    // 인접 노드 저장
    for (auto e : edges) {
        tree[e[0]].push_back(e[1]);
    }
    
    visited[0] = true;  // 시작 노드 방문 처리
    dfs({0});
    
    return answer;
}