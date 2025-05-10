// https://www.acmicpc.net/problem/11720
// 숫자의 합 (브론즈 4)
// 2025-05-10

#include <iostream>
#include <string>

using namespace std;

int main() 
{
    int n;
    int sum = 0;
    string s;

    cin >> n >> s;

    for (int i = 0; i < s.size(); i++) {
        sum += s[i] - '0';
    }

    cout << sum;
}