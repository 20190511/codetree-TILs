#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INF 0x7fffffff // INT 최대값을 정의합니다
#define MAX_N 2000 // 코드트리 랜드의 최대 도시 개수입니다
#define MAX_ID 30005 // 여행상품 ID의 최대값입니다

using namespace std;

int N, M; // 도시의 개수 N과 간선의 개수 M 입니다
int A[MAX_N][MAX_N]; // 코드트리 랜드의 간선을 인접 행렬로 저장합니다
int D[MAX_N]; // Dijkstra 알고리즘을 통해 시작도시 S부터 각 도시까지의 최단경로를 저장합니다
bool isMade[MAX_ID]; // index에 해당하는 ID를 갖는 여행상품이 만들어진적 있는지 저장합니다.
bool isCancel[MAX_ID]; // index에 해당하는 ID를 갖는 여행상품이 취소되었는지 저장합니다
int S; // 여행 상품의 출발지 입니다

// 여행 상품을 정의합니다
struct Package {
    int id; // 고유 식별자 ID
    int revenue; // 매출
    int dest; // 도착도시
    int profit; // 여행사가 벌어들이는 수익

    struct Comparator {
        bool operator()(const Package& a, const Package& b) const {
            if (a.profit == b.profit) {
                return a.id > b.id; // profit이 같으면 id가 작은 순으로
            }
            return a.profit < b.profit; // profit이 클수록 우선 순위 높게
        }
    };
};

// 최적의 여행 상품을 빠르게 찾아내기 위해 priority queue를 사용합니다
priority_queue<Package, vector<Package>, Package::Comparator> pq;

// dijkstra 알고리즘을 통해 시작도시 S에서 각 도시로 가는 최단거리를 구합니다.
void dijkstra() {
    bool visit[MAX_N];
    for (int i=0;i<N;i++){
        D[i] = INF;
        visit[i] = false;
    }
    D[S] = 0;
    for (int i=0; i<N-1;i++){
        int v=0, minDist = INF;
        for (int j=0;j<N;j++) {
            if (!visit[j] && minDist > D[j]) {
                v = j;
                minDist = D[j];
            }
        }
        visit[v] = true;
        for (int j=0;j<N;j++){
            if (!visit[j] && D[v] != INF && A[v][j] != INF && D[j] > D[v] + A[v][j]) {
                D[j] = D[v] + A[v][j];
            }
        }
    }
}

// 코드트리랜드를 입력받고
// 주어진 코드트리 랜드를 인접행렬에 저장합니다
void buildLand() {
    cin >> N >> M;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            A[i][j] = INF;
        }
        // 출발지와 도착지가 같은 경우 거리는 0입니다
        A[i][i] = 0;
    }
    for (int i=0;i<M;i++){
        int u,v,w;
        cin >> u >> v >> w;
        // 양방향 간선에 대해 두 도시간 여러 간선이 주어질 수 있으므로 min 값으로 저장합니다
        A[u][v] = min(A[u][v], w);
        A[v][u] = min(A[v][u], w);
    }
}
// 여행 상품을 추가합니다
// 추가된 여행상품은 priority queue안에도 들어가야합니다.
void addPackage(int id, int revenue, int dest) {
    Package p;
    isMade[id] = true;
    p.id = id;
    p.revenue = revenue;
    p.dest = dest;
    p.profit = p.revenue - D[p.dest];

    pq.push(p);
}
// id에 해당하는 여행상품이 취소되었음을 기록합니다
void cancelPackage(int id) {
    // 만들어진적 있는 여행상품에 대해서만 취소할 수 있습니다.
    if (isMade[id]) isCancel[id] = true;
}
// 최적의 여행상품을 판매합니다
int sellPackage() {
    while(!pq.empty()) {
        Package p = pq.top();
        // 최적이라고 생각한 여행 상품이 판매 불가능 하다면 while문을 빠져나가 -1을 반환합니다.
        if (p.profit < 0)
            break;
        pq.pop();
        if (!isCancel[p.id])
            return p.id; // 해당 여행 상품이 취소되지 않았다면 정상 판매되므로 id를 반환합니다
    }
    return -1;
}
// 변경할 시작도시를 입력받고 변경됨에 따른 기존 여행상품 정보들을 수정합니다.
void changeStart() {
    cin >> S; // 변경된 시작도시를 반영합니다
    vector<Package> packages;
    dijkstra(); // 시작도시가 변경됨에 따라 각 도시로 가는 최단경로를 갱신합니다
    // 기존의 여행상품들을 packages에 기록하며 priority queue에서 삭제합니다
    while(!pq.empty()) {
        packages.push_back(pq.top());
        pq.pop();
    }
    for (Package p : packages) {
        // 기존의 여행 상품들의 profit을 수정하여 새로이 priority queue에 넣습니다
        addPackage(p.id, p.revenue, p.dest);
    }
}
int main() {
    int Q, id, revenue, dest;
    cin >> Q;
    // 총 Q개의 쿼리를 입력받습니다
    while (Q--) {
        int T;
        cin >> T;

        // 쿼리의 종류에 따라 필요한 함수들을 호출하여 처리합니다
        switch (T)
        {
        case 100:
            buildLand();
            dijkstra();
            break;
        case 200:
            cin >> id >> revenue >> dest;
            addPackage(id, revenue, dest);
            break;
        case 300:
            cin >> id;
            cancelPackage(id);
            break;
        case 400:
            cout << sellPackage() << endl;
            break;
        case 500:
            changeStart();
            break;
        }
    }

    return 0;
}