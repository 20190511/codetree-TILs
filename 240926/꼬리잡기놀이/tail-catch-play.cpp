//꼬리잡기 놀이 0940
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define REOPEN false
#define BACK 3
#define FRONT 1
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

struct ptr
{
	int fx;
	int fy;
	int bx;
	int by;
	
	ptr(int fx=0, int fy= 0, int bx = 0, int by = 0) : fx(fx), fy(fy), bx(bx), by(by) {}
};

int N, M, K, score=0;
ptr team[6];
int map[21][21], teamMap[21][21];
pair<int, int> mv[4] = {
	{0,1}, {0,-1}, {1,0}, {-1,0}
};

void printTeam() {
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << teamMap[i][j] << " ";
		}
		cout << endl;
	}
	cout << "========" << endl;
}
void printMap() {


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 1; i <= M; i++) {
		cout << "[" << i << "] head=" << team[i].fx << ", " << team[i].fy << ", back=" << team[i].bx << ", " << team[i].by << endl;
	}

	cout << "===================" << endl;

}

void initSetting();
void move();
void ball(int round);

int main(void) {
#if REOPEN
	freopen("q.txt", "r", stdin);
#endif

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	initSetting();
#if DEBUG
	cout << " --- team Map ---" << endl;
	printTeam();
	cout << " === init === " << endl;
	printMap();
#endif



	for (int k = 1; k <= K; k++) {
#if DEBUG
		cout << " <<< round = " << k << " >>> " << endl << endl<< endl;
#endif
		//Move
		move();

#if DEBUG
		printMap();
#endif
		//ball
		ball(k);

#if DEBUG
		cout << "After Ball" << endl;
		printMap();
#endif

	}

	cout << score;
	return 0;
}

#define BALLDEBUG false
void debugMap(int v[21][21]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------" << endl;
}

void ball(int round) {

#if BALLDEBUG
	int v[21][21] = { 0, };
	int dbgs = 1;
#endif

	int sec = ((round-1) / N) % 4;
	int detail = (round - 1) % N;
	
#if BALLDEBUG
	cout << "sec=" << sec << endl;
#endif
	int s = -1;
	int sx = -1, sy = -1;
	if (sec == 0) {
		s = detail;
		for (int i = 0 ; i < N; i++) {
			int dx = s, dy = i;
			if (map[dx][dy] >= 1 && map[dx][dy] <= 3) {
				sx = dx, sy = dy;
				break;
			}
#if BALLDEBUG
			v[dx][dy] = dbgs++;
#endif
		}
	}
	else if (sec == 1) {
		s = detail;
		for (int i = N - 1; i >= 0; i--) {
			int dx = i, dy = s;
			if (map[dx][dy] >= 1 && map[dx][dy] <= 3) {
				sx = dx, sy = dy;
				break;
			}

#if BALLDEBUG
			v[dx][dy] = dbgs++;
#endif
		}
	}
	else if (sec == 2) {
		s = (N - 1) - detail;
		for (int i = N - 1; i >= 0; i--) {
			int dx = s, dy = i;
			if (map[dx][dy] >= 1 && map[dx][dy] <= 3) {
				sx = dx, sy = dy;
				break;
			}

#if BALLDEBUG
			v[dx][dy] = dbgs++;
#endif
		}
	}
	else if (sec == 3) {
		s = (N - 1) - detail;
		for (int i = 0; i < N; i++) {
			int dx = i, dy = s;
			if (map[dx][dy] >= 1 && map[dx][dy] <= 3) {
				sx = dx, sy = dy;
				break;
			}

#if BALLDEBUG
			v[dx][dy] = dbgs++;
#endif
		}
	}
	
#if BALLDEBUG
	debugMap(v);
#endif


	if (sx == -1 || sy == -1) return;

	// team 찾기
#if DEBUG
	cout << "! ball hit : " << sx << ", " << sy << endl;
#endif
	int my_team = teamMap[sx][sy];
	int v[21][21] = { 0, };

	//Count
	int px = team[my_team].fx, py = team[my_team].fy;
	int pos = 1;
	v[px][py] = true;
	while (px != sx || py != sy) {
		for (int x = 0; x < 4; x++) {
			int dx = px + mv[x].first, dy = py + mv[x].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N || map[dx][dy] == 4 || map[dx][dy] == 0 || v[dx][dy]) continue;

			//FRONT -> BACK 가는거 전처리 (오류날 수 있음)
			if (map[px][py] == FRONT && map[dx][dy] == BACK) continue;

			v[dx][dy] = true;
			px = dx, py = dy;
			break;
		}
		pos++;
	}

	int sfx = team[my_team].fx, sfy = team[my_team].fy;
	team[my_team].fx = team[my_team].bx;
	team[my_team].fy = team[my_team].by;
	team[my_team].bx = sfx;
	team[my_team].by = sfy;

	map[team[my_team].fx][team[my_team].fy] = FRONT;
	map[team[my_team].bx][team[my_team].by] = BACK;

	score += (pos * pos);

#if DEBUG
	cout << "score plus : " << pos << "*" << pos << "=" << pos * pos << ", --> totalScore = " << score << endl;
#endif

}



void move() {
	for (int t = 1; t <= M; t++) {
		// 선두 이동 -> team 포인터만 이동
		int sfx = team[t].fx, sfy = team[t].fy;
		int sbx = team[t].bx, sby = team[t].by;

		for (int x = 0; x < 4; x++) {
			int dx = sfx + mv[x].first, dy = sfy + mv[x].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N) continue;

			if (map[dx][dy] == BACK || map[dx][dy] == 4) {

				team[t].fx = dx, team[t].fy = dy;
				break;
			}
		}

		// 후미 이동
		for (int x = 0; x < 4; x++) {
			int dx = sbx + mv[x].first, dy = sby + mv[x].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N) continue;

			if (map[dx][dy] == 2) {

				team[t].bx = dx, team[t].by = dy;
				break;
			}
		}

		// 포인터 삭제
		map[sfx][sfy] = 2;
		map[sbx][sby] = 4;


		//재기록
		map[team[t].fx][team[t].fy] = FRONT;
		map[team[t].bx][team[t].by] = BACK;
	}
}


void initSetting() {
	
	queue<pair<int, int>> q;
	bool v[21][21] = { 0, };

	int teamCnt = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (v[i][j]) continue;
			else if (!map[i][j]) {
				v[i][j] = true;
				continue;
			}

			v[i][j] = true;
			teamMap[i][j] = teamCnt;
			q.push({ i,j });
			while (!q.empty()) {
				int cx = q.front().first, cy = q.front().second;
				q.pop();
				for (int x = 0; x < 4; x++) {
					int dx = cx + mv[x].first, dy = cy + mv[x].second;
					if (dx < 0 || dx >= N || dy < 0 || dy >= N || !map[dx][dy] || v[dx][dy] ) continue;

					if (map[dx][dy] == 1) {
						team[teamCnt].fx = dx;
						team[teamCnt].fy = dy;
					}
					else if (map[dx][dy] == 3) {
						team[teamCnt].bx = dx;
						team[teamCnt].by = dy;
					}
					
					v[dx][dy] = true;
					q.push({ dx,dy });
					teamMap[dx][dy] = teamCnt;

				}
			}

			teamCnt++;
		}
	}

}