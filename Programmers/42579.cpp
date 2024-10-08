//1235 ~ 1300 (25분)
//https://school.programmers.co.kr/learn/courses/30/lessons/42579
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct node {
    int idx;
    int plays;
    
    const bool operator< (const node& a) const {
        return plays < a.plays;
    }
};


struct genreNode {
    int idx;
    int plays;
    
    const bool operator< (const genreNode& a) const {
        return plays < a.plays;
    }
};


priority_queue<node> pq[102];
priority_queue<genreNode> gq;
int playsCnt[102];
map<string, int> idxCvt;

int totalCnt = 1;
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    int inputcnt = (int)genres.size();
    for (int i = 0 ; i < inputcnt ; i++) {
        string s = genres[i];
        int idx = idxCvt[s];
        if (!idx) {
            idx = totalCnt;
            idxCvt[s] = totalCnt++;
        }
        
        pq[idx].push({i, plays[i]});
        playsCnt[idx] += plays[i];
    }
        
    for (int i = 1 ; i < totalCnt ; i++) {
        gq.push({i, playsCnt[i]});
    }
    
    while(!gq.empty()) {
        int idx = gq.top().idx, plays = gq.top().plays;
        
        int cnt = 0;
        gq.pop();
        while (!pq[idx].empty() && cnt < 2) {
            int inIdx = pq[idx].top().idx, inPlays = pq[idx].top().plays;
            answer.push_back(inIdx);
            //cout<<inIdx<<", plays="<<inPlays<<endl;
            pq[idx].pop();
            cnt++;
        }
        
        //cout<<idx<<", "<<plays<<endl;
        
    }
    
    return answer;
}
