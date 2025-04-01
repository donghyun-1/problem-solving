// https://school.programmers.co.kr/learn/courses/30/lessons/43162

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int parent[201];

int findParent(int node) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent[node]);
}

void unionSet(int nodeA, int nodeB) {
    int rootA = findParent(nodeA);
    int rootB = findParent(nodeB);
    
    if (rootA != rootB) {
        parent[rootB] = rootA;
    }
}


int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (computers[i][j]) {
                unionSet(i, j);     // 네트워크 연결
            }
        }
    }
    
    unordered_map<int, bool> net_map;
    for (int i = 0; i < n; i++) {
        int root = findParent(i);   // 노드마다 최상위 부모 찾기
        
        if (!net_map[root]) {   // 기존에 없으면
            answer++;
            net_map[root] = true;
        }
    }
    
    return answer;
}