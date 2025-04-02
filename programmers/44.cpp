// https://school.programmers.co.kr/learn/courses/30/lessons/12978

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// 다익스트라 사용해야함
// 각 노드별로 걸리는 시간 저장해논 다음에 K 이하인거 count 하기

int solution(int N, vector<vector<int> > road, int K) {
    int count = 0;
    vector<bool> visited(N+1, false);
    vector<pair<int, int>> graph[N+1];
    vector<int> distance(N+1, numeric_limits<int>::max());
    distance[1] = 0;
    
    // graph 입력
    for (auto e : road) {
        int a = e[0], b = e[1], cost = e[2];
        graph[a].push_back({b, cost});
        graph[b].push_back({a, cost});
    }
    
    // priority_queue<자료형, 내부 컨테이너, 비교 함수>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    heap.push({0, 1});  // 거리(비용): 0, 노드: 1
     
    while (!heap.empty()) {
        int dist = heap.top().first;
        int node = heap.top().second;
        heap.pop();
        
        if (visited[node]) continue;
        visited[node] = true;
        
        // 다음 노드 찾고 비용 계산
        for (auto next : graph[node]) {
            int next_node = next.first;
            int next_dist = next.second;
            int cost = dist + next_dist;
            
            // 다음 노드까지 비용 업데이트
            if (cost < distance[next_node]) {
                distance[next_node] = cost;
                heap.push({cost, next_node});
            }
        }
    }
    
    for (int i = 0; i < N+1; i++) {
        if (distance[i] <= K) count++;
    }

    return count;
}