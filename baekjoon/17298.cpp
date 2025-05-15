// https://www.acmicpc.net/problem/17298
// 오큰수 (골드 4)
// 2025-05-16

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> v;
    stack<int> st;

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;

        v.push_back(n);
    }

    vector<int> ans(N);
    st.push(0);

    for (int i = 1; i < N; i++) {
        while (!st.empty() && v[st.top()] < v[i]) {
            ans[st.top()] = v[i];
            st.pop();
        }

        st.push(i);
    }

    while (!st.empty()) {
        ans[st.top()] = -1;
        st.pop();
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}