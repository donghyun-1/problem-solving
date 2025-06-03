// https://www.acmicpc.net/problem/15663
// N과 M (9) (실버 2)
// 2025-06-03
// 풀이1 : set 써서 중복 제거하기

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> num;
set<vector<int>> ans_set;
bool used[9] = { false };

void back_tracking(int start, int length, vector<int>& temp) {
    if (temp.size() == length) {
        ans_set.insert(temp);
        return;
    }

    for (int i = start; i < num.size(); i++) {
        if (used[i]) continue;

        used[i] = true;
        temp.push_back(num[i]);
        back_tracking(0, length, temp);
        temp.pop_back();
        used[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 입력
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        int a; 
        cin >> a;
        num.push_back(a);
    }

    // 정렬
    sort(num.begin(), num.end());

    // 백트래킹
    vector<int> temp;
    back_tracking(0, M, temp);

    // 출력
    vector<vector<int>> v(ans_set.begin(), ans_set.end());

    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}