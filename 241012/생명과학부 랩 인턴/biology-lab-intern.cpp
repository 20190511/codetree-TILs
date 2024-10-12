//1836 1911(거리구현)
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define DEBUGS false
#include <iostream>
#include <vector>
using namespace std;

struct virus {
	int x;
	int y;
	int s;
	int d;
	int p;
	bool die;
};
struct posNode {
	int first;
	int second;
	int dir;
};
int N, M, K;
int map[101][101];
virus virusInfo[10001];
vector<int> tmpMap[101][101];


void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "==================" << endl;
}

pair<int, int> mv[5] = {
	{-1,-1}, {-1,0}, {1,0}, {0,1}, {0,-1}
};


posNode pos(int x, int y, int dir, int s) {

	if (dir == 1 || dir == 2) { // 위-아래
		s = (s % (2 * (N - 1)));

		if (dir == 1) {
			if (s <= x) 
				return { x - s, y, 1};
			else if (s <= (x + N - 1)) {
				s -= x;
				return { s, y, 2};
			}
			else {
				s -= (x + N - 1);
				return { N - 1 - s, y, 1};
			}
		}
		else {
			if (s <= N-1-x)
				return { x + s, y, 2};
			else if (s <= (2*(N-1)-x)) {
				s -= ((N-1) - x);
				return { N-1-s, y, 1 };
			}
			else {
				s -= (2*(N-1)-x) ;
				return { s, y, 2 };
			}
		}
	}
	else {
		s = (s % (2 * (M - 1)));
		if (dir == 4) {
			if (s <= y)
				return {  x, y - s, 4 };
			else if (s <= (y + M - 1)) {
				s -= y;
				return { x, s,3 };
			}
			else {
				s -= (y + M - 1);
				return { x, M - 1 - s, 4};
			}
		}
		else {
			if (s <= M - 1 - y)
				return { x, y + s, 3 };
			else if (s <= (2 * (M - 1) - y)) {
				s -= ((M - 1) - y);
				return { x, M - 1 - s, 4 };
			}
			else {
				s -= (2 * (M - 1) - y);
				return { x, s, 3 };
			}
		}

	}
}

int manMove(int j) {
	int answer = 0;
	for (int i = 0; i < N; i++) {
		if (map[i][j]) {
			int idx = map[i][j];
			map[i][j] = 0;
			virusInfo[idx].die = true;
			answer += virusInfo[idx].p;
#if DEBUG
			cout << " idx=" << idx << " 가 잡힘 power=" << virusInfo[idx].p << endl;
#endif

			break;
		}
	}
	return answer;
}


void virusMove() {

	for (int v = 1; v <= K; v++) {
		if (virusInfo[v].die) continue;

		int vx = virusInfo[v].x, vy = virusInfo[v].y;

		map[vx][vy] = 0;
		posNode xy = pos(vx, vy, virusInfo[v].d, virusInfo[v].s);
		virusInfo[v].x = xy.first;
		virusInfo[v].y = xy.second;
		virusInfo[v].d = xy.dir;
		tmpMap[xy.first][xy.second].push_back(v);
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmpMap[i][j].empty()) continue;

			virus power = { -1,-1, 0,0,0 };
			int king = 0;
			while (!tmpMap[i][j].empty()) {
				int back = tmpMap[i][j].back();
				tmpMap[i][j].pop_back();
				
				virusInfo[back].die = true;
				if (power.p < virusInfo[back].p) {
					power = virusInfo[back];
					king = back;
				}
			}
			virusInfo[king].die = false;
			map[virusInfo[king].x][virusInfo[king].y] = king;

#if DEBUG
			cout << i << ", " << j << " -> 위치에 바이러스 =" << king << endl;
#endif
		}
	}
}


int main(void)
{
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	cin >> N >> M >> K;
	int x, y, s, d, b;
	for (int i = 1; i <= K; i++) {
		cin >> x >> y >> s >> d >> b;
		x--;
		y--;
		virusInfo[i] = {x,y,s,d,b, false};
		map[x][y] = i;
	}
	
#if DEBUG
	printMap();
#endif
	int answer = 0;
	for (int j = 0; j < M; j++) {
#if DEBUG
		cout << " <<<" << j << ">>>" << endl;
#endif

		//탐색
		answer += manMove(j);


		//virus 이동
		virusMove();

#if DEBUG
		printMap();
#endif
	}
	cout << answer;
	return 0;
}