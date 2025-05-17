// https://www.acmicpc.net/problem/1546
// 평균 (브론즈 1)
// 2025-05-10

#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    int n, max = 0;
    double sum = 0;
    vector<int> v;

    cin >> n;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        v.push_back(a);
        
        if (a > max) {
            max = a;
        }
    }

    for (int i = 0; i < n; i++) {
        sum += v[i] * 100.0 / max;
    }

    cout << sum / n;

    return 0;
}