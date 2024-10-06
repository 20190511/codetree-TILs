//1100 ~ 1110 이해 ~ 1220
#define _CRT_SECURE_NO_WARNINGS
#define DEBUGS false
#define DEBUG false
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct manNode {
	int x;
	int y;
	int d;
	int d2;
	bool die;

	manNode(int x=0, int y=0, int d=0, int d2=0, bool die=0) : x(x), y(y), d(d), d2(d2), die(die) {}
};
manNode man[10001];
pair<int, int> sulaeXY;

pair<int, int> manMv[3][2] = {
	{{-1,-1},{-1,-1}},
	{{0,1}, {0, -1}},
	{{1,0}, {-1, 0}},
};


//아래로 갈 때는 (d+3)%4, 중앙에서갈 때는 (d+1)%4
pair<int, int> mv[4] = {
	{-1,0}, {0,1}, {1,0}, {0,-1}
};


int N, M, H, K;

vector<int> map[100][100];
int namu[100][100];

int sulaeMap[2][100][100];
int sulaeMode = 0;
int sulaeDir = 0;

void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			
			cout << namu[i][j] << "[";
			for (auto it = map[i][j].begin() ; it != map[i][j].end(); it++) {
				cout << *it << " ";
			}

			if (sulaeXY.first == i && sulaeXY.second == j)
				cout << "X";

			cout << "] ";
		}
		cout << endl;
	}
	cout << "--------------" << endl;
	for (int i = 1; i <= M; i++) {
		if (man[i].die) continue;
		cout << "  man=" << i << ", d=" << man[i].d << ", d2=" << man[i].d2 << endl;
	}

	cout << " -sulaeDir = " << sulaeDir << endl;
	cout << "===================" << endl;
}

int dist(int m) {
	
	int mx = man[m].x, my = man[m].y;
	int sx = sulaeXY.first, sy = sulaeXY.second;

	return abs(mx - sx) + abs(my - sy);
}

void initSulae() {

	int i = N / 2, j = N / 2, d = 0;
	int cnt = 1;
	
	sulaeMap[0][i][j] = cnt++;

	for (int k = 1; k < N; k++) {

		for (int g = 0 ; g < k ; g++) {
			i += mv[d].first;
			j += mv[d].second;
			sulaeMap[0][i][j] = cnt++;

		}
		d = (d + 1) % 4;

		for (int g = 0; g < k; g++) {
			i += mv[d].first;
			j += mv[d].second;
			sulaeMap[0][i][j] = cnt++;

		}
		d = (d + 1) % 4;
	}

	for (int k = 1; k < N; k++) {
		i += mv[d].first;
		j += mv[d].second;
		sulaeMap[0][i][j] = cnt++;
	}

#if DEBUG
	cout << "sMap=1" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << sulaeMap[0][i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------" << endl;
#endif
	//가에서 시작

	i = 0, j = 0, cnt = 1, d=2;
	sulaeMap[1][i][j] = cnt++;

	for (int k = 1; k < N; k++) {
		i += mv[d].first;
		j += mv[d].second;
		sulaeMap[1][i][j] = cnt++;
	}

	d = 1;

	for (int k = N-1 ; k >= 0; k--) {

		for (int g = 0; g < k; g++) {
			i += mv[d].first;
			j += mv[d].second;
			sulaeMap[1][i][j] = cnt++;

		}
		d = (d + 3) % 4;

		for (int g = 0; g < k; g++) {
			i += mv[d].first;
			j += mv[d].second;
			sulaeMap[1][i][j] = cnt++;

		}
		d = (d + 3) % 4;
	}
#if DEBUG
	cout << "sMap=2" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << sulaeMap[1][i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------" << endl;
#endif
}

void manMove() {
	


	int sulX = sulaeXY.first, sulY = sulaeXY.second;
	for (int m = 1; m <= M; m++) {
		if (man[m].die) continue;
		
		
		if (!map[man[m].x][man[m].y].empty())
			map[man[m].x][man[m].y].clear();


		if (dist(m) > 3) continue;

#if DEBUG
		cout << "m=" << m << ", move" << endl;
#endif
		int originD = man[m].d;
		int subD = man[m].d2;
		
		int dx = man[m].x + manMv[originD][subD].first;
		int dy = man[m].y + manMv[originD][subD].second;

		// d전환
		if (dx < 0 || dx >= N || dy < 0 || dy >= N) {
			man[m].d2 = (man[m].d2 + 1) % 2;
			int subD = man[m].d2;
			int dx = man[m].x + manMv[originD][subD].first;
			int dy = man[m].y + manMv[originD][subD].second;
		}

		if (dx == sulX && dy == sulY) {
			continue;
		}
		man[m].x = dx, man[m].y = dy;
	}

	for (int m = 1; m <= M; m++) {
		if (man[m].die) continue;

		map[man[m].x][man[m].y].push_back(m);
	}
}

int sulaeMove(int turn) {
	
	sulaeXY.first += mv[sulaeDir].first;
	sulaeXY.second += mv[sulaeDir].second;
	int curscore = 0;

	int sx = sulaeXY.first, sy = sulaeXY.second;
	int pivot = sulaeMap[sulaeMode][sx][sy] + 1;
	bool findFlag = false;

	if (sx == 0 && sy == 0) {
		sulaeMode = 1;
		sulaeDir = 2;
		findFlag = true;
	}
	else if (sx == N / 2 && sy == N / 2) {
		sulaeMode = 0;
		sulaeDir = 0;
		findFlag = true;
	}

	//방향 설정
	for (int x = 0; x < 4 && !findFlag; x++) {
		int dx = sx + mv[x].first, dy = sy + mv[x].second;

		if (dx < 0 || dx >= N || dy < 0 || dy >= N) continue;
		
		if (pivot == sulaeMap[sulaeMode][dx][dy]) {

			sulaeDir = x;
			break;
		}
	}

#if DEBUG
	cout << " 술래 방향 : " << sulaeDir << endl;
	printMap();
#endif


	// 쥐를잡자 쥐를잡자

	for (int d = 0; d < 3; d++) {
		int dx = sx + mv[sulaeDir].first * d;
		int dy = sy + mv[sulaeDir].second * d;

		if (namu[dx][dy]) continue;

		while (!map[dx][dy].empty()) {
			int manN = map[dx][dy].back();

			curscore++;
			man[manN] = manNode(-1,-1,-1,-1,true);
#if DEBUG
			cout << "man=" << manN << " die!" << endl;
#endif
			map[dx][dy].pop_back();
		}
	}

	return curscore * turn;
}

int main(void)
{
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	cin >> N >> M >> H >> K;
	sulaeXY = { N / 2, N / 2 };
	for (int i = 1; i <= M; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		x--;
		y--;
		man[i] = manNode(x, y, d, 0, false);
		map[x][y].push_back(i);
	}

	for (int i = 1; i <= H; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		namu[x][y] = true;
	}


	initSulae();

#if DEBUG
	cout << "init" << endl;
	printMap();
#endif

	int totalScore = 0;
	for (int t = 1; t <= K; t++) {

#if DEBUG
		cout << " << t = " << t << " >>" << endl << endl;
#endif
		manMove();



		totalScore += sulaeMove(t);

		
#if DEBUG
		printMap();
		cout << "total Score = " << totalScore << endl;
#endif
	}

	cout << totalScore;

	return 0;
}