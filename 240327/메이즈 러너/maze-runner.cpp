//1100 ~ 1300
/**
	1. minPos 잡는 부분 잘못된 접근이 계속 나옴
	--> 처음에는 단순히 rx, ry가 큰 애로 잡았다가 오류가 남..
	--> 두 번째 시도에서는 단순히 혼자 해석해서 max(t1, t2) 로 두다가 직사각형이 안만들어져서 오류가남
	--> 세 번째 시도에서는 포기하고 직사각형을 미리 그려본 후 문제 그대로 좌상단 좌표를 문제와 비교를 해봤었음 (단, 에러처리는 뒤에 뒀었음)
	--> 네 번째 시도에서는 위에서 음수값이 나오는 경우 세팅 과정에서 문제가 생기게 되어서 예외처리도 뒤에 뒀어야함..


	2. 문제애서 얻은 피드백
		A. 중간 debug 매크로 이용해서 찍어보는 과정은 매우 굿
		B. 이동, 회전 부분 함수 분할 부분도 매우 굿
		C. --> 다만 문제에 정사각형 좌표를 찍어보는 문제는 쟁점을 잘 파악해서 좌상단, 우하단을 파악한 뒤에 
			>> 문제에 충실하게 한 케이스 당 적용해보기 *시간복잡도가 허용해준다면..
		D. 회전 문제의 피드백
			>> 회전은 평행이동이 고려된 경우에는 똑같이 넣어주면 되지만
				좌표 하나를 이동시켜야한다면 (시계방향의 경우)
					int mx = curX-a, my = curY-b;
					int mnx = my+a, mny = r - mx - 1 + b;
					a = {mnx, mny}와 같이 정의될 수 있다.
*/
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#define INF	0x7FFFFFFF
using namespace std;

int map[10][10], man[10][10];
pair<int, int> man_pos[10], ex;
pair<int, int> mv[4] = {
	{-1,0}, {1,0}, {0,-1}, {0,1}
};
int N, M, K; //M=참가자 수
int man_cnt, moving = 0;


void printMap() {
	cout << "==============" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (ex.first == i && ex.second == j)
				cout << "X  ";
			else
				if (map[i][j])
					printf("%-2d ", map[i][j]);
				else if (man[i][j])
					printf("%-2d ", -man[i][j]);
				else
					printf("   ");
		}
		cout << endl;
	}
}

int getN1(int ax, int ay, int bx, int by) {
	int tx = ax < bx ? bx - ax : ax - bx;
	int ty = ay < by ? by - ay : ay - by;
	return tx + ty;
}

void shortMove (int mCnt) {
	
	if (man_pos[mCnt].first == -1 || man_pos[mCnt].second == -1)
		return;

	int mx = man_pos[mCnt].first, my = man_pos[mCnt].second;
	int ox = ex.first, oy = ex.second;

	int curPath = getN1(ox, oy, mx, my);
	int mvNum = -1;

	for (int i = 0; i < 4; i++) {
		int dx = mx + mv[i].first, dy = my + mv[i].second;
		if (dx < 0 || dx >= N || dy < 0 || dy >= N || map[dx][dy]) continue;
		
		int nextPath = getN1(ox, oy, dx, dy);
		if (curPath > nextPath) {
			curPath = nextPath;
			mvNum = i;
		}
	}

	//이동
	if (mvNum == -1) return;

#if DEBUG
	cout << "moving :: " << mx << "," << my << "-->"<<curPath << endl;
#endif
	moving++;
	int dx = mx + mv[mvNum].first, dy = my + mv[mvNum].second;
	man[mx][my]--;
	//출구도착
	if (curPath == 0) {
		man_cnt--;
		man_pos[mCnt] = { -1,-1 };
		return;
	}

	man[dx][dy]++;
	man_pos[mCnt] = { dx,dy };

}
void move() {
	for (int i = 0; i < M; i++) {
		shortMove(i);
	}
}

void rotateG(int a, int b, int r) {

	int tm1[10][10];
	memcpy(tm1, map, sizeof(map));

	for (int i = 0; i < M; i++) {
		int mx = man_pos[i].first, my = man_pos[i].second;
		if (mx < a || mx >= a + r || my < b || my >= b + r)
			continue;

		man[mx][my]--;
		int tx = mx - a, ty = my - b;
		int mnx = ty + a, mny = r - tx - 1 + b;

		man[mnx][mny]++;
		man_pos[i] = {mnx, mny};
	}

	int ox = ex.first, oy = ex.second;
	int tx = ox - a, ty = oy - b;
	ex = {ty + a, r - tx - 1 + b};

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {

			map[i+a][j+b] = tm1[r - j - 1+a][i+b];
			if (map[i + a][j + b])
				map[i + a][j + b]--;
		}
	}
}

void rt() {
	int smallPath = INF, mx = N, my = N;
	int ox = ex.first, oy = ex.second;
	int rdx=INF, rdy=INF, lux=INF ,luy=INF;


	for (int i = 0; i < M; i++) {
		int tx = man_pos[i].first, ty = man_pos[i].second;
		if (tx < 0 || ty < 0) continue;

		int costX = ox < tx ? tx - ox : ox - tx;
		int costY = oy < ty ? ty - oy : oy - ty;
		int n1 = max(costX, costY);
		if (smallPath < n1) continue;

		int trdx = max(tx, ox), trdy = max(ty, oy);
		int tlux = trdx - n1, tluy = trdy - n1;
		if (tlux < 0) {
			tlux = 0;
			trdx = n1;
		}

		if (tluy < 0) {
			tluy = 0;
			trdy = n1;
		}

		if (smallPath > n1) {
			smallPath = n1;
			rdx = trdx;
			rdy = trdy;
			lux = tlux;
			luy = tluy;
		}
		else if ((tlux < lux) || ((tlux == lux) && (tluy < luy))) {
			rdx = trdx;
			rdy = trdy;
			lux = tlux;
			luy = tluy;
		}
		/*
		if  ((smallPath > n1) || 
			((smallPath == n1) && (tx < mx)) ||
			((smallPath == n1) && (tx == mx) && (ty < my)) )
		
		if ((smallPath > n1) ||
			((smallPath == n1) && (minPos < max(mx,my))) )
		{
			mx = tx, my = ty;
			smallPath = n1;
		}
		*/
	}

#if DEBUG
	cout << "in rotate\n";
	cout << mx << ", " << my << endl;
#endif

#if DEBUG
	cout << "up || down" << endl;
	cout << lux << "," << luy << " || " << rdx << "," << rdy << endl;
	cout << "smallPath = "<<smallPath << endl;
#endif

	rotateG(lux, luy, smallPath + 1);

}

void run() {
#if DEBUG
	printMap();
#endif
	man_cnt = M;
	for (int t = 0; t < K; t++) {
#if DEBUG
		cout << t + 1 << " th Execute\n";
#endif
		//이동
		move();
#if DEBUG
		cout << "Man count = " << man_cnt << ", moving = " << moving << endl;
		printMap();
		cout << "move   finish ===== \n";
#endif
		if (!man_cnt)
			break;
		//회전
		rt();
#if DEBUG
		printMap();
		cout << "rotate FInish ===== \n\n";

#endif 
	}
	cout << moving << "\n";
	cout << ex.first + 1 << " " << ex.second + 1;
}


int main(void)
{
	//freopen("input.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	}

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		man_pos[i] = { a - 1,b - 1 };
		man[a - 1][b - 1]++;
	}

	cin >> a >> b;
	ex = { a - 1,b - 1 };
	run();

	return 0;
};
