//1130 ~ 시간안에 못 품/. <- 왤캐어렵나 했더니 구현 Platinum 3 문제더라ㅋㅋㅋ ;;;

/**
* 로직이 꼬여버림 : 이미 놓는 시점을 통일해뒀는데 이걸 꼬아서 생각해서 재계산 재계산....
* --> // 이미 포인터를 회전해서 배치를 했다는건, 사람을 배치한 순간의 그 원판을 동시대에 볼 수 있도록 설계해뒀기 때문.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include <deque>
#include <vector>
#include <map>
using namespace std;

struct man_sub {
	int first;
	int second;
	int third;
};
int timer = 1, rail_size;
int total_food_cnt = 0, total_man_cnt = 0;
map<string, man_sub> man;
map<string, deque<pair<int, int> > > rail; //회전, 고정

// Eating 연산 수행
void eating(int timer) {
	deque<string> delName;
	for (map<string, man_sub>::iterator m = man.begin(); m != man.end(); m++) {
		string cur_name = m->first;
		int man_pos = m->second.first, man_times = m->second.third;
		deque<pair<int, int>>& q = rail[cur_name];

		int maxCnt = (int)q.size();
		deque<pair<int, int>> newQ;
		for (int cnt = 0; cnt < maxCnt; cnt++) {
			// 음식이 남자에게 도착할 때까지 필요한 시간을 계산한다.
			pair<int, int> q_it = q.at(cnt);
			int overtime, lasttime;
			if (man_times < q_it.first) {
				overtime = timer - q_it.first;
				int new_man_pos = (man_pos - (q_it.first % rail_size - man_times % rail_size));
				while (new_man_pos < 0)
					new_man_pos += rail_size;
				new_man_pos %= rail_size;
				lasttime = q_it.second > new_man_pos ? new_man_pos + rail_size - q_it.second : new_man_pos - q_it.second;
			}
			else {
				overtime = timer - man_times;
				lasttime = q_it.second > man_pos ? man_pos + rail_size - q_it.second : man_pos - q_it.second;
			}

			if (overtime < lasttime) {
				newQ.push_back(q_it);
			}
			else {
				total_food_cnt--;
				m->second.second--;
				if (!m->second.second)
					delName.push_back(cur_name);
			}
		}
		rail[cur_name] = newQ;
	}

	while (!delName.empty()) {
		rail.erase(delName.front());
		man.erase(delName.front());
		total_man_cnt--;
		delName.pop_front();
	}
}


int main(void)
{
	int B;
	//cin.tie(0)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	cin >> rail_size >> B;
	for (int k = 0; k < B; k++) {
		char name_char[32];
		int cmd, t, x, cnt;
		string name;
		scanf("%d", &cmd);

		// 현재 시간 대비 
		if (cmd == 100) {
			scanf("%d %d %s", &t, &x, name_char);
			name = string(name_char);
			map<string, deque<pair<int, int> > >::iterator tmp = rail.find(name);
			int cur_pos = x - t % rail_size + 1;
			while (cur_pos < 0)
				cur_pos += rail_size;
			cur_pos %= rail_size;
			if (tmp == rail.end()) {
				rail[name] = deque<pair<int, int>>();
				rail[name].push_back({ t, cur_pos });
			}
			else {
				rail[name].push_back({ t, cur_pos });
			}
			total_food_cnt++;
		}
		else if (cmd == 200) {
			scanf("%d %d %s %d", &t, &x, name_char, &cnt);
			name = string(name_char);
			int cur_pos = x - t % rail_size + 1; //레일을 돌리고 난 후 올라가기 때문....
			while (cur_pos < 0)
				cur_pos += rail_size;
			cur_pos %= rail_size;
			man[name] = { cur_pos, cnt, t };
			total_man_cnt++;
		}
		else if (cmd == 300) {
			scanf("%d", &t);
			// 사이에 적용된 계산들 수행
			eating(t);
			/*
			int total_cnt = 0;
			for (map<string, deque<pair<int, int>>>::iterator it = rail.begin(); it != rail.end(); it++) {
				total_cnt += (int)it->second.size();
			}

			int man_cnt = 0;
			for (map<string, man_sub>::iterator it = man.begin(); it != man.end(); it++) {
				if (it->second.second)
					man_cnt++;
			}
			printf("%d %d\n", man_cnt, total_cnt);
			*/
			printf("%d %d\n", total_man_cnt, total_food_cnt);
		}
	}


	return 0;
}