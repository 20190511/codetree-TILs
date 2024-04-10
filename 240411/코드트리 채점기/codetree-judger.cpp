//1117 : 복습
#define DEBUG	false
#define DEBUGS	false
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
using namespace std;

struct node {
	int dom;
	int id;
	int p;
	int t;
};

struct nodeCmp {
	bool operator() (node a, node b) {
		if (a.p == b.p)
			return a.t > b.t;
		return a.p > b.p;
	}
};
unordered_map<string, int> hashToIdx;
int str_idx = 1, wait_cnt = 0;

set<int> wait_problem[301];
//시간초과 방지 --> domain 별로 nextQ 두기.
priority_queue<node, vector<node>, nodeCmp> nextQ[301];

int judging_domain[301];
int judger[50001];
priority_queue<int, vector<int>, greater<int>> j_idxQ;
int domain_s[301];
int domain_e[301];
int domain_g[301];
int N, Q;


pair<int,int> urlParser(string s) {
	size_t i = s.find('/');
	string domain = s.substr(0, i - 1);
	string id = s.substr(i + 1);

	if (hashToIdx.find(domain) == hashToIdx.end()) {
		hashToIdx[domain] = str_idx;
		str_idx++;
	}

#if DEBUG
	cout << s <<"-->" << hashToIdx[domain] << " ," << id << endl;
#endif
	return { hashToIdx[domain], atoi(id.c_str())};
}

int nextJ() {
	if (j_idxQ.empty()) return -1;

	int n = j_idxQ.top();
	j_idxQ.pop();
	return n;
}
void init() {
	string url;
	cin >> N >> url;
	
	node a;
	pair<int, int> tmp = urlParser(url);

	a.dom = tmp.first, a.id = tmp.second;
	a.t = 0, a.p = 1;

	for (int i = 1; i <= N; i++)
		j_idxQ.push(i); 

	//waiting Queue에 자동 삽입
	wait_problem[a.dom].insert(a.id);
	nextQ[a.dom].push(a);
	wait_cnt++;

}

void request() {
	string url;
	node n;
	cin >> n.t >> n.p >> url;
	pair<int, int> tmp = urlParser(url);
	n.dom = tmp.first, n.id = tmp.second;
	int dom = n.dom, id = n.id;

	//추가
	if (wait_problem[dom].find(id) != wait_problem[dom].end()) return;

	wait_problem[dom].insert(id);
	nextQ[dom].push(n);
	wait_cnt++;
	
}

void judge() {
	int t;
	cin >> t;

	vector<node> q;
	int minDom = 301, minP = N + 1, minT = 10000001;
	for (int i = 1; i < str_idx; i++) {
		if (!nextQ[i].empty()) {
			node tmp = nextQ[i].top();

			int dom = tmp.dom, id = tmp.id;

			if (judging_domain[dom]) continue;
			if (domain_g[dom] > t) continue;

			if ((minP > tmp.p) ||
				((minP == tmp.p) && (minT > tmp.t))) {
				minDom = dom;
				minP = tmp.p;
				minT = tmp.t;
			}
		}
	}

	if (minDom != 301) {
		int j_idx = nextJ();
		if (j_idx == -1) {
			return;
		}

		node n = nextQ[minDom].top();
#if DEBUG
		cout << "judge :: " << n.dom << ", " << n.id << endl;
#endif
		int dom = n.dom, id = n.id;
		nextQ[minDom].pop();
		
		//waiting Queue에서 삭제
		wait_problem[dom].erase(wait_problem[dom].find(id));
		//채점기에 올리

		judger[j_idx] = dom;
		judging_domain[dom]++;
		domain_s[dom] = t;
		domain_g[dom] = 5000000;
		wait_cnt--;
	}
}

void finish() {
	int t, id;
	cin >> t >> id;
	if (!judger[id]) return;

	j_idxQ.push(id);
	int dom = judger[id];
	judger[id] = 0;
	judging_domain[dom]--;
	domain_g[dom] = (t - domain_s[dom])*3 + domain_s[dom];
}
void printCnt() {
	int t;
	cin >> t;
	cout << wait_cnt << endl;
}
int main(void) 
{
#if DEBUGS
	freopen("test.txt", "r", stdin);
#endif
	cin >> Q;
	int cmd;
	for (int i = 1; Q--; i++) {
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
			printCnt();
		}
	}
	return 0;
}