//1110 ~ 1200
//https://school.programmers.co.kr/learn/courses/30/lessons/42747#
/*
 문제 이해를 잘못해서 삽질을 30분함
 h-index를 구할 때 h 기준으로 h이상 본 편이 h회이상, 그 외가 h회 이하 인용을 의미하는 거였음.
 h인용 기준 본인은 h보다 큰게 가 h이상 , h이하를 만족하는 h를 찾는건줄 알았는데
*/
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int counter[10001], dp[10001];
int solution(vector<int> citations) {
    int answer = (int)citations.size();
    
    int minVal = citations[0], maxVal = citations[0];
    for (auto s : citations) {
        counter[s]++;        
        minVal = min(s, minVal);
        maxVal = max(s, maxVal);
    }
    
    dp[maxVal] = counter[maxVal];
    
    
    for (int i = maxVal ; i >= 0 ; i--) {
        if (i < maxVal)
            dp[i] = dp[i+1] + counter[i];
        
        int r = (int)citations.size() - dp[i];
            
        if (r <= i && dp[i] >= i) {
            answer = i;
            break;
        }
        
        //if (dp[i] > r) break;
        
        //cout<<i<<" -> "<<dp[i]<<", "<<r<<endl;
    }
    cout<<answer<<endl;
    return answer;
}
