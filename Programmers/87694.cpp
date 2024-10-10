/*

  1. Good, 좌표계의 경우 좌표 하나로 표현시 좌표 중첩을 표현할 수 없어 좌표계를 2배로 하는것 괜찮은 방식
  2. 채워짐 여부 판단 로직 아래에 있음.

  */
#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int map[102][102], v[102][102];

int N = 0;
void printMap() {
    for (int i = 0 ; i <= N ; i++) {
        for (int j = 0 ; j <= N ; j++) {
            printf("%-2d ", v[i][j]);
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}
void fillMap(vector<int> vec) {
    int lx = vec[0], ly = vec[1], rx = vec[2], ry = vec[3];
    
    N = max(rx*2, N);
    N = max(ry*2, N);
    for (int i = lx*2 ; i <= rx*2 ; i++) {
        for (int j = ly*2 ; j <= ry*2 ; j++) {
            if (( i == lx*2 || i == rx*2 || j == ly*2 || j == ry*2) && map[i][j] != 2)
                map[i][j] = 1;
            else
                map[i][j] = 2;
        }
    }
}


pair<int,int> mv[4] = {
    {0,1}, {0,-1}, {1,0} ,{-1,0}
};

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    for (vector<int> v : rectangle) {
        fillMap(v);
    }
    
    queue<pair<int,int>> q;
    q.push({characterX*2, characterY*2});
    v[characterX*2][characterY*2] = 1;
    
    while(!q.empty()) {
        int cx = q.front().first, cy = q.front().second;
        q.pop();
        
        for (int i = 0 ; i< 4 ; i++) {
            int dx = cx + mv[i].first, dy = cy + mv[i].second;
            if (dx < 0 || dx > N || dy < 0 || dy > N) continue;
            if (map[dx][dy] != 1 || v[dx][dy]) continue;
            
            v[dx][dy] = v[cx][cy] + 1;
            q.push({dx, dy});
            if(dx == itemX*2 && dy == itemY*2) {
                //printMap();
                return v[cx][cy] / 2;
            }
            
            
        }
    }

    return answer;
}
