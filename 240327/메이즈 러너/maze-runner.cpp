//1100
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#define INF	0x7FFFFFFF
using namespace std;

int map[10][10], man[10][10];
pair<int, int> man_pos[10], ex;
pair<int, int> mv[4] = {
	{-1,0}, {1,0}, {0,-1}, {0,1}
};
int N, M, K; //M=참가자 수
int man_cnt, moving = 0;


void printMap(int map[10][10]) {
	cout << "==============" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (ex.first == i && ex.second == j)
				cout << "X ";
			else
				cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int getN1(int ax, int ay, int bx, int by) {
	int tx = ax < bx ? bx - ax : ax - bx;
	int ty = ay < by ? by - ay : ay - by;
	return tx + ty;
}

void shortMove (int mCnt) {
	
	if (man_pos[mCnt].first == -1 || man_pos[mCnt].second == -1)
		return;

	int mx = man_pos[mCnt].first, my = man_pos[mCnt].second;
	int ox = ex.first, oy = ex.second;

	int curPath = getN1(ox, oy, mx, my);
	int mvNum = -1;

	for (int i = 0; i < 4; i++) {
		int dx = mx + mv[i].first, dy = my + mv[i].second;
		if (dx < 0 || dx >= N || dy < 0 || dy >= N || map[dx][dy]) continue;
		
		int nextPath = getN1(ox, oy, dx, dy);
		if (curPath > nextPath) {
			curPath = nextPath;
			mvNum = i;
		}
	}

	//이동
	if (mvNum == -1) return;

	moving++;
	int dx = mx + mv[mvNum].first, dy = my + mv[mvNum].second;
	man[mx][my]--;
	//출구도착
	if (curPath == 0) {
		man_cnt--;
		man_pos[mCnt] = { -1,-1 };
		return;
	}

	man[dx][dy]++;
	man_pos[mCnt] = { dx,dy };

}
void move() {
	for (int i = 0; i < M; i++) {
		shortMove(i);
	}
}

void rotateG(int a, int b, int r) {

	int tm1[10][10];
	memcpy(tm1, map, sizeof(map));

	for (int i = 0; i < M; i++) {
		int mx = man_pos[i].first, my = man_pos[i].second;
		if (mx < a || mx >= a + r || my < b || my >= b + r)
			continue;

		man[mx][my]--;
		int tx = mx - a, ty = my - b;
		int mnx = ty + a, mny = r - tx - 1 + b;

		man[mnx][mny]++;
		man_pos[i] = {mnx, mny};
	}

	int ox = ex.first, oy = ex.second;
	int tx = ox - a, ty = oy - b;
	ex = {ty + a, r - tx - 1 + b};

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {

			map[i+a][j+b] = tm1[r - j - 1+a][i+b];
			if (map[i + a][j + b])
				map[i + a][j + b]--;
		}
	}
}

void rt() {
	int smallPath = INF, mx = N, my = N;
	int ox = ex.first, oy = ex.second;

	for (int i = 0; i < M; i++) {
		int tx = man_pos[i].first, ty = man_pos[i].second;
		if (tx < 0 || ty < 0) continue;

		int costX = ox < tx ? tx - ox : ox - tx;
		int costY = oy < ty ? ty - oy : oy - ty;
		int n1 = max(costX, costY);

		if  ((smallPath > n1) || 
			((smallPath == n1) && (tx < mx)) ||
			((smallPath == n1) && (tx == mx) && (ty < my)) )
		{
			mx = tx, my = ty;
			smallPath = n1;
		}
	}

#if DEBUG
	cout << "in rotate\n";
	cout << mx << ", " << my << endl;
#endif

	int rdx = max(mx, ox), rdy = max(my, oy);
	int lux = rdx - smallPath, luy = rdy - smallPath;

	if (lux < 0) {
		lux = 0;
		rdx = smallPath;
	}

	if (luy < 0) {
		luy = 0;
		rdy = smallPath;
	}

#if DEBUG
	cout << "up || down" << endl;
	cout << lux << "," << luy << " || " << rdx << "," << rdy << endl;
	cout << "smallPath = "<<smallPath << endl;
#endif

	rotateG(lux, luy, smallPath + 1);

}

void run() {
	man_cnt = M;
	for (int t = 0; t < K; t++) {
#if DEBUG
		cout << t + 1 << " th Execute\n";
#endif
		//이동
		move();
#if DEBUG
		cout << "Man count = " << man_cnt << ", moving = " << moving << endl;
		printMap(map);
		printMap(man);
		cout << "move   finish ===== \n";
#endif
		if (!man_cnt)
			break;
		//회전
		rt();
#if DEBUG
		printMap(map);
		printMap(man);
		cout << "rotate FInish ===== \n\n";

#endif 
	}
	cout << moving << "\n";
	cout << ex.first + 1 << " " << ex.second + 1;
}


int main(void)
{
	//freopen("input.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	}

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		man_pos[i] = { a - 1,b - 1 };
		man[a - 1][b - 1]++;
	}

	cin >> a >> b;
	ex = { a - 1,b - 1 };
	run();

	return 0;
};