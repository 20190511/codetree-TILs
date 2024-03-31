//1445
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define DEBUG false
#define INF	0x7FFFFFFF
using namespace std;
int map[10][10], attack[10][10], attacked[10][10], visited[10][10];; //최근 공격한, 공격받은 포탑
pair<int, int> mv[4] = {
	{0,1}, {1,0}, {0,-1}, {-1,0}
};
pair<int, int> mv2[8] = {
	{0,1}, {0,-1}, {1,0}, {-1,0},
	{1,1}, {1,-1}, {-1,1}, {-1,-1}
};
int K, N, M;
int plusAttack;


void printMap(int k) {
	cout << "======= " << k << " ===========" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << "(" <<attack[i][j]<<"," << attacked[i][j]<< ") ";
		}
		cout << endl;
	}
}

void printMap2() {
	cout << "---------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << visited[i][j] <<" ";
		}
		cout << endl;
	}
}


pair<int, int> selects(int k) {
	int rx=-1, ry=-1;
	
	int power = INF, attackTime = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j] || map[i][j] > power) continue;
			else if (map[i][j] < power) {
				rx = i, ry = j;
				power = map[i][j], attackTime = attack[i][j];
				continue;

			}

			if (attack[i][j] < attackTime) continue;
			else if (attack[i][j] > attackTime) {
				rx = i, ry = j;
				power = map[i][j], attackTime = attack[i][j];
				continue;

			}

			int xySum = i + j;
			
			if (xySum < rx + ry) continue;
			else if (xySum > rx + ry) {
				rx = i, ry = j;
				power = map[i][j], attackTime = attack[i][j];
				continue;

			}

			if (j < ry) continue;
			rx = i, ry = j;
			power = map[i][j], attackTime = attack[i][j];

		}
	}
	return { rx,ry };
}

pair<int,int> selectX(int k) {
	int rx = N, ry = M;

	int power = -1, attackTime = K+1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j] || map[i][j] < power) continue;
			else if (map[i][j] > power) {
				rx = i, ry = j;
				power = map[i][j], attackTime = attack[i][j];
				continue;
			}

			if (attack[i][j] > attackTime) continue;
			else if (attack[i][j] < attackTime) {
				rx = i, ry = j;
				power = map[i][j], attackTime = attack[i][j];
				continue;
			}

			int xySum = i + j;

			if (xySum > rx + ry) continue;
			else if (xySum < rx + ry) {
				rx = i, ry = j;
				power = map[i][j], attackTime = attack[i][j];
				continue;
			}

			if (j > ry) continue;
			rx = i, ry = j;
			power = map[i][j], attackTime = attack[i][j];

		}
	}

	if (rx == N) {
		rx = ry = -1;
	}
	return { rx,ry };
}

//a는 현재 위치, b는 finish 조건
bool layzer(pair<int, int> a, pair<int, int> b, int power, int k) {

	int fx = a.first, fy = a.second;

	if (a.first == b.first && a.second == b.second) {
		return true;
	}

	map[fx][fy] -= power;
	for (int i = 0; i < 4; i++) {
		int dx = (a.first + mv[i].first + N) % N, dy = (a.second + mv[i].second + M) % M;
		if (!map[dx][dy] || visited[dx][dy] != visited[fx][fy]-1) continue;
		int check = layzer({ dx,dy }, b, power, k);
		if (check) {
			attacked[fx][fy] = k;
			if (map[fx][fy] < 0) map[fx][fy] = 0;
			return true;
		}
	}
	map[fx][fy] += power;
	return false;
}

void attacks(pair<int, int> a, pair<int,int> b, int k) {
	int fx = a.first, fy = a.second;
	int ex = b.first, ey = b.second;

	memset(visited, 0, sizeof(visited));
	visited[ex][ey] = 1;
	
	queue<pair<int, int>> q;
	q.push({ex, ey});
	//레이저 시도
	bool endFlag = false;
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int dx = (cx + mv[i].first + N) % N, dy = (cy + mv[i].second + M) % M;
			if (!map[dx][dy] || visited[dx][dy]) continue;

			visited[dx][dy] = visited[cx][cy] + 1;
			if (dx == fx && dy == fy) {
				endFlag = true;
				break;
			}
			q.push({ dx,dy });
		}
		
		if (endFlag) break;
	}

#if DEBUG
	printMap2();
#endif
	if (visited[fx][fy]) {
#if DEBUG
		cout << "레이저 공격\n";
#endif
		int power = map[fx][fy] / 2;
		
		//레이저 공격
		int savedK = attacked[fx][fy];
		layzer(a, b, power, k);
		map[fx][fy] += power;
		attacked[fx][fy] = savedK;
		map[ex][ey] = map[ex][ey] - map[fx][fy] < 0 ? 0 : map[ex][ey] - map[fx][fy];

	}
	else {
#if DEBUG
		cout << "포탄 공격\n";
#endif
		//포탄
		int power = map[fx][fy] / 2;
		map[ex][ey] = map[ex][ey] - map[fx][fy] < 0 ? 0 : map[ex][ey] - map[fx][fy];

		for (int i = 0; i < 8; i++) {
			int dx = (mv2[i].first + ex + N) % N, dy = (mv2[i].second + ey + M) % M;
			if (dx == fx && dy == fy) continue;

			if (map[dx][dy]) {
				map[dx][dy] -= power;
				if (map[dx][dy] < 0) map[dx][dy] = 0;
				attacked[dx][dy] = k;
			}
		}

	}



}


void resets(int k) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] && attack[i][j] != k && attacked[i][j] != k) {
				map[i][j]++;
			}
		}
	}
}

void run() {
	for (int i = 1; i <= K; i++) {
#if DEBUG
		cout << "++++++ " << i << " ++++++" << endl;
#endif
		pair<int, int> a = selects(i);
		pair<int, int> b = selectX(i);
#if DEBUG
		cout << "Attack :: " << a.first << ", " << a.second << endl;
		cout << "Attacked :: " << b.first << ", " << b.second << endl;
#endif
		if (a.first < 0 || b.first < 0) break;
		if (a.first == b.first && a.second == b.second) break;
		
		map[a.first][a.second] += plusAttack;
		attack[a.first][a.second] = i;
		
		attacked[b.first][b.second] = i;
		
		attacks(a,b, i);
#if DEBUG
		cout << "Attack Complete\n";
		printMap(i);
#endif
		resets(i);
#if DEBUG
		cout << "Reset\n";
		printMap(i);
#endif

	}

	int maxPower = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			maxPower = max(map[i][j], maxPower);
		}
	}

	cout << maxPower;
}

int main(void)
{
	//freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;
	plusAttack = N + M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

#if DEBUG
	printMap(0);
#endif
	run();
	return 0;
}