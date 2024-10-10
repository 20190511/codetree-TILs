//0803 ~ 35이해
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG false
#define DEBUGS false
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#define endl "\n"
/*
	문제 이해 실패 -> 하나라도 가능하면 q에서 빼는부분 망각.
*/

using namespace std;

struct node {
	int domainIdx;
	string domain;
	string url;
	int id;
	int t;
	int p;
	node(int domainIdx=0, string d="", string url="", int id = 0, int t = 0, int p = 0) : domainIdx(domainIdx), url(url), domain(d), id(id), t(t), p(p) {}

	const bool operator< (const node& b) const {
		if (p == b.p)
			return t > b.t;
		return  p > b.p;
	}
};

struct tmp {
	const bool operator() (const int& a, const int& b) const {
		return a > b;
	}
};

//unordered_map<string, int> wq_checker; //1이면 현재 존재, 0면 wq에서 나감.
set<string> wq_checker;
priority_queue<node> wq;
priority_queue<int, vector<int>, tmp> judgeIDQ;
pair<bool, node> judgeQ[100001];

unordered_map<string, int> domainIdx;
pair<int, int> history[301];

//unordered_map<string, pair<int,int>> history; //도메인 현 채점 상태 <시작, 끝> => 채점시작 시 1000001
//채점 시작 시 검사

int Q, N, runCnt=0, totalDomain=1;

pair<string, int> domainCvt(string url) {
	size_t tok = url.find("/");
	string domain = url.substr(0, tok);
	int id = atoi(url.substr(tok + 1).c_str());

	return { domain, id};
}

void goWait(string url, int p, int t) {

	//if (wq_checker[url] == 1) {
	if (wq_checker.find(url) != wq_checker.end()) {
#if DEBUG
		cout << " ** 동일 url 존재 : " << url << endl;
#endif
		return;
	}

	pair<string, int> cvt = domainCvt(url);
	//wq_checker[url] = true;

	wq_checker.insert(url);

	int mydomId = domainIdx[cvt.first];
	if (!mydomId) {
		domainIdx[cvt.first] = totalDomain;
		mydomId = totalDomain++;
	}
	wq.push(node(mydomId, cvt.first, url, cvt.second, t, p));

#if DEBUG
	cout << " ** url 대기큐 삽입 : " << url << endl;
#endif
}



void goJudge(int t) {
	if (!runCnt) {
#if DEBUG
		cout << " ** 쉬고 있는 채점기 없음" << endl;
#endif
		return;
	}

	if (wq.empty()) {
#if DEBUG
		cout << " ** 대기큐 비어있음." << endl;
#endif
		return;
	}

	queue<node> tmpQ;
	node top = wq.top();

	bool canJudge = false;
	
	while (!wq.empty()) {
		top = wq.top();
		wq.pop();

		pair<int, int> hist = history[top.domainIdx]; // t>=0

		int diff = hist.second - hist.first;
		int test = hist.first + 3 * diff;
		if (test > t) {
#if DEBUG
			cout << " ** url=" << top.url << "은 start + diff * 3 = " << test << ", curTime = " << t << " 으로 채점 불가" << endl;
#endif
		}
		else {
			canJudge = true;
			break;
		}
		tmpQ.push(top);
	}
	
	while (!tmpQ.empty()) {
		wq.push(tmpQ.front());
		tmpQ.pop();
	}
	
	if (!canJudge) {
#if DEBUG
		cout << " ** 대기큐 비어있음." << endl;
#endif
		return;
	}

	//wq_checker[top.url] = false;
	wq_checker.erase(top.url);
	int j_id = judgeIDQ.top();
	judgeIDQ.pop();
	judgeQ[j_id] = { true, top };
	history[top.domainIdx] = { t, 1000001 };
	runCnt--;

#if DEBUG
	cout << " ** 채점 시작: " << top.url<<", j_id="<<j_id << endl;
#endif
}

void goFinish(int t, int j_id) {
	if (!judgeQ[j_id].first) {
#if DEBUG
		cout << " ** 채점기 비어있음 : j_id=" <<j_id<< endl;
#endif
		return;
	}

	
	node top = judgeQ[j_id].second;
	judgeQ[j_id] = { false, node() };
	
	pair<int, int> save = history[top.domainIdx];
	history[top.domainIdx] = { save.first, t };
	judgeIDQ.push(j_id);
	runCnt++;
#if DEBUG
	cout << " ** j_ud="<< j_id << "채점 종료 : t=" << t << endl;
#endif

}

int main(void)
{

	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif

	cin >> Q;

	int cmd, t, p, j_id;
	string url;


	cin >> cmd >> N >> url;
	goWait(url, 1, 0);
	runCnt = N;
	for (int i = 1; i <= N; i++) {
		judgeIDQ.push(i);
	}

	for (int i = 2; i <= Q; i++) {
#if DEBUG
		cout << " <<< " << i << " >>>" << endl;
#endif
		cin >> cmd;

		if (cmd == 200) {
			cin >> t >> p >> url;
			goWait(url, p, t);
		}
		else if (cmd == 300) {
			cin >> t;
			goJudge(t);
		}
		else if (cmd == 400) {
			cin >> t >> j_id;
			goFinish(t, j_id);
		}
		else if (cmd == 500) {
			cin >> t;
			cout << wq.size() << endl;
		}
#if DEBUG
		if (i == 103)
			cout << "debug" << endl;
		if (i == 119)
			break;
#endif
	}

	return 0;
}