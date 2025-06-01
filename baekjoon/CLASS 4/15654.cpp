// https://www.acmicpc.net/problem/15654
// N과 M (5) (실버 3)
// 2025-06-02

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> num;
vector<bool> used;

void back_tracking(int length, vector<int>& v) {
    if (v.size() == length) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < num.size(); i++) {
        if (used[i]) continue;

        used[i] = true;
        
        v.push_back(num[i]);
        back_tracking(length, v);
        v.pop_back();

        used[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;

    num.resize(N);
    used.resize(N, false);

    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }

    sort(num.begin(), num.end());

    vector<int> v;
    back_tracking(M, v);

    return 0;
}