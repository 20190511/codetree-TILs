//문자열 BFS 신박함. 근데 빨리품
//https://school.programmers.co.kr/learn/courses/30/lessons/43163
#include <string>
#include <vector>
#include <queue>

using namespace std;


bool diffCheck(string cur, string next) {
    int cnt = 0;
    for (int i = 0 ; i < cur.size(); i++) {
        if (cur[i] != next[i])
            cnt++;
    }
    
    return cnt <= 1;
}

bool v[51] = {false,};
int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    queue<pair<string, int>> q;    
    
    q.push({begin, 0});
    while(!q.empty()) {
        string cur = q.front().first;
        int changeCnt = q.front().second;
        q.pop();
        
        for (int i = 0 ; i < (int)words.size() ; i++) {
            string next = words[i];
            
            if (v[i] || !diffCheck(cur, next)) continue;
                        
            v[i] = true;
            q.push({next, changeCnt+1});
            
            if (next == target)
                return changeCnt+1;
        }
    }
        
    return 0;
}
