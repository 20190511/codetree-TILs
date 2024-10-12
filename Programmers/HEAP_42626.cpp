//1026
//10분컷
// 스코빌 장난 문제
//https://school.programmers.co.kr/learn/courses/30/lessons/42626
// heapQ에 가장 위에있는 노드의 우선순위가 가장 높게하도록 짜는 문제
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct tmp {
    const bool operator() (const int& a, const int& b) const {
        return a > b;
    }
};
priority_queue<int, vector<int>, tmp> pq;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    for (int s : scoville) {
        pq.push(s);
    }
    
    int top = -1;
    while((top = pq.top()) < K && !pq.empty()) {
        answer++;
        pq.pop();
        if (pq.empty())
            return -1;
        int topSecond = pq.top();
        pq.pop();
        
        int newsc = top + (topSecond * 2);
        pq.push(newsc);
    }
    
    if (pq.empty())
        return -1;
    
    
    return answer;
}
