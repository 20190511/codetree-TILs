//1100 ~ 1110
//https://school.programmers.co.kr/learn/courses/30/lessons/42897
// 좋은 DP 문제
// 원으로 둘러져있는 집의 인접한 집은 털 수 없다.
// 첫 번째 집을 무조건 턴다. -> for문탐색으로 N-1 번까지 하면서 max(dp[i-2] + item , dp[i-1]) 해주면됨
// 마지막 집을 무조건 턴다. -> for문 탐색으로 N-1번까지 하면서 max(dp[i-2] + item, dp[i-1]) 해주면됨.

#include <string>
#include <vector>

using namespace std;

int dp[2][1000000]; //true, false

int solution(vector<int> money) {
    
    int N = (int)money.size();
    
    // 첫 집 무조건 털기
    dp[0][0] = money[0];
    dp[0][1] = max(money[0], money[1]);
    
    // 마지막 집 무조건털기 -> 첫 번째 집을 털면안됨..
    dp[1][1] = money[1];
    
    int answer = 0;
    for (int i = 2 ; i < N ; i++) {
        dp[1][i] = max(dp[1][i-1], dp[1][i-2] + money[i]);
        answer = max(dp[1][i], answer);
        if (i < N-1) {
            dp[0][i] = max(dp[0][i-1], dp[0][i-2] + money[i]);
            answer = max(dp[0][i], answer);
        }
    }    
    
    return answer;
}
