//0915 ~ 1008(설계) ~ 1117
/*
	pair 단순실수 (first, second 실수)
*/
#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define endl "\n"

using namespace std;

struct node
{
	int color;
	int id;
	int pid;
	int maxDepth; //얘만 있어도될거같음 min(p.maxDepth, curMaxdepth)
	pair<int, int> allColor; // <Q, color>
	int q; //진입점

	node(int color=0, int id=0, int pid=0, int maxDepth=0, pair<int, int> allColor ={0,0}, int q = 0) : color(color), id(id), pid(pid), maxDepth(maxDepth), allColor(allColor), q(q) {}
};

node nodes[100001];
vector<int> liveQ;

string DEBUGCOL[6] = {
	"", "빨강색", "주황색", "노랑색", "초록색", "파란색"
};

int Q;



void nodeUpdate(int id) {

	int pid = nodes[id].pid;
	liveQ.push_back(id);
	if (pid == -1) {
		return;
	}
	node& pNode = nodes[pid];

	nodes[id].maxDepth = min(pNode.maxDepth-1, nodes[id].maxDepth);

	if (nodes[id].maxDepth <= 0) {
		nodes[id] = node(); //초기화
#if DEBUG
		cout << "id=" << id << " 삽입 실패" << endl;
#endif
		liveQ.pop_back();
		return;
	}
}

int nodeColor(int id) {
	
	node ptr = nodes[id], origin = nodes[id];
	
	pair<int, int> ratest = { 0,0 } ;

	while (true) {
		// 색 비교
		pair<int, int> cur = ptr.allColor;
		if (cur.first != 0 && ratest.first < cur.first) {
			ratest = cur; 
		}
		
		int pid = ptr.pid;
		if (pid == -1) break;

		ptr = nodes[pid];
	}


	if (ratest.first == 0 || ratest.first < origin.q)
		return origin.color;

	return ratest.second;
}


int allColor() {
#if DEBUG
	cout << " << all Color >>: start " << endl;
#endif

	int colorB[100001] = { 0, };
	for (auto it = liveQ.begin(); it != liveQ.end(); it++) {
		int id = *it;
		int color = nodeColor(id);

#if DEBUG
		cout << *it << " : color = " << DEBUGCOL[color] << endl;
#endif
		
		
		// 부모 순회
		int curId = id;
		while (curId != -1) {
			colorB[curId] |= 1 << (color);
			
			curId = nodes[curId].pid;
		}
	}

	int totalSum = 0;
	for (auto it = liveQ.begin(); it != liveQ.end(); it++) {
#if DEBUG
		cout << *it << " : color = ";
#endif

		int tmpSum = 0;
		for (int i = 1; i <= 5; i++) {
			if (colorB[*it] & (1 << i)) {
				tmpSum++;
#if DEBUG
				cout << DEBUGCOL[i] << " ";
#endif
			}
		}


		totalSum += (tmpSum * tmpSum);
#if DEBUG
		cout << " (tmp Sum = " << tmpSum  <<  ")" << endl;
#endif
	}


#if DEBUG
	cout << " << all Color >>: end , totalSum=" <<totalSum<< endl;
#endif

	return totalSum;
}


int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	cin >> Q;
	int cmd, pid, id, color, curDepth;
	for (int i = 1; i <= Q; i++) {
		cin >> cmd;
		if (cmd == 100) {
			cin >> id >> pid >> color >> curDepth;
			nodes[id] = node(color, id, pid, curDepth, { 0,0 }, i);
			nodeUpdate(id);
		}
		else if (cmd == 200) {
			cin >> id >> color;
			nodes[id].allColor = { i, color };
		}
		else if (cmd == 300) {
			cin >> id;
			cout << nodeColor(id) << endl;
		}
		else if (cmd == 400) {
			cout << allColor() << endl;
		}

	}

	return 0;
}