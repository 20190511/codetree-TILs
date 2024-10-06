
//1524 : DP ~ 1600
/*
Lvl3
  N으로 표현하는 방법을 DP로 푼다.
근데 좀 쉽다.

F[1] = 5
F[2] = F[1] ? F[1] 로 표현한다. (?는 + / * + 가 된다.)
  + F[2] = NN 

F[3] = F[1]?F[2] | F[2]*F[1] 가 된다.
  + F[3] = NNN

F[4] = F[1]?F[3] | F[2]?F[2] | F[1]F[3] 
  + F[4] = NNNN 
....

즉 F[x] = Sigma(k=1~N-1) {F(k)*F(N-1-k)*4} + 1의 경우의수를 체크하면 된다.

최대 depth = 8
*/

#define DEBUG true
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <cmath>

using namespace std;

set<int> f[9];

int solution(int N, int number) {
    int answer = -1;
    
    f[1] = {N};
    
    int cnt = 1;
    
    if (N == number)
        return 1;
    
    bool breakFlag = false;
    for (int i = 2 ; i <= 8 ; i++) {
        int origin = N;
        for (int x = 1 ; x < i ; x++)
            origin += pow(10, x)*N;
        
        if (number == origin)
            return i;
        
        f[i].insert(origin);
        
#if DEBUGS
        cout<<"["<<i<<"] " <<origin<<endl;
#endif  
        
        for (int k = 1 ; k <= i-1 ; k++) {
            int k2 = i-k;
            for (auto it1 = f[k].begin() ; it1 != f[k].end() ; it1++) {
                for (auto it2 = f[k2].begin() ; it2 != f[k2].end(); it2++) {
#if DEBUGS
                    cout<<"["<<i<<"] " <<*it1<<"?"<<*it2<<endl;
#endif
                    int mul = (*it1) * (*it2);
                    f[i].insert(mul);
                    int plus = (*it1) + (*it2);
                    f[i].insert(plus);
                    int minus = (*it1) - (*it2);
                    f[i].insert(minus);
                    int div = -1;
                    if (*it2) {
                        div = (*it1) / (*it2);     
                        f[i].insert(div);
                    }
                    
                    if (mul == number || number == minus || number == plus || number == div) {
                        return i;
                    }
                }
            }
            
#if DEBUGS
            for (auto test = f[i].begin() ; test != f[i].end() ; test++) {
                cout<<*test<<" ";
            }
            cout<<endl;
#endif
        }
    }
    
    
    
    return answer;
}
