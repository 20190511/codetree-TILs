// 반복 연습 1회차  : 0908 (이해:22) ~ 11:38
/// map 1,1 시작
/**
	2시간 30분 걸린 쉽지않은 문제
	-> 실수 는 빠르게 잡았는데 실수한 부분들

	1. if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue 에서 nx, ny 대신 nx nx 로 적는 실수.
	2. 문제조건 중 가만히 있어야되는데 가만히 있지않고 가버린 실수
	---
	나머지는 침착하게 요소들을 디버깅할 수 있도록 짜서 시간은 조금 더 걸리지만 안전하게 풀이함.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

#define DEBUG false

struct santaObj
{
	int x;
	int y;
	int score;
	int state;
	bool die;
	bool active;
	
	santaObj(int x = -1, int y = -1, int b = 0, int s = 1, bool c = false, bool e = false) : x(x), y(y), state(s), score(b), die(c), active(e) {}
};
int N, M, P, C, D, santa_cnt, map[51][51];
pair<int, int> ru_pos;
pair<int, int> dir_r[8] = {
	{1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1}
};
pair<int, int> dir_s[4] = {
	{-1,0}, {0,1},  {1,0}, {0,-1}
};
santaObj santa[31];

void printMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			if (ru_pos.first == i && ru_pos.second == j) {
				cout << "r  ";
				continue;
			}
			
			int s_flag = false;
			for (int aa = 1; aa <= 30; aa++) {
				if (!santa[aa].active) continue;
				if (!santa[aa].die && santa[aa].x == i && santa[aa].y == j) {
					cout << "S" << aa << " ";
					s_flag = true;
					break;
				}
			}
			if (s_flag) continue;

			cout << map[i][j] << "  ";
		}
		cout << endl;
	}

	cout << "----------" << endl;
	for (int i = 1; i <= 31; i++) {
		if (santa[i].active)
			cout << "santa[" << i << "] score=" << santa[i].score <<", state="<<santa[i].state<< endl;
	}
	cout << "====================" << endl;
}



// 거리 계산
int cal(int a, int b, int a2, int b2) {
	return (a - a2) * (a - a2) + (b - b2) * (b - b2);
}

void dieSanta(int num) {
#if DEBUG
	cout << "santa=" << num << " die!" << endl;
#endif
	santa[num].die = true;
	santa[num].x = santa[num].y = -1;
	santa_cnt--;
}
void interect(int num, int p, int dirX, int dirY) {
	map[santa[num].x][santa[num].y] = 0;

	// 새로운 착지지역
	int nx = santa[num].x + dirX * p, ny = santa[num].y + dirY * p; 
#if DEBUG
		cout << "in interect new x=" << nx << ", " << ny << endl;
#endif
	if (nx <= 0 || nx > N || ny <= 0 || ny > N) {
		dieSanta(num);
		return;
	}

	if (!map[nx][ny]) {
		santa[num].x = nx, santa[num].y = ny;
		map[nx][ny] = num;
		return;
	}



	if (map[nx][ny]) {

		vector<int> q_list;
		int cx = nx, cy = ny;
		while (cx > 0 && cx <= N && cy > 0 && cy <= N && map[cx][cy]) {
			q_list.push_back(map[cx][cy]);
			cx += dirX;
			cy += dirY;
		}

		while (!q_list.empty()) {
			int s_num = q_list.back();
			q_list.pop_back();
			
			int newX = santa[s_num].x + dirX, newY = santa[s_num].y + dirY;
			if (newX <= 0 || newX > N || newY <= 0 || newY > N) {
				dieSanta(s_num);
				continue;
			}

			santa[s_num].x = newX, santa[s_num].y = newY;
			map[newX][newY] = s_num;
		}
		santa[num].x = nx;
		santa[num].y = ny;
		map[nx][ny] = num;

#if DEBUG
		cout << "상호작용 로직 종료" << endl;
		printMap();

#endif
	}

}

void ru_go(int turn) {
	//ru 이동
	int smallCnt = 0x7FFFFFFF, sNum = 0;
	int curX = ru_pos.first, curY = ru_pos.second;
	for (int s = 1; s <= 30; s++) {
		if (!santa[s].active || santa[s].die) continue;
		int cals = cal(curX, curY, santa[s].x, santa[s].y);

		if (smallCnt == cals) {
			int cx = santa[sNum].x, cy = santa[sNum].y, dx = santa[s].x, dy = santa[s].y;
			if (cx > dx) continue;
			else if (cx == dx && cy > dy) continue;
		}
		
		if (smallCnt >= cals) {
			smallCnt = cals;
			sNum = s;
		}
	}

#if DEBUG
	cout << "ru, santa_num=" << sNum <<", cals="<<smallCnt<< endl;
#endif

	// 이동
	int nx = santa[sNum].x - curX, ny = santa[sNum].y - curY;
	if (nx)
		nx = nx / abs(nx);
	if (ny)
		ny = ny / abs(ny);

#if DEBUG
	cout << nx << ", " << ny << endl;
#endif


	//map[ru_pos.first][ru_pos.second] = 0;
	ru_pos.first += nx;
	ru_pos.second += ny;
	//map[ru_pos.first][ru_pos.second] = -1;

	// 충돌
	if (map[ru_pos.first][ru_pos.second]) {
#if DEBUG
		cout << "ru 충돌!" << endl;
#endif
		int sNum = map[ru_pos.first][ru_pos.second];
		//점수 증가
		santa[sNum].state = turn + 2;
		santa[sNum].score += C;
		
		//상호작용 짜보기 -> 새 착지지역
		interect(sNum, C, nx, ny);
	}
#if DEBUG
	cout << "turn=" << turn << " ru go" << endl;
	printMap();
#endif
}


/// <summary>
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void santa_go(int turn, int num) {

	int curX = santa[num].x, curY = santa[num].y;
	int ruX = ru_pos.first, ruY = ru_pos.second;
	int smallCnt = cal(curX, curY, ruX, ruY), dir = -1;
	for (int i = 0; i < 4; i++) {
		int dx = curX + dir_s[i].first, dy = curY + dir_s[i].second;
		if (dx <= 0 || dx > N || dy <= 0 || dy > N || map[dx][dy] > 0) continue;

		int newDist = cal(dx, dy, ruX, ruY);
		if (newDist < smallCnt) {
			smallCnt = newDist;
			dir = i;
		}
	}
	if (dir == -1) {
#if DEBUG
		cout << "못 움직임!!" << endl;
#endif
		return;
	}

#if DEBUG
	cout << "turn=" << turn << "-> santa[" << num << "] dir=" << dir << endl;
#endif

	int nx = curX + dir_s[dir].first, ny = curY + dir_s[dir].second;

	if (nx !=ruX || ny != ruY) {
		map[curX][curY] = 0;
		map[nx][ny] = num;
		santa[num].x = nx, santa[num].y = ny;
		return;
	}

	//루돌프 충돌
#if DEBUG
	cout << "santa 충돌! santa=" << num << endl;
#endif
	map[santa[num].x][santa[num].y] = 0;
	santa[num].score += D;
	santa[num].state = turn + 2;
	santa[num].x = nx;
	santa[num].y = ny;
	interect(num, D, -dir_s[dir].first, -dir_s[dir].second);
}

int main(void)
{
#if DEBUG
	freopen("q.txt", "r", stdin);
#endif

	cin >> N >> M >> P >> C >> D;
	cin >> ru_pos.first >> ru_pos.second;
	santa_cnt = P;
	for (int i = 0; i < P; i++) {
		int num;
		cin >> num;
		santa[num].active = true;
		santa[num].die = false;
		cin >> santa[num].x >> santa[num].y;
		map[santa[num].x][santa[num].y] = num;
	}

#if DEBUG
	printMap();
#endif

	// 시작
	for (int turn = 1; turn <= M; turn++) {
		if (!santa_cnt) break; //santa 다 죽었으면 break
		
		ru_go(turn);
		for (int i = 1; i <= 30; i++) {
			if (!santa[i].active || santa[i].die || santa[i].state > turn)
				continue;
			santa_go(turn, i);
		}


		for (int i = 1; i <= 30; i++) {
			if (santa[i].active && !santa[i].die) {
				santa[i].score++;
				if (santa[i].state == turn)
					santa[i].state++;
			}
		}
#if DEBUG

		cout << "<<<        turn=" << turn << "        >>>"<<endl;
		printMap();
#endif
	}
	for (int i = 1; i <= P; i++) {
		if (santa[i].active)
			cout << santa[i].score << " ";
	}
	
	return 0;
}
