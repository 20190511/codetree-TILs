//1945
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define DEBUGS false

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int N=3, M=3;
int maps[101][101];
int cpyMap[101][101];

struct node {
	int cnt;
	int val;

	const bool operator< (const node& b) const {
		if (cnt != b.cnt)
			return cnt > b.cnt;
		return val > b.val;
	}
};

int R, C, K;
void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << maps[i][j] << " ";
		}
		cout << endl;
	}
	cout << "=================" << endl << endl;
}


void nExtend() {
	int newM = 0;
	for (int i = 0; i < N; i++) {
		map<int, int> cnt;
		priority_queue<node> pq;
		for (int j = 0; j < M; j++) {
			if (!cpyMap[i][j]) continue;
			cnt[cpyMap[i][j]]++;
		}


		// 확장
		for (auto it = cnt.begin(); it != cnt.end() ; it++) {
			pq.push({ it->second, it->first });
		}

		int ptr = 0;
		while (!pq.empty() && ptr < 100) {
			node t = pq.top();
			pq.pop();
			maps[i][ptr++] = t.val;
			if (ptr >= 100) break;
			maps[i][ptr++] = t.cnt;
		}
		newM = max(ptr, newM);
	}
	M = newM;
}

void mExtend() {
	int newN = 0;
	for (int i = 0; i < M; i++) {
		map<int, int> cnt;
		priority_queue<node> pq;
		for (int j = 0; j < N; j++) {
			if (!cpyMap[j][i]) continue;
			cnt[cpyMap[j][i]]++;
		}


		// 확장
		for (auto it = cnt.begin(); it != cnt.end(); it++) {
			pq.push({ it->second, it->first });
		}

		int ptr = 0;
		while (!pq.empty() && ptr < 100) {
			node t = pq.top();
			pq.pop();
			maps[ptr++][i] = t.val;
			if (ptr >= 100) break;
			maps[ptr++][i] = t.cnt;
		}
		newN = max(ptr, newN);
	}
	N = newN;
}
void simul() {

	memcpy(cpyMap, maps, sizeof(maps));
	memset(maps, 0, sizeof(maps));
	if (N >= M) {
		nExtend();
	}
	else {
		mExtend();
	}

#if DEBUG
	printMap();
#endif
}

int main(void) {
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif
	cin >> R >> C >> K;
	R--;
	C--;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> maps[i][j];
		}
	}

	if (maps[R][C] == K) {
		cout << 0;
		return 0;
	}

#if DEBUG
	printMap();
#endif
	int t = 1;
	for (t = 1; t <= 100; t++) {
#if DEBUG
		cout << "  <<" << t << ">> " << endl;
#endif

		simul();

		if (maps[R][C] == K) {
			cout << t;
			return 0;
		}
#if DEBUG
#endif
	}

	if (maps[R][C] != K)
		cout << -1;
	else
		cout << t;



	return 0;
}