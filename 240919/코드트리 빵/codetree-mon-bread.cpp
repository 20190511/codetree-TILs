//1014 -> 27 ~ 11:40
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/**

	반성 1. 행작, 열작 문제는 mv[4] = { {-1,0}, {0,-1}, ...} 방식으로 하면안된다. -> v맵으로 시간 기록해놓고 풀 것.
	반성 2. 문제에서 1,2 번을 분리시켜놨는데 내가 임의로 합치다가 동시에 이동하는 점을 간과한 실수. (문제 순서 이해 오류)
*/

int map[16][16];

bool block[16][16], camp[16][16], manStop[31];
int N, M, stopCnt = 0;

pair<int, int> mv[4] = {
	{-1,0}, {0,-1}, {0,1}, {1,0}
};
pair<int, int> shop[31], man[31];

queue<int> dieMan;

void printMapTmp(int dmap[16][16]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << dmap[i][j] << " ";
		}
		cout << endl;
	}
	cout << "--------" << endl;
}
void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (camp[i][j]) {
				cout << "C ";
			}
			else if (map[i][j] < 0) {
				cout << "S" << -map[i][j];
			}
			else {
				cout << map[i][j]<<" ";
			}

			if (block[i][j]) {
				cout << "(X) ";
			}
			else {
				cout << "(O) ";
			}
		}
		cout << endl;
	}
	cout << "===================" << endl;
}


void findCamp(int num) {
	int v[16][16] = { 0, };
	queue<pair<int, int>> q;
	
	int shortest = 16 * 16;
	int cx = shop[num].first, cy = shop[num].second;
	q.push({ cx, cy });
	v[cx][cy] = true;

	int rx=N, ry=N;
	while (!q.empty()) {
		cx = q.front().first, cy = q.front().second;
		int curdist = v[cx][cy];
		q.pop();
		for (int i = 0; i < 4; i++) {
			int dx = cx + mv[i].first, dy = cy + mv[i].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || block[dx][dy] || v[dx][dy]) continue;

			if (shortest < curdist + 1) continue;

			if (camp[dx][dy] && (rx > dx || ((rx == dx) && ry > dy))) {
				rx = dx, ry = dy;
				shortest = curdist + 1;
			}
			q.push({ dx,dy });
			v[dx][dy] = curdist + 1;
		}
	}

#if DEBUG
	cout << "num=" << num << " camp (" << rx << ", " << ry << ")" << endl;
#endif
	block[rx][ry] = true;
	man[num] = { rx, ry };
	map[rx][ry] = num;

}

void go(int num) {

	//bfs 추적
	bool v[16][16] = { 0, };
	bool exitFlag = false;

	int dmap[16][16] = { 0, };
	int rmv[4] = { 3, 2, 1, 0 };
	queue<pair<int, int>> q;

	int ox = man[num].first, oy = man[num].second;
	q.push({ ox,oy });
	v[ox][oy] = true;

	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int dx = cx + mv[i].first, dy = cy + mv[i].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || v[dx][dy] || block[dx][dy]) continue;

			v[dx][dy] = true;
			dmap[dx][dy] = rmv[i];
			q.push({dx,dy});

			if (dx == shop[num].first && dy == shop[num].second) {
				exitFlag = true;
				break;
			}
		}
		if (exitFlag) break;
	}

	//추적 시작
#if DEBUG
	printMapTmp(dmap);
#endif

	int px = shop[num].first, py = shop[num].second, dir = -1;
	
	while (px != ox || py != oy) {
		dir = dmap[px][py];
		px += mv[dir].first;
		py += mv[dir].second;
	}
#if DEBUG
	cout << "dir = " << dir << endl;
#endif

	dir = rmv[dir];
	map[ox][oy] = 0;
	//die check
	ox += mv[dir].first;
	oy += mv[dir].second;
	
	if (ox == shop[num].first && oy == shop[num].second) {
#if DEBUG
		cout << "man=" << num << " 도착" << endl;
#endif
		man[num] = { -1, -1 };
		map[ox][oy] = -num;

		//block[ox][oy] = true;
		dieMan.push(num);
		manStop[num] = true;
		stopCnt++;
		return;
	}

	man[num] = { ox, oy };
	map[ox][oy] = num;
#if DEBUG
	printMap();
#endif
}


int main(void)
{
#if DEBUG
	freopen("test.txt", "r", stdin);
#endif
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> camp[i][j];
		}
	}

	for (int i = 1; i <= M; i++) {
		cin >> shop[i].first >> shop[i].second;
		shop[i].first--;
		shop[i].second--;

		map[shop[i].first][shop[i].second] = -i;
	}



#if DEBUG
	printMap();
#endif

	for (int i = 1; ; i++) {
#if DEBUG
		cout << endl << "===== "<< i <<" =====" << endl << endl;
#endif
		//1~2. 최단경로 이동 및 도착하면 블락
		for (int m = 1; m <= M; m++) {
			if (manStop[m] || m >= i) continue;
			go(m);
		}

		while (!dieMan.empty()) {
			int dieManNum = dieMan.front();
			dieMan.pop();

			int dieX = shop[dieManNum].first, dieY = shop[dieManNum].second;
			block[dieX][dieY] = true;
		}
		/*
		for (int m = 1; m <= M; m++) {
			if (manStop[m] && !block[shop[m].first][shop[m].second]) {
				block[shop[m].first][shop[m].second] = true;
			}
		}
		*/

		if (stopCnt == M) {
			cout << i;
			return 0;
		}

		//3. camp찾기
		if (i <= M) findCamp(i);

#if DEBUG
		printMap();
#endif
	}
	return 0;
}