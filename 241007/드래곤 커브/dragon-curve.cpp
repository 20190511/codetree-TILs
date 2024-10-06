//0726 ~ 이해 0745 ~ 0830
/*
* vector 연결할 때 q.insert(q.end(), n.begin(), n.end()); 이다.
* 근데 emplace로 연결해버리는 실수로 한 10분 까먹었다.
* emplace는 보니까 push_back과 비슷한거 같다.
*/
#define _CRT_SECURE_NO_WARNINGS
#define DEBUGS false
#define DEBUG false
#include <iostream>
#include <vector>
#include <queue>
using namespace std;



int map[101][101];
int N;

int qG[21];
vector<pair<int, int>> q[21];


pair<int, int> changer(pair<int, int> pos) {

	
	int ax = 0;
	if (pos.first)
		ax = pos.first / abs(pos.first);
	int ay = 0;
	if (pos.second)
		ay = pos.second / abs(pos.second);
	
	if (ax == 1 && ay == -1) {
		return pair<int, int>({ -abs(pos.second), -abs(pos.first) });
	}
	else if (ax == -1 && ay == -1) {
		return pair<int, int>({ -abs(pos.second), abs(pos.first) });
	}
	else if (ax == -1 && ay == 1) {
		return pair<int, int>({ abs(pos.second), abs(pos.first) });
	}
	else if (ax == 1 && ay == 1) {
		return pair<int, int>({ abs(pos.second), -abs(pos.first) });
	}
	else if (ax == 0 && ay == -1) {
		return pair<int, int>({ -abs(pos.second), -abs(pos.first) });
	}
	else if (ax == -1 && ay == 0) {
		return pair<int, int>({ -abs(pos.second), abs(pos.first) });
	}
	else if (ax == 0 && ay == 1) {
		return pair<int, int>({ abs(pos.second), abs(pos.first) });
	}
	else if (ax == 1 && ay == 0) {
		return pair<int, int>({ abs(pos.second), -abs(pos.first) });
	}
	else if (ax == 0 && ay == 0)
		return pair<int, int>({ 0,0 });
}

pair<int, int> diffPos(pair<int, int> e, pair<int, int> the) {
	return pair<int, int>({ the.first - e.first, the.second - e.second });
}

pair<int, int> mv[4] = {
	{0,1},{-1,0},{0,-1},{1,0}
};


void simul(int num) {

	auto it = q[num].rbegin();
	vector<pair<int, int>> newQ;

	pair<int, int> end = *it++;
#if DEBUG
	cout << "[" << end.first << ", " << end.second << "]" << endl;
#endif
	
	for (; it != q[num].rend(); it++) {
		pair<int, int> s = *it;

		pair<int, int> dpos = diffPos(end, s);
		pair<int, int> addPos = changer(dpos);

		pair<int, int> newPos = pair<int, int>{ end.first + addPos.first, end.second + addPos.second };
		newQ.push_back(newPos);

#if DEBUG
		cout << s.first << "," << s.second << " --> " << newPos.first << "," << newPos.second << endl;
#endif
	}

	q[num].insert(q[num].end(), newQ.begin(), newQ.end());

}


int mapCheck() {

	int maxX = 0;
	int maxY = 0;

	for (int i = 1; i <= N; i++) {
		for (auto it : q[i]) {
			maxX = max(maxX, it.first);
			maxY = max(maxY, it.second);
			map[it.first][it.second] = 1;
		}
	}

#if DEBUG
	for (int i = 0; i <= maxX; i++) {
		for (int j = 0; j <= maxY; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
#endif

	int retVal = 0;
	for (int i = 0; i < maxX; i++) {
		for (int j = 0; j < maxY; j++) {
			int lx = i, ly = j + 1;
			int rx = i + 1, ry = j;
			int cx = i + 1, cy = j + 1;

			if (map[i][j] && map[lx][ly] && map[rx][ry] && map[cx][cy]) {
				retVal++;
			}
		}
	}

	return retVal;
}
int main(void)
{
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif
	
	cin >> N;
	int x, y, dx, dy, d;
	for (int i = 1; i <= N; i++) {
		cin >> x >> y >> d >> qG[i];

		dx = x + mv[d].first;
		dy = y + mv[d].second;

		q[i].push_back({ x,y });
		q[i].push_back({ dx,dy });
	}


	for (int i = 1; i <= N; i++) {
		for (int t = 1; t <= qG[i]; t++) {
#if DEBUG
			cout << " << t=" << t << " >>" << endl;
#endif
			simul(i);

		}
	}

	cout<<mapCheck();

	return 0;
}