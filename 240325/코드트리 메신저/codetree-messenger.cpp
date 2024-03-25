//0935 ~ 1120 (로직 꼬임으로 인한 재설계 반복..)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

struct alarm {
	int next;
	unordered_set<int> prev;
	int power;
	int cnt;
	bool on_off; // cnt+1 만큼 위에 껐다 켰다 해야함.
	
};

struct cmd {
	int cmd;
	int c1;
	int c2;
	int power;
};

alarm vecQ[100000];
queue<int> sortQ;
vector<cmd> cmdQ;
int N, Q;

void alarm_on(int s);
void alarm_off(int s);
void run();
int main(void) {
	//freopen("input.txt", "r", stdin);
	cin.tie(0)->sync_with_stdio(false);
	cin >> N >> Q;
	int cmd;
	cin >> cmd;
	Q--;
	vecQ[0] = { 0,{}, 0,0,true };
	for (int i = 1; i <= N; i++) {
		int mom;
		cin >> mom;
		vecQ[i].next = mom;
		vecQ[i].on_off = true;
		vecQ[mom].prev.insert(i);
	}
	
	for (int i = 1; i <= N; i++) {
		int power;
		cin >> power;
		vecQ[i].power = power;
	}

	while (Q--) {
		int c1=0, c2=0, power=0;
		cin >> cmd;
		if (cmd == 200)
			cin >> c1;
		else if (cmd == 300)
			cin >> c1 >> power;
		else if (cmd == 400)
			cin >> c1 >> c2;
		else if (cmd == 500)
			cin >> c1;

		cmdQ.push_back({ cmd,c1,c2,power });
	}

	run();
	return 0;
}

int sums = 0;
//depth 1로 시작
void dfs(int s, int depth) {
	if (!vecQ[s].on_off)
		return;

	for (auto p : vecQ[s].prev) {
		if (vecQ[p].on_off) {
			if (vecQ[p].power >= depth)
				sums++;
			dfs(p, depth + 1);
		}
	}
		
}
void run() {
	for (auto c : cmdQ) {
		if (c.cmd == 200) {
			if (!vecQ[c.c1].on_off)
				vecQ[c.c1].on_off = true;
			else
				vecQ[c.c1].on_off = false;
		}
		else if (c.cmd == 300) {
			vecQ[c.c1].power = c.power;
		}
		else if (c.cmd == 400) {
			int n1 = vecQ[c.c1].next, n2 = vecQ[c.c2].next;
			if (n1 == n2) continue;
			
			vecQ[n1].prev.erase(c.c1);
			vecQ[n2].prev.erase(c.c2);
			vecQ[n1].prev.insert(c.c2);
			vecQ[n2].prev.insert(c.c1);
			vecQ[c.c1].next = n2;
			vecQ[c.c2].next = n1;

		}
		else if (c.cmd == 500) {
			//dfs 탐색.
			sums = 0;
 			dfs(c.c1, 1);
			cout << sums << "\n";
		}
	}
}