#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <functional>

using namespace std;

struct program {
    int num;
    unsigned long long s, p;

    program(int num, unsigned long long s, unsigned long long p) {
        this->num = num;
        this->s = s;
        this->p = p;
    }
};

bool compare(program p1, program p2) {
    if (p1.p > p2.p)
        return false;
    else return !((p1.p == p2.p) && (p1.s >= p2.s));
}

int main() {
    int n, m;
    priority_queue<program, vector<program>, function<bool(program, program)>> q(compare);
    priority_queue<pair<unsigned long long, int>, vector<pair<unsigned long long, int>>, greater<>> pqs;
    vector<pair<int, int>> result;
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    fin >> m >> n;
    for (int i = 0; i < n; i++) {
        unsigned long long sTime, pTime;
        fin >> sTime >> pTime;
        q.push(program(i + 1, sTime, pTime));
    }
    for (int i = 0; i < m; i++) {
        pqs.emplace(make_pair(0, i + 1));
    }
    unsigned long long time = 0, r = 0;
    while (!q.empty()) {
        program p = q.top();
        int num = pqs.top().second;
        if (time < pqs.top().first)
            time = pqs.top().first;
        time += p.s;
        q.pop();
        pqs.pop();
        pqs.emplace(make_pair(time + p.p, num));
        if (r < time + p.p)
            r = time + p.p;
        result.emplace_back(p.num, num);
    }
    fout << r << "\n";
    for (auto &i : result) {
        fout << i.first << " " << i.second << "\n";
    }
    return 0;
}