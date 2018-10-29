#pragma comment(linker, "/STACK:67108864")

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>

using namespace std;

unsigned int n, m, a, b;
const int MAXN = 10001;
vector<pair<int, int>> graph[MAXN];
int pred[2][MAXN];
int count[MAXN];
int path[2][MAXN];
vector<long long> d[2];

long long dijkstra() {
    int s = a - 1;
    for (auto &i : d)
        i.reserve(n);
    for (int i = 0; i < n; i++) {
        count[i] = 0;
        path[0][i] = pred[1][i] = 0;
        d[0][i] = d[1][i] = LLONG_MAX;
        pred[0][i] = pred[1][i] = -1;
    }
    d[0][s] = 0;
    priority_queue<pair<long long, pair<int, int>>> q;
    q.push(make_pair((long long) 0, make_pair(-1, s)));
    while (!q.empty() && d[1][b - 1] == LLONG_MAX) {
        int vFrom = q.top().second.first,
                v = q.top().second.second;
        long long int dThis = -q.top().first;
        q.pop();
        if (count[v] == 2)
            continue;
        d[count[v]][v] = dThis;
        pred[count[v]][v] = vFrom;
        for (int j = 0; j < graph[v].size(); j++) {
            int to = graph[v][j].first,
                    len = graph[v][j].second,
                    from = v;
            if (count[to] != 2) {
                if (d[count[from]][from] + len < d[count[to]][to]) {
                    int pTo = path[count[to]][to];
                    int pFrom = path[count[from]][from];
                    path[count[to]][to] = path[count[from]][from] + 1;
                    q.push(make_pair(-1 * (d[count[from]][from] + len), make_pair(from, to)));
                }
            }
        }
        count[v]++;
    }
    return d[1][b - 1];
}

int main() {
    ifstream fin("input.in");
    ofstream fout("output.out");
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        u--, v--;
        graph[u].emplace_back(v, w);
    }
    fin >> a >> b;
    long long result = dijkstra();
    fout << result << "\n";
    vector<int> r;
    int prev = b - 1;
    r.push_back(b);
    count[prev]--;
    prev = pred[count[prev]][prev];
    for (auto &i : graph[prev]) {
        if (i.first == b - 1) {
            result = result - i.second;
            break;
        }
    }
    while (result > 0) {
        int temp = prev;
        r.push_back(prev + 1);
        if (d[0][prev] == result)
            prev = pred[0][prev];
        else prev = pred[1][prev];
        //result = result - matrix[prev][temp];
        for (auto &i : graph[prev]) {
            if (i.first == temp) {
                result = result - i.second;
                break;
            }
        }
    }
    r.push_back(a);
    for (int i = r.size(); i > 0; i--) {
        fout << r[i - 1] << " ";
    }
    return 0;
}