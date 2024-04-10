//0918
/**
N = 50
M = 턴 수 = 1000
P = 산타 수 = 1 ~ 30
C = 루돌프
D = 산타
*/
#define DEBUG false
#define DEBUGS false
#define CHECK(X,Y,S) (X <= 0 || X > S || Y <= 0 || Y > S)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

struct santa {
	int x; //탈락시 -1
	int y;
	int score;
	int state;
};

int N, M, P, C, D;
int map[51][51];
int totalSanta;
pair<int, int> ru = { 0,0 };
pair<int, int> mv[8] = {
	{-1,0}, {0,1}, {1,0}, {0,-1},
	{-1,1}, {1,-1}, {-1,-1}, {1,1}
};
santa san[31];


void printMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (ru.first == i && ru.second == j) cout << "R ";
			else cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "========" << endl;
}
void printScore() {
	for (int i = 1; i <= P; i++) {
		cout << san[i].score << " ";
	}
	cout << endl;
}

int calcDist(int x1, int y1, int x2, int y2) {
	int dx = x1 < x2 ? x2 - x1 : x1 - x2;
	int dy = y1 < y2 ? y2 - y1 : y1 - y2;
	return dx * dx + dy * dy;
}
void comm(int nx, int ny, int sanN, int dir) {
	if (CHECK(nx, ny, N)) {
		san[sanN].x = san[sanN].y = san[sanN].state = -1;
		totalSanta--;
		return;
	}

	int cx = nx, cy = ny, curSan = sanN;
	while (map[cx][cy]) {
		if (CHECK(cx, cy, N)) {
			san[curSan].x = san[curSan].y = san[curSan].state = -1;
			totalSanta--;
			return;
		}


		san[curSan].x = cx;
		san[curSan].y = cy;

		int tmp = map[cx][cy];
		map[cx][cy] = curSan;
		curSan = tmp;

		cx += mv[dir].first;
		cy += mv[dir].second;
	}

	map[cx][cy] = curSan;
	san[curSan].x = cx;
	san[curSan].y = cy;
}


void ru_move() {
	int cx = ru.first, cy = ru.second;
	int maxDist = N * N + N, sanNum = 0;
	for (int i = 1; i <= P; i++) {
		if (san[i].x == -1) continue;

		int dist = calcDist(san[i].x, san[i].y, cx, cy);
		if ( (dist < maxDist) || 
			((dist == maxDist) && (san[sanNum].x < san[i].x)) ||
			((dist == maxDist) && (san[sanNum].x == san[i].x) && (san[sanNum].y < san[i].y)) ) 
		{
			maxDist = dist;
			sanNum = i;
		}
	}

#if DEBUG	
	cout << "san num = " << sanNum << endl;
#endif

	int minDist = N*N+N, dir = -1;
	int sx = san[sanNum].x, sy = san[sanNum].y;
	bool c_check = false;
	for (int i = 0; i < 8; i++) {
		int dx = cx + mv[i].first, dy = cy + mv[i].second;
		if (CHECK(dx, dy, N)) continue;

		int dist = calcDist(dx, dy, sx, sy);
		if (dist < minDist) {
			minDist = dist;
			dir = i;
		}
		if (dist == 0) c_check = true;
	}

	//루돌프 이동
	ru = { cx + mv[dir].first, cy + mv[dir].second };
	cx = ru.first, cy = ru.second;
	if (c_check) {
		map[cx][cy] = 0;

		//상호작용..
		int newX = cx + mv[dir].first * C, newY = cy + mv[dir].second * C;
		//산타 어지러움
		san[sanNum].state = 2;
		san[sanNum].score += C;
		comm(newX, newY, sanNum, dir);
	}
}

void san_move() {
	int rx = ru.first, ry = ru.second;
	for (int i = 1; i <= P; i++) {
		if (san[i].state || san[i].x == -1) continue;

		int sx = san[i].x, sy = san[i].y;
		int minDist = calcDist(sx, sy, rx, ry), dir = -1;
		bool c_check = false;
		for (int x = 0; x < 4; x++) {
			int dx = sx + mv[x].first, dy = sy + mv[x].second;
			if (CHECK(dx, dy, N) || map[dx][dy]) continue;

			int dist = calcDist(dx, dy, rx, ry);
			if (dist < minDist) {
				minDist = dist;
				dir = x;
			}

			if (dist == 0)
				c_check = true;
		}

		if (dir == -1) continue;

		int nx = sx + mv[dir].first, ny = sy + mv[dir].second;
		map[sx][sy] = 0;
		if (c_check) {
			san[i].score += D;
			san[i].state = 2;
			int newDir = (dir + 2) % 4;
			nx += mv[newDir].first * D;
			ny += mv[newDir].second * D;
			comm(nx,ny,i,newDir);
		}
		else { //충돌X
			map[nx][ny] = i;
			san[i].x = nx;
			san[i].y = ny;
		}
	}
}

void after_process() {
	//점수 up + state -- 
	for (int i = 1; i <= P; i++) {
		if (san[i].x == -1) continue;
		
		if (san[i].state) san[i].state--;
		san[i].score++;
	}
}
void run() {
	for (int i = 1; i <= M; i++) {
#if DEBUG
		cout << "+++++ " << i << " +++++" << endl;
#endif
		ru_move();
#if DEBUG
		cout << "ru_move finish" << endl;
		printMap();
		printScore();
#endif
		if (!totalSanta) {
#if DEBUG
			cout << "break" << endl;
#endif
			break;
		}

		san_move();

#if DEBUG
		cout << "san move finish "<< endl;
		printMap();
		printScore();
#endif
		if (!totalSanta) {
#if DEBUG
			cout << "break" << endl;
#endif
			break;
		}

		after_process();
#if DEBUG
		cout << "after process finish " << endl;
		printMap();
		printScore();
#endif
	}
	printScore();
}
int main(void) {
#if DEBUGS
	freopen("test.txt", "r", stdin);
#endif
	san[0] = { -1,-1,-1,-1 };
	cin >> N >> M >> P >> C >> D;
	totalSanta = P;
	int p, x, y;
	cin >> ru.first >> ru.second;
	for (int i = 0; i < P; i++) {
		int p;
		cin >> p >> x >> y;
		san[p].state = 0;
		san[p].score = 0;
		san[p].x = x;
		san[p].y = y;
		map[x][y] = p;
	}

#if DEBUG
	printMap();
#endif
	run();
	return 0;
}