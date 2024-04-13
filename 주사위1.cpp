#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
//1625 ~ 1700
using namespace std;
int dice[6] = { 0,0,0,0,0,0 };
int N, M, X, Y, K;
int map[21][21];
pair<int, int> mv[5] = {
	{-1,-1}, {0,1}, {0,-1}, {-1,0}, {1,0}
};
vector<int> cmd;
void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------" << endl;
	for (int x = 0; x < 6; x++)
		cout << dice[x] << " ";
	cout << endl << "================" << endl;
}
void move(int dir) {
	int tmpDice[6];
	memcpy(tmpDice, dice, sizeof(dice));
	int arr[5][6] = {
		{0,0,0,0,0,0},
		{5,4,2,3,0,1},
		{4,5,2,3,1,0},
		{0,1,5,4,2,3},
		{0,1,4,5,3,2}
	};

	for (int i = 0; i < 6; i++) {
		dice[i] = tmpDice[arr[dir][i]];
	}
}

void run() {
	int cx = X, cy = Y;
	for (int i = 0; i < K; i++) {

		int dir = cmd[i];
#if DEBUG
		cout << "+++++ i = " << i + 1 << ", dir = "<<dir<<" ++++++" << endl;
#endif
		int dx = cx + mv[dir].first, dy = cy + mv[dir].second;
		if (dx < 0 || dx >= N || dy < 0 || dy >= M) continue;
		cx = dx, cy = dy;

		move(dir);
		if (map[cx][cy] == 0) {
			map[cx][cy] = dice[5];
		}
		else {
			dice[5] = map[cx][cy];
			map[cx][cy] = 0;
		}

#if DEBUG
		cout << "dice X = " << cx << ", Y = " << cy << endl;
		printMap();
#endif
		cout << dice[4]<<endl;
	}
}
int main(void)
{
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif
	cin >> N >> M >> X >> Y >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		int x;
		cin >> x;
		cmd.push_back(x);
	}
	run();
	return 0;
}
