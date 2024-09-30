/// 10:25 ~ 11:40
/*
	쉬운 구현
	-1 +1 Algorithm + Hash 문제
*/
#define DEBUG false
#define DEBUGS false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;
struct vec {
	int cmd;
	int t;

	const bool operator< (vec& b) {
		if (t != b.t)
			return t < b.t;
		
		return cmd < b.cmd;
	}

	vec(int cmd, int t) : cmd(cmd), t(t) {}
};
int L, Q;

struct man{
	int t;
	int x;
	string name;
	int n;
	man(int t, int x, string name, int n) : t(t), x(x), name(name), n(n) { }
};
//test 해보기
vector<vec> v, plusV;
unordered_map<string, vector<pair<int,int>>> hashVec; //시간과 벨트

vector<man> manQ; // 사람 Q
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
#if DEBUGS
	freopen("q.txt", "r", stdin);
#endif
	
	cin >> L >> Q;
	for (int i = 0; i < Q; i++) {
		int cmd, t, x, n;
		string name;
		
		cin >> cmd >> t;

		if (cmd == 100) {
			cin >> x >> name;

			if (hashVec.find(name) == hashVec.end()) {
				hashVec[name] = vector<pair<int, int>>({ {t,x} });
				v.push_back({ cmd, t });
				continue;
			}
			
			hashVec[name].push_back({ t,x });
		}
		else if (cmd == 200) {
			cin >> x >> name >> n;
			manQ.push_back({ t, x,name,n });
		}
		else if (cmd == 300) {
		}

		v.push_back({ cmd, t });
	}

	// 사람 처리
	while (!manQ.empty()) {
		int n = manQ.back().n, t = manQ.back().t, x = manQ.back().x;
		string name = manQ.back().name;
		manQ.pop_back();

		vector<pair<int, int>> v = hashVec[name];
		sort(v.begin(), v.end());

		int endEatTime = 0;
		for (auto it = v.begin(); it != v.end(); it++) {
			int cT = it->first, cPos = it->second;
			int standardT = cT;
#if DEBUG
			cout << "name=" << name << ", t=" << it->first << ", pos=" << it->second << endl;
#endif
			
			if (cT < t) {
				cPos = (cPos + (t - cT)) % L;
				standardT = t;
			}

#if DEBUG
			cout << "RePos name=" << name << ", t=" << cT << ", pos=" << cPos << "{Pos="<< x<<"}" << endl;
#endif
		
			int eatTime = x - cPos;
			if (eatTime < 0) eatTime += L;
#if DEBUG
			cout << "eatTime = " << eatTime << endl;
#endif

			eatTime += standardT;
			plusV.push_back({ 101, eatTime });
			endEatTime = max(eatTime, endEatTime);
		}

#if DEBUG
		cout << "Out name=" << name << ", endTime=" << endEatTime << endl << endl;
#endif
		plusV.push_back({ 201, endEatTime});

	}

	// 정렬 및 순회
	v.insert(v.end(), plusV.begin(), plusV.end());
	sort(v.begin(), v.end());


	int manCnt = 0, babCnt = 0;
	for (auto s = v.begin(); s != v.end(); s++) {
#if DEBUG
		cout << s->t << ", " << s->cmd << endl;
#endif
		int t = s->t, cmd = s->cmd;
		if (cmd == 100)
			babCnt++;
		else if (cmd == 101)
			babCnt--;
		else if (cmd == 200)
			manCnt++;
		else if (cmd == 201)
			manCnt--;
		else if (cmd == 300) {
			cout << manCnt << " " << babCnt << "\n";
		}

	}

	return 0;
}