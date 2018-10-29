#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    unsigned int n, m;
    fin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);
    vector<unsigned long long> d(n, ULLONG_MAX);
    set<pair<unsigned long long, int>> set;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        u--, v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    int s = 0;
    d[s] = 0;
    set.insert(make_pair(d[s], s));
    while (!set.empty()) {
        int v = set.begin()->second;
        set.erase(set.begin());
        for (int i = 0; i < graph[v].size(); i++) {
            int to = graph[v][i].first, l = graph[v][i].second;
            if (d[v] + l < d[to]) {
                set.erase(make_pair(d[to], to));
                d[to] = d[v] + l;
                set.insert(make_pair(d[to], to));
            }
        }
    }
    fout << d[n - 1];
    return 0;
}