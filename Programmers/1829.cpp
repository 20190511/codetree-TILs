
//https://school.programmers.co.kr/learn/courses/30/lessons/1829#
//얶까문제임 풀지마셈

#include <vector>
#include <queue>
#include <iostream>

#define DEBUG false
using namespace std;
int N, M;
int map[101][101];


void printMap() {
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < M ; j++) {
            cout << map[i][j]<< " ";
        }
        cout<<endl;
    }
    cout<<"============"<<endl;
}

void cpyMap(vector<vector<int>>& p) {
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < M ; j++) {
            map[i][j] = p[i][j];
        }
    }
}

pair<int,int> mv[4] = {
    {0,1}, {0,-1}, {1,0}, {-1,0}
};
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    N=m, M=n;
    
    cpyMap(picture);
    printMap();
    bool v[101][101] = {0,};
    
    
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ;j < M ; j++) {
            if (v[i][j] || !map[i][j]) continue;
            
            int tmpArea = 0; 
            queue<pair<int,int>> q;
            q.push({i,j});
            number_of_area++;
            v[i][j] = true;
            int pivot = map[i][j];
            while(!q.empty()) {
                int cx = q.front().first, cy = q.front().second;
                tmpArea++;
                
                q.pop();
                for (int x = 0 ; x < 4 ; x++) {
                    int dx = cx + mv[x].first, dy = cy + mv[x].second;
                    if (dx < 0 || dx >= N || dy < 0 || dy >= N || v[dx][dy] || map[dx][dy] != pivot) continue;
                    
                    q.push({dx,dy});
                    v[dx][dy] = true;
                }
            }
            
            max_size_of_one_area = max(max_size_of_one_area, tmpArea);
        }
    }
    
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
