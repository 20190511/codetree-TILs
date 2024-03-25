// user.cpp

#define MAP_SIZE_MAX    350
#define INF     0x7FFFFFFF
#define DEBUG   true
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <deque>
#include <unordered_map>

using namespace std;

struct gateStatus{
    int x;
    int y;
    bool open;
};

// 맵 복사 방법 테크닉
int (*map)[MAP_SIZE_MAX], gateMap[MAP_SIZE_MAX][MAP_SIZE_MAX];
int hp, n, curGateNum = 0;
gateStatus gate[201];
int gateCost[201][201];
pair<int, int> mv[4] = {
    {0,1}, {0,-1}, {1,0}, {-1,0}
};
//////////
void printMap(int map[MAP_SIZE_MAX][MAP_SIZE_MAX]) {
    cout << "==========" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


// dp 로 최단경로를 구해야함 -> 한 번 구해서 각 Gate에서 Gate로 비용 구하면됨.
void bfs(int gateNum) {

    queue<pair<int, int>> q;
    q.push({ gate[gateNum].x, gate[gateNum].y});
    int dp[MAP_SIZE_MAX][MAP_SIZE_MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;

    dp[gate[gateNum].x][gate[gateNum].y] = 1;

    while (!q.empty()) {
        int sx = q.front().first, sy = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int dx = mv[i].first + sx, dy = mv[i].second + sy;
            if (dx < 0 || dx >= n || dy < 0 || dy >= n || map[dx][dy] || dp[dx][dy])  continue;
            
            dp[dx][dy] = dp[sx][sy] + 1;
            q.push({ dx,dy });
        }
    }

    // 게이트 최솟값 갱신
    for (int i = 1; i < gateNum; i++) {
        if (!gate[i].open) continue;
        int gx = gate[i].x, gy = gate[i].y;
        if (!dp[gx][gy])
            gateCost[i][gateNum] = gateCost[gateNum][i] = INF;
        else
            gateCost[i][gateNum] = gateCost[gateNum][i] = dp[gx][gy] - 1;
    }
}





void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
    map = mMap;
    n = N;
    memset(gateMap, 0, sizeof(gateMap));

    for (int i = 0; i < 201; i++) {
        for (int j = 0; j < 201; j++)
            gateCost[i][j] = INF;
    }
    hp = mMaxStamina;

    return;
}

void addGate(int mGateID, int mRow, int mCol)
{
    curGateNum = mGateID;
    gate[mGateID].x = mRow;
    gate[mGateID].y = mCol;
    gate[mGateID].open = true;
    gateMap[mRow][mCol] = mGateID;
    gateCost[mGateID][mGateID] = 0;
    bfs(mGateID);
    return;
}

void removeGate(int mGateID)
{
    gateStatus &xy = gate[mGateID];
    xy.open = false;
    gateMap[xy.x][xy.x] = 0;

    for (int i = 1; i <= curGateNum; i++) {
        gateCost[i][mGateID] = gateCost[mGateID][i] = INF;
    }
    return;
}

int dijkstra(int start, int end) {
    int v[201];
    for (int i = 0; i <= curGateNum; i++) v[i] = INF;
    v[start] = 0;
    priority_queue<pair<int, int>> q;
    q.push({ 0, start });
    while (!q.empty()) {
        int cost = -q.top().first, cur = q.top().second;
        q.pop();
        
        for (int i = 1; i <= curGateNum; i++) {
            if (!gate[i].open) continue;
            //hp보다 비용 많으면 거쳐 못감.
            if (gateCost[cur][i] == INF || gateCost[cur][i] > hp) continue;
            int dist = gateCost[cur][i] + cost;
            if (v[i] > dist) {
                v[i] = dist;
                q.push({ -dist, i });
            }
        }
    }

    return v[end] == INF ? -1 : v[end];
}

int getMinTime(int mStartGateID, int mEndGateID)
{
    gateStatus sxy = gate[mStartGateID], exy = gate[mEndGateID];
    //bfs({sxy.first, sxy.second});
    int ret = dijkstra(mStartGateID, mEndGateID);
    return ret ;
}
