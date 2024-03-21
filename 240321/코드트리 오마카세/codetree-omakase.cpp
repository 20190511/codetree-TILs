#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
// 시간별로 정렬하되 스시를 먹을 때마다 갱신 08:30 ~ 09:00
/**
	핵심 아이디어 : 
 >> CMD Vector를 모두 받아두고 Eating 하는 순서를 sort 정렬을 통해 정렬시킴
 >>> 중요한 점은, 이전 아이디어처럼 가독성을 높이기 위해 연산 시에만 배열을 돌려서 보는걸 추천
 	(미리 돌려서 넣어서 이게 맞는지 틀린지 확인 불가능한 코드는 안 좋은 코드임")

 >>중요 점
  : unordered_map 을 복잡하게 만들지 말 것. 되도록이면 그냥 아래처럼 변수 3개로 운용할 것
  	(메모리는 많이 차지하지만 속도는 빠름)
  : deque보다 vector가 월등히 빠르므로 선입선출이 상관없을 시 vector를 사용할 것.
  : sort는 a < b 가 True 이면 1로 설정되므로 (return 값이 크다? a 가 b 보다 앞에오는 조건임)
*/
using namespace std;
struct CMD {
	int cmd;
	int pos;
	int cur_time;
	string name;
};

unordered_map<string, int> man_pos, man_time, man_canent;
vector<CMD> cmd_list, v;
int rail_size;

bool compare(CMD& a, CMD& b) {
	if (a.cur_time != b.cur_time)
		return a.cur_time < b.cur_time;
	return a.cmd < b.cmd;
}
void run() {
	for (auto item : cmd_list) {
		if (item.cmd != 100)
			continue;

		int when_man_come = man_time[item.name];
		int manPos = man_pos[item.name];
		int eat_time;
		CMD newCmd;
		newCmd.cmd = 110; //Eating CMD

		//Eating사람 보다 초밥이 먼저 옴
		if (when_man_come > item.cur_time) {
			eat_time = when_man_come;
			int rePosition = (item.pos + (when_man_come - item.cur_time)) % rail_size;
			eat_time += rePosition > manPos ? rail_size + manPos - rePosition : manPos - rePosition;
		}
		else {
			eat_time = item.cur_time;
			eat_time += item.pos > manPos ? rail_size + manPos - item.pos : manPos - item.pos;
		}

		newCmd.cur_time = eat_time;
		newCmd.name = item.name;
		newCmd.pos = item.pos;
		v.push_back(newCmd);
	}
	cmd_list.insert(cmd_list.end(), v.begin(), v.end()); //연결
	sort(cmd_list.begin(), cmd_list.end(), compare);

	int total_susi = 0, total_man = 0;
	for (auto item : cmd_list) {
		if (item.cmd == 100) {
			total_susi++;
		}
		else if (item.cmd == 110) {
			total_susi--;
			man_canent[item.name]--;
			if (!man_canent[item.name]) {
				total_man--;
			}
		}
		else if (item.cmd == 200)
			total_man++;
		else if (item.cmd == 300) {
			cout << total_man << " " << total_susi << "\n";
		}
	}
}
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
	string name;
	int c, t, x, n, q;
	cin >> rail_size >> q;
	//input
	while (q--) {
		cin >> c >> t;
		if (c == 100) {
			cin >> x >> name;
			cmd_list.push_back({ c, x, t, name});
		}
		else if (c == 200) {
			cin >> x >> name >> n;
			man_pos[name] = x;
			man_time[name] = t;
			man_canent[name] = n;
			cmd_list.push_back({ c,x,t,name });
		}
		else if (c == 300) {
			cmd_list.push_back({ c, 0, t, ""});
		}
	}

	run();
	return 0;
}
