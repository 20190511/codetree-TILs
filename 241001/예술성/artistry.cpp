//2030
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define DEBUGS false
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;


int map[30][30], groupMap[30][30], mapCopy[30][30];
int N;
int groups[900][900], groupVal[900], groupCounter[900];
int groupCnt = 0;
int totalScore = 0;

pair<int, int> mv[4] = {
	{1,0}, {0,1}, {-1,0}, {0,-1}
};

void printMap(int map[30][30] ) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "===============" << endl;
}


void groupBFS() {
	memset(groupMap, 0, sizeof(groupMap));
	memset(groups, 0, sizeof(groups));
	memset(groupVal, 0, sizeof(groupVal));
	memset(groupCounter, 0, sizeof(groupCounter));


	groupCnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (groupMap[i][j]) continue;

			groupCnt++;
			queue<pair<int, int>> q;
			q.push({ i,j });
			groupMap[i][j] = groupCnt;

			int pivot = groupVal[groupCnt] = map[i][j];
			groupCounter[groupCnt] = 0;
			while (!q.empty()) {
				int cx = q.front().first, cy = q.front().second;
				groupCounter[groupCnt]++;
				q.pop();

				for (int x = 0; x < 4; x++) {
					int dx = cx + mv[x].first, dy = cy + mv[x].second;
					if (dx < 0 || dx >= N || dy < 0 || dy >= N || groupMap[dx][dy] || map[dx][dy] != pivot) continue;

					groupMap[dx][dy] = groupCnt;
					q.push({ dx,dy });
				}
			}
#if DEBUG
			cout << "group = " << groupCnt << ", count = " << groupCounter[groupCnt] << endl;
#endif
		}
	}
}

void findBFS() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			int pivot = groupMap[i][j];

			for (int x = 0; x < 2; x++) {
				int dx = i + mv[x].first, dy = j + mv[x].second;
				if (dx < 0 || dx >= N || dy < 0 || dy >= N || groupMap[dx][dy] == pivot) continue;

				int pivot2 = groupMap[dx][dy];
				
				int sg = min(pivot, pivot2);
				int bg = max(pivot, pivot2);
				
				groups[sg][bg]++;
			}
		}
	}
}


void rotateSmall(int x, int y) {

	int newN = N / 2;
	for (int i = 0; i < newN; i++) {
		for (int j = 0; j < newN; j++) {
			map[i + x][j + y] = mapCopy[newN - j - 1+x][i+y];
		}
	}
}

void getScore() {
	//인접면 세기 + 점수
	findBFS();
	int curScore = 0;
	for (int i = 1; i <= groupCnt; i++) {
		for (int j = 1; j <= groupCnt; j++) {
			if (!groups[i][j]) continue;

			int s = i, b = j, cnt = groups[i][j];
#if DEBUG
			cout << "s=" << s << ", b=" << b << ", cnt=" << cnt << endl;
#endif
			int sb = groupVal[s], bb = groupVal[b];
			int sc = groupCounter[s], bc = groupCounter[b];
			int tmpScore = (sc + bc) * sb * bb * cnt;
#if DEBUG
			cout << "sb=" << sb << ", bb=" << bb << ", sc=" << sc << ", bc" << bc << endl;
			cout << "score = " << tmpScore << endl;
#endif
			curScore += tmpScore;
		}
	}
	totalScore += curScore;

#if DEBUG
	cout << "curScore = " << curScore << ", totalScore=" << totalScore << endl;
	printMap(map);
#endif
}


void rotate() {
	//크게 왼쪽 90도 회전
	
	memcpy(mapCopy, map, sizeof(mapCopy));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			map[N - j - 1][i] = mapCopy[i][j];
		}
	}
#if DEBUG
	cout << "Rotate1 Big" << endl;
	printMap(map);
#endif

	rotateSmall(0, 0);
	rotateSmall(N/2+1, 0);
	rotateSmall(0, N/2+1);
	rotateSmall(N/2+1, N/2+1);

#if DEBUG
	cout << "Rotate1 Small" << endl;
	printMap(map);
#endif

//작게 4부분으로 90도 회전
}

int main(void)
{
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

#if DEBUG
	printMap(map);
#endif

	groupBFS();
#if DEBUG
	printMap(groupMap);
#endif
	getScore();


	for (int t = 0; t < 3; t++) {


		//회전
		rotate();

		groupBFS();
		getScore();
#if DEBUG
		printMap(groupMap);
#endif
	}





	cout << totalScore;
	return 0;
}