//1020 ~ 1250 
// 회전 시작, 끝 점 오류 수정
// i 변수중첩실수..
//실수 1. 꼬리잡기 부분이 다 차 있을 수도 있다.
#define DEBUG	false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

struct info {
	int hx;
	int hy;
	int tx;
	int ty;
	int teamCnt;
};

int score = 0;
bool line[20][20], man[20][20];
int N, M, K;
pair<int, int> tailQ[5];
info team[5];

pair<int, int> mv[4] = {
	{1,0}, {-1,0} ,{0,-1}, {0,1}
};

void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int cf = false;
			for (int x = 0; x < M; x++) {
				if (team[x].hx == i && team[x].hy == j) {
					cout << "H ";
					cf = true;
				}
				else if (team[x].tx == i && team[x].ty == j) {
					cout << "T ";
					cf = true;

				}
			}
			if (cf) continue;
			if (man[i][j]) cout << "M ";
			else if (line[i][j]) cout << "1 ";
			else
				cout << "  ";
		}
		cout << endl;
	}
}



int manCnt(int x, int y, int& teamNum) {

	for (int i = 0; i < M; i++) {
		if (team[i].tx == x && team[i].ty == y) {
			teamNum = i;
			return team[i].teamCnt;
		}
		else if (team[i].hx == x && team[i].hy == y) {
			teamNum = i;
			return 1;
		}
	}
	int cx = x, cy = y;
	int count = 1;
	int prevX=cx, prevY=cy;

	for (int i = 0; i < 4; i++) {
		int dx = cx + mv[i].first, dy = cy + mv[i].second;
		if (prevX == dx && prevY == dy) continue;
		if (dx < 0 || dx >= N || dy < 0 || dy >= N || !line[dx][dy] || !man[dx][dy]) continue;

		prevX = cx, prevY = cy;
		cx = dx, cy = dy;
		count++;
		for (int j = 0; j < M; j++) {

			if (cx == team[j].hx && cy == team[j].hy) {
#if DEBUG
				cout << "in manCnt :: " << cx << "," << cy << ", count = " << count << endl;
#endif
				teamNum = j;
				return count;
			}
			else if (cx == team[j].tx && cy == team[j].ty) {
#if DEBUG
				cout << "in manCnt :: " << cx << "," << cy << ", count = " << team[j].teamCnt - count + 1 << endl;
#endif
				teamNum = j;
				return team[j].teamCnt - count + 1;
			}
		}
		
		i = -1;
	}


#if DEBUG
	cout << "error" << endl;
#endif
	return 0;
}

void findTail() {
	bool vs[20][20];
	memset(vs, 0, sizeof(vs));
	for (int i = 0; i < M; i++) {
		info& obj = team[i];
		queue < pair<int, int> > q;
		int cx = obj.hx, cy = obj.hy;
		vs[cx][cy] = true;
		q.push({ cx, cy });

		while (!q.empty()) {
			cx = q.front().first, cy = q.front().second;
			q.pop();
			for (int j = 0; j < 4; j++) {
				int dx = cx + mv[j].first, dy = cy + mv[j].second;
				if (dx < 0 || dx >= N || dy < 0 || dy >= N || !line[dx][dy] || vs[dx][dy]) continue;
				if (!man[dx][dy]) continue;

				obj.teamCnt++;
				vs[dx][dy] = true;
				for (int i = 0; i < M; i++) {
					if (tailQ[i].first == dx && tailQ[i].second == dy)
						obj.tx = dx, obj.ty = dy;
				}
				q.push({ dx,dy });
				break;
			}
		}
		//obj.tx = cx, obj.ty = cy;
#if DEBUG
		cout << "team NUM " << i + 1;
		cout << "  tail = " << obj.tx << ", " << obj.ty << " --> teamCount = " << obj.teamCnt << endl;
#endif
	}
}

