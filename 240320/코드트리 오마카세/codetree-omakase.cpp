#ifndef DEBUG
// 재도전 ... 2036
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;
struct detail {
	int first;
	int second;
	int third;
};

int rail_size, totalFoodCnt = 0, totalManCnt = 0;
unordered_map <string, vector<pair<int, int>>> rail; //시간, 위치
unordered_map <string, detail> man; //시간, 위치, 먹는 개수, 원래위치
unordered_map <string, priority_queue<pair<int, int>>> prev_q;
unordered_map <string, vector<pair<int, int>>> pq; //시간 위치

int calcLastTime(string name, int pos)
{
	int manPos = man[name].second;
	int lt = manPos < pos ? manPos + rail_size - pos : manPos - pos;
	return lt;
}

void manSort(string name, int timer)
{
	auto rail_it = rail.find(name);
	if (rail_it == rail.end()) {
		pq[name] = vector<pair<int, int>>();
		return;
	}


	detail& tmp = man[name];
	int manTime = tmp.first, manPos = tmp.second;

	vector<pair<int, int>>& dq = rail_it->second;
	pq[name] = vector<pair<int, int>>();
	prev_q[name] = priority_queue<pair<int, int>>();

	while (!dq.empty()) {
		int item_time = dq.back().first, item_pos = dq.back().second;
		int item_cur_pos = (item_pos + (timer - item_time)) % rail_size;
		int lasttime = calcLastTime(name, item_cur_pos);
		prev_q[name].push({ -lasttime, dq.back().first }); //최소힙 정렬
		dq.pop_back();
	}
}


void eatProcess(int curTime) {
	deque<string> deleteQ;
	for (auto man_it = prev_q.begin(); man_it != prev_q.end(); man_it++) {
		priority_queue<pair<int, int>>& prev_q = man_it->second;
		auto& man_obj = man[man_it->first];
		while (!prev_q.empty()) {
			int overtime = curTime - man_obj.first;
			int lasttime = -prev_q.top().first;
			if (overtime >= lasttime) {
				prev_q.pop();
				totalFoodCnt--;
				man_obj.third--;
				if (!man_obj.third)
					deleteQ.push_back(man_it->first);
			}
			else
				break;
		}
	}

	for (auto man_it = pq.begin(); man_it != pq.end(); man_it++) {
		vector<pair<int, int>>& dq = man_it->second, newQ;
		auto& man_obj = man[man_it->first];
		while (!dq.empty()) {
			int overtime = curTime - dq.back().second;
			int lasttime = -dq.back().first;
			if (overtime >= lasttime) {
				totalFoodCnt--;
				man_obj.third--;
				if (!man_obj.third)
					deleteQ.push_back(man_it->first);
			}
			else
				newQ.push_back(dq.back());
			dq.pop_back();
		}
		man_it->second = newQ;
	}

	while (!deleteQ.empty()) {
		totalManCnt--;
		rail.erase(deleteQ.back());
		man.erase(deleteQ.back());
		pq.erase(deleteQ.back());
		prev_q.erase(deleteQ.back());
		deleteQ.pop_back();
	}

}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int m;
	cin.tie(0)->sync_with_stdio(false);
	cin >> rail_size >> m;
	while (m--) {
		string name;
		int cmd, t, x, n;
		cin >> cmd >> t;

		if (cmd == 100) {
			totalFoodCnt++;
			cin >> x >> name;
			auto pq_it = pq.find(name);
			/*
			int pos = x - t % rail_size + 1;
			while (pos < 0) pos += rail_size;
			*/
			if (pq_it != pq.end()) {
				int lt = man[name].second - x;
				if (lt < 0) lt += rail_size;
				pq_it->second.push_back({ -lt, t });
				continue;
			}

			auto rail_it = rail.find(name);
			if (rail_it == rail.end()) {
				rail[name] = vector<pair<int, int>>();
				rail[name].push_back({ t, x });
			}
			else
				rail[name].push_back({ t,x });

		}
		else if (cmd == 200) {
			totalManCnt++;
			cin >> x >> name >> n;
			/*
			int pos = x - t % rail_size + 1;
			while (pos < 0) pos += rail_size;
			*/

			man[name] = { t, x, n };
			manSort(name, t);
		}
		else if (cmd == 300) {
			eatProcess(t);
			printf("%d %d\n", totalManCnt, totalFoodCnt);

		}

	}
	return 0;
}
#endif