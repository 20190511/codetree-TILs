//1500
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define DEBUGS false
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
* 1. 바람 외벽일때 이동안하는거 고려못한 실수
* 2. 적분 영상기법에서 N-1로 임의로 범위를 좁히면 안됨
*/

int map[21][21], siwon[21][21];
bool cwall[22][22], rwall[22][22];
int N, M, K;

pair<int, int> mv[4] = {
	{0, -1}, {-1,0}, {0,1}, {1,0}
};

struct node{
	int x;
	int y;
	int dir;

	node(int x=0, int y=0, int dir = 0) : dir(dir), x(x), y(y) {}
};

struct baramNode {
	int x;
	int y;
	int power;

	baramNode(int x = 0, int y = 0, int power = 0) : power(power), x(x), y(y) {}
};

vector<node> airconQ;
vector<pair<int, int>> spaceQ;

void printMap() {
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl << endl;
	}

	cout << "--------------" << endl;
	*/
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%-3d", siwon[i][j]);
			if (cwall[i][j])
				cout << "X";
			else
				cout << " ";

		}
		cout << endl;
		for (int j = 1; j <= N; j++) {
			if (rwall[i][j])
				cout << "X";
			else
				cout << " ";
			cout << "   ";

		}
		cout << endl;
	}

	cout << "======================" << endl << endl;
}



bool canGo(int x, int y, int dir) {

	int dx = x + mv[dir].first, dy = y + mv[dir].second;

	if (dx <= 0 || dy > N || dy <= 0 || dy > N) return false;

	if (dir == 0 && cwall[x][y-1]) return false;
	if (dir == 1 && rwall[x-1][y]) return false;
	if (dir == 2 && cwall[x][y]) return false;
	if (dir == 3 && rwall[x][y]) return false;

	return true;
}


void airconSimul() {
	
	for (auto a : airconQ) {
		int ax = a.x, ay = a.y, aDir = a.dir;
		int x = ax + mv[aDir].first, y = ay + mv[aDir].second;
		int curVal = 5;

		if (x <= 0 || y > N || y <= 0 || y > N) continue;

		siwon[x][y] += curVal;
		
		queue<baramNode> q;
		q.push({ x,y,curVal });

		bool v[21][21] = { 0, };
		v[x][y] = true;

		while (!q.empty()) {
			int cx = q.front().x, cy = q.front().y;
			curVal = q.front().power;
			q.pop();
			if (!(curVal - 1)) continue;

			int iDir;

			//직진
			int dx = cx + mv[aDir].first, dy = cy + mv[aDir].second;
			if (canGo(cx, cy, aDir)) {
				if (curVal - 1 && !v[dx][dy]) {
					v[dx][dy] = true;
					q.push({ dx,dy,curVal - 1 });
					siwon[dx][dy] += curVal - 1;

				}
			}

			//선회 1
			iDir = (aDir + 1) % 4;
			dx = cx + mv[iDir].first, dy = cy + mv[iDir].second;
			if (canGo(cx, cy, iDir) && canGo(dx, dy, aDir)) {
				dx += mv[aDir].first;
				dy += mv[aDir].second;
				if (curVal - 1 && !v[dx][dy]) {
					v[dx][dy] = true;
					q.push({ dx,dy,curVal - 1 });
					siwon[dx][dy] += curVal - 1;

				}

			}

			//선회 2
			iDir = (aDir + 3) % 4;
			dx = cx + mv[iDir].first, dy = cy + mv[iDir].second;
			if (canGo(cx, cy, iDir) && canGo(dx, dy, aDir)) {
				dx += mv[aDir].first;
				dy += mv[aDir].second;
				if (curVal - 1 && !v[dx][dy]) {
					v[dx][dy] = true;
					q.push({ dx,dy,curVal - 1 });
					siwon[dx][dy] += curVal - 1;

				}

			}

		}


	}
#if DEBUG
	printMap();
#endif

}




void baramMove() {
	int cpyMap[21][21];
	memcpy(cpyMap, siwon, sizeof(cpyMap));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			
			int cur = cpyMap[i][j], right = cpyMap[i][j + 1], down = cpyMap[i + 1][j];

			int rDiff = abs(cur - right) / 4;
			int dDiff = abs(cur - down) / 4;

			if (canGo(i, j, 2)) {
				if (cur < right) {
					siwon[i][j] += rDiff;
					siwon[i][j + 1] -= rDiff;
				}
				else if (cur > right) {
					siwon[i][j] -= rDiff;
					siwon[i][j + 1] += rDiff;
				}
			}

			if (canGo(i, j, 3)) {
				if (cur < down) {
					siwon[i][j] += dDiff;
					siwon[i + 1][j] -= dDiff;
				}
				else if (cur > down) {
					siwon[i][j] -= dDiff;
					siwon[i + 1][j] += dDiff;
				}
			}

		}
	}

#if DEBUG
	cout << "+Baram Move+" << endl << endl;
	printMap();
#endif

}

void wallMinus() {
	
	if (siwon[1][1]) siwon[1][1]--;
	if (siwon[1][N]) siwon[1][N]--;
	if (siwon[N][1]) siwon[N][1]--;
	if (siwon[N][N]) siwon[N][N]--;

	for (int i = 2; i <= N-1; i++) {
		if (siwon[1][i]) siwon[1][i]--;
		if (siwon[N][i]) siwon[N][i]--;
		if (siwon[i][1]) siwon[i][1]--;
		if (siwon[i][N]) siwon[i][N]--;
	}

#if DEBUG
	cout << "+Wall Minus" << endl << endl;
	printMap();
#endif
}

bool spaceCheck() {

	for (auto s : spaceQ) {
		
		if (siwon[s.first][s.second] < K) {
#if DEBUG
			cout << s.first << ", " << s.second << " 사무실이 아직 불만족 중" << endl;
#endif
			return false;
		}
	}
	return true;
}

int main(void)
{
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif
	cin >> N >> M >> K;
	int x, y, mode;
	int v;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> v;
			map[i][j] = v;
			if (!v)
				continue;
			else if (v == 1)
				spaceQ.push_back({ i,j });
			else {
				airconQ.push_back({ i,j,v - 2 });
			}
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> mode;
		if (mode == 0) {
			rwall[x-1][y] = true;
		}
		else {
			cwall[x][y-1] = true;
		}
	}


	int t = 1;
	for (t = 1; t <= 100; t++) {
#if DEBUG
		cout <<endl<< "  <<< " << t << ">>> " << endl;
#endif


		airconSimul();

		baramMove();

		wallMinus();

		if (spaceCheck()) {

			cout << t;
			return 0;
		}
#if DEBUG
		printMap();
#endif
	}

	cout << -1;
	return 0;
}