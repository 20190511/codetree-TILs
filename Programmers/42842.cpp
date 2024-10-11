//완전탐색1
//https://school.programmers.co.kr/learn/courses/30/lessons/42842
// yellow 구해서 약수 구하는 알고리즘

#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    int maxNum = yellow;
    for (int i = 1 ; i <= maxNum ; i++) {
        if (yellow % i) continue;
        
        maxNum = yellow / i;
        
        int y = i + 2;
        int x = maxNum + 2;
        
        //cout<<"x="<<x<<", y="<<y<<" -> "<< ((x-1)*2 + (y-1)*2) <<endl;
        if ( ((x-1)*2 + (y-1)*2)  == brown) {
            answer.push_back(x);
            answer.push_back(y);
            return answer;
        }
            
        if (i == maxNum) break;
    }
    return answer;
}
