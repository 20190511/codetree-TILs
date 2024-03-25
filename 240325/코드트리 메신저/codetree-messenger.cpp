//0935 ~ 1120 (로직 꼬임으로 인한 재설계 반복..) -> 구현은 하였으나 시간초과.
// 13:00 ==> 트리 DP 문제 공부..
/**
* 실제 구현에서 가장 중요한 점은 힘의 세기를 전달하는 벡터가 존재한다는 점.
*	-> 각 노드에서 힘의 세기를 전달하는 배열을 어떻게 놔둘 것인지가 맹점.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

struct alarm {
	int next;
	int power;
	bool on_off;
};

struct cmd {
	int cmd;
	int c1;
	int c2;
	int power;
};

alarm vecQ[100001];
int ptable[100001][22];
queue<int> sortQ;
vector<cmd> cmdQ;
int N, Q;


void alarmOff(int s) {
	int curNode = vecQ[s].next, curPower = vecQ[s].power;
	if (!vecQ[s].on_off)
		return;

	//ptable에서 onBit 된 것들만큼 순회
	for (int depth = 1; vecQ[curNode].on_off ; depth++) {
		for (int i = 0; i+depth < 22; i++) {
			ptable[curNode][i] -= ptable[s][i+depth];
		}
		
		if (!curNode) break;
		curNode = vecQ[curNode].next;

	}
}

void alarmOn(int s) {
	int curNode = vecQ[s].next, curPower = vecQ[s].power;
	if (!vecQ[s].on_off)
		return;

	//ptable에서 onBit 된 것들만큼 순회
	for (int depth = 1; vecQ[curNode].on_off ; depth++) {
	
		for (int i = 0; i + depth < 22; i++) {
			ptable[curNode][i] += ptable[s][i + depth];
		}
		if (!curNode) break;
		curNode = vecQ[curNode].next;
	}
}

int main(void) {
	//freopen("input.txt", "r", stdin);
	cin.tie(0)->sync_with_stdio(false);
	cin >> N >> Q;
	int cmd;
	cin >> cmd;
	Q--;

	vecQ[0].on_off = true;
	for (int i = 1; i <= N; i++) {
		cin >> vecQ[i].next;
		vecQ[i].on_off = true;
	}
	for (int i = 1; i <= N; i++) {
		cin >> vecQ[i].power;
		vecQ[i].power = min(vecQ[i].power, 20);
	}

	//힘 전달 테이블 제작. -> 자신의 power까지 더해서 계산.
	for (int i = 1; i <= N ; i++) {
		int cur = i, curPower = vecQ[cur].power;
		
		//위로 올라가면서 갱신
		while (curPower > -1) {
			ptable[cur][curPower--]++;
			if (!cur)
				break;
			cur = vecQ[cur].next;
		}
	}

	while (Q--) {
		int c1 = 0, c2 = 0, power = 0;
		cin >> cmd;
		if (cmd == 200) {
			cin >> c1;
			if (!vecQ[c1].on_off) {
				vecQ[c1].on_off = true;
				alarmOn(c1);
			}
			else {
				alarmOff(c1);
				vecQ[c1].on_off = false;
			}
		}
		else if (cmd == 300) {
			cin >> c1 >> power;
			alarmOff(c1);
			ptable[c1][vecQ[c1].power]--;
			vecQ[c1].power = power;
			ptable[c1][power]++;
			alarmOn(c1);
		}
		else if (cmd == 400) {
			cin >> c1 >> c2;
			alarmOff(c1);
			alarmOff(c2);
			int n1 = vecQ[c1].next, n2 = vecQ[c2].next;
			vecQ[c1].next = n2;
			vecQ[c2].next = n1;
			alarmOn(c1);
			alarmOn(c2);
				
		}
		else if (cmd == 500) {
			cin >> c1;
			int sums = 0;
			for (int i = 0; i < 22; i++)
				sums += ptable[c1][i];
			cout << sums - 1 << "\n";

		}
	}
	return 0;
}