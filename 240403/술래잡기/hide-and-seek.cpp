//1030 
#define DEBUG false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
using namespace std;
struct info {
	int x;
	int y;
	int d; //바라보는 방향
	int move_k;
};

pair<int, int> mv[4] = {
	{-1,0}, {0,1}, {1,0}, {0,-1}
};

int N, M, H, K;
bool tree_map[100][100];
vector<int> map[100][100];

char guide[100][100];
char guide_r[100][100];

info man[10000];
info attack;
bool inc = 1;

int totalMan = 0;

//술래 움직임
void inits() {
	int x = N / 2, y = N / 2, d = 0;
	int i;
	for (i = 2 ; x != 0 || y != 0; i++, d = (d+1)%4 ) {
		for (int j = 0; j < i / 2; j++) {
			int prevX = x, prevY = y;
			x = prevX + mv[d].first, y = prevY + mv[d].second;
			if (x == 0 && y == 0) break;
			guide[prevX][prevY] = d;
		}
	}
	
	i--;
	x = -1;
	for (d = 2; x != N / 2 || y != N / 2; i--, d = (d + 3) % 4) {
		for (int j = 0; j < i / 2; j++) {
			int prevX = x, prevY = y;
			x = prevX + mv[d].first, y = prevY + mv[d].second;
			if (x == N/2 && y == N/2) break;
			if (prevX == -1) continue;
			guide_r[prevX][prevY] = d;
		}
	}
	
	guide_r[N / 2 - 1][N / 2] = 2;
#if DEBUGS
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << (int)guide[i][j] << " ";
		}
		cout << endl;
	}
	cout << i << endl;
	cout << "------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << (int)guide_r[i][j] << " ";
		}
		cout << endl;
	}
#endif
}
void printMap() {
	cout << "======" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tree_map[i][j]) cout << "T";
			else if (attack.x == i && attack.y == j) cout << "X";

			cout << "{";
			if (map[i][j].size()) {
				for (auto item : map[i][j])
					cout << item << " ";
			}
			cout << "} ";
		}
		cout << endl;
	}
}

//도망자 움직임 -> 한꺼번에 다 움직임
void run_move(vector<int>& v, int n, int k) {
	int x = man[n].x, y = man[n].y;
	while (!map[x][y].empty()) {
		int m_num = map[x][y].back();
		map[x][y].pop_back();
		
		info& mobj = man[m_num];
		int& d = mobj.d;
		int dx = x + mv[d].first, dy = y + mv[d].second;
		if (dx < 0 || dx >= N || dy < 0 || dy >= N) {
			d = (d + 2) % 4;
			dx = x + mv[d].first, dy = y + mv[d].second;
		}

		if (attack.x != dx || attack.y != dy) {
			mobj.x = dx, mobj.y = dy;
		}
		mobj.move_k = k;
		v.push_back(m_num);
	}

}

int man_dist(int n) {
	int x = attack.x, y = attack.y;
	int mx = man[n].x, my = man[n].y;
	
	int dx = mx < x ? x - mx : mx - x;
	int dy = my < y ? y - my : my - y;
	return dx + dy;
}

void attack_move() {
	int& x = attack.x, & y = attack.y;
	
	x += mv[attack.d].first;
	y += mv[attack.d].second;
	if (inc && x == 0 && y == 0) {
		inc = false;
		attack.d = 2;
	}
	else if (!inc && x == N / 2 && y == N / 2) {
		inc = true;
		attack.d = 0;
	}
	else {
		attack.d = inc ? guide[x][y] : guide_r[x][y];
	}
#if DEBUG
	cout << "attcker sight == " << attack.d << endl;
#endif
}


int man_die(int x, int y) {
	if (tree_map[x][y]) return 0;

	int sums = map[x][y].size();
	totalMan -= sums;
	while (!map[x][y].empty()) {
		int m_n = map[x][y].back();
		map[x][y].pop_back();

		man[m_n].x = -1, man[m_n].y = -1;
	}
	return sums;
}
int attacks(int k) {

	int die_man = 0;
	//자신 위치 공격
	int x = attack.x, y = attack.y;
	die_man += man_die(x, y);
	for (int i = 0; i < 2; i++) {
		x += mv[attack.d].first, y += mv[attack.d].second;
		if (x < 0 || x >= N || y < 0 || y >= N) break;

		die_man += man_die(x, y);
	}
	return die_man * k;
}
void run() {
	int score = 0;
	totalMan = M;
	for (int k = 1; k <= K; k++) {
#if DEBUG
		cout << "time == " << k << endl;
#endif
		vector<int> q;
		for (int i = 1; i <= M; i++) {
			if (man[i].x == -1 || man[i].move_k == k) continue;
			else if (man_dist(i) > 3) continue;
			run_move(q, i, k);
		}

		while (!q.empty()) {
			int man_n = q.back();
			q.pop_back();
			int mx = man[man_n].x, my = man[man_n].y;
			map[mx][my].push_back(man_n);
		}
#if DEBUG
		cout << "man move finish\n";
		printMap();
#endif

		//술래 움직임
		attack_move();
#if DEBUG
		cout << "attacker move finish\n";
		printMap();
#endif
		int add_score = attacks(k);

#if DEBUG
		cout << "attack Score = " << add_score<<endl;
		printMap();
#endif
		score += add_score;
		
		if (!totalMan) break;
	}
	cout << score;
}

int main(void)
{
#if DEBUG
	freopen("input.txt", "r", stdin);
#endif

	cin >> N >> M >> H >> K;
	attack.x = N / 2;
	attack.y = N / 2;
	attack.d = 0;

	for (int i = 1; i <= M; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		if (d == 1) man[i].d = 1;
		else if (d == 2) man[i].d = 2;
		man[i].x = --x;
		man[i].y = --y;
		man[i].move_k = 0;
		map[x][y].push_back(i);
	}

	for (int i = 0; i < H; i++) {
		int x, y;
		cin >> x >> y;
		tree_map[--x][--y] = true;
	}
	inits();

#if DEBUG
	printMap();
#endif

	run();

	return 0;
}