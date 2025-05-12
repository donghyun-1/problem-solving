// https://www.acmicpc.net/problem/12891
// DNA 비밀번호 (실버 2)
// 2025-05-13

#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
int arr[4];                     // 최소 개수
int check[4] = {0, 0, 0, 0};    // 부분문자열 문자 개수

void Add(char c) {
    if (c == 'A') {
        check[0]++;
        if (check[0] == arr[0]) {
            cnt++;
        }
    }
    else if (c == 'C') {
        check[1]++;
        if (check[1] == arr[1]) {
            cnt++;
        }
    }
    else if (c == 'G') {
        check[2]++;
        if (check[2] == arr[2]) {
            cnt++;
        }
    }
    else if (c == 'T') {
        check[3]++;
        if (check[3] == arr[3]) {
            cnt++;
        }
    }
}

void Remove(char c) {
    if (c == 'A') {
        if (check[0] == arr[0]) {
            cnt--;
        }
        check[0]--;
    }
    else if (c == 'C') {
        if (check[1] == arr[1]) {
            cnt--;
        }
        check[1]--;
    }
    else if (c == 'G') {
        if (check[2] == arr[2]) {
            cnt--;
        }
        check[2]--;
    }
    else if (c == 'T') {
        if (check[3] == arr[3]) {
            cnt--;
        }
        check[3]--;
    }
}

int main() 
{
    int ans = 0;
    int s, p;
    string pw;

    cin >> s >> p >> pw;

    for (int i = 0; i < 4; i++) {
        cin >> arr[i];
        if (arr[i] == 0) cnt++;
    }

    // 인덱스 0 ~ p-1 까지
    for (int i = 0; i < p; i++) {
        Add(pw[i]);
    }

    if (cnt == 4) {
        ans++;
    }

    // 인덱스 p ~ s-1 까지
    for (int i = p; i < s; i++) {
        int j = i - p;

        Add(pw[i]);
        Remove(pw[j]);
        
        if (cnt == 4) {
            ans++;
        }
    }

    cout << ans;

    return 0;
}