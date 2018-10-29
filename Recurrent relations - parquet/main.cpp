#include <cmath>
#include <iostream>
#include <fstream>
const int n = 1e7;
unsigned long long F[n + 1];
unsigned long long f[n + 1];

unsigned long long func(int n) {
    for (int i = 0; i < n; ++i) {
        F[i] = 0;
        f[i] = 0;
    }
    F[0] = 1;
    F[2] = 5;
    for (int i = 4; i <= n; i = i + 2) {
        f[i - 2] = ((F[i - 4] + 2 * f[i - 4]) % 1000000007);
        F[i] = ((3 * F[i - 2] + 2 * (F[i - 2] + 2 * f[i - 2])) % 1000000007);
    }
    return F[n];
}

unsigned long long int numberOfVariations(int n) {
    if (n % 2 != 0 || n == 0)
        return 0;
    else return func(n);
}

int main() {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    int n;
    fin >> n;
    fout << numberOfVariations(n);
    return 0;
}
