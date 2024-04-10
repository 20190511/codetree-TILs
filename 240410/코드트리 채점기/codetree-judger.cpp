//1115 연습용.

/*
* 첫 번째 줄에 명령의 수 Q가 주어집니다.
코드트리 채점기 준비
100 N u0

채점 요청
200 t p u 형태로 공백을 사이에 두고 주어집니다. 이는 t초에 채점 우선순위가 p이며 url이 u인 문제에 대한 채점 요청이 들어왔음을 의미합니다.
채점 시도
300 t 형태로 공백을 사이에 두고 주어집니다. 이는 t초에 채점 대기 큐에서 즉시 채점이 가능한 경우 중 우선순위가 가장 높은 채점 task를 골라 채점을 진행하게 됨을 뜻합니다.
채점 종료
400 t J_id 형태로 공백을 사이에 두고 주어집니다. 

채점 대기 큐 조
500 t 형태로 공백을 사이에 두고 주어집니다. 이 경우 시간 t에 채점 대기 큐에 있는 채점 task의 수를 출력해야합니다.
1 ≤ Q ≤ 50,000
1 ≤ N ≤ 50,000
1 ≤ 도메인의 길이 ≤ 19
1 ≤ 주어지는 서로 다른 도메인의 수 ≤ 300
1 ≤ 문제 ID ≤ 1,000,000,000
1 ≤ p ≤ N
1 ≤ J 
id≤ N
1 ≤ t ≤ 1,000,000
입력으로 주어지는 t 값은 모두 다르며, 오름차순으로 정렬되어 주어짐을 가정해도 좋습니다.
*/

#define DEBUG false
#define DEBUGS	false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
struct node{
	string full_name;
	pair<string, int> url;
	int p;
	int t;
};

//priority_queue 넣어줄 때는 조건을 반대로 넣어줘야함. (앞이 0, 뒤가 1)
struct cmp {
	bool operator()(const node a, const node b) {
		if (a.p == b.p)
			return a.t > b.t;
		else
			return a.p > b.p;
	}
};

priority_queue<node, vector<node>, cmp> waitQ;
int waitcnt = 0, Q, N;
unordered_map<int, unordered_map<string, int>> waitCheckor;
unordered_map<string, int> history; //<domain, diff>
unordered_map<string, int> domain_counter; // 채점 완료한 history만 비교해서 삽입.
node judger[50001];
priority_queue<int, vector<int>, greater<int>> j_counter;

pair<string, int> u_parser(string s) {
	size_t t = s.find('/');
	string url = s.substr(0, t);
	int id = atoi(s.substr(t + 1).c_str());
	return { url,id };
}
void nodeIn (node& a, node& b) {
	a.full_name = b.full_name;
	a.p = b.p;
	a.t = b.t;
	a.url = b.url;
}
void initJudge() {
	for (int i = 1 ; i <= N; i++) {
		j_counter.push(i);
	}
}
int nextJudge() {
	int next = j_counter.top();
	j_counter.pop();
	return next;
}

void add_waiting(node node) {
	auto id_finder = waitCheckor.find(node.url.second);
	if (id_finder != waitCheckor.end()) {
		auto domain_finder = id_finder->second.find(node.url.first);
		if (domain_finder != id_finder->second.end())
			return;

		id_finder->second[node.url.first] = node.t;
		waitQ.push(node);
		waitcnt++;
		return;
	}
	waitCheckor[node.url.second] = unordered_map<string, int>();
	waitCheckor[node.url.second][node.url.first] = node.t;
	waitcnt++;
	waitQ.push(node);
}

void start_scoring(int t) {
	vector<node> q;
	while (!waitQ.empty()) {
		node next = waitQ.top();
		waitQ.pop();
		string domain = next.url.first;
		int id = next.url.second;

		auto hist = history.find(domain); //삽입 시 start 보고 판단
		auto d_test = domain_counter.find(domain);
		if (d_test == domain_counter.end()) {
			domain_counter[domain] = 0;
		}
		int d_cnt = domain_counter[domain];
		if (d_cnt) {
			q.push_back(next);
			continue;
		}

		//아예 역사가 없으면
		int gap_check = 0;
		if (hist != history.end()) {
			gap_check = history[domain];
		}

		//삽입가능
		if (gap_check <= t) {
			int n = nextJudge();
			domain_counter[domain]++;
			nodeIn(judger[n], next);
			judger[n].t = t;
			waitCheckor[next.url.second].erase(next.url.first); //waitQ 에서 지워줌
			waitcnt--;
			break;
		}
		q.push_back(next);
	}

	while (!q.empty()) {
		waitQ.push(q.back());
		q.pop_back();
	}
}
void end_scoring(int t, int id) {
	if (!judger[id].p) return; //예외처리

	node exit = judger[id];
	string domain = exit.url.first;

	int calDiff = (t - exit.t) * 3 + exit.t;
	
	auto h_check = history.find(domain);
	if (h_check == history.end()) {
		history[domain] = calDiff;
	}
	
	int originDiff = history[domain];
	if (originDiff < calDiff) {
		history[domain] = calDiff;
	}

	j_counter.push(id);
	domain_counter[domain]--;
	judger[id].full_name = "";
	judger[id].p = judger[id].t = 0;
	judger[id].url = { "", 0 };
}
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUG
	freopen("test.txt", "r", stdin);
#endif
	cin >> Q;
	string url;
	int t;
	node n;
	while (Q--) {
		int cmd;
		cin >> cmd;
		if (cmd == 100) {
			cin >> N >> url;
			initJudge();
			n.full_name = url;
			n.t = 0;
			n.url = u_parser(url);
			n.p = 1;
			add_waiting(n);
		}
		else if (cmd == 200) {
			int p;
			cin >> n.t >> n.p >> url;
			n.full_name = url;
			n.url = u_parser(url);
			add_waiting(n);
		}
		else if (cmd == 300) {
			cin >> t;
			start_scoring(t);
		}
		else if (cmd == 400) {
			int id;
			cin >> t >> id;
			end_scoring(t, id);
		}
		else if (cmd == 500) {
			cin >> t;
			cout << waitcnt << endl;
		}
	}

	return 0;
}