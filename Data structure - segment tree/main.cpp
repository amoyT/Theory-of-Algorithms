#include <iostream>
#include <fstream>

const int MAXN = 100001, MAX = static_cast<const int>(1e12);
long long tSum[MAXN << 2] = {}, tMin[MAXN << 2] = {}, tMax[MAXN << 2] = {}, tAdd[MAXN << 2] = {};
int n;

void push(int v, int tl, int tr) {
    int tm = (tl + tr) / 2;
    int fs = v << 1;
    int ss = (v << 1) + 1;
    tSum[fs] += tAdd[v] * (tm - tl + 1);
    tSum[ss] += tAdd[v] * (tr - tm);
    tMin[fs] += tAdd[v];
    tMin[ss] += tAdd[v];
    tMax[fs] += tAdd[v];
    tMax[ss] += tAdd[v];
    tAdd[fs] += tAdd[v];
    tAdd[ss] += tAdd[v];
    tAdd[v] = 0;
}

long long sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return tSum[v];
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    return (sum((v << 1), tl, tm, l, std::min(r, tm)) + sum((v << 1) + 1, tm + 1, tr, std::max(l, tm + 1), r));
}

long long sum(int l, int r) {
    return sum(1, 0, n - 1, l, r);
}

long long min(int v, int tl, int tr, int l, int r) {
    if (r < tl || l > tr)
        return MAX;
    if (l <= tl && tr <= r)
        return tMin[v];
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    int fs = v << 1;
    int ss = (v << 1) + 1;
    long long fsm = min(fs, tl, tm, l, std::min(tm, r));
    long long ssm = min(ss, tm + 1, tr, std::max(tm + 1, l), r);
    long long kek = std::min(fsm, ssm);
    return kek;
}

long long min(int l, int r) {
    return min(1, 0, n - 1, l, r);
}

long long max(int v, int tl, int tr, int l, int r) {
    if (r < tl || tr < l)
        return -MAX;
    if (l <= tl && tr <= r)
        return tMax[v];
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    int fs = v << 1;
    int ss = (v << 1) + 1;
    long long fsm = max(fs, tl, tm, l, std::min(tm, r));
    long long ssm = max(ss, tm + 1, tr, std::max(tm + 1, l), r);
    return std::max(fsm, ssm);
}

long long max(int l, int r) {
    return max(1, 0, n - 1, l, r);
}

void set(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        tSum[v] = val;
        tMin[v] = val;
        tMax[v] = val;
    } else {
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        int fs = v << 1;
        int ss = (v << 1) + 1;
        if (pos <= tm)
            set(fs, tl, tm, pos, val);
        else set(ss, tm + 1, tr, pos, val);
        tSum[v] = tSum[fs] + tSum[ss];
        tMin[v] = std::min(tMin[fs], tMin[ss]);
        tMax[v] = std::max(tMax[fs], tMax[ss]);
    }
}

void set(int pos, int value) {
    set(1, 0, n - 1, pos, value);
}

void add(int v, int tl, int tr, int l, int r, int val) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        tSum[v] += val * (tr - tl + 1);
        tMin[v] += val;
        tMax[v] += val;
        tAdd[v] += val;
    } else {
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        int fs = v << 1;
        int ss = (v << 1) + 1;
        add(v * 2, tl, tm, l, std::min(r, tm), val);
        add(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val);
        tSum[v] = tSum[fs] + tSum[ss];
        tMin[v] = std::min(tMin[fs], tMin[ss]);
        tMax[v] = std::max(tMax[fs], tMax[ss]);
        tAdd[v] = 0;
    }
}

void add(int l, int r, int val) {
    add(1, 0, n - 1, l, r, val);
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    fin >> n;
    int l = 1;
    while (l != 0) {
        int v, a, b;
        fin >> l;
        switch (l) {
            case 1:
                int ind;
                fin >> ind >> v;
                set(1, 0, n - 1, ind, v);
                break;
            case 2:
                fin >> a >> b >> v;
                add(1, 0, n - 1, a, b, v);
                break;
            case 3:
                fin >> a >> b;
                fout << sum(1, 0, n - 1, a, b) << "\n";
                break;
            case 4:
                fin >> a >> b;
                fout << min(1, 0, n - 1, a, b) << "\n";
                break;
            case 5:
                fin >> a >> b;
                fout << max(1, 0, n - 1, a, b) << "\n";
                break;
            default:
                break;
        }
    }
    return 0;
}