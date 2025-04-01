// https://school.programmers.co.kr/learn/courses/30/lessons/42861

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

vector<int> parent, treeRank;

void init(int size) {
    parent.resize(size, -1);
    treeRank.resize(size, 0);
}

// 최상위 노드 찾기
int findParent(int node) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent[node]);     // 경로 압축
}

void unionSet(int nodeA, int nodeB) {
    int rootA = findParent(nodeA);
    int rootB = findParent(nodeB);
    
    if (rootA != rootB) {   // 부모 다르면 랭크 기반으로 합치기
        if (treeRank[rootA] > treeRank[rootB])
            parent[rootB] = rootA;
        else if (treeRank[rootA] < treeRank[rootB])
            parent[rootA] = rootB;
        else {
            parent[rootB] = rootA;
            treeRank[rootA]++;
        }
    }
}

int Kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());   // cost로 오름차순 정렬
    init(n);    // size 초기화
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;  // 자기 자신으로 초기화
    }
    
    int totalCost = 0, cnt = 0;
    for (int i = 0; i < edges.size(); i++) {
        if (findParent(edges[i].to) != findParent(edges[i].from)) {  // 같은 부모 아니면
            unionSet(edges[i].to, edges[i].from);
            totalCost += edges[i].cost;
            cnt++;
        }
        
        if (cnt == n-1) break;
    }
    
    return totalCost;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;  
    vector<Edge> edges;
    
    for (int i = 0; i < costs.size(); i++) {
        edges.push_back({costs[i][0], costs[i][1], costs[i][2]});
    }
    
    answer = Kruskal(n, edges);
    
    return answer;
}