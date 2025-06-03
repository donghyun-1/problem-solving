// https://www.acmicpc.net/problem/15652
// N과 M (4) (실버 3)
// 2025-06-03

#include <iostream>
#include <vector>

using namespace std;

vector<int> num;

void back_tracking(int start, int length, vector<int>& ans) {
    if (ans.size() == length) {
        for (int i = 0; i < length; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = start; i < num.size(); i++) {
        ans.push_back(num[i]);
        back_tracking(i, length, ans);
        ans.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        num.push_back(i);
    }

    vector<int> ans;
    back_tracking(0, M, ans);

    return 0;
}