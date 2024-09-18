#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int n, S;
int vec[100001];
int main() {
    cin >> n >> S;
    for (int i = 0; i < n; i++)
        cin >> vec[i];

    int s = 0, e = 0, tmpSum = vec[e], minLen = 100001;
    while (s < n && e < n) {
        if (tmpSum < S) {
            e++;
            tmpSum += vec[e];
        }
        else {
            if (tmpSum >= S) {
                //cout << "e=" << e << ", s=" << s << endl;
                minLen = min(e - s + 1, minLen);
            }
            if (s == e) e++;
            tmpSum -= vec[s];
            s++;

        }
    }
    cout << minLen;
    // 여기에 코드를 작성해주세요.
    return 0;
}