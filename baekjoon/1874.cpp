// https://www.acmicpc.net/problem/1874
// 스택 수열 (실버 2)
// 2025-05-16

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    stack<int> st;
    vector<char> v;
    int idx = 1;
    st.push(1);
    v.push_back('+');
    int flag = 0;

    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;

        if (st.empty()) {
            idx++;
            st.push(idx);
            v.push_back('+');
        }

        while (1) {
            if (num > st.top()) {
                idx++;
                st.push(idx);
                v.push_back('+');
            }
            else if (num == st.top()) {
                st.pop();
                v.push_back('-');
                break;
            }
            else if (num < st.top()) {
                flag = 1;
                break;
            }
        }

        if (flag) {
            break;
        }
    }

    if (flag) {
        cout << "NO";
    }
    else {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << "\n";
        }
    }

    return 0;
}