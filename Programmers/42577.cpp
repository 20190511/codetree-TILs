// 1223 ~ 1231
// 해시를 이용한 전화번호
//https://school.programmers.co.kr/learn/courses/30/lessons/42577?language=cpp

#include <string>
#include <vector>
#include <map>


using namespace std;

bool solution(vector<string> phone_book) {
    map<string, int> hashQ;
    
    for (auto s : phone_book) {
        if (hashQ[s]) return false;
        
        string pre = "";
        for (int i = 0 ; i < (int)s.length()-1 ; i++) {
            pre += s[i];
            hashQ[pre] = 1;
        }
    }
    
    for (auto s : phone_book) {
        if (hashQ[s]) return false;
    }
    bool answer = true;
    return answer;
}
