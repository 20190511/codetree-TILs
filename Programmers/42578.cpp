//1735
/*
https://school.programmers.co.kr/learn/courses/30/lessons/42578
 단순 해시 재귀 문제 : 
 --> 종류별 곱 누적으로 풀면된다.
*/
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

#define DEBUG true
unordered_map<string, int> hashIdx;
unordered_map<string, bool> hashCvt;
int totalCnt = 1;
int cateCnt[31];

int totalSums = 0;

void recul(int depth, int tmpSums=1) {
    if (depth == totalCnt) {
#if DEBUGS
        cout<<tmpSums<<endl;
#endif
        totalSums += tmpSums;
        return;
    }
    
    recul(depth+1, tmpSums);
    recul(depth+1, tmpSums * cateCnt[depth]);
}

int solution(vector<vector<string>> clothes) {
    int answer = 0;
    
    for (vector<string> v : clothes) {
        string name = v[0];
        string cate = v[1];
        
#if DEBUGS
        cout<<"name="<<name<<", cate="<<cate<<endl;
#endif
        int idx = hashIdx[cate];
        if (!idx) {
            cateCnt[totalCnt] = 1;
            hashIdx[cate] = totalCnt++;
            continue;
        }
        else {
            cateCnt[idx]++;
        }
    }
    
#if DEBUGS
    cout<<"totalCnt = "<<totalCnt<<endl;
#endif
    recul(1);
    answer = totalSums - 1;
    
    return answer;
}
