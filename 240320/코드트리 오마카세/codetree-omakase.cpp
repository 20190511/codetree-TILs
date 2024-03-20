// 재도전 ... 2036
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <unordered_map>
#include <queue>
#include <deque>
#include <string>
using namespace std;
struct detail {
	int first;
	int second;
	int third;
};

int rail_size, totalFoodCnt = 0, totalManCnt = 0;
unordered_map <string, deque<pair<int, int>>> rail; //시간, 위치
unordered_map <string, detail> man; //시간, 위치, 먹는 개수, 원래위치
unordered_map <string, priority_queue<pair<int, int>>> prev_q;
unordered_map <string, deque<pair<int, int>>> pq; //시간 위치

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
		pq[name] = deque<pair<int, int>>();
		return;
	}


	detail& tmp = man[name];
	int manTime = tmp.first, manPos = tmp.second;

	deque<pair<int, int>>& dq = rail_it->second;
	pq[name] = deque<pair<int, int>>();
	prev_q[name] = priority_queue<pair<int, int>>();

	while (!dq.empty()) {
		int item_time = dq.front().first, item_pos = dq.front().second;
		int item_cur_pos = (item_pos + (timer - item_time)) % rail_size;
		int lasttime = calcLastTime(name, item_cur_pos);
		prev_q[name].push({ -lasttime, dq.front().first }); //최소힙 정렬
		dq.pop_front();
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
		deque<pair<int, int>>& dq = man_it->second, newQ;
		auto& man_obj = man[man_it->first];
		while (!dq.empty()) {
			int overtime = curTime - dq.front().second;
			int lasttime = -dq.front().first;
			if (overtime >= lasttime) {
				totalFoodCnt--;
				man_obj.third--;
				if (!man_obj.third)
					deleteQ.push_back(man_it->first);
			}
			else
				newQ.push_back(dq.front());
			dq.pop_front();
		}
		man_it->second = newQ;
	}

	while (!deleteQ.empty()) {
		totalManCnt--;
		rail.erase(deleteQ.front());
		man.erase(deleteQ.front());
		pq.erase(deleteQ.front());
		prev_q.erase(deleteQ.front());
		deleteQ.pop_front();
	}

}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int m;
	scanf("%d %d", &rail_size, &m);
	while (m--) {
		char c_name[32];
		string name;
		int cmd, t, x, n;
		scanf("%d %d", &cmd, &t);

		if (cmd == 100) {
			totalFoodCnt++;
			scanf("%d %s", &x, c_name);
			name = string(c_name);
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
				rail[name] = deque<pair<int, int>>();
				rail[name].push_back({ t, x });
			}
			else
				rail[name].push_back({ t,x });

		}
		else if (cmd == 200) {
			totalManCnt++;
			scanf("%d %s %d", &x, c_name, &n);
			/*
			int pos = x - t % rail_size + 1;
			while (pos < 0) pos += rail_size;
			*/
			name = string(c_name);

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