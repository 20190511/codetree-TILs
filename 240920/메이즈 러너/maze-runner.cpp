//1003 ~ 1158
/*
* 회전 문제 고찰 -> 1,1 좌표 시작인 경우 평행 이동 시 시작점 좌표에 -1씩 해주고 해야함.
* + 그리고 for (int i = 1 ; i <= r ; i++) 형태로 해야 가능함.
* 
* 
* (회전 문제는 조금 더 유형정리를 해둘 필요가 있음)
*/
#define DEBUG false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;


int calDist(pair<int, int> a, pair<int, int> b) {
	return abs(a.first-b.first) + abs(a.second-b.second);
}

struct man {
	int x;
	int y;
	bool exits;
	int mvcnt;

	man(int x=0, int y=0, bool exits=true, int mvcnt=0) : x(x), y(y), exits(exits), mvcnt(mvcnt) {}
};

int N, M, K;
int map[11][11];
int exManCnt = 0;
pair<int, int> door, mv[4] = {
	{-1,0}, {1,0}, {0,-1}, {0,1}
};
man mans[11];


void printMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			if (door.first == i && door.second == j)
				cout << "E(";
			else
				cout << map[i][j] << "(";
			for (int m = 1; m <= M; m++) {
				if (mans[m].x == i && mans[m].y == j) {
					cout << m << " ";
				}
			}
			cout << ") ";
		}
		cout << endl;
	}
	cout << "====================" << endl;
}

void moves(int num) {
	int mx = mans[num].x, my = mans[num].y;

	int dir = -1, minDist = calDist(door, { mx,my });
	for (int i = 0; i < 4; i++) {
		int dx = mx + mv[i].first, dy = my + mv[i].second;
		if (dx <= 0 || dx > N || dy <= 0 || dy > N || map[dx][dy]) continue;
		
		int curMin = calDist(door, {dx, dy});
		if (minDist > curMin) {
			minDist = curMin;
			dir = i;
		}
	}

#if DEBUG
	cout << "Man=" << num << " 이동 -> " << dir << endl;
#endif


	if (dir == -1) return;

	int gx = mx + mv[dir].first;
	int gy = my + mv[dir].second;
	mans[num].mvcnt++;

	if (!calDist(door, { gx,gy })) {
		mans[num].x = 0;
		mans[num].y = 0;
		mans[num].exits = true;
		exManCnt++;
		return;
	}

	mans[num].x = mx + mv[dir].first;
	mans[num].y = my + mv[dir].second;
}

//주의 사람도 회전

int findR(pair<int, int> a, pair<int, int> b) {
	return  max(abs(a.first - b.first), abs(a.second - b.second)) + 1;
}

void rotateIn(pair<int, int> top, pair<int, int> bottom, int r) {
	queue<int> q;
	int tmpMap[11][11];
	bool chgMan[11] = { 0, };
	bool chgdoor = false;

	memcpy(tmpMap, map, sizeof(tmpMap));

	int sx = top.first-1, sy = top.second-1;
	for (int i = 1; i <= r; i++) {
		for (int j = 1 ; j <= r; j++) {

			//값하나 줄이기
			int val = tmpMap[i + sx][j + sy] - 1;
			val = val < 0 ? 0 : val;

			//회전
			map[j + sx][(r - i + 1) + sy] = val;

			//사람도 돌리기
			for (int m = 1; m <= M; m++) {
				if (mans[m].exits || chgMan[m]) continue;

				if (mans[m].x == (i+sx) && mans[m].y == (j+sy)) {
					mans[m].x = j + sx;
					mans[m].y = (r - i + 1) + sy;
					chgMan[m] = true;
				}
			}

			if (door.first == (i + sx) && door.second == (j+sy) && !chgdoor) {
				door = { j + sx, (r - i + 1) + sy };
				chgdoor = true;
			}
		}
	}
	
}


void rotate() {

	int minR = N + 1, minTx = N+1, minTy = N+1;
	for (int m = 1; m <= M; m++) {
		if (mans[m].exits) continue;

		//가장 우하단 좌표 찾기
		
		int mx = max(mans[m].x, door.first), my = max(mans[m].y, door.second);

		//거리 측정해서 좌상단 찾기

		int curR = findR({ mans[m].x, mans[m].y }, door);
		int tx = mx - curR + 1, ty = my - curR + 1;

		//오차 조정
		
		if (tx <= 0) {
			tx = 1;
		}

		if (ty <= 0) {
			ty = 1;
		}

		//좌상단이 원점이면 원점에서 좌하단 길이 재측정.
		int curOR = findR({ 1,1 }, {mx, my});
		if (tx == 1 && ty == 1 && curR > curOR) {
			mx = my = curOR;
			curR = curOR;
		}

		//비교
		if (curR > minR) continue;
		else if ((curR == minR) && minTx < tx) continue;
		else if ((curR == minR) && (minTx == tx) && (minTy < ty)) continue;

		minR = curR;
		minTx = tx;
		minTy = ty;
	}

	int tx = minTx, ty = minTy, bx = minTx + minR - 1, by = minTy + minR - 1;
#if DEBUG
	cout << "Rotate 하단길이=" << minR << ", 좌하단 좌표=(" << minTx << ", " << minTy << "), 우하단좌표=("<<bx<<", "<<by<<")" << endl;
#endif


	//회전
	rotateIn({ tx,ty }, { bx,by }, minR);
#if DEBUG
	printMap();
#endif
}

int main(void)
{
#if DEBUG
	freopen("test.txt", "r", stdin);
#endif
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= M; i++) {
		int x, y;
		cin >> x >> y;
		mans[i] = man(x, y, false, 0);
	}

	cin >> door.first >> door.second;

	//////
#if DEBUG
	printMap();
#endif

	for (int t = 1; t <= K; t++) {
#if DEBUG
		cout << " ====== " << t << " =====" << endl << endl;
#endif
		//move
		for (int m = 1; m <= M; m++) {
			if (mans[m].exits) continue;
			moves(m);
		}

#if DEBUG
		printMap();
#endif
		if (exManCnt == M)
			break;
		//rotate
		rotate();
	}

	int distSum = 0;
	for (int i = 1; i <= M; i++) {
		distSum += mans[i].mvcnt;
	}
	cout << distSum << endl;
	cout << door.first << " " << door.second;
	return 0;
}