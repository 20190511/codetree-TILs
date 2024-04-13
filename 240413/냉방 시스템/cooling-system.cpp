//0846
#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <queue>
using namespace std;

//2 ≤ n ≤ 20
//1 ≤ m ≤ n ^ 2
//1 ≤ k ≤ 1, 000

pair<int, int> mv[4] = {
	{0,-1}, {-1,0}, {0,1}, {1,0 }
};


int N, M, K;
int map[21][21], wind[21][21];
bool garo[21][21], sero[21][21];
vector<pair<int, int>> air;
void printMap2(int map[21][21]) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------" << endl;
}
void printMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << wind[i][j];
			if (sero[j][i]) cout << "|";
			else cout << " ";
		}
		cout << endl;
		for (int j = 1; j <= N; j++) {
			if (garo[i][j]) cout << "--";
			else cout << "  ";
		}
		cout << endl;
	}
	cout << "=============" << endl;
}
int smallValue() {
	int smallVal = 0x7FFFFFFF;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 1)
				smallVal = min(wind[i][j], smallVal);
		}
	}
	return smallVal;
}

#define CHECK(X,Y) (X <= 0 || X > N || Y <= 0 || Y > N)

void windMove() {
	for (auto& item : air) {
		int ax = item.first, ay = item.second, dir = map[ax][ay] - 2;
		int tmpMap[21][21] = { 0, };
		memset(tmpMap, 0, sizeof(tmpMap));
		int fx = ax + mv[dir].first, fy = ay + mv[dir].second;
		queue<pair<int, int>> q;
		tmpMap[fx][fy] = 5;
		wind[fx][fy] += 5;
		q.push({ fx,fy });

		while (!q.empty()) {
			int cx = q.front().first, cy = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				if (i == (dir + 2) % 4) continue;
				int dx = cx + mv[i].first, dy = cy + mv[i].second;
				if (CHECK(dx, dy) || tmpMap[dx][dy]) continue;

				if (i == 0 && (CHECK(cy - 1, cx) || sero[cy - 1][cx])) continue;
				else if (i == 1 && (CHECK(cx - 1, cy) || garo[cx - 1][cy])) continue;
				else if (i == 2 && sero[cy][cx]) continue;
				else if (i == 3 && garo[cx][cy]) continue;


				if (i != dir) {
					if (dir == 0 && (CHECK(dy - 1, dx) || sero[dy - 1][dx])) continue;
					else if (dir == 1 && (CHECK(dx - 1, dy) || garo[dx - 1][dy])) continue;
					else if (dir == 2 && sero[dy][dx]) continue;
					else if (dir == 3 && garo[dx][dy]) continue;

					dx = dx + mv[dir].first, dy = dy + mv[dir].second;
					if (CHECK(dx, dy) || tmpMap[dx][dy]) continue;
				}

				tmpMap[dx][dy] = tmpMap[cx][cy] - 1;
				wind[dx][dy] += tmpMap[dx][dy];
				if (tmpMap[dx][dy] != 1)
					q.push({ dx,dy });
				continue;
			}

		}
#if DEBUG
		printMap2(tmpMap);
#endif
	}
}

void windCross() {
	int tmpMap[21][21];
	memcpy(tmpMap, wind, sizeof(tmpMap));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			for (int x = 2; x < 4; x++) {
				int dx = i + mv[x].first, dy = j + mv[x].second;

				if (CHECK(dx, dy)) continue;
				if (x == 2 && sero[j][i]) continue;
				else if (x == 3 && garo[i][j]) continue;


				int diff = (tmpMap[i][j] - tmpMap[dx][dy]) / 4;
				wind[i][j] -= diff;
				wind[dx][dy] += diff;
#if DEBUG
				cout << "i,j" << i << ", " << j << " && dx,dy" << dx << ", " << dy << " --> " << diff << endl;
#endif
			}
		}
	}
}
void run() {
#if DEBUG
	printMap();
#endif

	// 1. 바람 이동
	windMove();
#if DEBUG
	cout << "1 Process finish" << endl;
	printMap();
#endif
	// 2. 공기 섞임
	windCross();
#if DEBUG
	cout << "2 Process finish" << endl;
	printMap();
#endif
	// 3. 바깥 사무실 - 1
	for (int i = 2; i <= N - 1; i++) {
		if (wind[i][1]) wind[i][1]--;
		if (wind[i][N]) wind[i][N]--;

		if (wind[1][i]) wind[1][i]--;
		if (wind[N][i]) wind[N][i]--;
	}

	if (wind[1][1]) wind[1][1]--;
	if (wind[N][N]) wind[N][N]--;
	if (wind[1][N]) wind[1][N]--;
	if (wind[N][1]) wind[N][1]--;
#if DEBUG
	cout << "3 Prcess finish :: " << endl;
	printMap();
#endif

}

int main(void) {
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] > 1) air.push_back({ i,j });
		}
	}
	for (int i = 0; i < M; i++) {
		int a, b, s;
		cin >> a >> b >> s;
		if (s)
			sero[b - 1][a] = true;
		else
			garo[a - 1][b] = true;
	}

	int t = 1;
	for (t = 1; smallValue() < K && t <= 100 ; t++) {
#if DEBUG
		cout << "+++++ t = " << t << " +++++" << endl;
#endif
		run();

	}
	if (t > 100)
		cout << -1;
	else
		cout << t - 1;

	return 0;
}