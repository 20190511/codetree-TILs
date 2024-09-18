#include <iostream>
using namespace std;

int n,S;
int vec[100001];
int main() {
    cin>>n>>S;
    for (int i = 0 ; i < n ; i++)
        cin>>vec[i];

    int s=0, e=0, tmpSum = 0, minLen = 100001;
    while (s < n) {
        if (tmpSum < S) {
            tmpSum += vec[e];
            e++;
        } else {
            if (tmpSum >= S) {
                minLen = min(e-s, minLen);
            }
            if (s == e) e++;
            tmpSum -= vec[s];
            s++;
                        
        }
    }
    cout<<minLen;
    // 여기에 코드를 작성해주세요.
    return 0;
}