//1023
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#include <iostream>
#include <deque>
#include <vector>
#include <cstring>
using namespace std;


int map[10][10], man_map[10][10]; // 사람 수 표기 <- 점수 시 곱하기
int N, M, K;
int moving = 0;

pair<int, int> ex, mv[4] = {
	{-1,0}, {1,0}, {0,-1}, {0,1}
};
int totalMan;
vector<pair<int,int>> man_pos;

void printMap(int map[10][10]) {
	cout << "=========" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int getDist(int ox, int oy, int dx, int dy) {
	int distX = dx < ox ? ox - dx : dx - ox;
	int distY = dy < oy ? oy - dy : dy - oy;
	int dist = distX + distY;
	return dist;
}

void getRotate(int ux, int uy, int r) {
	int tmp[10][10], tmp2[10][10];
	memcpy(tmp, map, sizeof(tmp));
	memcpy(tmp2, man_map, sizeof(tmp2));

	bool change = true;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			if ((ex.first == r - j - 1 + ux) && (ex.second == i + uy) && change) 
				ex = { i + ux, j + uy }, change=false;
			map[i + ux][j + uy] = tmp[r - j - 1 + ux][i + uy];
			man_map[i + ux][j + uy] = tmp2[r - j - 1 + ux][i + uy];
			if (map[i + ux][j + uy])
				map[i + ux][j + uy]--;
		}
	}
}
bool move() {
	int tmp_map[10][10];
	memset(tmp_map, 0, sizeof(tmp_map));

	int ox = ex.first, oy = ex.second;
	vector<pair<int, int>> tmp_man_pos;

	while (!man_pos.empty()) {
		int sx = man_pos.back().first, sy = man_pos.back().second;
		int curDist = getDist(ox, oy, sx, sy);

		man_pos.pop_back();

		for (int i = 0; i < 4; i++) {
			int dx = sx + mv[i].first, dy = sy + mv[i].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || map[dx][dy]) {
				if (i == 3) {
					tmp_man_pos.push_back({ sx,sy });
					tmp_map[sx][sy] = man_map[sx][sy];
				}
				continue;
			}

			int newDist = getDist(ox, oy, dx, dy);

			//도착했을 때
			if (!newDist) {
				moving += man_map[sx][sy];
				break;
			}
			else if (curDist > newDist) {
				moving += man_map[sx][sy];
				if (!tmp_map[dx][dy]) tmp_man_pos.push_back({ dx,dy });
				tmp_map[dx][dy] += man_map[sx][sy];
				break;
			}

			if (i == 3) {
				tmp_man_pos.push_back({ sx,sy });
				tmp_map[sx][sy] = man_map[sx][sy];
			}
		}
	}
	if (tmp_man_pos.empty())
		return false;

	int r = 0x7FFFFFFF, w = N, h = N;
	for (auto s : tmp_man_pos) {
		int distX = (ox < s.first ? s.first - ox : ox - s.first) + 1;
		int distY = (oy < s.second ? s.second - oy : oy - s.second) + 1;
		int maxVal = max(distX, distY);
		if ((maxVal <= r) && (s.first <= w) && (s.second <= h)) {
			w = s.first;
			h = s.second;
			r = maxVal;
		}
	}

	if (w <= ox && h <= oy)
		w = ox, h = oy;

	// 정사각형 설정
	int dx = w, dy = h;
	int ux = dx - r + 1, uy = dy - r + 1;
	if (ux < 0) {
		ux += -ux;
		dx += -ux;
	}

	if (uy < 0) {
		uy += -uy;
		dy += -uy;
	}

	memcpy(man_map, tmp_map, sizeof(tmp_map));
	getRotate(ux, uy, r);
#if DEBUG
	printMap(map);
	printMap(man_map);
	cout << "exit :: " << ex.first << " " << ex.second<<endl;
	cout << "rotate finsh" << endl;
#endif
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (man_map[i][j])
				man_pos.push_back({ i,j });
		}
	}


	return true;
	
}
void run() {
	for (int i = 0; i < K; i++) {
	//참가자 이동
		if (!move())
			break;
	}
	cout << moving << "\n";
	cout << ex.first+1 << " " << ex.second+1 << "\n";
}
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	totalMan = M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		man_pos.push_back({ a,b });
		man_map[a][b]++;
	}

	cin >> ex.first >> ex.second;
	ex.first--, ex.second--;

	run();
	return 0;
}