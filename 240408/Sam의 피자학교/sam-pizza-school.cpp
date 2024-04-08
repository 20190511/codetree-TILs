//1108 ~ 1235 (회전 30분 초과 --> 다른 방법)
/*
* 1 ≤ n ≤ 100
0 ≤ k ≤ 5
1 ≤ (밀가루의 양) ≤ 3000
n은 4의 배수입니다.
*/
#define DEBUG	false
#define DEBUGS	false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
int s=0, e=1, h=1, minV = 3001, maxV = 0;
int N, K;
int map[100][100];
pair<int, int> mv[4] = {
	{0,1}, {1,0}
};

void printMap() {
	cout << "===========" << endl;
	for (int i = 0; i < h; i++) {
		for (int j = s; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}


int diffVal() {
	minV = 3001, maxV = 0;
	for (int i = 0; i < N; i++) {
		int v = map[0][i];
		if (minV > v) minV = v;
		if (maxV < v) maxV = v;
	}
#if DEBUG
	cout << "maxV = " << maxV << ", minV = " << minV << endl;
#endif
	return maxV - minV;
}

void smallUpdate() {
	for (int i = 0; i < N; i++)
		if (minV == map[0][i]) map[0][i]++;
}


void crawl() {
	int tmpMap[100][100];
	for (int hh = 3 ; e+h <= N; hh++, s = e, e += h, h = hh/2) {
#if DEBUG
		cout << "s = " << s << ", e = " << e << ", h = " << h << endl;
		printMap();
#endif

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < h; j++) {
				tmpMap[h - j - 1][i] = map[i][j + s];
				if (j+s == e) continue;
				map[i][j + s] = 0;
			}
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < h; j++) {
				if (hh % 2)
					map[i + 1][j + e] = tmpMap[i][j];
				else {
					if (i - 1 < 0) continue;
					map[i][j + e] = tmpMap[i][j];
				}
			}
		}
	}
}

void flatting() {
	int tmp[100];
	int cnt = 0;

	
	for (int j = s; j < e; j++) {
		for (int i = 0; i < h; i++) {
			if (i != 0 && j >= e) break;
			tmp[cnt++] = map[i][j];
			map[i][j] = 0;
		}
	}
	
	s = 0, e = 1, h = 1;
	for (int i = 0; i < cnt; i++) {
		map[0][i] = tmp[i];
	}
}
void press() {
	int tmpMap[100][100];
	memcpy(tmpMap, map, sizeof(tmpMap));

	for (int i = 0; i < h; i++) {
		for (int j = s; j < N; j++) {
			if (i != 0 && j >= e) break;

			int c = tmpMap[i][j];
			for (int x = 0; x < 2; x++) {
				int dx = mv[x].first + i, dy = mv[x].second + j;
				if (dx < 0 || dx >= h || dy < s || dy >= N) continue;
				if (dx != 0 && dy >= e) continue;
				
				int o = tmpMap[dx][dy];
				int diff = (o - c) / 5;
				
				map[dx][dy] -= diff;
				map[i][j] += diff;
			}
		}
	}

#if DEBUG
	cout << "press finish" << endl;
	printMap();
#endif

	flatting();
}

void doubling() {

	for (int i = 0, j = N-1; i < N / 2; i++, j--) {
		map[1][j] = map[0][i];
		map[0][i] = 0;
	}
	s = N / 2;
	h = 2;
#if DEBUG
	cout << "first doubling" << endl;
	printMap();
#endif
	
	for (int i = s, j = N-1; i < (s + (N - s) / 2); i++, j--) {

		map[3][j] = map[0][i];
		map[2][j] = map[1][i];
		map[0][i] = map[1][i] = 0;
	}
	s += ((N - s) / 2);
	e = N;
	h = 4;

#if DEBUG
	cout << "second doubling" << endl;
	printMap();
	cout << "s = " << s << ", e = " << e << ", h = " << h << endl;
#endif


}
void run() {
	int z = 1;
	for (; diffVal() > K; z++) {
#if DEBUG
		cout << "+++++ " << z << " +++++" << endl;
#endif
		// 밀가루 +1
		smallUpdate();
#if DEBUG
		cout << "plus powder finish" << endl;
		printMap();
#endif

		// 도우 말기
		crawl();
#if DEBUG
		cout << "crawl power finish" << endl;
		cout << "s = " << s << ", e = " << e << ", h = " << h << endl;
		printMap();
#endif
		// 도우 누르기
		press();
#if DEBUG
		cout << "flatting" << endl;
		printMap();
#endif
		// 도우 2번 반으로 접기
		doubling();
		// 도우 펴기
		press();
#if DEBUG
		cout << "flatting" << endl;
		printMap();
#endif
	}

	cout << z-1;
}
int main(void)
{

#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> map[0][i];

#if DEBUG
	printMap();
#endif
	run();
	return 0;
}