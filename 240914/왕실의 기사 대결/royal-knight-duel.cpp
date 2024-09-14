//1415 ~ 1438(모니터이슈 5분) ~ 1540
// 1시간 20분
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
#define DEBUG false

pair<int, int> mv[4] = {
	{-1,0}, {0,1}, {1,0}, {0,-1}
};

struct Gisa{
	int hp;
	int oHp;
	int x;
	int y;
	int h;
	int w;
	Gisa(int x=0, int y=0, int h=0, int w=0, int hp=0, int oHp = 0) : x(x), y(y), oHp(oHp), h(h), w(w), hp(hp) {}
};

int map[41][41];
int gmap[41][41];

int vec[100][2];
int L, N, Q;
Gisa gisa[41];

void printMap() {
	for (int i = 1; i <= N; i++) {
		if (gisa[i].hp <= 0) {
			cout << "[" << i << "] die" << endl;
			continue;
		}
		cout << "[" << i << "] hp=" << gisa[i].hp << "-> (" << gisa[i].x << ", " << gisa[i].y << ")" << endl;
	}
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			if (!gmap[i][j])
				cout << " ("<<map[i][j]<<") ";
			else
				cout << gmap[i][j] << "(" << map[i][j] << ") ";
		}
		cout << endl;
	}
	cout << "=============================" << endl;
}

void move(int num, int dir) {
	vector<int> manS;
	vector<int> q;

	bool manCheck[41] = { 0, };
	manCheck[num] = true;

	//stack 넣기
	q.push_back(num);
	manS.push_back(num);
	while (!q.empty()) {
		int n = q.back();
		q.pop_back();
		int cx = gisa[n].x, cy = gisa[n].y;
		
		for (int i = cx; i <= cx + gisa[n].h - 1; i++) {
			for (int j = cy; j <= cy + gisa[n].w - 1; j++) {
				int dx = i + mv[dir].first, dy = j + mv[dir].second;

				if (dx <= 0 || dx > L || dy <= 0 || dy > L || map[dx][dy] == 2) return;

				if (gmap[dx][dy] == n) continue;

				int curMan = gmap[dx][dy];
				if (manCheck[curMan]) continue;

				if (curMan) {
					manCheck[curMan] = true;
					manS.push_back(curMan);
					q.push_back(curMan);
				}

			}
		}
	}

	while (!manS.empty()) {
		int n = manS.back();
		manS.pop_back();
#if DEBUG
		cout << "pop :: " << n << endl;
#endif
		int cx = gisa[n].x, cy = gisa[n].y;
		gisa[n].x = cx + mv[dir].first;
		gisa[n].y = cy + mv[dir].second;

		for (int i = cx; i <= cx + gisa[n].h - 1; i++) {
			for (int j = cy; j <= cy + gisa[n].w - 1; j++) {
				gmap[i][j] = 0;
			}
		}

		for (int i = cx; i <= cx + gisa[n].h - 1; i++) {
			for (int j = cy; j <= cy + gisa[n].w - 1; j++) {
				
				int dx = i + mv[dir].first, dy = j + mv[dir].second;
				gmap[dx][dy] = n;
				if (map[dx][dy] == 1 && num != n) {
					gisa[n].hp--;
				}
			}
		}


		if (gisa[n].hp > 0) continue;
		// Gisa Die Check

		cx = gisa[n].x, cy = gisa[n].y;
		for (int i = cx; i <= cx + gisa[n].h - 1; i++) {
			for (int j = cy; j <= cy + gisa[n].w - 1; j++) {
				gmap[i][j] = 0;
			}
		}

		gisa[n] = Gisa(0, 0, 0, 0, 0, 0);
	}
}

int main(void)
{
#if DEBUG
	freopen("test.txt", "r", stdin);
#endif

	cin >> L >> N >> Q;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		gisa[i] = Gisa(r,c,h,w,k, k);

		for (int x = r; x <= r + h - 1; x++) {
			for (int y = c; y <= c + w - 1; y++) {
				gmap[x][y] = i;
			}
		}
	}

	for (int i = 0; i < Q; i++) {
		cin >> vec[i][0] >> vec[i][1];
	}

#if DEBUG
	printMap();
#endif

	for (int num = 0; num < Q; num++) {
#if DEBUG
		if (num == 5)
			cout << "in" << endl;
#endif
		int n = vec[num][0], dir = vec[num][1];
		move(n, dir);


#if DEBUG
		cout << "---- [ " << num + 1 << "] ----" << endl;
		cout << " move : " << n << ", dir =" << dir << endl;
		printMap();
#endif
	}

	int sums = 0;
	for (int i = 1; i <= N; i++) {
		if (gisa[i].hp <= 0) continue;

		sums += (gisa[i].oHp - gisa[i].hp);
	}
	cout << sums;
	
	return 0;
}

