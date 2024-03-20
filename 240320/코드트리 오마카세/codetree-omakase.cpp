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
	int fourth;
};

int rail_size, totalFoodCnt = 0, totalManCnt = 0;
unordered_map <string, deque<pair<int, int>>> rail; //시간, 위치
unordered_map <string, detail> man; //시간, 위치, 먹는 개수, 원래위치
unordered_map <string, priority_queue<pair<int, int>>> pq; //시간 위치

int calcLastTime(string name, int t, int pos)
{
	int manPos = man[name].second;
	int lt = manPos < pos ? manPos + rail_size - pos : manPos - pos;
	return lt;
}

void manSort(string name)
{
	auto rail_it = rail.find(name);
	if (rail_it == rail.end())
		return;

	detail &tmp = man[name];
	int manTime = tmp.first, manPos = tmp.second;
	
	deque<pair<int, int>>& dq = rail_it->second;
	pq[name] = priority_queue<pair<int, int>>();
	while (!dq.empty()) {
		int lasttime = calcLastTime(name, dq.front().first, dq.front().second);
		pq[name].push({ -lasttime, dq.front().first }); //최소힙 정렬
		dq.pop_front();
	}
}

void eatProcess(int curTime) {
	deque<string> deleteQ;
	for (auto man_it = pq.begin(); man_it != pq.end(); man_it++) {
		priority_queue<pair<int, int>>& pq = man_it->second;
		auto& man_obj = man[man_it->first];
		while (!pq.empty()) {
			int overtime = curTime - max(pq.top().second, man_obj.first);
			int lasttime = -pq.top().first;
			if (overtime >= lasttime) {
				pq.pop();
				totalFoodCnt--;
				man_obj.third--;
				if (!man_obj.third)
					deleteQ.push_back(man_it->first);
			}
			else
				break;
		}
	}

	while (!deleteQ.empty()) {
		totalManCnt--;
		rail.erase(deleteQ.front());
		man.erase(deleteQ.front());
		pq.erase(deleteQ.front());
		deleteQ.pop_front();
	}

}

int main(void)
{
	//freopen("input.txt", "r", stdin);
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

			int pos = x - t % rail_size + 1;
			while (pos < 0) pos += rail_size;
			if (pq_it != pq.end()) {
				int lt = man[name].fourth - x;
				if (lt < 0) lt += rail_size;
				pq_it->second.push({-lt, t});
				continue;
			}

			auto rail_it = rail.find(name);
			if (rail_it == rail.end()) {
				rail[name] = deque<pair<int, int>>();
				rail[name].push_back({ t, pos });
			}
			else
				rail[name].push_back({ t,pos });
			
		}
		else if (cmd == 200) {
			totalManCnt++;
			scanf("%d %s %d", &x, c_name, &n);
			int pos = x - t % rail_size + 1;
			while (pos < 0) pos += rail_size;
			name = string(c_name);
			man[name] = {t, pos, n, x};
			manSort(name);
		}
		else if (cmd == 300) {
			eatProcess(t);
			printf("%d %d\n", totalManCnt, totalFoodCnt);

		}

	}
	return 0;
}