void man_move() {
	for (int x = 0; x < M; x++) {
		info& obj = team[x];
		int cx = obj.hx, cy = obj.hy, nx = cx, ny = cy;
		int tx = obj.tx, ty = obj.ty;

		for (int i = 0; i < 4; i++) {
			int dx = cx + mv[i].first, dy = cy + mv[i].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || !line[dx][dy] || man[dx][dy]) continue;
			man[dx][dy] = true;
			nx = dx, ny = dy;
			break;
		}
		
		if (nx == cx && ny == cy) {
			for (int i = 0; i < 4; i++) {
				int dx = tx + mv[i].first, dy = ty + mv[i].second;
				if (dx < 0 || dx >= N || dy < 0 || dy >= N || !line[dx][dy] || (obj.hx == dx && obj.hy == dy)) continue;
				obj.tx = dx, obj.ty = dy;
				break;
			}
			obj.hx = tx;
			obj.hy = ty;
			continue;
			/*
			for (int i = 0; i < 4; i++) {
				int dx = cx + mv[i].first, dy = cy + mv[i].second;
				if (dx < 0 || dx >= N || dy < 0 || dy >= N || !line[dx][dy] || (obj.tx == dx && obj.ty == dy)) continue;
				obj.hx = dx, obj.hy = dy;
				break;
			}
			obj.tx = cx;
			obj.ty = cy;
			*/
		}

		obj.hx = nx, obj.hy = ny;
		//꼬리부분
		for (int i = 0; i < 4; i++) {
			int dx = tx + mv[i].first, dy = ty + mv[i].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || !line[dx][dy] || !man[dx][dy]) continue;
			man[tx][ty] = false;
			man[dx][dy] = true;
			obj.tx = dx, obj.ty = dy;
			break;
		}
		
	}
}
void ball_move(int k) {
	int num = k % N;
	int dir = (k / N) % 4;

	int rx = -1, ry = -1;
	if (dir == 0) {
		for (int i = 0; i < N; i++) {
			if (man[num][i]) {
				rx = num, ry = i;
				break;
			}
		}
	}
	else if (dir == 1) {
		for (int i = N-1; i >= 0; i--)
		{
			if (man[i][num]) {
				rx = i, ry = num;
				break;
			}
		}
	}
	else if (dir == 2) {
		num = N - num - 1;
		for (int i = N-1; i >= 0; i--) {
			if (man[num][i]) {
				rx = num, ry = i;
				break;
			}
		}
	}
	else if (dir == 3) {
		num = N - num - 1;
		for (int i = 0; i < N; i++) {
			if (man[i][num]) {
				rx = i, ry = num;
				break;
			}
		}
	}

	if (rx == -1)
		return;

	int teamNum = -1;
	int count = manCnt(rx, ry, teamNum);
	swap(team[teamNum].hx, team[teamNum].tx);
	swap(team[teamNum].hy, team[teamNum].ty);
	
#if DEBUG
	cout << "ball move :: " << k << ", score = " << count * count << ", team Num = " << teamNum << ", num =" << num << ", dir = " << dir << endl;
	cout << "head <->tail\n";
	cout << teamNum << ":: head " << team[teamNum].hx << ", " << team[teamNum].hy << ", tail = " << team[teamNum].tx << ", " << team[teamNum].ty << endl;
#endif
	score += count * count;
}
void run() {
	for (int i = 0; i < K; i++) {
#if DEBUG
		cout << "+++++ " << i << " +++++" << endl;
#endif
		man_move();
#if DEBUG
		cout << "man move finish" << endl;
		printMap();
		for (int i = 0; i < M; i++) {
			cout << i << ":: head " << team[i].hx << ", " << team[i].hy << ", tail = " << team[i].tx << ", " << team[i].ty << endl;
		}
#endif
		ball_move(i);
#if DEBUG
#endif
	}
	cout << score;
}
int main(void)
{
#if DEBUG
	freopen("input.txt", "r", stdin);
#endif

	cin >> N >> M >> K;
	int teamCnt = 0;
	int tailCnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int t;
			cin >> t;
			if (t == 1) {
				team[teamCnt].hx = i;
				team[teamCnt].hy = j;
				team[teamCnt].teamCnt++;

				line[i][j] = true;
				man[i][j] = true;
				teamCnt++;
			}
			else if (t >= 2) {
				if (t < 4)
					man[i][j] = true;
				if (t == 3)
					tailQ[tailCnt++] = {i,j};
				line[i][j] = true;
			}
		}
	}

#if DEBUG
	printMap();
#endif
	findTail();
	run();
	return 0;
}
