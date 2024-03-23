//1850
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

struct santaObj {
	int status; // -1 일 시 죽음 (쫓겨남)
	int score;
	int x;
	int y;
};
#define ruN	99
int map[50][50];
santaObj santa[30];
pair<int, int> ru_pos;
int santaN, ruP, santaP, n, m;
int santaCnt;


void printMap() {
	cout << "===========\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << map[i][j] << "  ";
		}
		cout << endl;
	}
}

//산타 밀려남 구현
void collison(int santaN, int dx, int dy, int power) {
	// 첫번째 밀려남
	int ndx = dx * power, ndy = dy * power;
	int csx = santa[santaN - 1].x, csy = santa[santaN - 1].y;
	//map[csx][csy] = 0;

	int newX = ndx + csx, newY = ndy + csy;
	if (newX < 0 || newX >= n || newY < 0 || newY >= n) {
		santa[santaN - 1].status = -1;
		santaCnt--;
		return;
	}
	if (!map[newX][newY]) {
		santa[santaN - 1].x = newX;
		santa[santaN - 1].y = newY;
		map[newX][newY] = santaN;
		return;
	}

	//한칸 씩 밀려남
	vector<int> pos;
	int curSanta = santaN;
	int mx = newX, my = newY;
	while (mx >= 0 && mx < n && my >= 0 && my < n && map[mx][my]) {
		santa[curSanta - 1].x = mx, santa[curSanta - 1].y = my;
		pos.push_back(curSanta);
		curSanta = map[mx][my];
		mx += dx, my += dy;
	}
	
	santa[curSanta - 1].x = mx, santa[curSanta - 1].y = my;
	pos.push_back(curSanta);
	
	while (!pos.empty()) {
		int sn = pos.back();
		pos.pop_back();
		int tx = santa[sn - 1].x, ty = santa[sn - 1].y;
		if (tx < 0 || tx >= n || ty < 0 || ty >= n) {
			santa[sn - 1].status = -1;
			santaCnt--;
			continue;
		}
		map[santa[sn - 1].x][santa[sn - 1].y] = sn;
		
	}
}


//루돌프 이동 
void ru_run() {
	
	int sx=-1, sy=-1;
	double rad = 3000;
	int cx = ru_pos.first, cy = ru_pos.second;

	for (int i = 0; i < santaN; i++) {
		if (santa[i].status == -1)
			continue;
		int csx = santa[i].x, csy = santa[i].y;
		double tmp_rad = (csx - cx) * (csx - cx) + (csy - cy) * (csy - cy);
		if ((tmp_rad < rad) || 
			((tmp_rad == rad) && csx > sx) || 
			((tmp_rad == rad) && (csx == sx) && csy > sy))  {

			sx = csx, sy = csy;
			rad = tmp_rad;
		}
	}
	
	int dx, dy;
	if (sx == cx) dx = 0;
	else if (sx > cx) dx = 1;
	else dx = -1;

	if (sy == cy) dy = 0;
	else if (sy > cy) dy = 1;
	else dy = -1;

	// 루돌프 이동
	map[cx][cy] = 0;
	int newX = cx + dx, newY = cy + dy;
	ru_pos = { newX,newY};

	//산타 존재
	if (map[newX][newY]) {
		int tag = map[newX][newY];
		santa[tag - 1].score += ruP;
		santa[tag - 1].status = 2; // 이번턴, 다음턴 기절
		collison(tag, dx, dy, ruP);
	}

	map[newX][newY] = ruN;
}

//산타 이동
void santa_run() {
	pair<int, int> mv[4] = {
		{-1,0}, {0,1}, {1,0}, {0,-1}
	};

	int rx = ru_pos.first, ry = ru_pos.second;
	for (int i = 0; i < santaN; i++) {
		if (santa[i].status) continue;

		int sx = santa[i].x, sy = santa[i].y;
		double cur_rad = (sx - rx) * (sx - rx) + (sy - ry) * (sy - ry);

		int ddx, ddy, dj=-5;
		for (int j = 0; j < 4; j++) {
			int dx = sx + mv[j].first, dy = sy + mv[j].second;
			if (dx < 0 || dx >= n || dy < 0 || dy >= n || (map[dx][dy] != ruN && map[dx][dy] > 0)) continue;

			double next_rad = (dx - rx) * (dx - rx) + (dy - ry) * (dy - ry);
			if (cur_rad <= next_rad) continue;
			
			cur_rad = next_rad;
			ddx = dx, ddy = dy;
			dj = j;
		}
		
		if (dj == -5) continue;
		map[sx][sy] = 0;
		if (map[ddx][ddy] == ruN) {
			santa[i].score += santaP;
			santa[i].status = 2;
			santa[i].x = ddx, santa[i].y = ddy;
			collison(i + 1, -mv[dj].first, -mv[dj].second, santaP);
		}
		else {
			map[ddx][ddy] = i + 1;
			santa[i].x = ddx, santa[i].y = ddy;
		}

	}
}
void run() {
	santaCnt = santaN;
	for (int i = 0; i < m; i++) {
#if DEBUG
		cout << i + 1 << "번째 시도 >> " << endl;
#endif
		ru_run();
		if (!santaCnt)
			break;
#if DEBUG
		printMap();
#endif
		santa_run();
		if (!santaCnt)
			break;

		for (int i = 0; i < santaN; i++) {
			if (santa[i].status >= 0) {
				santa[i].score++;
				if (santa[i].status)
					santa[i].status--;
			}
		}

#if DEBUG
		printMap();
#endif

	}

	for (int i = 0 ; i < santaN ; i++)
		cout << santa[i].score << " ";
	cout << "\n";
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
	cin >> n >> m >> santaN >> ruP >> santaP;
	int tx, ty;
	cin >>tx >> ty;
	map[tx - 1][ty - 1] = ruN;
	ru_pos = {tx-1, ty-1};
	for (int i = 0; i < santaN; i++) {
		int n, x, y;
		cin >> n >> x >> y;
		santa[n - 1] = { 0,0,x - 1,y - 1 };
		map[x - 1][y - 1] = n;
	}

	run();

	return 0;
}