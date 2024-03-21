#include <iostream>
#include <vector>
//0913
using namespace std;
#define SUCCESS	25
#define CHECK(X,Y) (X < 0 || X >= 5 || Y < 0 || Y >= 5 || map[X][Y])
int map[5][5] = { 0, };
int cur_walks = 0, answer = 0;
pair<int, int> mv[4] = {
	{-1,0}, {1,0}, {0,1}, {0,-1}
}, aPtr = { 0,0 }, bPtr = { 4,4 };

void printMap() {
	cout << "======\n";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
}

void run() {
	pair<int, int> originA = aPtr, originB = bPtr;
	for (int i = 0; i < 4; i++) {
		int ax = aPtr.first + mv[i].first, ay = aPtr.second + mv[i].second, bx, by;
		if (CHECK(ax, ay)) continue;
		map[ax][ay] = 1;
		aPtr = {ax, ay};
		cur_walks++;
		for (int j = 0; j < 4; j++) {
			bx = bPtr.first + mv[j].first, by = bPtr.second + mv[j].second;
			if (bx == ax && ay == by) {
				if (cur_walks == SUCCESS) {
					answer++;
				}
				continue;
			}
			if (CHECK(bx, by)) continue;
			
			map[bx][by] = 2;
			cur_walks++;
			bPtr = { bx,by };
			run();

			map[bx][by] = 0;
			cur_walks--;
			bPtr = originB;

		}
		map[ax][ay] = 0;
		cur_walks--;
		aPtr = originA;
	}
	
}
int main(void) {
	int c,x,y;
	cin >> c;
	cur_walks = c + 2;
	while (c--) {
		cin >> x >> y;
		map[x-1][y-1] = 4;
	}
	map[0][0] = 1;
	map[4][4] = 2;
	run();
	cout << answer;
	return 0;
}