//1155 ~ 1157
//스택도아님
//https://school.programmers.co.kr/learn/courses/30/lessons/12909
#include<string>
#include <vector>
#include <iostream>

using namespace std;

bool solution(string s)
{
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    int k = 0;
    for (const char c : s) {
        if (c == '(') {
            k++;
        }
        else if (c == ')') {
            if (k == 0)
                return false;
            k--;
        }
        
    }
    
    return k == 0 ? true : false;
}
