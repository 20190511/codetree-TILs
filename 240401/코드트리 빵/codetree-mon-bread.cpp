//1023 ~ 1200
#define DEBUG false
#define	_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;


struct man {
	int x; //next 위치
	int y;
	bool finish;
};

int blocked[15][15], map[15][15];
int N, M;
int manCnt;
pair<int, int> manGo[31];

pair<int, int> bscmp[225];
int bscmpCnt = 0;
man mans[31];

pair<int, int> mv[4] = {
	{-1,0}, {0,-1}, {0,1}, {1,0}
};


void printMap2(int map[15][15]) {
	cout << "==========" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

void printMap(int t) {
	cout << "==========" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (blocked[i][j]) cout << "X {";
			else cout << "O {";
			for (int m = 1; m <= M && m < t; m++) {
				if (mans[m].x == i && mans[m].y == j)
					cout << m << " ";
			}
			cout << "} ";
		}
		cout << endl;
	}
}

void findBFS(int m) {
	pair<int, int> navi[15][15];
	
	int tmpMap[15][15];
	memset(tmpMap, 0, sizeof(tmpMap));
	queue<pair<int, int>> q;
	q.push({ mans[m].x, mans[m].y });

	tmpMap[mans[m].x][mans[m].y] = 1;
	bool breakFlag = false;
	//BFS
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int dx = mv[i].first + cx, dy = mv[i].second + cy;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || blocked[dx][dy] || tmpMap[dx][dy]) continue;


			tmpMap[dx][dy] = tmpMap[cx][cy] + 1;
			navi[dx][dy] = { cx,cy };
			q.push({ dx,dy });

			if (dx == manGo[m].first && dy == manGo[m].second) {
				breakFlag = true;
				break;
			}
			
		}
		if (breakFlag) break;
	}

#if DEBUG
	printMap2(tmpMap);
#endif
	//역추적
	int mx = manGo[m].first, my = manGo[m].second;
	int savedX = mx, savedY = my;
	while (mx != mans[m].x || my != mans[m].y) {
		savedX = mx, savedY = my;
		mx = navi[savedX][savedY].first, my = navi[savedX][savedY].second;
	}
	mans[m].x = savedX, mans[m].y = savedY;

#if DEBUG
	cout << m << "th man pos = " << savedX << ", " << savedY << endl;
#endif
	return;
}
void finds(int t) {
	for (int i = 1; i <= M && i < t; i++) {
		if (mans[i].finish) continue;
		findBFS(i);
	}
}

void move(int t) {
	for (int i = 1; i <= M && i < t; i++) {
		if (mans[i].finish) continue;
		if (mans[i].x == manGo[i].first && mans[i].y == manGo[i].second) {
			mans[i].finish = true;
			blocked[mans[i].x][mans[i].y] = true;
			manCnt--;
		}
	}
}

void mansCamp(int t) {
	if (t > M) return;
	
	//BFS 시작
	int tmpMap[15][15];
	memset(tmpMap, 0, sizeof(tmpMap));
	queue<pair<int, int>> q;
	q.push(manGo[t]);

	tmpMap[manGo[t].first][manGo[t].second] = 1;
	
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int dx = mv[i].first + cx, dy = mv[i].second + cy;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || blocked[dx][dy] || tmpMap[dx][dy]) continue;
			tmpMap[dx][dy] = tmpMap[cx][cy] + 1;
			q.push({ dx,dy });

		}
		
	}


#if DEBUG
	printMap2(tmpMap);
#endif

	int smallCnt = 0x7FFFFFFF, idx = -1;
	//baseCamp.erase(baseCamp.begin() + idx);

	for (int i = 0; i < bscmpCnt; i++) {
		int bx = bscmp[i].first, by = bscmp[i].second;
		if (bx == -1 || tmpMap[bx][by] > smallCnt || !tmpMap[bx][by]) continue;

		if (tmpMap[bx][by] < smallCnt) {
			idx = i;
			smallCnt = tmpMap[bx][by];
			continue;
		}

		if (bx > bscmp[idx].first) continue;
		if (bx < bscmp[idx].first) {
			smallCnt = tmpMap[bx][by];
			idx = i;
		}
		if (by > bscmp[idx].second) continue;
		if (by < bscmp[idx].second) {
			smallCnt = tmpMap[bx][by];
			idx = i;
		}
	}

#if DEBUG
	cout << "basecamp idx == " << idx << endl;
#endif
	
	mans[t].x = bscmp[idx].first;
	mans[t].y = bscmp[idx].second;
	mans[t].finish = false;
	blocked[mans[t].x][mans[t].y] = true;
	bscmp[idx] = { -1,-1 };
	//basecamp block

}

void run() {
	int i;
	for (i = 1; manCnt ; i++) {
#if DEBUG
		cout << "====== " << i << " ======" << endl;
#endif
		// 1. 최단 경로 찾기
		finds(i);
#if DEBUG
		cout << "mans pos change" << endl;
		printMap(i);
#endif
		// 2. 최단 경로로 모두 이동
		move(i);

#if DEBUG
		cout << "mans cnt = " << manCnt<<endl;
#endif

		mansCamp(i);
#if DEBUG
		cout << "3. mansCamp finish" << endl;
		printMap(i+1);
#endif
	}
	cout << i-1;
}
int main(void) {
#if DEBUG
	freopen("input.txt", "r", stdin);
#endif
	cin >> N >> M;
	manCnt = M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int check;
			cin >> check;
			if (check) {
				bscmp[bscmpCnt++] = { i,j };
			}
		}
	}
	
	for (int i = 1; i <= M; i++) {
		int a, b;
		cin >> a >> b;
		manGo[i].first = a - 1;
		manGo[i].second = b - 1;
	}

	mans[0].finish = true;
	run();
	return 0;
}