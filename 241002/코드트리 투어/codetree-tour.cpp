//코드트리 투어 11:30 ~ 13:20
/*
	-> Queue를 15개 두고 풀면 된다.
	=> 임의의 원소 삭제 테크닉은 checkArr과 recentArr 로 최신 checkArr 과 recentArr로 while 나올 때 무시하면 된다.
*/
#define DEBUG false
#define DEBUGS false

#define INF 0x7FFFFFFF
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;
#define endl "\n"

unordered_map<int, int> idxCvt; //idConverter
int distArr[17][2001];


struct item {
	int pid;
	int start;
	int dest;
	int re;

	item(int pid=0, int dest=0, int re=0, int start=0) : pid(pid), re(re), dest(dest), start(start){}
	const bool operator< (const item& b) const {
		int sIdx = idxCvt[start];


		int costA = distArr[sIdx][dest];
		int costB = distArr[sIdx][b.dest];
		
		int optA = re - costA;
		int optB = b.re - costB;

		if (optA != optB)
			return optA < optB;
		return pid > b.pid;
	}
};


bool itemCheck[30001];
item itemRecent[30001];


struct cmd {
	int cmd;
	int id;
	int revenue;
	int dest;
	int s;
};

map<int, int> distVec[2001];

queue<cmd> cmdQ;

int sArr[17]; //0번은 기본
int totalS = 1;
int N, M;
int Q;


priority_queue<item> pq[17];


void dijkstr(int start, int idx) {
#if DEBUG
	cout << "dijk s = " << start<<endl;
#endif
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>> > q;

	for (int i = 0; i < N; i++) {
		distArr[idx][i] = INF;
	}
	distArr[idx][start] = 0;

	q.push({ 0, start });
	while (!q.empty()) {
		int n = q.top().second, dist = q.top().first;
		q.pop();

		for (auto it = distVec[n].begin(); it != distVec[n].end(); it++) {
			
			int next = it->first, nextDir = it->second;
			int countDir = distArr[idx][n] + nextDir;
			if (countDir < distArr[idx][next]) {
				distArr[idx][next] = countDir;
				q.push({ countDir, next });
			}

		}

	}

}


int curS = 1;


int FindItem() {

	int ret = -1;
	item retItem(-1,-1,-1,-1);
	while (!pq[curS].empty()) {
		retItem = pq[curS].top();
		pq[curS].pop();

		ret = retItem.pid;
		if (itemRecent[ret].re != retItem.re || itemRecent[ret].dest != retItem.dest) {
			retItem.pid = -1;
			continue;
		}

		if (itemCheck[retItem.pid])
			break;

		retItem.pid = -1;
	}

	if (retItem.pid == -1)
		return -1;


	int curDist = distArr[curS][retItem.dest];
	int opt = retItem.re - curDist;

	if (opt < 0 || curDist == INF) {
		pq[curS].push(retItem);
		return -1;
	}

	itemCheck[retItem.pid] = false;
	return retItem.pid;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	int cmd;
	cin >> Q;
	cin >> cmd >> N >> M;
	for (int i = 0; i < M; i++) {
		int v, u, w;
		cin >> v >> u >> w;
		if (v == u) continue;

		int curWeight = distVec[v][u];
		if (!curWeight || curWeight > w) {
			distVec[v][u] = distVec[u][v] = w;
		}
	}

	idxCvt[0] = 1;
	sArr[1] = 0;

	int id, re, dest, s;
	for (int i = 0; i < Q-1; i++) {
		cin >> cmd;

		if (cmd == 200) {
			cin >> id >> re>>dest;
			cmdQ.push({ cmd,id,re, dest,0 });

		}
		else if (cmd == 300) {
			cin >> id;
			cmdQ.push({ cmd,id,0,0,0 });

		}
		else if (cmd == 400) {
			cmdQ.push({ cmd, 0,0,0,0 });

		}
		else if (cmd == 500) {
			cin >> s;
			cmdQ.push({ cmd, 0,0,0,s });

			if (!idxCvt[s]) {
				totalS++;
				idxCvt[s] = totalS;
				sArr[totalS] = s;
			}
		}

		//cmdQ.push_back
	}

	for (int i = 1; i <= totalS; i++) {
		dijkstr(sArr[i], i);
	}

	while (!cmdQ.empty()) {
		cmd = cmdQ.front().cmd, id = cmdQ.front().id, dest=cmdQ.front().dest, re = cmdQ.front().revenue, s=cmdQ.front().s;
		cmdQ.pop();

		if (cmd == 200) {
#if DEBUG
			cout << "cmd=200, id=" << id << ", revenue=" << re << ", dest=" << dest << endl;
#endif

			itemRecent[id].pid = id;
			itemRecent[id].dest = dest;
			itemRecent[id].re = re;
			itemCheck[id] = true;


			for(int i = 1; i <= totalS; i++) {
				itemRecent[id].start = sArr[i];
				pq[i].push(itemRecent[id]);
			}
		}
		else if (cmd == 300) {
#if DEBUG
			cout << "cmd=300, id=" << id << endl;
#endif

			itemCheck[id] = false;
		}
		else if (cmd == 400) {
#if DEBUG
			cout << "cmd=400" << endl;
#endif
			cout << FindItem() << endl;
		}
		else if (cmd == 500) {
#if DEBUG
			cout << "cmd=500, s=" << s << endl;
#endif
			curS = idxCvt[s];
		}
	}


	return 0;
}