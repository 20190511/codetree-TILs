//0756 ~ 0809 |밥| 0818
//3 ≤ n ≤ 29
//1 ≤ 주어지는 숫자 ≤ 10
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define MAXN	32
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <cstring>
using namespace std;

int N;
int map[MAXN][MAXN], grp_map[MAXN][MAXN], tmp_map[MAXN][MAXN];
int grp_side[MAXN][MAXN];
int grp_cnt[MAXN];
pair<int, int> grpXY[MAXN], mv[4] = {
	{0,1}, {0,-1}, {1,0}, {-1,0}
};
int grpCnt = 0;
int score[4] = { 0,0,0,0 };

void printMap(int m[MAXN][MAXN]) {
	cout << "=========" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

void printMap2() {
	cout << "=========" << endl;
	for (int i = 1; i <= grpCnt; i++) {
		for (int j = 1; j <= grpCnt; j++) {
			cout << grp_side[i][j] << " ";
		}
		cout << endl;
	}
}

//Rotate
void s_rotate(int x, int y, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[j + x][y + size - i - 1]  = tmp_map[i + x][j + y];
		}
	}
}
void total_rotate() {
	memcpy(tmp_map, map, sizeof(tmp_map));
	
	//중앙 rotate
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == N / 2 || j == N / 2) {
				map[i][j] = tmp_map[j][N - i - 1];
			}
		}
	}

	// 사각형 rotate
	int x = 0, y = 0, s_size = N / 2;
#if DEBUG
	cout << "small size = "<<s_size << endl;
#endif
	s_rotate(x, y, s_size);
	s_rotate(x + s_size + 1, y, s_size);
	s_rotate(x, y + s_size + 1, s_size);
	s_rotate(x + s_size + 1, y + s_size + 1, s_size);

}

//Grouping
void grouping() {
	grpCnt = 0;
	memset(grp_map, 0, sizeof(grp_map));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grp_map[i][j]) continue;

			grpCnt++;
			queue<pair<int, int>> q;
			q.push({i,j});

			grp_map[i][j] = grpCnt;
			grpXY[grpCnt] = {i,j};
			grp_cnt[grpCnt] = 1;
			int curColor = map[i][j];
			while (!q.empty()) {
				int cx = q.front().first, cy = q.front().second;
				q.pop();
				for (int i = 0; i < 4; i++) {
					int dx = cx + mv[i].first, dy = cy + mv[i].second;
					if (dx < 0 || dx >= N || dy < 0 || dy >= N || grp_map[dx][dy] || map[dx][dy] != curColor) continue;
					
					grp_map[dx][dy] = grpCnt;
					q.push({ dx,dy });
					grp_cnt[grpCnt]++;
				}
			}
		}
	}


#if DEBUG
	cout << "Group Map Finish\n";
	printMap(grp_map);
#endif
}


int grouping2() {
	int totalScore = 0;
	bool v [MAXN][MAXN];
	memset(v, 0, sizeof(v));
	memset(grp_side, 0, sizeof(grp_side));
	for (int x = 1; x <= grpCnt; x++) {
		int ccx = grpXY[x].first, ccy = grpXY[x].second;
		v[ccx][ccy] = true;
		
		queue<pair<int, int>> q;
		q.push({ ccx,ccy });
		int curGrp = grp_map[ccx][ccy];
		int cur_col = map[ccx][ccy];
		while (!q.empty()) {
			int cx = q.front().first, cy = q.front().second;
			q.pop();
			for (int i = 0 ; i < 4 ; i++) {
				int dx = mv[i].first + cx, dy = mv[i].second + cy;
				if (dx < 0 || dx >= N || dy < 0 || dy >= N || v[dx][dy]) continue;
				else if (grp_map[dx][dy] != curGrp) {
					grp_side[x][grp_map[dx][dy]]++;
					continue;
				}
				
				v[dx][dy] = true;
				q.push({ dx,dy });
			}
		}
		for (int xx = 1; xx <= grpCnt; xx++) {
			if (!grp_side[x][xx]) continue;
			int side_cnt = grp_side[x][xx];
			int other_col = map[grpXY[xx].first][grpXY[xx].second];
			int each_cnt = (grp_cnt[x] + grp_cnt[xx]) * other_col * cur_col * side_cnt;
#if DEBUG
			cout << x << "," << xx << "||" << "(" << grp_cnt[x] << " + " << grp_cnt[xx] << ") * " << other_col << " * " << cur_col << " * " << side_cnt << " = " << each_cnt << endl;
#endif
			totalScore += each_cnt;
		}
		//Counting
	}

#if DEBUG
	cout << "Adj Cnt = "<< totalScore <<"\n";
	printMap2();
	//printMap(grp_side);
#endif

	return totalScore;
}

void run() {
	for (int t = 0; t < 4; t++) {
#if DEBUG
		cout << "++++++ t == " << t << " ++++++" << endl;
#endif
		grouping();
		int sums = grouping2();
		score[t] = sums;
		total_rotate();
#if DEBUG
		cout << "rotate Finish" << endl;
		printMap(map);
#endif
	}
	int ans = score[0] + score[1] + score[2] + score[3];
	cout << ans;
}
int main(void)
{
#if DEBUG
	freopen("input.txt", "r", stdin);
#endif

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}


	run();

	return 0;
}