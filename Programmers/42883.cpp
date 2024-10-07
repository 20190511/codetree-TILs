// 새롭게 배운 알고리즘
// Stack 이용 그리디
//Good Greedy 스택 으로 풀 수 있음.
/// 자신이 나올 때까지 Stack pop 하는 원리 (Greedy 문제를 좀 연습해둘 것)
//https://school.programmers.co.kr/learn/courses/30/lessons/42883


#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer;
    vector<char> stack;
    
    for (char s : number) {
        if (stack.empty())  {
            stack.push_back(s);
            continue;            
        }
        
        while (stack.back() < s && !stack.empty() && k) {
            stack.pop_back();
            k--;
        }
        
        stack.push_back(s);
        
    }
    
    while(k > 0) {
        stack.pop_back();
        k--;
    }
    
    for (auto s : stack)
            answer += s;
    return answer;
}
