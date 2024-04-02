//1020 ~ 1143 <-- 시간초과가 아니라 메모리초과
// 메모리 초과에 대한 실수 주의
#define _CRT_SECURE_NO_WARNINGS
#define DEBUGS  false
#define DEBUG   false
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;
struct man {
    int x;
    int y;
    int d;
    int power;
    int gun;
};

priority_queue<int> map[20][20];
int man_map[20][20];
int N, M, K;
int score[31];
man mans[31];


pair<int, int> mv[4] = {
    {-1,0}, {0,1}, {1,0}, {0,-1}
};

void printMap() {
    cout << "======" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (man_map[i][j]) cout << man_map[i][j]<<" ";

            cout << "{";
            vector<int> q;
            while (!map[i][j].empty()) {
                cout << map[i][j].top() << " ";
                q.push_back(map[i][j].top());
                map[i][j].pop();
            }
            cout<<"} ";

            while (!q.empty()) {
                map[i][j].push(q.back());
                q.pop_back();
            }
        }
        cout << endl;
    }
}
void printManStat() {
    for (int i = 1; i <= M; i++) {
        cout << "x = " << mans[i].x << ", y = " << mans[i].y << ", power = " << mans[i].power << ", guns = " << mans[i].gun << ", score = " << score[i] << endl;
    }
}

void dirChanger(int mNum) {
    man& m = mans[mNum];
    if (m.d == 0) m.d = 2;
    else if (m.d == 1) m.d = 3;
    else if (m.d == 2) m.d = 0;
    else if (m.d == 3) m.d = 1;
}

void gunSwap(int dx, int dy, man& cur) {
    if (!map[dx][dy].empty()) {
        int mapGun = map[dx][dy].top();
        int playerGun = cur.gun;
        if (mapGun > playerGun) {
            cur.gun = mapGun;
            map[dx][dy].pop();
            if (playerGun)
                map[dx][dy].push(playerGun);
        }
    }
}
void move(int m) {
    man& cur = mans[m];
    
    int cx = cur.x, cy = cur.y;

    int dx = cx + mv[cur.d].first, dy = cy + mv[cur.d].second;
    if (dx < 0 || dx >= N || dy < 0 || dy >= N) {
        dirChanger(m);
        dx = cx + mv[cur.d].first, dy = cy + mv[cur.d].second;
    }
    mans[m].x = dx, mans[m].y = dy;
    man_map[cx][cy] = 0;

#if DEBUG
    cout << "move pos : " << dx << "," << dy << endl;
#endif

    // map 확인
    if (man_map[dx][dy]) {
        // 사람 O
        int manNum = man_map[dx][dy];
        man& enemy = mans[manNum];
        
        int myP = cur.gun + cur.power;
        int enemyP = enemy.gun + enemy.power;

        int winMan = -1, loseMan = -1;
        if (myP == enemyP) {
            if (cur.power > enemy.power) 
                winMan = m, loseMan = manNum;
            else
                winMan = manNum, loseMan = m;
        }
        else {
            if (myP > enemyP)
                winMan = m, loseMan = manNum;
            else
                winMan = manNum, loseMan = m;
        }

#if DEBUG
        cout << "winner = "<< winMan << ", " << "loser = "<<loseMan << endl;

#endif // DEBUG

        man& loser = mans[loseMan], &winner = mans[winMan];
        int sc = myP < enemyP ? enemyP - myP : myP - enemyP;
        score[winMan] += sc;
        //loser 총 버림
        int loserGun = loser.gun;

        if (loserGun) {
            map[dx][dy].push(loserGun);
        }
        loser.gun = 0;

        int lx = loser.x, ly = loser.y;
        int ldx = lx + mv[loser.d].first, ldy = ly + mv[loser.d].second; 
        
        int cnt = 1;
        while (ldx < 0 || ldx >= N || ldy < 0 || ldy >= N || man_map[ldx][ldy]) {
            loser.d = (loser.d + 1) % 4;
            ldx = lx + mv[loser.d].first, ldy = ly + mv[loser.d].second;
#if DEBUG
            if (cnt > 4) {
                cout << "impossible loop\n";
                exit(1);
            }
#endif
            //무한루프??
        }
        loser.x = ldx, loser.y = ldy;
        man_map[ldx][ldy] = loseMan;
        gunSwap(ldx, ldy, loser);

        //이긴사람
        man_map[dx][dy] = winMan;
        gunSwap(dx, dy, winner);
    }
    else {
        // 사람X
        man_map[dx][dy] = m;
        gunSwap(dx, dy, cur);
    }
}


void run() {
    for (int i = 0; i < K; i++) {
#if DEBUG
        cout << "++++++ " << i << " ++++++" << endl;
#endif
        // 차례대로 man 이동
        for (int m = 1; m <= M; m++) {
            move(m);
#if DEBUG
            cout << "man: " << m << " move.." << endl;
            printMap();
            printManStat();
#endif

        }
    }
    for (int i = 1; i <= M; i++) {
        cout << score[i] << " ";
    }
}

int main() {
#if DEBUGS
    freopen("input.txt", "r", stdin);
    clock_t start, end;
    double result;
    start = clock();
#endif
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int gn;
            cin >> gn;
            if (gn) map[i][j].push(gn);
        }
    }

    for (int i = 1; i <= M; i++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        mans[i].x = x - 1;
        mans[i].y = y - 1;
        mans[i].d = d;
        mans[i].power = s;
        man_map[x - 1][y - 1] = i;
    }
#if DEBUG
    printMap();
#endif
    run();
#if DEBUGS
    end = clock();
    cout << "time :: " << end - start << endl;

#endif // 

    return 0;
}