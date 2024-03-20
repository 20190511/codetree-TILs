#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define FOR(i,s,e) for(int i=s; i<e; ++i)
#define Q_MAX 10

int L, Q;
struct CMD {
    int cmd, x, t, n;
    string name;
};
vector<CMD> commands;
unordered_map<string, int> sitting_position; // 손님이 앉은 자리 매핑
unordered_set<string> visitting_customer_names; // 방문한 손님 목록 저장 ( 재방문은 없으므로 중복이 없다 )
unordered_map<string, int> visit_customer_time; // 손님이 방문한 시간대
unordered_map<string, int> eat_cnt; // 손님이 먹어야할 초밥 갯수 매핑
vector<CMD> v;
int sushi_cnt; // 남은 초밥 갯수
int customer_cnt; // 남은 손님 명수

void input() {
    cin >> L >> Q;
    FOR(i, 0, Q) {
        int cmd = -1, t = -1, x = -1, n = -1;
        string name = "";

        cin >> cmd;

        if (cmd == 100) {
            cin >> t >> x >> name;
        }
        else if (cmd == 200) {
            cin >> t >> x >> name >> n;

            visitting_customer_names.insert(name);
            sitting_position[name] = x; // 오는 손님은 모두 다르다 ( 재방문 x )
            visit_customer_time[name] = t; // 손님이 방문한 시각
            eat_cnt[name] = n;
        }
        else if (cmd == 300) cin >> t;
        commands.push_back({cmd,x,t,n,name});
    }
}

bool mcmp(CMD left, CMD right) {
    if (left.t > right.t) return false;
    if (left.t < right.t) return true;

    if (left.cmd > right.cmd) return false;
    if (left.cmd < right.cmd) return true;

    return false;
}

void sol() {
    FOR(i, 0, commands.size()) {// 생성된 초밥이 언제 없어질지 기록
        if (commands[i].cmd != 100) continue; 
        CMD sushis = commands[i];
        int meet_sushi_cutomer_time = 0; // 초밥과 손님이 만나게 할 수 있는 보정 시간
        int eat_sushi_time = 0; //초밥을 먹는 시간

        if (sushis.t < visit_customer_time[sushis.name]) {
            int now_sushi_position = sushis.x;

            int diff_t = visit_customer_time[sushis.name] - sushis.t;

            now_sushi_position = ((now_sushi_position + diff_t) % L);

            if (sitting_position[sushis.name] >= now_sushi_position) {
                meet_sushi_cutomer_time = sitting_position[sushis.name] - now_sushi_position;
            }
            else if (sitting_position[sushis.name] < now_sushi_position) {
                meet_sushi_cutomer_time = (sitting_position[sushis.name] + L) - now_sushi_position;
            }
            eat_sushi_time = visit_customer_time[sushis.name] + meet_sushi_cutomer_time;
        }
        else {
            int now_sushi_position = sushis.x;
            if (sitting_position[sushis.name] >= now_sushi_position) {
                meet_sushi_cutomer_time = sitting_position[sushis.name] - now_sushi_position;
            }
            else if (sitting_position[sushis.name] < now_sushi_position) {
                meet_sushi_cutomer_time = (sitting_position[sushis.name] + L) - now_sushi_position;
            }
            eat_sushi_time = sushis.t + meet_sushi_cutomer_time; // 초밥을 먹을 수 있을 때 까지 걸리는 시간
        }

        // 초밥이 사라지는 시점을 저장
        CMD tmp;
        tmp.cmd = sushis.cmd + 1;
        tmp.t = eat_sushi_time;
        tmp.x = -1;
        tmp.name = sushis.name;
        tmp.n = -1;
        v.push_back(tmp);
    }

    // 전체 명령과 초밥이 사라지는 시점에 대한 정보를 합침
    commands.insert(commands.end(), v.begin(), v.end());

    // t가 작을 수록, 명령이 작을수록 우선순위를 부여해 정렬함
    // 명령 우선순위 (100 -> 101 -> 200 -> 300)
    sort(commands.begin(), commands.end(), mcmp);

    FOR(i, 0, commands.size()) {

        if (commands[i].cmd == 100) {

            ++sushi_cnt;
        }
        else if (commands[i].cmd == 101) {

            --sushi_cnt;

            string now_name = commands[i].name;
            eat_cnt[now_name] = eat_cnt[now_name] - 1;
            if (eat_cnt[now_name] <= 0) --customer_cnt; 
        }
        else if (commands[i].cmd == 200) {

            ++customer_cnt;
        }
        else if (commands[i].cmd == 300) {

            cout << customer_cnt << " " << sushi_cnt << '\n';
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    input();
    sol();

    return 0;
}