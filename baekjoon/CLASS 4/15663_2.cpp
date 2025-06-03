// https://www.acmicpc.net/problem/15663
// N과 M (9) (실버 2)
// 2025-06-03
// 풀이2 : 마지막 숫자 비교하기

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> num;
vector<int> before;
bool used[9] = { false };

void back_tracking(int start, int length, vector<int>& temp) {
    if (temp.size() == length) {
        for (int i = 0; i < length; i++) {
            cout << temp[i] << " ";
        }
        cout << "\n";

        return;
    }

    int prev = -1; // 같은 깊이에서 중복 방지

    for (int i = start; i < num.size(); i++) {
        if (used[i]) continue;
        if (num[i] == prev) continue; // ex) 9 다음에 1, 7, 9 중 비교

        used[i] = true;
        temp.push_back(num[i]);
        prev = num[i];
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

    return 0;
}