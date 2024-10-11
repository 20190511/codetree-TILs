//0848 ~ 0901
//BFS + BruteForce Search
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

int N = -1;
int answer = 999;
bool map[101][101];


int solution(int n, vector<vector<int>> wires) {
    N = n;
    for (vector<int> v : wires) {
        int s = v[0], e = v[1];
        map[s][e] = map[e][s] = true;
    }
    
    bool visit[100] = {0, };
    for (vector<int> v : wires) {
        memset(visit, 0, sizeof(visit));
        
        int s = v[0], e = v[1];
        map[s][e] = map[e][s] = false;
        
        queue<int> q;
        visit[s] = true;
        q.push(s);
        int cnt = 0;
        while(!q.empty()) {
            int cur = q.front();
            cnt++;
            q.pop();
            
            for (int i = 1 ; i <= n ; i++) {
                if (!map[cur][i] || visit[i]) continue;
                visit[i] = true;
                q.push(i);
            }
        }
        
        int other = n - cnt;
        //cout<<"vec=["<<s<<","<<e<<"] = ("<<cnt<<", "<<other<<")"<<endl;
        answer = min(abs(other - cnt), answer);
        map[s][e] = map[e][s] = true;
        
    }
        
    return answer;
}
