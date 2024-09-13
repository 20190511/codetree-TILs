#include <iostream>
using namespace std;

int ans[4];
int main() {
    for (int i = 0 ; i< 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            int k;
            cin>>k;
            ans[i] += k;
        }
    }
    
    for (int i = 0 ; i < 4 ; i++) {
        cout<<ans[i]<<"\n";
    }
    // 여기에 코드를 작성해주세요.
    return 0;
}