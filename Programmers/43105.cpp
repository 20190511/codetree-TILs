//1110 ~ 1120 
// 삼각형 DP (누적 값이 가장 큰 것은?) 쉬운 DP문제
//https://school.programmers.co.kr/learn/courses/30/lessons/43105
#include <string>
#include <vector>

using namespace std;

int dp[501][501];

int solution(vector<vector<int>> triangle) {
    dp[0][0] = triangle[0][0];
    int answer = 0;
    
    for (int i = 1 ; i < triangle.size() ; i++) {
        for (int j = 0 ; j < triangle[i].size() ; j++) {
            int maxV = -1;
            if (j < triangle[i-1].size())
                maxV = max(maxV, dp[i-1][j]);
            if (j-1 >= 0)
                maxV = max(maxV, dp[i-1][j-1]);
            dp[i][j] = maxV + triangle[i][j];
            answer = max(dp[i][j], answer);
        }
    }
    
    return answer;
}
