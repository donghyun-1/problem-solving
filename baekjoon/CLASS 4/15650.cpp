// https://www.acmicpc.net/problem/15650
// N과 M (2) (실버 3)
// 2025-06-02

#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;

void back_traking(int start, int length, vector<int>& ans) {
    if (ans.size() == length) {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    for (int i = start; i < arr.size(); i++) {
        ans.push_back(arr[i]);
        back_traking(i + 1, length, ans);
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

    for (int i = 0; i <= N; i++) {
        arr.push_back(i);
    }

    vector<int> ans;
    back_traking(1, M, ans);

    return 0;
}