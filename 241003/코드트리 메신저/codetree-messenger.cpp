//1816 ~ 1837 (해석완료)
#define DEBUG false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

#define NODECNT	100001
#define endl "\n"

struct node {
	int parent;
	bool button;
	int auth;

	node(int parent = 0, bool switches = false, int auth = 0) :parent(parent), button(button), auth(auth) {

	}
};

node nodes[NODECNT];
int saveAuth[NODECNT][21]; //현 nodepower
int N, Q;

void addAlarm(int s, int power) {
	
	int cur = s;
	int curPower = power;
	while (curPower >= 0) {
		int powerIdx = min(20, curPower);
		saveAuth[cur][powerIdx]++;

		if (nodes[cur].parent == cur)
			break;

		cur = nodes[cur].parent;
		curPower--;
	}
}

void deleteAlarm(int s, int power) {
	int cur = s;
	int curPower = power;
	while (curPower >= 0) {
		int powerIdx = min(20, curPower);
		saveAuth[cur][powerIdx]--;

		if (nodes[cur].parent == cur)
			break;

		cur = nodes[cur].parent;
		curPower--;
	}
}


//자기껀 안지웁니다.
void addAlarmSet(int s) {
	
	int pDepth = 1;
	int parent = nodes[s].parent;
	while (true) {

		for (int i = pDepth; i <= 20; i++) {
			saveAuth[parent][i - pDepth] += saveAuth[s][i];
		}

		if (parent == nodes[parent].parent) break;
		parent = nodes[parent].parent;
		pDepth++;
	}

}

void deleteAlarmSet(int s) {
	int pDepth = 1;
	int parent = nodes[s].parent;
	while (true) {

		for (int i = pDepth; i <= 20; i++) {
			saveAuth[parent][i - pDepth] -= saveAuth[s][i];
		}

		if (parent == nodes[parent].parent) break;
		parent = nodes[parent].parent;
		pDepth++;
	}
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
	int cmd, c1, c2, c, power;
#if DEBUG
	freopen("q.txt", "r", stdin);
#endif

	cin >> N >> Q;
	
	//0번 설정
	nodes[0].auth = 0;
	nodes[0].button = true;

	cin >> cmd;

	for (int i = 1; i <= N; i++) {
		cin >> c;
		nodes[i].parent = c;
		nodes[i].button = true;
	}
	for (int i = 1; i <= N; i++) {
		cin >> power;
		nodes[i].auth = power;

		addAlarm(i, power);
	}


	for (int i = 0; i < Q-1; i++) {
		cin >> cmd;
		if (cmd == 200) {
			cin >> c;
			bool curState = nodes[c].button;
			if (curState) {
				deleteAlarmSet(c);
				nodes[c].button = false;
			}
			else {
				addAlarmSet(c);
				nodes[c].button = true;
			}

		}
		else if (cmd == 300) {
			cin >> c >> power;
			
			deleteAlarm(c, nodes[c].auth);
			nodes[c].auth = power;
			addAlarm(c, nodes[c].auth);

		}
		else if (cmd == 400) {
			cin >> c1 >> c2;
			
			if (nodes[c1].button)
				deleteAlarmSet(c1);

			if (nodes[c2].button)
				deleteAlarmSet(c2);
			
			swap(nodes[c1].parent, nodes[c2].parent);

			if (nodes[c1].button)
				addAlarmSet(c1);
			if (nodes[c2].button)
				addAlarmSet(c2);

		}
		else if (cmd == 500) {
			cin >> c;

			int cnt = 0;

			for (int i = 0; i <= 20; i++) {
				cnt += saveAuth[c][i];
			}


			cout << cnt-1 << endl;
		}
	}

	return 0;
}