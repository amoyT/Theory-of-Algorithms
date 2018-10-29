#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

const int MAX = 100001;

std::vector<int> findLIS(std::vector<int> v, bool isReverse) {
    const int n = v.size();
    if (isReverse)
        std::reverse(v.begin(), v.end());
    std::vector<int> d;
    d.reserve(static_cast<unsigned int>(n + 1));
    int pos[n + 1];
    int prev[n];
    int l = 0;
    pos[0] = -1;
    d.push_back(-MAX);
    for (int i = 1; i < n + 1; i++) {
        d.push_back(MAX);
    }
    for (int i = 0; i < n; i++) {
        auto j = std::upper_bound(d.begin(), d.end(), v[i]) - d.begin();
        if (d[j - 1] < v[i] && v[i] < d[j]) {
            d[j] = v[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            l = std::max(l, j);
        }
    }
    std::vector<int> lis;
    int p = pos[l];
    while (p != -1) {
        lis.push_back(p + 1);
        p = prev[p];
    }
    std::reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    std::ifstream fin("report.in");
    std::ofstream fout("report.out");
    int n;
    fin >> n;
    std::vector<int> v;
    v.reserve(static_cast<unsigned int>(n + 1));
    for (int i = 0; i < n; i++) {
        int m;
        fin >> m;
        v.push_back(m);
    }
    int result = 1;
    std::vector<int> answer;
    std::vector<int> ansEnd;
    std::vector<int> res01 = findLIS(v, false);
    std::vector<int> res02 = findLIS(v, true);

    int minRes = std::min(res01.size(), res02.size());

    if (2 * minRes - 1 > result) {
        for (int j = 0; j < minRes; j++) {
            if (res01[j] < n + 1 - res02[j]) {
                if (j == minRes - 1) {
                    if (res01.size() > res02.size()) {
                        answer.push_back(n + 1 - res02[j]);
                    } else answer.push_back(res01[j]);
                } else {
                    answer.push_back(res01[j]);
                    ansEnd.push_back(n + 1 - res02[j]);
                }
            } else if (res01[j] == n + 1 - res02[j]) {
                answer.push_back(res01[j]);
                break;
            } else {
                if (v[res01[j] - 1] > v[n + 1 - res02[j] - 1]) {
                    if (res01[j] > *(answer.end() - 1) && res01[j] < *(ansEnd.end() - 1)) {
                        answer.push_back(res01[j]);
                    } else ansEnd.erase(ansEnd.end() - 1);
                } else {
                    if (n + 1 - res02[j] > *(answer.end() - 1) && n + 1 - res02[j] < *(ansEnd.end() - 1)) {
                        answer.push_back(n + 1 - res02[j]);
                    } else ansEnd.erase(ansEnd.end() - 1);
                }
            }
        }
        reverse(ansEnd.begin(), ansEnd.end());
        answer.insert(answer.end(), ansEnd.begin(), ansEnd.end());
    } else answer.push_back(1);
    fout << (answer.size() - 1) / 2 << "\n";
    for (int &it : answer) {
        fout << it << ' ';
    }
    return 0;
}