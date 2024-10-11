//0901 ~ 0920 
//얘도 dfs 순회 : 간단한 재귀함수 테크닉 (상태함수 테크닉 -> 사전 정렬)
#include <string>
#include <vector>
#include <iostream>
using namespace std;

string sent[5] = {"A", "E", "I", "O", "U"};
int answer = 0, cnt = 0;
vector<string> word;
string target = "";
bool check() {
    string unions = "";
    for (auto w : word) {
        unions += w;
    }
    if (target == unions) {
        answer = cnt;
        return true;        
    }
    return false;
}

string unions() {
    string u = "";
    for (auto w : word) {
        u += w;
    }
    return u;
}

bool dfs (int depth) {
   // cout<<unions()<<endl;
    
    if (depth == 5) {
        return false;
    }
    
    for (int i = 0 ; i < 5 ; i++) {
        cnt++;
        word.push_back(sent[i]);
        if (check()) {
            answer = cnt;
            return true;            
        }
        
        bool check = dfs(depth+1);
        if (check) {
            return true;            
        }
        
        word.pop_back();
    }
    return false;
}

int solution(string word) {
    target = word;
    dfs(0);
    return answer;
}
