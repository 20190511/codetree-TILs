//https://school.programmers.co.kr/learn/courses/30/lessons/42587
//1200 
//1207 삽질 -> 문제 이해 잘못함. ~ 20
// 1207 ~ 1220 (프로세스 queue순회랑 비슷함.)
// stack에서 빼서 다시 삽입하는 문제였음.
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct process {
    int pid;
    int pri;
};

priority_queue<int> pq;

queue<process> q;
int solution(vector<int> priorities, int location) {
    for (int i = 0 ; i < priorities.size() ; i++) {
        q.push({i, priorities[i]});
        pq.push(priorities[i]);
        
    }
    
    int answer = 0;
    while(!pq.empty()) {
        int top = pq.top();
        pq.pop();
       // cout<<"top = "<<top<<endl;
        
        process p = q.front();
        
        //char v = ('A' + p.pid);
        //cout<<p.pri<<", pid="<<v<<endl;
        q.pop();
        
        while(p.pri != top) {
            q.push(p);
            p = q.front();
            q.pop();
        }
        
        
        answer++;
        if (p.pid == location)
            return answer;
    }
    return answer;
}
