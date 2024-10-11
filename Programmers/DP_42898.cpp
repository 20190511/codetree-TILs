//1123 ~ 1141
//https://school.programmers.co.kr/learn/courses/30/lessons/42898
// DP 경로 나눠주는거 1000000007 있는데 생각못함. <-- 문제 안읽고 푼 폐해
// 그리고 중간에 paddle로 막히더라도 DP에서는 자기자신만 0으로 취하고 break를 걸어서는 안된다.
// 아주 기본적인 DP
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int dp[101][101];
bool map[101][101];

int solution(int m, int n, vector<vector<int>> puddles) {
    dp[1][1] = 1;
    
    for (auto v : puddles) {
        map[v[1]][v[0]] = true;
    }
    
    for (int i = 2 ; i<= m ; i++) {
        if (map[1][i]) break;
        dp[1][i] = 1;
    }
    
    for (int i = 2 ; i<= n; i++) {
        if (map[i][1]) break;
        
        dp[i][1] = 1;
    }
    
    for (int i = 2 ; i <= n ; i++) {
        for (int j = 2 ; j <= m ; j++) {
            if (!map[i][j])
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % 1000000007;
        }
    }

    
    int answer = dp[n][m];
    return answer;
}
