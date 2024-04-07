#define DEBUG false
#define DEBUGS false
#define CHECK(X,Y,T) (X < 0 || X >= T || Y < 0 || Y >= T)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
//2150
/*
5 ≤ n ≤ 20
1 ≤ m ≤ 1000
1 ≤ k ≤ 20
1 ≤ c ≤ 10
*/
using namespace std;
int map[20][20], timer[20][20], spray[20][20];
int N, M, K, C;
int total = 0;
pair<int, int> mv[4] = {
	{0,1}, {0,-1}, {1,0}, {-1,0}
};
pair <int, int> mv2[4] = {
	{-1,-1}, {-1,1}, {1,1}, {1,-1}
};

void printMap(int m[20][20]) {
	cout << "=========" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}


void grow() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] <= 0) continue;

			int adjTreeCnt = 0;
			for (int x = 0; x < 4; x++) {
				int dx = i + mv[x].first, dy = j + mv[x].second;
				if (CHECK(dx, dy, N) || map[dx][dy] <= 0) continue;
				adjTreeCnt++;
			}
			map[i][j] += adjTreeCnt;
		}
	}
}

void treeFlush() {
	int tmpMap[20][20];
	memcpy(tmpMap, map, sizeof(tmpMap));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tmpMap[i][j] <= 0 || timer[i][j]) continue;

			int emptySpace = 0;
			for (int x = 0; x < 4; x++) {
				int dx = i + mv[x].first, dy = j + mv[x].second;
				if (CHECK(dx, dy, N) || tmpMap[dx][dy] || timer[dx][dy]) continue;
				emptySpace++;
			}
			if (!emptySpace) continue;

			int growCnt = tmpMap[i][j] / emptySpace;
			for (int x = 0; x < 4; x++) {
				int dx = i + mv[x].first, dy = j + mv[x].second;
				if (CHECK(dx, dy, N) || tmpMap[dx][dy] || timer[dx][dy]) continue;
				map[dx][dy] += growCnt;
			}
			
		}
	}
}

void spraying() {
	int dieTreeCnt = 0;
	int maxCnt = 0, smallX = N, smallY = N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] <= 0) {
#if DEBUG
				spray[i][j] = 0;
#endif
				continue;
			}

			dieTreeCnt = map[i][j];

			for (int x = 0; x < 4; x++) {
				for (int k = 1; k <= K; k++) {
					int dx = i + k*mv2[x].first, dy = j + k*mv2[x].second;
					if (CHECK(dx, dy, N) || map[dx][dy] <= 0) break;
					dieTreeCnt += map[dx][dy];

				}
			}

#if DEBUG
			spray[i][j] = dieTreeCnt;
#endif

			if ((dieTreeCnt > maxCnt) ||
				((dieTreeCnt == maxCnt) && (smallX > i)) ||
				((dieTreeCnt == maxCnt) && (smallX == i) && (smallY > j)) ) {

				maxCnt = dieTreeCnt;
				smallX = i;
				smallY = j;
			}
		}
	}

#if DEBUG	
	printMap(spray);
	cout << "maxCnt = " << maxCnt << " --> (" << smallX << ", " << smallY << ")" << endl;
#endif

	total += maxCnt;
	timer[smallX][smallY] = C + 1;
	map[smallX][smallY] = 0;
	for (int x = 0; x < 4; x++) {
		for (int k = 1; k <= K; k++) {
			int dx = smallX + k * mv2[x].first, dy = smallY + k * mv2[x].second;
			if (CHECK(dx, dy, N)) break;
			
			timer[dx][dy] = C + 1;
			if (map[dx][dy] > 0) {
				map[dx][dy] = 0;
			}
			else break;
		}
	}
	
}

void timerDown() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (timer[i][j]) timer[i][j]--;
		}
	}
}
void run() {
	for (int i = 0; i < M; i++) {
#if DEBUG
		cout << "+++++ " << i << " +++++" << endl;
#endif

		// 나무 성장
		grow();
#if DEBUG
		cout << "grow finish" << endl;
		printMap(map);
#endif
		// 번식
		treeFlush();
#if DEBUG
		cout << "tree flush finish" << endl;
		printMap(map);
#endif
		// 제초제 선정 및 나무 삭제
		spraying();
#if DEBUG
		cout << "spray flush finish" << endl;
		printMap(map);
#endif
		// 제초제 타이머 하락
		timerDown();
#if DEBUG
		cout << "Timer finish" << endl;
		printMap(timer);
#endif
	}
	cout << total;
}
int main(void)
{
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif
	cin >> N >> M >> K >> C;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

#if DEBUG
	cout << "init\n";
	printMap(map);
#endif

	run();
	return 0;
}