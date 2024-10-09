//1255 (프림?) ~ 1333

/*
  프림에서 노드 체크할 때 중요한 점은 
  해당 알고리즘에서는 트리가 단순히 모두 연결되었나가 아닌, 모든 부모의 공통조상이 같냐로 봐야한다.

  그렇기에 단순히 v[] 배열로 체크는 불가능하다.

  그래서 union-set 알고리즘을 응용해서 부모를 연결해야한다.

  Prim + UnionSet
  */

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <set>

using namespace std;
bool v[101];
int parent[101];
vector<int> nodeQ;

struct Node {
    int dist;
    int x;
    int y;
    
    const bool operator<  (const Node& b) const {
        return dist > b.dist;
    }
};


int find(int a) {
    if (a == parent[a])
        return a;
    
    int p = find(parent[a]);
    parent[a] = p;
    return p;
}

void unions(int p, int a) {
    int pp = find(p);
    int ap = find(a);
    
    parent[ap] = pp;
}


bool check(int n) {
    for (int i = 0 ; i < n ; i++) {
        if (find(i) != 0)
            return false;
    }
    return true;
}
int solution(int n, vector<vector<int>> costs) {
    priority_queue<Node> q;
    
    for (vector<int> e : costs) {
        int a, b, d;
        a = e[0], b = e[1], d=e[2];
        q.push({d,a,b});
        
        parent[a] = a;
        parent[b] = b;
    }
    int answer = 0;
    while (!q.empty() && !check(n)) {
        Node e = q.top();
        //cout<<e.dist<<" -> "<<e.x<<","<<e.y<<endl;
        q.pop();
        
        int xp = find(e.x);
        int yp = find(e.y);
        //cout<<xp<<", "<<yp<<endl;
        if (xp == yp)
            continue;
        
        int mins = min(xp, yp);
        int maxs = max(xp, yp);
        
        parent[maxs] = mins;
        
        answer += e.dist;
        
    }
    return answer;
}
