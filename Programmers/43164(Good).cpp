//0908 ~ 0949 Good
// https://school.programmers.co.kr/learn/courses/30/lessons/43164#

//해시 & BFS
// 재귀함수는 잘 짰는데 return 마지막에 안 넣어서 false로 안 넣으면 자동으로 true가 리턴되서 오류가 난다. 명심하라

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N = 0;
struct node {
    string s;
    string e;
    bool v;
};

const bool cmp (const node& a, const node &b) {
        if (a.s == b.s)
            return a.e < b.e;
        return a.s < b.s;
}
node tck[10001];


vector<string> retVec;

int totalCnt = 0;
bool dfs(int depth=0) {
    if (depth == N) {
        if ((int)retVec.size() == N+1) {
            return true;            
        }
        else
            return false;
    }
    
    for (int i = 0 ; i < N ; i++) {
        string s = tck[i].s;
        if (tck[i].v || s != retVec.back()) continue;
        
        
        //cout<<"back : "<<retVec.back()<<", start : "<<tck[i].e<<endl;
        totalCnt++;
        tck[i].v = true;
        retVec.push_back(tck[i].e);
        bool check = dfs(depth+1);
        if (check) return true;
        retVec.pop_back();
        tck[i].v = false;
        totalCnt--;
        
        
    }
    
    return false;
    
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
    for (int i = 0 ; i < tickets.size() ; i++) {
        tck[i].s = tickets[i][0];
        tck[i].e = tickets[i][1];
        tck[i].v = false;
    }
    
    sort(tck, tck + tickets.size(), cmp);
    N = (int)tickets.size();
    
    /*
    for (int i = 0 ; i < tickets.size() ; i++) {
        cout<<tck[i].s<<", "<<tck[i].e<<endl;
    }
    */
    
    
    retVec.push_back("ICN");
    dfs(0);
    
    return retVec;
}
