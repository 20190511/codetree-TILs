//0950
#define _CRT_SECURE_NO_WARNINGS
#define DEBUGS false
#define DEBUG  false
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#define N 5
#define endl "\n"
using namespace std;


int K, M, totalScore=0;
int map[N+1][N+1];
queue<int> q;
pair<int, int> mv[4] = {
	{0,1}, {0,-1}, {1,0}, {-1, 0}
};

void printMap(int maps[N+1][N+1] = map) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] <<" ";
		}
		cout << endl;
	}
	cout << "===========================" << endl;
}


int bfs() {
	bool v[6][6] = { 0, };
	
	int retSums = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (v[i][j]) continue;

			queue<pair<int, int>> bq;
			v[i][j] = true;
			bq.push({ i,j });
			int pivot = map[i][j];

			int curCnt = 1;

			while (!bq.empty()) {
				int cx = bq.front().first, cy = bq.front().second;
				bq.pop();

				for (int x = 0; x < 4; x++) {
					int dx = cx + mv[x].first, dy = cy + mv[x].second;
					if (dx < 0 || dx >= N || dy < 0 || dy >= N || map[dx][dy] != pivot || v[dx][dy]) continue;

					v[dx][dy] = true;
					bq.push({ dx, dy });
					curCnt++;
				}
			}


			if (curCnt >= 3)
				retSums += curCnt;
		}	
	}
	return retSums;
}

bool bfsClear() {
#if DEBUG
	cout << "clear map " << endl;

#endif
	bool v[6][6] = { 0, };

	int retSums = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (v[i][j]) continue;

			queue<pair<int, int>> bq;
			vector <pair<int, int>> saveQ;
			v[i][j] = true;

			bq.push({ i,j });
			int pivot = map[i][j];

			int curCnt = 1;

			while (!bq.empty()) {
				int cx = bq.front().first, cy = bq.front().second;
				saveQ.push_back({ cx, cy });

				bq.pop();

				for (int x = 0; x < 4; x++) {
					int dx = cx + mv[x].first, dy = cy + mv[x].second;
					if (dx < 0 || dx >= N || dy < 0 || dy >= N || map[dx][dy] != pivot || v[dx][dy]) continue;

					v[dx][dy] = true;
					bq.push({ dx, dy });
					curCnt++;
				}
			}


			if (curCnt >= 3) {
				while (!saveQ.empty()) {
					retSums++;
					int cx = saveQ.back().first, cy = saveQ.back().second;
					saveQ.pop_back();
					map[cx][cy] = 0;
				}
			}
		}
	}

	return retSums;
}

void fillMap() {
#if DEBUG
	cout << "Fill map" << endl;

#endif

	int cnt = 1;
	for (int j = 0; j < N; j++) {
		for (int i = N-1; i >= 0; i--) {
			if (!map[i][j]) {
				totalScore++;
				map[i][j] = q.front();
				q.pop();
			}
		}
	}

}


int rotate(int sx, int sy, int bfsCheck) {

	int cpyMap[N+1][N+1] = { 0, };
	memcpy(cpyMap, map, sizeof(cpyMap));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			map[i+sx][j+sy] = cpyMap[2 - j + sx][i + sy];
		}
	}

	if (bfsCheck)
		return bfs();
	else
		return 0;
}

bool findRotate() {

	//cx,cy 한 칸씩 올려줘야됨
	int rCnt = 4, cx = -1, cy = -1, maxCnt = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			
			for (int r = 0; r < 3; r++) {
				int curScore = rotate(i, j, true);
				if (maxCnt < curScore || 
					( (maxCnt == curScore) && (rCnt > r) ) )
				{
					rCnt = r;
					cx = i;
					cy = j;
					maxCnt = curScore;
				}


#if DEBUG
				cout << "i=" << i << ", j=" << j << ", r=" << r << ", score=" << curScore << endl;
				printMap(map);
#endif
			}


			//초기화
			rotate(i, j, false);
		}
	}

	if (!maxCnt)
		return false;



#if DEBUG
	cout << "find cx =" << cx << ", cy=" << cy << ", r=" << rCnt << ", score="<<maxCnt<< endl;
#endif

	for (int r = 0; r <= rCnt; r++) {
		rotate(cx, cy, false);
	}

#if DEBUG
	printMap();
#endif
	int clearCnt = bfsClear();

#if DEBUG
	printMap();
#endif
	
	fillMap();

#if DEBUG
	printMap();
#endif


	return true;
}


int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	cin >> K >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int s;
		cin >> s;
		q.push(s);
	}



	for (int t = 1; t <= K; t++) {
#if DEBUG
		cout << " <<< t = " << t << endl;
#endif

		bool check = findRotate();
		if (!check)
			break;


#if DEBUG
		printMap();
#endif
		while (bfsClear()) {
			fillMap();

#if DEBUG
			printMap();
#endif
		}

		cout << totalScore << " ";
		totalScore = 0;
	}

	return 0;
}