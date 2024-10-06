//1715 ~ 1727 왜 레벨3냐?
#define DEBUG true
#include <string>
#include <vector>
#include <queue>
#include <iostream>

bool v[201];

using namespace std;

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    for (int i = 0 ; i < n ; i++) {
        if (v[i]) continue;
        answer++;
        queue<int> q;
        
        q.push(i);
        v[i] = true;
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int idx = 0 ; idx < n ; idx++) {
                if (!computers[cur][idx]) continue;
#if DEBUGS
                cout<<"["<<cur<<"] idx="<<idx<<endl;
#endif
                if (idx == i || v[idx]) continue;
                
                v[idx] = true;
                q.push(idx);
            }
        }
    }    
    return answer;
}
