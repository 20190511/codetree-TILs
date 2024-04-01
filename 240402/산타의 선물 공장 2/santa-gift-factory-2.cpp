//1045
#define DEBUG false
#define PREV 0
#define NEXT 1
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


vector<int> belt[100001];
int item[100001][2];
int Q, N, M;


void init(vector<int>& q) {
	for (int i = M; !q.empty(); i--) {
		int belt_n = q.back();

		item[i][PREV] = item[i][NEXT] = -1;
		if (belt[belt_n].size()) {
			int next_item = belt[belt_n].back();
			item[next_item][PREV] = i;
			item[i][NEXT] = next_item;
		}
		belt[belt_n].push_back(i);
		
		q.pop_back();
	}
}

int process2(int a, int b) {

	vector<int>& src = belt[a];
	vector<int>& dst = belt[b];

	if (!src.size()) return (int)dst.size();

	int dst_front = dst.size() ? dst.back() : -1;
	int src_back = src.front();
	
	item[src_back][NEXT] = dst_front;
	if (dst_front != -1) {
		item[dst_front][PREV] = src_back;
	}

	dst.insert(dst.end(), src.begin(), src.end());
	src.clear();
	return (int)dst.size();
}

int process3(int a, int b) {
	vector<int>& src = belt[a];
	vector<int>& dst = belt[b];

	int src_back = src.size() ? src.back() : -1;
	int dst_back = dst.size() ? dst.back() : -1;
	if (dst.size()) dst.pop_back();
	if (src.size()) src.pop_back();

	if (dst.size()) item[dst.back()][PREV] = -1;
	if (src.size()) item[src.back()][PREV] = -1;

	if (src_back != -1) {
		if (dst.size()) {
			item[dst.back()][PREV] = src_back;
			item[src_back][NEXT] = dst.back();
		}
		else {
			item[src_back][NEXT] = -1;
		}
		dst.push_back(src_back);
	}
	if (dst_back != -1) {
		if (src.size()) {
			item[src.back()][PREV] = dst_back;
			item[dst_back][NEXT] = src.back();
		}
		else {
			item[dst_back][NEXT] = -1;
		}
		src.push_back(dst_back);
	}

	return (int)dst.size();
}


int process4(int a, int b) {
	vector<int>& src = belt[a];
	vector<int>& dst = belt[b];

	int src_cnt = src.size();
	if (src_cnt <= 1) return (int)dst.size();

	int move_cnt = src.size() / 2;
	int new_end = src[src.size() - move_cnt];
	if (dst.size()) {
		
		item[new_end][NEXT] = dst.back();
		item[dst.back()][PREV] = new_end;
	}
	else {
		item[new_end][NEXT] = -1;
	}
	dst.insert(dst.end(), src.end() - move_cnt, src.end());
	src.erase(src.end() - move_cnt, src.end());
	if (src.size()) item[src.back()][PREV] = -1;

	return (int)dst.size();
}
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUG
	freopen("input.txt", "r", stdin);
#endif

	cin >> Q;
	while (Q--) {
		int cmd;
		cin >> cmd;
		int src, dst;
		if (cmd == 100) {
			cin >> N >> M;
			int bNum;
			vector<int> q;
			for (int i = 0; i < M; i++) {
				cin >> bNum;
				q.push_back(bNum);
			}
			init(q);
		}
		else if (cmd == 200) {
			cin >> src >> dst;
			int val = process2(src, dst);
			cout << val << "\n";
		}
		else if (cmd == 300) {
			cin >> src >> dst;
			int val = process3(src, dst);
			cout << val << "\n";
		}
		else if (cmd == 400) {
			cin >> src >> dst;
			int val = process4(src, dst);
			cout << val << "\n";
		}
		else if (cmd == 500) {
			int p_num;
			cin >> p_num;
			int a = item[p_num][PREV], b = item[p_num][NEXT];
			cout << a + 2 * b << "\n";

		}
		else if (cmd == 600) {
			int b_num;
			cin >> b_num;
			int a, b, c = (int)belt[b_num].size();
			a = c ? belt[b_num].back() : -1;
			b = c ? belt[b_num].front() : -1;
			cout << a + 2 * b + 3 * c << "\n";
		}
	}

	return 0;

}