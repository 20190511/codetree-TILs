//https://school.programmers.co.kr/learn/courses/30/lessons/12952?language=cpp#
//1915 ~ 2002 
/*
 nQueens 삽질 -> 뒤집어 씌워지는 오류가 발생할 수 있음.
  (즉, nQueens 의 값이 덮어씌워지면서 지워지는 오류를 방지해야함)
*/
#include <string>
#include <vector>
#include <iostream>
#define DEBUGS true
using namespace std;
int sums = 0;
int N;

int map[13][13];
int qMap[13][13];

void printQMap() {
    for (int i = 0 ;i < N ; i++) {
        for (int j = 0 ; j < N ; j++) {
            cout<<qMap[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"==============="<<endl;
}

void printMap() {
    for (int i = 0 ;i < N ; i++) {
        for (int j = 0 ; j < N ; j++) {
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"==============="<<endl;
}

void queenMove(int x, int y, bool check = true) {
    int l = y, m = y, r = y;
    
    for (int i = x ; i < N ; i++, l--, r++) {
        
        
        if (l >= 0) {
            if (check && !map[i][l]) {
                map[i][l] = check*(x+1);            
            }
            if (!check && map[i][l] == (x+1)) {
                map[i][l] = check*(x+1);            
            }
        }
        if (r < N) {
            if (check && !map[i][r]) {
                map[i][r] = check*(x+1);            
            }
            if (!check && map[i][r] == (x+1)) {
                map[i][r] = check*(x+1);            
            }
        }
            if (check && !map[i][m]) {
                map[i][m] = check*(x+1);            
            }
            if (!check && map[i][m] == (x+1)) {
                map[i][m] = check*(x+1);            
            }
    }
    
}

void recul(int n) {
    
    if (n == N) {
        sums++;
#if DEBUG
        printQMap();
#endif
        return;        
    }
    
    bool check = false;
    
    for (int i = 0 ; i < N ; i++) {
        if (!map[n][i]) {
            check = true;
            break;
        }
    }
    
    if (!check) {
        return;        
    }
    
    
    for (int i = 0 ; i < N ; i++) {
        if (map[n][i]) continue;
        
        // 퀸 이동
        queenMove(n,i, true);
        qMap[n][i] = 1;
        recul(n+1);
        qMap[n][i] = 0;
        queenMove(n,i, false);
    }
}



int solution(int n) {
    int answer = 0;
    N = n;
    
    recul(0);
    answer = sums;
    return answer;
}
