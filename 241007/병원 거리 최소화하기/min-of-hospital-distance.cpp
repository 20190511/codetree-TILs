//0845
#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

int N, M;
int map[51][51];
bool map2[51][51];

vector<pair<int, int>> manQ, hospiQ;
int hospiCnt = 0;


int minDist(pair<int, int> pos) {
	int minDist = 51 * 51;
	for (auto h : hospiQ) {
		if (!map2[h.first][h.second]) continue;

		minDist = min(minDist, abs(pos.first - h.first) + abs(pos.second - h.second));
	}

	return minDist;
}

int retval = 51 * 51;
void recul(int depth, int cnt) {


	if (cnt == M) {
		int sumMinDist = 0;
		for (auto man : manQ) {
			sumMinDist += minDist(man);
		}

#if DEBUG
		cout << "sumMInDist = " << sumMinDist << endl;
#endif
		retval = min(retval, sumMinDist);
	}

	if (depth == hospiCnt)
		return;

	pair<int, int> curPos = hospiQ[depth];

	//on
	map2[curPos.first][curPos.second] = true;
	recul(depth + 1, cnt + 1);

	//off
	map2[curPos.first][curPos.second] = false;
	recul(depth + 1, cnt);


}

int main(void)
{
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int v;
			cin >> v;
			map[i][j] = v;
			if (v == 1) {
				manQ.push_back({ i,j });
			}
			else if (v == 2) {
				hospiCnt++;
				hospiQ.push_back({ i,j });
			}
		}
	}

	// 병원 고르기
	recul(0, 0);
	cout << retval;

	return 0;
}