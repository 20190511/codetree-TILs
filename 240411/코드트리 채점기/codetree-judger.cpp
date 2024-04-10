#include <iostream>
#include <queue>
#include <set>
#include <map>

using namespace std;

#define INF 1987654321
#define MAX_N 50000
#define MAX_D 300

int q;
int n;

// 해당 도메인에서 해당 문제ID가 레디큐에 있는지 관리해줍니다.
set<int> is_in_readyq[MAX_D + 1];

// 현재 쉬고 있는 채점기들을 관리해줍니다.
priority_queue<int, vector<int>, greater<int> > rest_judger;

// 각 채점기들이 채점할 때, 도메인의 인덱스를 저장합니다.
int judging_domain[MAX_N + 1];

// 각 도메인별 start, gap, end(채점이 가능한 최소 시간)을 관리합니다.
int s[MAX_D + 1];
int g[MAX_D + 1];
int e[MAX_D + 1];

// 도메인을 관리하기 위해 cnt를 이용합니다.
// 도메인 문자열을 int로 변환해주는 map을 관리합니다.
map<string, int> domainToIdx;
int cnt;

// 현재 채점 대기 큐에 있는 task의 개수를 관리합니다.
int ans;

struct Url{
    int tme, id;
    int num;

    // 우선순위가 높은 url을 결정하기 위해 정렬함수를 만들어줍니다.
    bool operator <(const Url &b) const {
        if(id != b.id) return id > b.id;
        return tme > b.tme;
    }
};

// 각 도메인별로 priority queue를 만들어
// 우선순위가 가장 높은 url을 뽑아줍니다.
priority_queue<Url> url_pq[MAX_D + 1];

// 채점기를 준비합니다.
void Init() {
    string url;
    cin >> n >> url;

    for(int i = 1; i <= n; i++) rest_judger.push(i);

    // url에서 도메인 부분과 숫자 부분을 나누어줍니다.
    int idx = 0;
    for(int i = 0; i < url.length(); i++) {
        if(url[i] == '/') idx = i;
    }

    string domain = url.substr(0, idx);
    int num = stoi(url.substr(idx + 1));

    // 만약 도메인이 처음 나온 도메인이라면 domainToIdx에 갱신합니다.
    if(!domainToIdx[domain]) {
        cnt++;
        domainToIdx[domain] = cnt;
    }
    int domain_idx = domainToIdx[domain];

    // 도메인 번호에 맞는 레디큐에 숫자 부분을 넣어줍니다.
    is_in_readyq[domain_idx].insert(num);

    // 새로 들어온 url을 도메인에 맞춰 url_pq에 넣어줍니다.
    Url newUrl;
    newUrl.tme = 0;
    newUrl.id = 1;
    newUrl.num = num;
    url_pq[domain_idx].push(newUrl);

    // 채점 대기 큐에 값이 추가됐으므로 개수를 1 추가합니다.
    ans++;
}

// 새로운 url을 입력받아 레디큐에 추가해줍니다.
void NewUrl() {
    int tme, id;
    string url;
    cin >> tme >> id >> url;

    // url에서 도메인 부분과 숫자 부분을 나누어줍니다.
    int idx = 0;
    for(int i = 0; i < url.length(); i++) {
        if(url[i] == '/') idx = i;
    }

    string domain = url.substr(0, idx);
    int num = stoi(url.substr(idx + 1));

    // 만약 도메인이 처음 나온 도메인이라면 domainToIdx에 갱신합니다.
    if(!domainToIdx[domain]) {
        cnt++;
        domainToIdx[domain] = cnt;
    }

    int domain_idx = domainToIdx[domain];
    // 만약 숫자 부분이 이미 레디큐에 있으면 중복되므로 넘어갑니다.
    if(is_in_readyq[domain_idx].find(num) != is_in_readyq[domain_idx].end()) {
        return;
    }
    // 도메인 번호에 맞는 레디큐에 숫자 부분을 넣어줍니다.
    is_in_readyq[domain_idx].insert(num);

    // 새로 들어온 url을 도메인에 맞춰 url_pq에 넣어줍니다.
    Url newUrl;
    newUrl.tme = tme;
    newUrl.id = id;
    newUrl.num = num;
    url_pq[domain_idx].push(newUrl);

    // 채점 대기 큐에 값이 추가됐으므로 개수를 1 추가합니다.
    ans++;
}

// 다음 도메인을 찾아 assign합니다.
void Assign() {
    int tme;
    cin >> tme;

    // 쉬고 있는 채점기가 없다면 넘어갑니다.
    if(rest_judger.empty()) return;

    // 가장 우선순위가 높은 url을 찾습니다.
    int min_domain = 0;
    Url minUrl;
    minUrl.id = INF;

    for(int i = 1; i <= cnt; i++) {
        // 만약 현재 채점중이거나, 현재 시간에 이용할 수 없다면 넘어갑니다.
        if(e[i] > tme) continue;

        // 만약 i번 도메인에 해당하는 url이 존재한다면
        // 해당 도메인에서 가장 우선순위가 높은 url을 뽑고 갱신해줍니다.
        if(!url_pq[i].empty()) {
            Url curUrl = url_pq[i].top();

            if(minUrl < curUrl) {
                minUrl = curUrl;
                min_domain = i;
            }
        }
    }

    // 만약 가장 우선순위가 높은 url이 존재하면
    // 해당 도메인과 쉬고 있는 가장 낮은 번호의 채점기를 연결해줍니다.
    if(min_domain) {
        int judger_idx = rest_judger.top(); rest_judger.pop();

        // 해당 도메인의 가장 우선순위가 높은 url을 지웁니다.
        url_pq[min_domain].pop();

        // 도메인의 start, end를 갱신해줍니다.
        s[min_domain] = tme;
        e[min_domain] = INF;

        // judger_idx번 채점기가 채점하고 있는 도메인 번호를 갱신해줍니다.
        judging_domain[judger_idx] = min_domain;

        // 레디큐에서 해당 url의 숫자를 지워줍니다.
        is_in_readyq[min_domain].erase(is_in_readyq[min_domain].find(minUrl.num));

        // 채점 대기 큐에 값이 지워졌으므로 개수를 1 감소합니다.
        ans--;
    }
}

// 채점 하나를 마무리합니다.
void Finish() {
    int tme, id;
    cin >> tme >> id;

    // 만약 id번 채점기가 채점 중이 아닐 경우 스킵합니다.
    if(judging_domain[id] == 0) return;

    // id번 채점기를 마무리합니다.
    rest_judger.push(id);
    int domain_idx = judging_domain[id];
    judging_domain[id] = 0;

    // 해당 도메인의 gap, end 값을 갱신해줍니다.
    g[domain_idx] = tme - s[domain_idx];
    e[domain_idx] = s[domain_idx] + 3 * g[domain_idx];
}

// 현재 채점 대기 큐에 있는 url의 개수를 출력해줍니다.
void Check() {
    int tme;
    cin >> tme;

    cout << ans << "\n";
}

int main() {
    cin >> q;

    while(q--) {
        int query;
        cin >> query;

        if(query == 100) {
            // 채점기를 준비합니다.
            Init();
        }
        if(query == 200) {
            // 새로운 url을 입력받아 레디큐에 추가해줍니다.
            NewUrl();
        }
        if(query == 300) {
            // 다음 도메인을 찾아 assign합니다.
            Assign();
        }
        if(query == 400) {
            // 채점 하나를 마무리합니다.
            Finish();
        }
        if(query == 500) {
            // 현재 채점 대기 큐에 있는 url의 개수를 출력해줍니다.
            Check();
        }
    }
}