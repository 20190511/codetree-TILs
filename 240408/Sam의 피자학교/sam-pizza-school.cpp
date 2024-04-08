#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
//0930
#include <iostream>
#include <cstring>
using namespace std;

int map[100][100];
int tmpMap[100][100];
int N, K;
int s=0, e=1, h=1;
int minV, maxV;

void printMap() {
	cout << "-----" << endl;
	for (int i = 0; i < h; i++) {
		for (int j = s; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}
int diff() {
	minV = 3001, maxV = 0;
	for (int i = 0; i < N; i++) {
		minV = min(minV, map[0][i]);
		maxV = max(maxV, map[0][i]);
	}

	return maxV - minV;
}

void increaseBread() {
	for (int i = 0; i < N; i++) {
		if (minV == map[0][i]) map[0][i]++;
	}
}

void rotateMap(int sz, int s) {
	
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			tmpMap[sz - j - 1][i] = map[i][j+s];
			if (i == 0 && j+s >= e) continue;
			map[i][j + s] = 0;
		}
	}

}
void crawl() {
	int prevH = 1;
	int hh;
	for (hh = 3, s = 0, e = 1, h = hh / 2; h+e < N; hh++, s = e, e += h, h = hh / 2) {

#if DEBUG
		cout << "h = " << h << ", s = " << s << ", e = " << e << ", prevH = " << prevH << endl;
		printMap();
#endif
		
		rotateMap(h, s);
		for (int i = h-prevH, i2 = 1; i < h; i++, i2++) {
			for (int j = 0; j < h; j++) {
				map[i2][j + e] = tmpMap[i][j];
			}
		}
		prevH = h;
	}
}

pair<int, int> mv[2] = {
	{1,0}, {0,1}
};

void flatting() {
	int cnt = 0;
	for (int j = s ; j < N; j++) {
		for (int i = 0; i < h; i++) {
			if (i != 0 && j >= e) break;
			
			tmpMap[0][cnt++] = map[i][j];
			map[i][j] = 0;
		}
	}

	for (int i = 0; i < cnt; i++)
		map[0][i] = tmpMap[0][i];

	s = 0, e = 1, h = 1;
}

void push() {
	memcpy(tmpMap, map, sizeof(tmpMap));
	
	for (int j = s; j < N; j++) {
		for (int i = 0; i < h; i++) {
			if (i != 0 && j >= e) break;
			int c = tmpMap[i][j];
			for (int x = 0; x < 2; x++) {
				int dx = i + mv[x].first, dy = j + mv[x].second;
				if (dx < 0 || dx >= h || dy < s || dy >= N) continue;
				if (dx != 0 && dy >= e) continue;
				int o = tmpMap[dx][dy];

				int diff = (o - c)/5;

				map[i][j] += diff;
				map[dx][dy] -= diff;
			}
		}
	}

#if DEBUG
	cout << "push finish" << endl;
	printMap();
#endif

	flatting();
#if DEBUG
	cout << "flat finish" << endl;
	printMap();
#endif

}

void doubling() {
	for (int i = 0; i < N / 2; i++) {
		map[1][N-i-1] = map[0][i];
		map[0][i] = 0;
	}

	s = N / 2;
	h = 2;
#if DEBUG
	cout << "1> double finish" << endl;
	printMap();
#endif

	for (int i = s, i2= N-1; i < N/4 + N/2; i++, i2--) {
		map[2][i2] = map[1][i];
		map[3][i2] = map[0][i];
		map[0][i] = map[1][i] = 0;
	}
	s += N / 4;
	h = 4;
	e = N;
#if DEBUG
	cout << "2> double finish" << endl;
	printMap();
#endif
}
void run() {
	int timer = 0;
	for (; diff() > K; timer++) {
#if DEBUG
		cout << "+++++ Timer = " << timer << " +++++" << endl;
		printMap();
#endif
		// 1. 빵 도우 증가
		increaseBread();
#if DEBUG
		cout << "Bread Increase Finish" << endl;
		printMap();
#endif
		// 2. 도우 말기
		crawl();
#if DEBUG
		cout << "Crawl Finish" << endl;
		cout << "h = " << h << ", s = " << s << ", e = " << e << endl;
		printMap();
#endif
		// 3. 도우 누르기
		push();
		// 4. 도우 2번 반 접기
		doubling();
		// 5. 도우 누르기 X2
		push();
		//최솟값 증가
	}
	cout << timer;
}
int main(void) {
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> map[0][i];
	}
	run();
	return 0;
}