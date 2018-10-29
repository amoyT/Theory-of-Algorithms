#pragma comment(linker, "/STACK:67108864")
#include <iostream>
#include <fstream>
#include <vector>

const int MAX = 100005;
std::vector<int> list[MAX];
std::vector<bool> used;

void dfs(int v) {
    used[v] = true;
    for (int son : list[v]) {
        if (!used[son]) {
            dfs(son);
        }
    }
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n, m, k = 0;
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        u--, v--;
        list[u].push_back(v);
        list[v].push_back(u);
    }
    used.reserve(MAX);
    for (int i = 0; i < n; i++){
        used[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
            k++;
        }
    }
    fout << k - 1;
    return 0;
}