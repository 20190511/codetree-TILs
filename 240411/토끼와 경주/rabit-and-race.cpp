//0852 ~ 1100
#define DEBUG	false
#define	DEBUGS	false
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct rabbit {
	int x;
	int y;
	int jcnt;
	int d;
	int pid;
	int score;

	bool operator>(const rabbit& t) {
		if ((x + y) != (t.x + t.y)) return (x+y) > (t.x+t.y);
		if (x != t.x) return x > t.x;
		if (y != t.y) return y > t.y;
		return pid > t.pid;
	}
};
struct cmp {
	bool operator()(rabbit a, rabbit b) {
		if (a.jcnt != b.jcnt)
			return a.jcnt > b.jcnt;
		if ((a.x + a.y) != (b.x + b.y))
			return (a.x + a.y) > (b.x + b.y);
		if (a.x != b.x)
			return a.x > b.x;
		if (a.y != b.y)
			return a.y > b.y;
		return a.pid > b.pid;
	}
};

rabbit obj[2001];
priority_queue<rabbit, vector<rabbit>, cmp> rabbitQ;
int Q, N, M, P;
int all_add = 0;
pair<int, int> mv[4] = {
	{1,0}, {0,1}, {-1,0}, {0,-1}
};

int reDist(int sz, int cur, int d, int dir) {
	if (d >= (sz - 1) * 2) {
		d %= ((sz - 1) * 2);
	}

	if (dir > 0) {
		if (d > (sz - 1) - cur) {
			dir = -1;
			d -= ((sz - 1) - cur);
			cur = sz - 1;
		}

		if (d > (sz - 1)) {
			dir = 1;
			d -= (sz - 1);
			cur = 0;
		}
	}//사이즈 정상화
	else {
		if (d > cur) {
			dir = 1;
			d -= cur;
			cur = 0;
		}
		if (d > (sz - 1)) {
			dir = -1;
			d -= (sz - 1);
			cur = sz - 1;
		}
	}
	return cur + d*dir;
}

void init() {
	cin >> N >> M >> P;
	int pid, d;
	for (int i = 1; i <= P; i++) {
		cin >> pid >> d;
		obj[pid].pid = pid;
		obj[pid].d = d;
		rabbitQ.push(obj[pid]);
	}
}

void race() {
	int k, s;
	cin >> k >> s;
	rabbit bestRabbit;
	bestRabbit.x = -1;
	bestRabbit.y = -1;
	bestRabbit.pid = 0;

	for (int i = 0; i < k; i++) {
		rabbit rr = rabbitQ.top();
		rabbit& r = obj[rr.pid];
		rabbitQ.pop();
		int cx = r.x, cy = r.y, cd = obj[r.pid].d;
		int savedX = -1, savedY = -1;
		for (int i = 0; i < 4; i++) {
			int dx, dy;
			if (mv[i].first == 0) {
				dx = cx;
				dy = reDist(M, cy, cd, mv[i].second);
			}
			else {
				dx = reDist(N, cx, cd, mv[i].first);
				dy = cy;
			}
#if DEBUGSS
			cout << dx << "," << dy << endl;
#endif
			int savedSum = savedX + savedY;
			int dxdySum = dx + dy;
			if (savedSum < dxdySum ||
				((savedSum == dxdySum) && (savedX < dx)) ||
				((savedSum == dxdySum) && (savedX == dx) && (savedY < dy))) {
				
				savedX = dx;
				savedY = dy;
			}
		}

		r.x = savedX;
		r.y = savedY;
		r.jcnt++;
#if DEBUG
		cout << "k = " << k << endl;
		cout << "Rabbit : " << r.pid << " --> " << r.x << ", " << r.y << endl;
#endif
		int score = r.x + r.y + 2;
		all_add += score;
		r.score -= score;
		rabbitQ.push(r);
		if (r > bestRabbit) {
			bestRabbit = r;
		}
	}

#if DEBUG
	cout << "best rabbit = " << bestRabbit.pid << endl;
#endif
	obj[bestRabbit.pid].score += s;

}
void change() {
	int pid, l;
	cin >> pid >> l;
	obj[pid].d *= l;
}
void totalScore() {
	int maxScore = 0;
	while (!rabbitQ.empty()) {
		maxScore = max(obj[rabbitQ.top().pid].score + all_add, maxScore);
		rabbitQ.pop();
	}
	cout << maxScore;
}
int main(void) {
#if DEBUGS
	freopen("test.txt", "r", stdin);
#endif
	
	cin >> Q;
	int cmd;
	while (Q--) {
		cin >> cmd;
		if (cmd == 100) {
			init();
		}
		else if (cmd == 200) {
			race();
#if DEBUG
			cout << "Race Score" << endl;
			for (int x = 1; x <= 2000; x++) {
				if (!obj[x].pid) continue;
				cout <<"pid = "<<x<<" -->"<< obj[x].score + all_add << endl;
			}
#endif
		}
		else if (cmd == 300) {
			change();
		}
		else if (cmd == 400) {
			totalScore();
		}
	}
	return 0;
}