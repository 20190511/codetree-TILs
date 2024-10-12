//Floid Ford 최단경로
//https://school.programmers.co.kr/learn/courses/30/lessons/72413
//Floyd 최단경로 알고리즘
/*


  Floyd = 모든 경로 최단거리 (+ 다익스트라 N번해도되긴함.)
    1. 시작 전 O(V) 만큼 모든 최단거리를 distMap에 표현해야함. + INF 초기화 (unisigned int로 초기화하면 편함)
      -> O(NNN) = 

    for (중간 노드 k (1 ~ N) ) {
      for (시작 노드 i (1 ~ N)) {
        for (끝 노드 j (1 ~ N)) {
          distMap[i][j] = min(distMap[i][j], distMap[i][k] + distMap[k][j]);
        }
      }
    }

  
  Bellman Ford :음수 간선 찾을 수 있는 최단거리
  -> for (노드 만큼 순회 (음수일시 +1 하고 갱신여부 체크) ) {
    for (간선 정보 vec) {
        s = vec[0], e =vec[1], dist=vec[2];
        if ( cur[s] != INF && (cur[e] > cur[s] + dist) {
          cur[e] = cur[s] + dist;
        }
    }
  }
*/
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#define INF 0xFFFFFFFF
using namespace std;

unsigned int distMap[301][301] = {INF, };

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    unsigned int answer = 0;
    memset(distMap, 0xFF, sizeof(distMap));
    for (int i = 1 ; i <= n ; i++){
        distMap[i][i] = 0;
    }
    
    for (vector<int> q : fares) {
        unsigned int s = q[0], e = q[1], dist = q[2];
        distMap[s][e] = distMap[e][s] = dist;
    }
    
    
    for (int k = 1 ; k <= n ; k++) {
        for (int i = 1 ; i <= n ;i++) {
            for (int j = 1 ; j <= n ; j++) {
                if (distMap[i][k] == INF || distMap[k][j] == INF) continue;
                
                distMap[i][j] = min(distMap[i][j], distMap[i][k] + distMap[k][j]);
            }
        }
    }
    
    /*
    for (int i = 1 ; i <= n ;i++) {
        for (int j = 1 ; j <= n ; j++) {
            cout<<distMap[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    
    //바로가는 최단거리 (따로가는)
    int sa = distMap[s][a], sb = distMap[s][b];
    answer = sa + sb;
    
    for (int i = 1 ; i <= n ; i++) {
        
        //공통 비용
        unsigned int common = distMap[s][i], ma = distMap[i][a], mb = distMap[i][b];
        if (common == INF || ma == INF || mb == INF) continue;
        
        answer = min(common + ma + mb, answer);
    }
    
    
    return (int)answer;
}
