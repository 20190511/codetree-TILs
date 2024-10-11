//https://school.programmers.co.kr/learn/courses/30/lessons/42576
//단순 해시
//1144 ~ 1148
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map<string, int> table;


string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    for (string p: participant) {
        int cnt = table[p];
        if(!cnt) {
            table[p] = 1;
        }
        else
            table[p]++;
    }
    
    for (string c : completion) {
        int cnt = table[c];
        if (cnt) {
            table[c]--;
        }
    }
    
    for (auto it = table.begin(); it != table.end() ;it++) {
        if (it->second)
            return it->first;
    }
    return answer;
}
