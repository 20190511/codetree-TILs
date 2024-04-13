//1110
#define DEBUGS	false
#define DEBUG	false
#define _CRT_SECURE_NO_WARNINGS
#define ITEM_CNT	100000
#define BELT_CNT	10
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

int Q, N, M;
set<int> belt_item[BELT_CNT+1];
int belt[BELT_CNT +1][2];
unordered_map<int, int> idToIdx;
bool belt_status[BELT_CNT + 1];

int weight[ITEM_CNT + 1];
int i_prev[ITEM_CNT + 1];
int i_next[ITEM_CNT + 1];

void printBelt() {
	for (int i = 1; i <= M; i++) {
		if (!belt_status[i]) {
			cout << "belt[" << i << "] is bad\n";
			continue;
		}
		
		int head = belt[i][0];
		cout << "belt [" << i<<"] {";

		for (head = belt[i][0]; head != belt[i][1]; head = i_next[head]) {
			cout << head << " ";
		}
		cout << head << "}"<< endl;
	}
}
void init() {
	cin >> N >> M;
	int max_cnt = N / M;
	int id, w;
	for (int i = 1; i <= N; i++) {
		int belt_num = ((i-1) / max_cnt) + 1;
		belt_status[belt_num] = true;
		int idx = ((i - 1) % max_cnt);
		cin >> id;
		
		idToIdx[id] = i; //등록
		belt_item[belt_num].insert(i);
		if (idx == 0) {
			belt[belt_num][0] = belt[belt_num][1] = i;
			i_prev[i] = -1;
			i_next[i] = -1;
		}
		else {
			int cur_tail = belt[belt_num][1];
			i_prev[i] = cur_tail;
			i_next[i] = -1;
			i_next[cur_tail] = i;
			belt[belt_num][1] = i;
		}
	}
	
	for (int i = 1; i <= N; i++) {
		cin >> weight[i];
	}
}
void down() {
	int max_cnt;
	cin >> max_cnt;
	long long sum_weight = 0;
	for (int i = 1; i <= M; i++) {
		if (!belt_status[i]) continue;
		int head = belt[i][0];
		if (head == -1) continue;
		if (weight[head] <= max_cnt) {
#if DEBUG
			cout << "belt [" << i << "] down :: " << head << endl;
#endif
			sum_weight += (long long) weight[head];
			belt_item[i].erase(head);
			if (i_next[head] == -1) {
				belt[i][0] = belt[i][1] = -1;
				i_next[head] = i_prev[head] = -1;
				continue;
			}
			else {
				belt[i][0] = i_next[head];
				i_prev[belt[i][0]] = -1;
				i_next[head] = i_prev[head] = -1;
			}
		}
		else {
#if DEBUG
			cout << "belt [" << i << "] push_back (down) :: " << head << endl;
#endif
			if (i_next[head] == -1) {
				continue;
			}

			belt[i][0] = i_next[head];
			int tail = belt[i][1];
			belt[i][1] = head;

			i_prev[belt[i][0]] = -1;
			i_next[tail] = head;
			i_prev[head] = tail;
			i_next[head] = -1;
		}
	}
	cout << sum_weight << endl;
}

int idx_cvt(int hashIdx) {
	if (idToIdx.find(hashIdx) == idToIdx.end()) {
#if DEBUG
		cout << "no idx :: " << hashIdx << endl;
#endif
		return -1;
	}
	return idToIdx[hashIdx];
}
void err_item() {
	int id_h;
	cin >> id_h;
	int idx = idx_cvt(id_h);
	if (idx == -1) {
		cout << -1 << endl;
		return;
	}
#if DEBUG
	cout << "erase idx :: " << idx << endl;
#endif
	for (int i = 1; i <= M; i++) {
		if (!belt_status[i]) continue;
		
		set<int>::iterator it = belt_item[i].find(idx);
		if (it != belt_item[i].end()) {
			belt_item[i].erase(it);
			
			if (belt[i][0] == belt[i][1]) {
				belt[i][0] = belt[i][1] = -1;
			}
			else  if (belt[i][0] == idx) {
				belt[i][0] = i_next[idx];
				i_prev[belt[i][0]] = -1;
			}
			else if (belt[i][1] == idx) {
				belt[i][1] = i_prev[idx];
				i_next[belt[i][1]] = -1;
			}
			else {
				i_next[i_prev[idx]] = i_next[idx];
				i_prev[i_next[idx]] = i_prev[idx];
			}
			i_prev[idx] = i_next[idx] = -1;
			cout << id_h << endl;
			return;
		}
	}

	cout << -1 << endl;
}
void confirm() {
	int id_h;
	cin >> id_h;
	int idx = idx_cvt(id_h);
	if (idx == -1) {
		cout << -1 << endl;
		return;
	}
#if DEBUG
	cout << "confirm idx :: " << idx << endl;
#endif

	for (int i = 1; i <= M; i++) {
		if (!belt_status[i]) continue;

		set<int>::iterator it = belt_item[i].find(idx);
		if (it != belt_item[i].end()) {

			int prev = i_prev[idx];
			if (prev != -1) {
				int tail = belt[i][1];

				i_next[tail] = belt[i][0];
				i_prev[belt[i][0]] = tail;
				
				i_next[prev] = -1;
				i_prev[idx] = -1;
				belt[i][1] = prev;
				belt[i][0] = idx;
			}
			cout << i << endl;
			return;
		}
	}

	cout << -1 << endl;
}
void bad() {
	int b_num;
	cin >> b_num;
	if (!belt_status[b_num]) {
#if DEBUG
		cout << b_num << " is already bad\n";
#endif
		cout << -1 << endl;
		return;
	}

	for (int i = (b_num + 1) % M, cnt = 0; cnt < M - 1; cnt++, i = (i + 1) % M) {
		if (belt_status[i]) {
			int cur_head = belt[b_num][0];
			int next_tail = belt[i][1];

			if (cur_head != -1) {
				if (next_tail == -1) { //없음
					belt[i][0] = belt[b_num][0];
					belt[i][1] = belt[b_num][1];
				}
				else {
					belt[i][1] = belt[b_num][1];
					i_next[next_tail] = cur_head;
					i_prev[cur_head] = next_tail;
				}
				belt_item[i].insert(belt_item[b_num].begin(), belt_item[b_num].end());
				belt_item[b_num].clear();
			}

			belt[b_num][0] = belt[b_num][1] = -1;
			cout << b_num << endl;
			belt_status[b_num] = false;
			return;
		}
	}
	cout << -1 << endl;
}
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("input.txt", "r", stdin);
#endif

	cin >> Q;
	int cmd;
	for (int i = 1; i <= Q; i++) {
		cin >> cmd;
#if DEBUG
		cout << "+++++ q = " << i << "(" << cmd << ") +++++" << endl;
#endif
		if (cmd == 100) {
			init();
		}
		else if (cmd == 200) {
			down();
		}
		else if (cmd == 300) {
			err_item();
		}
		else if (cmd == 400) {
			confirm();
		}
		else if (cmd == 500) {
			bad();
		}

#if DEBUG
		printBelt();
#endif
	}
}