//1537
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <cstring>
#include <deque>
using namespace std;
struct man {
	int hp;
	int dmg;
	int ux;
	int uy;
	int dx;
	int dy;
};

int map[41][41];
int man_map[41][41];
pair<int, int> mv[4] = {
	{-1,0}, {0,1}, {1,0}, {0,-1}
};
int L, N, Q;
man figher[31];
pair<int, int> cmd[100];

void printMap() {
	cout << "======" << endl;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------" << endl;
	cout << "<man pos>" << endl;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cout << man_map[i][j] << " ";
		}
		cout << endl;
	}
	
}

void unfiil_fighter(int m) {
	for (int i = figher[m].ux; i <= figher[m].dx; i++) {
		for (int j = figher[m].uy; j <= figher[m].dy; j++)
			man_map[i][j] = 0;
	}
}

void fill_fighter(int m) {
	for (int i = figher[m].ux; i <= figher[m].dx; i++) {
		for (int j = figher[m].uy; j <= figher[m].dy; j++) {
			man_map[i][j] = m;
		}
	}
}
bool fill_fighter_2(int m) {
	for (int i = figher[m].ux; i <= figher[m].dx; i++) {
		for (int j = figher[m].uy; j <= figher[m].dy; j++) {
			if (map[i][j] == 1) {
				figher[m].dmg++;
				figher[m].hp--;
				if (figher[m].hp <= 0) {
					unfiil_fighter(m);
					return false;
				}
			}
			man_map[i][j] = m;
		}
	}


	return true;
}



//이동 가능하면 true, 안되면 false
bool man_move(set<int> &q, int m, int dir) {
	
	int ux = figher[m].ux, uy = figher[m].uy, dx = figher[m].dx, dy = figher[m].dy;
	int nx, ny;
	int i, j;
	if (dir == 0) { //상
		i = ux;
		
		for (j = uy; j <= dy; j++) {
			nx = i + mv[dir].first, ny = j + mv[dir].second;
			if (nx <= 0 || nx > L || ny <= 0 || ny > L || map[nx][ny] == 2) return false;
			if (man_map[nx][ny]) q.insert(man_map[nx][ny]);
		}
	}
	else if (dir == 1) { //오
		j = dy;
		for (i = ux; i <= dx; i++) {
			nx = i + mv[dir].first, ny = j + mv[dir].second;
			if (nx <= 0 || nx > L || ny <= 0 || ny > L || map[nx][ny] == 2) return false;
			if (man_map[nx][ny]) q.insert(man_map[nx][ny]);
		}
	}
	else if (dir == 2) { //아
		i = dx;
		for (j = uy; j <= dy; j++) {
			nx = i + mv[dir].first, ny = j + mv[dir].second;
			if (nx <= 0 || nx > L || ny <= 0 || ny > L || map[nx][ny] == 2) return false;
			if (man_map[nx][ny]) q.insert(man_map[nx][ny]);
		}
	}
	else if (dir == 3) { //왼
		j = uy;
		for (i = ux; i <= dx; i++) {
			nx = i + mv[dir].first, ny = j + mv[dir].second;
			if (nx <= 0 || nx > L || ny <= 0 || ny > L || map[nx][ny] == 2) return false;
			if (man_map[nx][ny]) q.insert(man_map[nx][ny]);
		}
	}

	return true;
}


void run() {
	for (int s = 0; s < Q; s++) {
		int f = cmd[s].first, d = cmd[s].second;
		if (figher[d].hp <= 0) continue;
		bool check;
		bool visited[31];
		memset(visited, 0, sizeof(visited));
		vector<int> man_stack;
		queue<int> tmp_queue;
		tmp_queue.push(f);
		man_stack.push_back(f);

		while (!tmp_queue.empty()) {
			int m = tmp_queue.front();
			tmp_queue.pop();
			set<int> tmp_set;
			check = man_move(tmp_set, m, d);

			if (!check) {
				man_stack.clear();
				break;
			}

			for (auto s : tmp_set) {
				if (visited[s]) continue;
				visited[s] = true;
				tmp_queue.push(s);
				man_stack.push_back(s);
			}
		}
				
		while (!man_stack.empty()) {
			int m = man_stack.back();
			man_stack.pop_back();
			unfiil_fighter(m);
			figher[m].dx += mv[d].first, figher[m].dy += mv[d].second;
			figher[m].ux += mv[d].first, figher[m].uy += mv[d].second;

			if (man_stack.size() == 0)
				fill_fighter(m);
			else
				fill_fighter_2(m);
		}
		//printMap();

	}

	int sums = 0;
	for (int i = 1; i <= N; i++)
		if (figher[i].hp > 0)
			sums += figher[i].dmg;
	cout << sums;
}
int main(void)
{
	cin.tie(0)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++)
			cin >> map[i][j];
	}
	
	for (int i = 1; i <= N; i++) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		h--, w--;
		figher[i] = { k,0, r, c, r+h, c+w};
		fill_fighter(i);
	}

	for (int i = 0; i < Q; i++)
		cin >> cmd[i].first >> cmd[i].second;
	
	run();
	return 0;
}