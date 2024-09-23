#define  _CRT_SECURE_NO_WARNINGS
#define DEBUG false

//0911
/// move 로직이 좀 어려움
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;



int total = 1;
int Q, N, M, P;


struct rabbit {
	int x;
	int y;
	int count;
	int dist;
	int pid;
	int score;
	int idx;
	
	rabbit(bool select=false ,int x=0, int y=0, int count=0, int dist=0, int pid=0, int score=0, int idx=0) : x(x), y(y), count(count), dist(dist), pid(pid), score(score), idx(idx) {}
	const bool operator< (const rabbit& b) const {
		if (count != b.count)
			return count > b.count;

		if (x + y != (b.x + b.y))
			return x + y > (b.x + b.y);
		
		if (x != b.x)
			return x > b.x;
		
		if (y != b.y)
			return y > b.y;

		return pid > b.pid;
	}
};

unordered_map<int, int> cvt;
bool ice[2001];
rabbit rbt[2001];
priority_queue<rabbit> q;
pair<int, int> mv[4] = {
	{1,0}, {-1,0}, {0,1}, {0,-1}
};


void printMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << "(";
			for (int k = 1; k < total; k++) {
				if (i == rbt[k].x && j == rbt[k].y)
					cout << k << " ";
			}

			cout << ") ";
		}
		cout << endl;
	}

	for (auto it = cvt.begin(); it != cvt.end(); it++) {
		int idx = it->second;
		cout << "토끼(*idx=" << idx << ") pid=" << rbt[idx].pid << ", count=" << rbt[idx].score << ", dist=" << rbt[idx].dist << ", score=" << rbt[idx].score << endl;
	}
	cout << "===============" << endl;
}

void zigMove(int& x, int& y, int dir, int dist) {
	// x 이동
	int newDist = dist % ((N - 1) * 2);
	if (mv[dir].first) {
		newDist = dist % ((N - 1) * 2);


		if (mv[dir].first > 0) {
			int first = N - x;
			if (first >= newDist) {
				x += (mv[dir].first) * newDist;
				return;
			}

			//반대방향
			newDist -= first;
			int second = N - 1;
			if (second >= newDist) {
				x = N - newDist;
				return;
			}

			newDist -= second;
			x = 1 + newDist;
			return;
		}
		else {
			int first = x - 1;
			if (first >= newDist) {
				x -= newDist;
				return;
			}

			//반대방향
			newDist -= first;
			int second = N - 1;
			if (second >= newDist) {
				x = 1 + newDist;
				return;
			}

			newDist -= second;
			x = N - newDist;
			return;
		}
	}

	// y 이동
	if (mv[dir].second) {
		newDist = dist % ((M - 1) * 2);

		if (mv[dir].second > 0) {
			int first = M - y;
			if (first >= newDist) {
				y += (mv[dir].second) * newDist;
				return;
			}

			//반대방향
			newDist -= first;
			int second = M - 1;
			if (second >= newDist) {
				y = M - newDist;
				return;
			}

			newDist -= second;
			y = 1 + newDist;
			return;
		}
		else {
			int first = y - 1;
			if (first >= newDist) {
				y -= newDist;
				return;
			}

			//반대방향
			newDist -= first;
			int second = M - 1;
			if (second >= newDist) {
				y = 1 + newDist;
				return;
			}

			newDist -= second;
			y = M - newDist;
			return;
		}
	}
}
void move() {
	rabbit curRbt = rbt[q.top().idx];
	q.pop();

	int cx = curRbt.x, cy = curRbt.y;

	int sx = 0, sy = 0;
	for (int x = 0; x < 4; x++) {
		//진동 움직임 해줘야됨.
		int dx=cx, dy=cy;
		zigMove(dx, dy, x, curRbt.dist);
		
		if ((sx + sy) > (dx + dy)) continue;
		else if ((sx + sy) == (dx + dy) && (sx > dx)) continue;
		else if ((sx + sy) == (dx + dy) && (sx == dx) && (sy > dy)) continue;

		sx = dx, sy = dy;
	}
#if DEBUG
	cout << curRbt.pid << "-> (" << sx << ", " << sy << ")" << endl;
#endif
	int idx = curRbt.idx;
	rbt[idx].x = sx;
	rbt[idx].y = sy;
	rbt[idx].count++;

	for (int i = 1; i < total; i++) {
		if (i == idx) continue;
		rbt[i].score += (sx + sy);
	}

	q.push(rbt[idx]);
}


#define DEBUGS false
#if DEBUGS
int main(void) {
	N = 3, M = 5;
	int x = 3, y = 5;

	for (int i = 0; i < 4; i++) {
		int dx = x, dy = y;
		zigMove(dx, dy, i, 4);
		cout << dx << ", " << dy << endl;
	}
	exit(0);
	for (int k = 1; k <= 20; k++) {
		int dx = x, dy= y;
		zigMove(dx, dy, 3, k);
		cout << dy << " ";
	}
}
#else
int main(void) {
#if DEBUG
	freopen("q.txt", "r", stdin);
#endif

	cin >> Q;
	
	int cmd;
	cin >> cmd >> N >> M >> P;
	for (int i = 0; i < P; i++) {
		int pid, dist;
		cin >> pid >> dist;
		cvt[pid] = total;
			
		rbt[total].x = rbt[total].y = 1;
		rbt[total].pid = pid;
		rbt[total].dist = dist;
		rbt[total].idx = total;
		q.push(rbt[total]);
		total++;
	}
	Q--;

	for (int QQ = 0; QQ < Q; QQ++) {
		cin >> cmd;

		if (cmd == 200) {
			int K, S;
			cin >> K >> S;
			for (int i = 1; i <= K; i++) {
				move();
#if DEBUG
				cout << "Tern = " << i << endl;
				printMap();
#endif
			}

			int rbtNum = 0, rx = 0, ry = 0, rpid = 0;
			for (int i = 1; i < total; i++) {
				if (!rbt[i].count) continue;
				if ((rbt[i].x + rbt[i].y) < (rx + ry)) continue;
				if (rbt[i].x < rx) continue;
				if (rbt[i].y < ry) continue;
				if (rbt[i].pid < rpid) continue;

				rx = rbt[i].x;
				ry = rbt[i].y;
				rpid = rbt[i].pid;
				rbtNum = i;
			}

			rbt[rbtNum].score += S;

		}
		else if (cmd == 300) {
			int pid, dist;
			cin >> pid >> dist;
			int k = cvt[pid];
			rbt[k].dist *= dist;
#if DEBUG
			cout << "chnge opt : " << pid << " --> " << rbt[k].dist << endl;
#endif
		}
		else {
			int maxScore = 0;
			for (int i = 1; i < total; i++) {
				maxScore = max(maxScore, rbt[i].score);
			}
			cout << maxScore;
		}



#if DEBUG
		printMap();
#endif
	}
	


	return 0;
}
#endif