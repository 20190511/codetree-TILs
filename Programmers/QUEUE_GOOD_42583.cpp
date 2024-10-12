//순서대로 1152 ~ 1231
//https://school.programmers.co.kr/learn/courses/30/lessons/42583#
// 차가 시간 전에 Queue에서 이미 나간 케이스를 고려하지 못함.
//Queue -> Time 시뮬레이션
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct node {
    int w;
    int end_t;
};
int answer = 0;
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int curWeight = 0;
    queue<node> road;
        
    int curT = 0, curW=0;
    for (int w : truck_weights) {
        //나가기
        bool byPass = true;
        
        while(!road.empty() && curT >= road.front().end_t) {
            curW -= road.front().w;
            road.pop();
        }
        
        while (curW + w > weight) {
            curT = max(road.front().end_t, curT);
            curW -= road.front().w;
            road.pop();
            byPass = false;
        }
        
        if (byPass) curT++;
        
        //cout<<"curT="<<curT<<", w="<<w<<", end_t="<<curT+bridge_length<<" bypass="<<byPass<<endl;
        road.push({w, curT+bridge_length});
        curW += w;
        answer = max(answer, road.back().end_t);
    }
    
    return answer;
}
