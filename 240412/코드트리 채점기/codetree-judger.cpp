//1626
#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <set>
#include <queue>
using namespace std;
int N, Q;
int wait_cnt = 0;
struct node {
	int t;
	int p;
	int domain;
	int id;

	bool operator<(node a) const {
		if (p != a.p)
			return p > a.p;
		return t > a.t;
	}
};
unordered_map<string, int> hashIdx;
int curHashIdx = 1;
priority_queue<int, vector<int>, greater<int>> judgerQ;
priority_queue<node> nextQ[301];
int judging[301]; // 채점중인 domain 번호
set<int> judging_dom;

set<int> domainList[301]; //wait domain list
int d_s[301];
int d_g[301];

pair<int, int> stringParser(string s) {
	size_t idx = s.find('/');
	string dom = s.substr(0, idx);
#if DEBUG
	cout << idx << ", " << dom << endl;
#endif
	int id = atoi(s.substr(idx+1).c_str());
	
	if (hashIdx.find(dom) == hashIdx.end()) {
		hashIdx[dom] = curHashIdx++;
	}

#if DEBUG
	cout << s << " --> " << "{" << hashIdx[dom] << " , " << id<< "}" << endl;
#endif
	return { hashIdx[dom], id };
}

void init() {
	string url;
	cin >> N >> url;
#if DEBUG
	cout << "100 " << N << " " << url << endl;
#endif
	for (int i = 1; i <= N; i++) {
		judgerQ.push(i);
	}
	node init;
	pair<int, int> urlSet = stringParser(url);
	init.p = 1, init.t = 0, init.domain = urlSet.first, init.id = urlSet.second;
	nextQ[1].push(init);
	domainList[1].insert(urlSet.second);
	wait_cnt++;

#if DEBUG
#endif

}
void request() {
	node news;
	string url;
	cin >> news.t >> news.p >> url;
#if DEBUG
	cout << "200 " << news.t << " " << news.p << " " << url << endl;
#endif
	pair<int, int> sets = stringParser(url);
	news.domain = sets.first, news.id = sets.second;

	if (domainList[news.domain].find(news.id) != domainList[news.domain].end()) {
#if DEBUG
		cout << url << " is in wait queue" << endl;
#endif
		return;
	}
	
#if DEBUG
	cout << "request :: " << url << " waited" << endl;
#endif
	domainList[news.domain].insert(news.id);
	nextQ[news.domain].push(news);
	wait_cnt++;
}

void judge() {
	int t;
	cin >> t;
#if DEBUG
	cout << "300 " << t << endl;
#endif
	if (judgerQ.empty()) {
#if DEBUG
		cout << "judger is full\n";
#endif
		return;
	}

	node n;
	n.p = 50001, n.t = 1000001;
	for (int i = 1; i <= 300; i++) {
		if (nextQ[i].empty()) continue;
		if (judging_dom.find(i) != judging_dom.end()) continue;
		if (d_g[i] > t) continue;

		node tmp = nextQ[i].top();
		if (tmp.p < n.p || (tmp.p == n.p && tmp.t < n.t)) {
			n.domain = tmp.domain;
			n.p = tmp.p;
			n.t = tmp.t;
			n.id = tmp.id;
		}
	}

	if (n.p == 50001) return;
	
#if DEBUG
	cout << n.domain << ", " << n.id << " --> judge start\n";
#endif
	nextQ[n.domain].pop();
	d_s[n.domain] = t;
	d_g[n.domain] = 10000001;
	judging_dom.insert(n.domain);
	
	int n_judge = judgerQ.top();
	judgerQ.pop();
	judging[n_judge] = n.domain;

	//wait Queue에서 빼기
	domainList[n.domain].erase(n.id);

	wait_cnt--;

}

void finish() {
	int t, id;
	cin >> t >> id;
#if DEBUG
	cout << "400 " << t << " " << id << endl;
#endif
	if (!judging[id]) {
#if DEBUG
		cout << "id :: " << id << " is resting already" << endl;
#endif
		return;
	}

	int cur = judging[id];
	judging[id] = 0;
	judging_dom.erase(cur);
	judgerQ.push(id);
	d_g[cur] = (t- d_s[cur]) * 3 + d_s[cur];
#if DEBUG
	cout << "Finish :: " << cur << ", gap == "<< d_g[cur] << endl;
#endif
}
int main(void) {
#if DEBUG
	freopen("test.txt", "r", stdin);
#endif
	cin >> Q;
	int cmd;
	for (int i = 1; i <= Q; i++) {
#if DEBUG
		cout << "+++++ " << i << " +++++" << endl;
#endif
		cin >> cmd;
		if (cmd == 100) {
			init();
		}
		else if (cmd == 200) {
			request();
		}
		else if (cmd == 300) {
			judge();
		}
		else if (cmd == 400) {
			finish();
		}
		else if (cmd == 500) {
			int t;
			cin >> t;
			cout << wait_cnt << endl;
		}
	}

	return 0;
}