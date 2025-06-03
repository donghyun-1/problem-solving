// [S/W 문제해결 기본] 1일차 - View (D3)
// 2025-06-03

#include<iostream>

using namespace std;

int building[256][1005];        // 건물 보드 [건물높이][건물위치]
int building_h[1005];           // [건물위치] = 높이
int D[4] = {-1, -2, 1, 2};      // 왼쪽 두 칸, 오른쪽 두 칸
int N;

// 초기화
void init() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 1005; j++) {
            building[i][j] = 0;
        }
    }
}

// 입력
void input() {
    cin >> N;
    
    for (int i = 2; i < 2 + N; i++) {
        int h;
        cin >> h;
        building_h[i] = h;  // 건물 높이

        for (int j = 0; j < h; j++) {
            building[j][i] = 1;
        }
    }
}

// 조망권 확인
int check_view() {
    int ans = 0;

    for (int i = 2; i < 2 + N; i++) {
        int building_num = i;
        int building_height = building_h[i];

        for (int h = 0; h < building_height; h++) {
            bool check = true;

            for (int l = 0; l < 4; l++) {
                int side = building_num + D[l];   // 양 옆 확인
                if (building[h][side] == 1) {
                    check = false;
                }
            }

            if (check) ans++;
        }
    }

    return ans;
}

// 디버깅 용 출력
void print_building() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 15; j++) {
            cout << building[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
	int test_case;
	int T = 10;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int ans = 0;
		
        init();

        input();

        // print_building();

        ans = check_view();

        cout << "#" << test_case << " " << ans << "\n";
	}

	return 0;
}