#define DEBUG false
#define DEBUGS true
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

//1700 (주사위 한 번 더) ~ 
using namespace std;
int dice[6] = { 4,3,5,2,1,6 };
int N, M, K, score = 0;
int map[21][21];
pair<int, int> mv[4] = { //동남서북
	{0,1}, {1,0}, {0,-1}, {-1,0}
};
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
	int arr[4][6] = {
		{5,4,2,3,0,1},
		{0,1,4,5,3,2},
		{4,5,2,3,1,0},
		{0,1,5,4,2,3},
	};

	for (int i = 0; i < 6; i++) {
		dice[i] = tmpDice[arr[dir][i]];
	}
}

int map_score(int x, int y) {
	bool visited[20][20];
	int id = map[x][y];
	int tmp_score = 0;
	memset(visited, 0, sizeof(visited));
	visited[x][y] = true;
	queue<pair<int, int>> q;
	q.push({ x,y });
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		tmp_score++;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int dx = cx + mv[i].first, dy = cy + mv[i].second;
			if (dx < 0 || dx >= N || dy < 0 || dy >= M || visited[dx][dy] || id != map[dx][dy])
				continue;

			visited[dx][dy] = true;
			q.push({ dx,dy });
		}
	}
#if DEBUG
	for (int i = 0 ; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}
#endif
	return tmp_score * id;
}
void run() {
	int cx = 0, cy = 0, dir = 0;
	for (int i = 0; i < K; i++) {

#if DEBUG
		cout << "+++++ i = " << i + 1 << ", dir = "<<dir<<" ++++++" << endl;
#endif
		
		int dx = cx + mv[dir].first, dy = cy + mv[dir].second;
		if (dx < 0 || dx >= N || dy < 0 || dy >= M) {
			dir = (dir + 2) % 4;
			dx = cx + mv[dir].first, dy = cy + mv[dir].second;
		}
		cx = dx, cy = dy;
		int tmp_score = map_score(cx,cy);
		move(dir);
#if DEBUG
		cout << "score plus :: " << tmp_score << endl;
#endif
		score += tmp_score;

		int bottom = dice[5];
		if (bottom > map[cx][cy])
			dir = (dir + 1) % 4;
		else if (bottom < map[cx][cy])
			dir = (dir + 3) % 4;


#if DEBUG
		cout << "dice X = " << cx << ", Y = " << cy << endl;
		printMap();
#endif
	}
	cout << score;
}
int main(void)
{
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	run();
	return 0;
}
