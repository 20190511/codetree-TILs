//1225 ~ 1300
//int -> string으로할 때는 to_string() 으로 해주면된다.
/*
 좋은 문제 정렬기준을 처음에 길이를 % 로 해준 값으로 잘 잡았으나

 완전히 배열이 동일할 때 어떻게 처리할 것인가에 대한 문제가 있음.

 --> ex
 101 10 은 동일한 비율이지만
 10110  이 10101 보다 큼
 왜그런가? 101 과 10 의 맨 마지막 글자의 크기를 마지막에 비교해주면된다.
 101의 마지막 1 이 10의 마지막 0 보다 크다는것을 고려해주라.!
*/
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const bool cmp(const int a, const int b) {
    string sa = to_string(a);
    string sb = to_string(b);

    int maxLen = max(sa.length(), sb.length());

    for (int i = 0; i < maxLen; i++) {
        if (sa[i % sa.length()] != sb[i % sb.length()]) {
            return sa[i % sa.length()] > sb[i % sb.length()];
        }
    }
    
    if (sa[sa.length()-1] != sb[sb.length()-1])
        return sa[sa.length()-1] > sb[sb.length()-1];
    
    return 0;
}

string solution(vector<int> numbers) {
    sort(numbers.begin(), numbers.end(), cmp);

    string answer = "";
    bool onlyZero = true;
    
    for (auto n : numbers) {
        if (n) onlyZero = false;
        //cout<<n<<" ";
        answer += to_string(n);
    }
    
    if (onlyZero) return "0";
    return answer;
}
