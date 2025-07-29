// https://www.acmicpc.net/problem/24937
// SciComLove (2022) (브론즈 2)
// 2025-07-30

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int N;
    cin >> N;

    string s = "SciComLove";

    int idx = N % 10;

    s = s.substr(idx) + s.substr(0, idx);

    cout << s;

    return 0;
}