//Greedy 연습
// Greedy 문제에 보트 최대 2개임을 명심하라/
// 최대 2개이므로 left <-> right 끝 자라씩 비교하면 된다. 그리디하게 풀 수 있다.

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    int peopleCnt = (int)people.size();
    sort(people.begin(), people.end());


    int left = 0, right = (int)people.size() - 1;
    
    while (left <= right) {
        if (left == right) {
            answer++;
            break;
        }
        if (people[left] + people[right] <= limit) {
            left++;
        }
        right--;
        answer++;
    }

    return answer;
}
