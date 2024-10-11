//0834 ~ 0846
//상태함수 --> 순서가 있어서 for문 도는 상태함수로 할 것. (완전탐색)
// 
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> dung;
bool v[10];
int answer = -1;
void dfs(int hp, int depth, int counts) {
    answer = max(answer, counts);
    if (depth == (int)dung.size()) {
        return;
    }    
    
    for (int i = 0 ; i < (int)dung.size() ; i++) {
        if (dung[i][0] > hp || v[i]) {
            continue;
        }
        v[i] = true;
        dfs(hp-dung[i][1], depth+1, counts+1);
        v[i] = false;
    }

}


int solution(int k, vector<vector<int>> dungeons) {
    dung = dungeons;
    dfs(k, 0, 0);
    
    return answer;
}
