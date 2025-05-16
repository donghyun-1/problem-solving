// https://www.acmicpc.net/problem/1427
// 소트인사이드 (실버 5)
// 2025-05-17

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    cin >> s;

    vector<int> v;

    for (int i = 0; i < s.size(); i++) {
        v.push_back(s[i] - '0');
    }

    for (int i = 0; i < v.size(); i++) {
        int max = i;
        
        for (int j = i+1; j < v.size(); j++) {
            if (v[j] > v[max]) {
                max = j;
            }
        }

        int temp = v[i];
        v[i] = v[max];
        v[max] = temp;
    }

    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }

    return 0;
}