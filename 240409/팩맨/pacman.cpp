//0916
#define DEBUG	false
#define DEBUGS	false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
/**
* 첫 줄에는 몬스터의 마리 수 m과 진행되는 턴의 수 t이 주어집니다. 
두번째 줄에는 팩맨의 격자에서의 초기 위치 r, c가 주어집니다. 
r은 격자의 몇번째 행인지, c는 격자의 몇번째 열인지를 나타냅니다. 
그 다음 줄부터 m개의 줄에는 몬스터의 위치 r, c와 방향 정보 d가 주어집니다. 
r과 c는 각각 격자의 몇번째 행인지, 
c는 격자의 몇번째 열인지를 의미하고, 방향 d는 1부터 순서대로 ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 를 의미합니다.

1 ≤ m ≤ 10
1 ≤ t ≤ 25
몬스터의 초기 위치와 팩맨의 초기 위치는 같을 수도 있습니다.
턴이 진행되는 동안 살아있는 몬스터의 수가 100만개가 넘는 입력은 주어지지 않는다고 가정해도 좋습니다.
*/
#define CHECK(X,Y) (X < 0 || X >= 4 || Y < 0 || Y >= 4) 
vector<int> tmp_map[4][4];
vector<int> mon_map[4][4], egg_map[4][4];
vector<int> die_map[4][4];
pair<int, int> packman = { 0,0 };
int M, T, N=4;

//packman 0번부터 2칸씩 증가.
//↑, ↖, ←, ↙, ↓, ↘, →, ↗
// 0  1   2   3    4   5  6   7
pair <int, int> mv[8] = {
	{-1,0}, {-1,-1}, {0,-1}, {1,-1},
	{1,0}, {1,1}, {0,1}, {-1,1}
};

void print_map(vector<int>(& m)[4][4]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (packman.first == i && packman.second == j)
				cout << "O";

			cout << "{";
			for (auto x : m[i][j])
				cout << x << " ";
			cout << "} ";
		}
		cout << endl;
	}
	cout << "---------" << endl;
}

void dups() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (auto item : mon_map[i][j]) {
				egg_map[i][j].push_back(item);
			}
		}
	}
}
void mon_move() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			while (!mon_map[i][j].empty()) {
				int curDir = mon_map[i][j].back();
				bool changed = false;
				mon_map[i][j].pop_back();

				for (int d = curDir, cnt = 0; cnt < 8; d = (d + 1) % 8, cnt++) {
					int dx = i + mv[d].first, dy = j + mv[d].second;
					if (dx < 0 || dx >= N || dy < 0 || dy >= N) continue;
					if (packman.first == dx && packman.second == dy)continue;
					if (die_map[dx][dy].size()) continue;

					changed = true;
					tmp_map[dx][dy].push_back(d);
					break;
				}
				if (!changed) {
					tmp_map[i][j].push_back(curDir);
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			while (!tmp_map[i][j].empty()) {
				mon_map[i][j].push_back(tmp_map[i][j].back());
				tmp_map[i][j].pop_back();
			}
		}
	}
}
void pack_move() {

	int max_die = 0, saved[3] = { 0,0,0 };
	int cntMap[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			cntMap[i][j] = (int)mon_map[i][j].size();

	int cx = packman.first, cy = packman.second;
	int cur_die = 0;
	for (int a = 0; a < 8; a += 2) {
		int dx1 = cx + mv[a].first, dy1 = cy + mv[a].second;
		if (CHECK(dx1, dy1)) continue;
		
		cur_die += cntMap[dx1][dy1];
		cntMap[dx1][dy1] = 0;
		for (int b = 0; b < 8; b += 2) {
			int dx2 = dx1 + mv[b].first, dy2 = dy1 + mv[b].second;
			if (CHECK(dx2, dy2)) continue;

			cur_die += cntMap[dx2][dy2];
			cntMap[dx2][dy2] = 0;
			for (int c = 0; c < 8; c += 2) {
				int dx3 = dx2 + mv[c].first, dy3 = dy2 + mv[c].second;
				if (CHECK(dx3, dy3)) continue;

				if (cur_die + cntMap[dx3][dy3] > max_die) {
					max_die = cur_die + cntMap[dx3][dy3];
					saved[0] = a, saved[1] = b, saved[2] = c;
				}
			}
			cntMap[dx2][dy2] = (int)mon_map[dx2][dy2].size();
			cur_die -= (int)mon_map[dx2][dy2].size();
		}
		cntMap[dx1][dy1] = (int)mon_map[dx1][dy1].size();
		cur_die -= (int)mon_map[dx1][dy1].size();
	}

#if DEBUG
	cout << "maxEat = " << max_die << " --> saved = (";
	for (int i = 0; i < 3; i++)
		cout << saved[i] << " ";
	cout << ")" << endl;
#endif

	int dx = cx, dy = cy;
	for (int i = 0; i < 3; i++) {
		dx += mv[saved[i]].first, dy += mv[saved[i]].second;
		if (mon_map[dx][dy].empty()) continue;
		die_map[dx][dy].push_back(3);
		mon_map[dx][dy].clear();
	}
	packman = { dx,dy };
}
void die_clear() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (die_map[i][j].empty())
				continue;
			for (int idx = 0; idx < (int)die_map[i][j].size(); idx++) {
				if (die_map[i][j][idx]) die_map[i][j][idx]--;
			}

			if (!die_map[i][j].back()) {
				die_map[i][j].clear();
			}
		}
	}
}
void revise() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (egg_map[i][j].empty()) continue;
			
			mon_map[i][j].insert(mon_map[i][j].begin(), egg_map[i][j].begin(), egg_map[i][j].end());
			egg_map[i][j].clear();
		}
	}
}

void run() {
	for (int t = 1; t <= T; t++) {
#if DEBUG
		cout << "+++++ timer=" << t << " +++++" << endl;
#endif
		// 1. 복제 시도
		dups();
#if DEBUG
		cout << "duplicate finish\n";
		print_map(egg_map);
#endif

		// 2. 몬스터 이동
		mon_move();
#if DEBUG
		cout << "monster move finish" << endl;
		print_map(mon_map);
#endif

		// 3. 팩맨 이동 ->  상좌하우
		pack_move();
#if DEBUG
		cout << "packman move finish" << endl;
		print_map(mon_map);
		print_map(die_map);
#endif

		// 4. 몬스터 시체 소멸 -> die_map --
		die_clear();
#if DEBUG
		cout << "die_man clear finish" << endl;
		print_map(die_map);
#endif

		// 5. 몬스터 복제 완료 -> egg_map
		revise();
#if DEBUG
		cout << "revise finish" << endl;
		print_map(mon_map);
#endif
	}

	int counts = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			counts += (int)mon_map[i][j].size();
		}
	}
	cout << counts;
}
int main(void)
{
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif

	cin >> M >> T;
	int tx, ty, dir;
	cin >> tx >> ty;
	packman = { tx - 1, ty - 1 };
	for (int i = 0; i < M; i++) {
		cin >> tx >> ty >> dir;
		mon_map[tx - 1][ty - 1].push_back(dir - 1);
	}

#if DEBUG
	print_map(mon_map);
#endif
	run();
	return 0;
}