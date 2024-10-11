//0922 ~ 0942
//https://school.programmers.co.kr/learn/courses/30/lessons/42839
// 소수찾기
//atoi("001") 도 1로 인식해준다.
// 주안점 1. string('c') 가 안되는데 왜 안되는가?
// 해결: visit 방문 점 빼버리면서 전체 탐색하며 소수를 찾으면된다. 단, set으로 한 번 방문한 곳은 다시 방문하지 않도록 한다.
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

bool visit[8] = {0,};
set<int> findQ;
int answer = 0;

vector<char> wQ;
string target = "";

int unions() {
    int ret = 0;
    for (const char s : wQ) {
        ret *= 10;
        ret += s - '0';
    }
    
    return ret;
}

bool sosuCheck(int v) {
    if (v < 2) return false;
    
    for (int i = 2 ; i*i <= v ; i++) {
        if (!(v % i))
            return false;
    }
    return true;
}

void dfs(int depth) {
    if (depth == target.length()) 
        return;
    
    for (int i = 0 ; i < target.length() ; i++) {
        if (visit[i]) continue;
        wQ.push_back(target[i]);
        visit[i] = true;
        int ret = unions();
        
        if (findQ.find(ret) == findQ.end())  {
            //cout<<ret<<endl;
            findQ.insert(ret);
            if (sosuCheck(ret)) {
                answer++;
            }
        }
        dfs(depth+1);
        visit[i] = false;
        wQ.pop_back();
    }
    
}
int solution(string numbers) {
    target= numbers;
    dfs(0);
    return answer;
}
