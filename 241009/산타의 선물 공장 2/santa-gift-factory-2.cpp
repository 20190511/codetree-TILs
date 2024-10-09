//0956 ~ 1013 이해 ~ 1132 (풀이)

/*
* 
* 아이템 추적 Vector (수동연결리스트) 와 vector의 조화로 풀 수 있음
* 단, item 추적을 위해 연결할 때 실수가 자주 나는데
*	-1 일 때 연결여부에서 실수가 주로남
* 
* *** 해결책 ***
*	좀 과도할지라도 초기화가 필요없음에도 초기화를 꾸준히 해주고 items를 수동연결할 것.
*/
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define DEBUGS false
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define endl "\n"
using namespace std;

struct item {
	int idx;
	int front;
	int back;
	
	item(int idx = 0, int front = -1, int back = -1) : idx(idx), front(front), back(back) {}
};


int N, M, Q;
vector<int> belt[100001];
item items[100001];


void moveFuncAll(int src, int dst) {

	int srcBack = -1, dstFront = -1;
	if (belt[src].empty())
		srcBack = -1;
	else
		srcBack = belt[src].front();

	if (belt[dst].empty())
		dstFront = -1;
	else
		dstFront = belt[dst].back();

	if (srcBack == -1)
		return;

	if (dstFront != -1) {
		items[dstFront].front = srcBack;
		items[srcBack].back = dstFront;
	}
		
	belt[dst].insert(belt[dst].end(), belt[src].begin(), belt[src].end());
	belt[src].clear();
}


void moveFunc (int src, int dst) {

	int srcBack = -1, dstFront = -1;
	int moveCnt = 0;
	int srcCnt = (int)belt[src].size();

	if (srcCnt <= 1)
		return;
	else
		moveCnt = srcCnt / 2;

	if (belt[src].empty())
		srcBack = -1;
	else
		srcBack = belt[src][srcCnt - moveCnt];

	if (belt[dst].empty())
		dstFront = -1;
	else
		dstFront = belt[dst].back();


	if (srcBack == -1)
		return;

	//src 후처리
	int nextBeltFront = belt[src][srcCnt - moveCnt - 1];
	items[nextBeltFront].front = -1;
	items[srcBack].back = -1;

	if (dstFront != -1) {
		items[dstFront].front = srcBack;
		items[srcBack].back = dstFront;
	}


	//검사
	vector<int> tmpStack;
	for (int i = 0; i < moveCnt; i++) {
		tmpStack.push_back(belt[src].back());
		belt[src].pop_back();
	}

	for (int i = 0; i < moveCnt; i++) {
		belt[dst].push_back(tmpStack.back());
		tmpStack.pop_back();
	}
}

void endChanger(int src, int dst) {

	int srcFront = -1;
	int dstFront = -1;
	if (!belt[src].empty()) {
		srcFront = belt[src].back();
		belt[src].pop_back();
	}
	if (!belt[dst].empty()) {
		dstFront = belt[dst].back();
		belt[dst].pop_back();
	}
	
	if (srcFront != -1)
		items[srcFront].back = -1;
	if (dstFront != -1)
		items[dstFront].back = -1;

	if (!belt[src].empty()) {
		items[belt[src].back()].front = dstFront;
		if (dstFront != -1) {
			items[dstFront].back = belt[src].back();
		}
	}
	
	if (!belt[dst].empty()) {
		items[belt[dst].back()].front = srcFront;
		if (srcFront != -1)
			items[srcFront].back = belt[dst].back();
	}

	if (srcFront != -1)
		belt[dst].push_back(srcFront);
	if (dstFront != -1)
		belt[src].push_back(dstFront);

	
}

int main(void) {
#if DEBUG
	freopen("q.txt", "r", stdin);
#endif
	
	int cmd, m_src, m_dst, p_num, b_num;
	set<int> beltQ;
	cin >> Q;
	cin >> cmd >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> b_num;
		
		items[i] = item(i, -1, -1);
		if (!belt[b_num].empty()) {
			int end = belt[b_num].back();
			
			items[end].back = i;
			items[i].front = end;
		}

		belt[b_num].push_back(i);
		beltQ.insert(b_num);
		
	}

	//순서를 반대로
	for (auto num : beltQ) {
		vector<int> tmpVec;
		tmpVec.insert(tmpVec.begin(), belt[num].rbegin(), belt[num].rend());
		belt[num] = tmpVec;
		tmpVec.clear();
	}


	Q--;
	for (int i = 1; i <= Q; i++) {
		cin >> cmd;

		if (cmd == 200) {
			cin >> m_src >> m_dst;
			moveFuncAll(m_src, m_dst);
			int retVal = (int)belt[m_dst].size();
			cout << retVal << endl;
		}
		else if (cmd == 300) {
			cin >> m_src >> m_dst;
			endChanger(m_src, m_dst);
			int retVal = (int)belt[m_dst].size();
			cout << retVal << endl;
		}
		else if (cmd == 400) {
			cin >> m_src >> m_dst;
			moveFunc(m_src, m_dst);
			int retVal = (int)belt[m_dst].size();
			cout << retVal << endl;
		}
		else if (cmd == 500) {
			cin >> p_num;
			
			int front = items[p_num].front;
			int back = items[p_num].back;

			cout << front + 2 * back << endl;

		}
		else if (cmd == 600) {
			cin >> b_num;

			if (belt[b_num].empty()) {
				cout << -3 << endl;
				continue;
			}
			int front = belt[b_num].back();
			int back = belt[b_num].front();
			int sz = (int)belt[b_num].size();
			cout << front + 2 * back + 3 * sz << endl;
		}
	}
	
	return 0;
}