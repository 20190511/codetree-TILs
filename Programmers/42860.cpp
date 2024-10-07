//1343~ 학교에서 못품
// 숫자 이동방향은 쉬운데 좌,우 방향은 크게 두 방향으로 잡았다.
// 좌로만, 우로만, 좌, 우 idx를 정하고 min(2*좌+우, 2*우+좌) 로 잡았다.
//https://school.programmers.co.kr/learn/courses/30/lessons/42860#
//중요 아이디어 tick 이동의 경우에는 단순계산으로 구할 수 없다.

#include <iostream>

#include <string>
#include <vector>

using namespace std;

int diffCnt(const char v) {
    return min(abs(v-'A'), abs('Z'-v+1));
}


int solution(string name) {
    int answer = 0;
    
    // 반대로만 탐색
    for (int i = name.length() ; i >= 0 ; i--) {
        if (name[i] == 'A') continue;
        answer = name.length() - i;
    }
    
    // 앞으로만 탐색
    int tmp = 0;
    for (int i = 1 ; i < name.length() ; i++) {
        if (name[i] == 'A') continue;
        tmp = i;
    }
    answer = min(answer, tmp);
    
    // 왔다갔다 탐색
    // 앞 먼저
    int nameSize = (int)name.length();
    
    int minIdx = 0;
    int maxIdx = nameSize - 1;
    
    int tmpMinVal = nameSize;
    for (int i = 1 ; i < nameSize ; i++) {
        if (name[i] != 'A') 
            minIdx = i;
        
        for (int j = i+1 ; j < nameSize ; j++) {
            if (name[j] == 'A') continue;
            
            maxIdx= j;
            break;
        }
        
        int backCnt = nameSize - maxIdx;
        tmpMinVal = min(2*minIdx+backCnt, 2*backCnt + minIdx);
        //cout<<"i="<<i<<", minIdx="<<minIdx<<", maxIdx="<<maxIdx<<endl;
        answer = min(answer, tmpMinVal);
    }
    
    cout<<answer<<endl;
    for (int i = 0 ; i < name.length() ; i++) {
        int tmpVal = diffCnt(name[i]);
        answer += tmpVal;
    }
    return answer;
}
