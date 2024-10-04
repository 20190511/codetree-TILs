//1100 ~ 1128 (이해) ~ 1227 (1시간30분걸림)
/**
	딱히 실수 없었음. 난이도 쉬움
*/
#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

pair<int, int> mv[4] = {
	{-1,0}, {0,1}, {1,0}, {0,-1}
};

struct golNode {
	int x;
	int y;
	int d; //출구방향

	golNode(int x = -1, int y = -1, int d = 0) : x(x), y(y), d(d) {}
};


int sc[1001]; //디버그용 점수
golNode golem[1001];
int golMap[71][71];
int R, C, K;
int totalScore = 0;

pair<int, int> golDoor(int n) {
	
	return { golem[n].x + mv[golem[n].d].first, golem[n].y + mv[golem[n].d].second };
}

void printMap() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int k = golMap[i][j];
			if (k && golDoor(k).first == i && golDoor(k).second == j)
				cout << "E ";
			else
				cout << golMap[i][j] << " ";
		}
		cout << endl;
	}

	cout << " ============= " << endl;

}

// x가 <= 0 인건 체크안하셔도된다.

bool downMove(int n) {
	golNode g = golem[n];

	int cx = g.x, cy = g.y;

	int lx = cx + 1, ly = cy - 1;
	int rx = cx + 1, ry = cy + 1;
	int bx = cx + 2, by = cy;

	if (lx != 0 && golMap[lx][ly])
		return false;

	if (rx != 0 && golMap[rx][ry])
		return false;
	
	if (golMap[bx][by])
		return false;


	// y 체크

	if (ly <= 0 || ly > C || lx > R)
		return false;
	if (ry <= 0 || ry > C || rx > R)
		return false;
	if (by <= 0 || by > C || bx > R)
		return false;

	return true;
}

bool leftMove(int n) {
	golNode g = golem[n];
	int cx = g.x, cy = g.y;

	int ax = cx - 1, ay = cy - 1;
	int bx = cx    , by = cy - 2;
	int Cx = cx + 1, Cy = cy - 2;
	int dx = cx + 1, dy = cy - 1;

	int ex = cx + 2, ey = cy - 1; //x 체크 해줘야함


	if (ax > 0 && golMap[ax][ay])
		return false;

	if (bx > 0 && golMap[bx][by])
		return false;

	if (Cx > 0 && golMap[Cx][Cy])
		return false;

	if (dx > 0 && golMap[dx][dy])
		return false;

	if (golMap[ex][ey])
		return false;

	if (ay <= 0 || ay > C || ax > R)
		return false;
	if (by <= 0 || by > C || bx > R)
		return false;
	if (Cy <= 0 || Cy > C || Cx > R)
		return false;
	if (dy <= 0 || dy > C || dx > R)
		return false;
	if (ey <= 0 || ey > C || ex > R)
		return false;

	return true;
}

bool rightMove(int n) {
	golNode g = golem[n];
	int cx = g.x, cy = g.y;

	int ax = cx - 1, ay = cy + 1;
	int bx = cx, by = cy + 2;
	int Cx = cx + 1, Cy = cy + 2;
	int dx = cx + 1, dy = cy + 1;

	int ex = cx + 2, ey = cy + 1; //x 체크 해줘야함


	if (ax > 0 && golMap[ax][ay])
		return false;

	if (bx > 0 && golMap[bx][by])
		return false;

	if (Cx > 0 && golMap[Cx][Cy])
		return false;

	if (dx > 0 && golMap[dx][dy])
		return false;

	if (golMap[ex][ey])
		return false;

	if (ay <= 0 || ay > C || ax > R)
		return false;
	if (by <= 0 || by > C || bx > R)
		return false;
	if (Cy <= 0 || Cy > C || Cx > R)
		return false;
	if (dy <= 0 || dy > C || dx > R)
		return false;
	if (ey <= 0 || ey > C || ex > R)
		return false;

	return true;

}

bool golemMove(int n) {
	golNode& g = golem[n];


	bool curCheck = true;

	while (curCheck) {
		
		curCheck = downMove(n);
		if (curCheck) {
			g.x++;
			continue;
		}
		curCheck = leftMove(n);
		if (curCheck) {
			g.x++;
			g.y--;
			g.d = (g.d + 3) % 4;

			continue;
		}
		curCheck = rightMove(n);
		if (curCheck) {
			g.x++;
			g.y++;
			g.d = (g.d + 1) % 4;
			continue;
		}
	}


	if (g.x - 1 <= 0) return false;
	// 마지막에 골렘 자취 map에 기록
	golMap[g.x][g.y] = n;

	golMap[g.x+1][g.y] = n;
	golMap[g.x][g.y+1] = n;
	golMap[g.x-1][g.y] = n;
	golMap[g.x][g.y-1] = n;

#if DEBUG
	printMap();

#endif
	return true;
}

int angelMove(int n) {
	int retR = 0;
	bool v[1001] = { 0, };

	v[n] = true;
	queue<int> q;
	q.push(n);

	while (!q.empty()) {
		int idx = q.front(); 
		q.pop();

		retR = max(golem[idx].x + 1, retR);
		
		pair<int, int> out = golDoor(idx);

		for (int i = 0; i < 4; i++) {
			int dx = out.first + mv[i].first, dy = out.second + mv[i].second;
			if (dx <= 0 || dx > R || dy <= 0 || dy > C)
				continue;

			int next = golMap[dx][dy];
			if (!next || next == idx || v[next] || !golMap[dx][dy]) continue;

			v[next] = true;
			q.push(next);
		}

	}

	return retR;
}


int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif
	int c, d;
	cin >> R >> C >> K;
	for (int i = 1; i <= K; i++) {
		cin >> c >> d;
		golem[i] = golNode(-1, c, d);
	}



	for (int k = 1; k <= K; k++) {
#if DEBUG
		cout << " << k = " << k << " >> " << endl;
#endif

		//골렘 이동 
		bool check = golemMove(k);

		// 골렘 벗어낫는지 체크
		if (!check) {
#if DEBUG
			cout << "골렘 맵 벗어남 초기화 ..," << endl;
#endif
			memset(golMap, 0, sizeof(golMap));
			continue;
		}


		//정령 이동
		int curScore = angelMove(k);

		totalScore += curScore;
#if DEBUG
		cout << "curScore = " << curScore << endl;
#endif
	}

	cout << totalScore;



	return 0;
}