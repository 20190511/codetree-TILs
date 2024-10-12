//1109 ~ 1149
/*
//https://school.programmers.co.kr/learn/courses/30/lessons/42627#
  디스크 컨트롤러 우선순위큐인지 검증하느라 시간이 걸림
  SJF 를 할 때는 항상 가장 runTime이 짧은 시간을 앞에 배정하면 항상 유리함.
  그래서 Time을 고려하여 panddingQ에서 하나씩 빼서 넣어주면됨
*/
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

struct node {
    int enter_t;
    int run_t;
    
    node(int e=0, int r=0) : enter_t(e), run_t(r) {}
    
    const bool operator< (const node& b) const {
        if (run_t != b.run_t)
            return run_t > b.run_t;
        return enter_t > b.enter_t;
    }
};

const bool cmp(const node& a, const node& b) {
    return a.enter_t < b.enter_t;
}

node jobNode[501];
int answer = 0;
priority_queue<node> pq;

int sums = 0;
int nodeCnt = 0;

int solution(vector<vector<int>> jobs) {
    for (vector<int> s : jobs) {
        int e = s[0], r =s[1];
        jobNode[nodeCnt++] = {e, r};
    }
        
    sort(jobNode, jobNode+nodeCnt, cmp);
    
    int ptr = 0;
    int checkNode = 0;
    for (int t = 0 ; t < 1000001 && checkNode < nodeCnt ; t++) {
        while (jobNode[ptr].enter_t <= t && ptr < nodeCnt) {
            pq.push(jobNode[ptr++]);
        }
        //panddingQ에서 찾기
        
        if (pq.empty()) continue;
        
        checkNode++;
        node top = pq.top();
        pq.pop();
        int enter_t = top.enter_t, run_t = top.run_t;
        
        //cout<<"t="<<t<<" => "<<enter_t<<", run_t="<<run_t<<endl;
        sums += (t + run_t - enter_t);
        t += (run_t - 1);
    }
    
    
    answer = sums / (int)jobs.size();
    return answer;
}
