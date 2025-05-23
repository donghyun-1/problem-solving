// https://www.acmicpc.net/problem/1929
// 소수 구하기 (실버 3)
// 2025-05-23

#include <iostream>

using namespace std;

bool checkPrime(int n) {
    if (n == 1) return false;
    if (n == 2) return true;
    
    for (int i = 3; i*i <= n; i+=2) {
        if (n % i == 0) 
            return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int M, N;
    cin >> M >> N;

    for (int i = M; i <= N; i++) {
        if (i > 2 && i % 2 == 0) continue;

        if (checkPrime(i)) {
            cout << i << "\n";
        }
    }

    return 0;
}