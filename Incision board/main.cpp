#pragma comment(linker, "/STACK:67108864")

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
int k;
set<string> maps;

void also(string value) {
    string val1, val2, val3;
    double x1, x2, x3, y1, y2, y3;
    x1 = x2 = x3 = y1 = y2 = y3 = 0;
    for (int i = 0; i < value.size(); i++) {
        //value1
        if (value[i] == 'U') {
            val1 += 'D';
            x1 += (1 / 2);
        } else if (value[i] == 'D') {
            val1 += 'U';
            x1 -= 1 / 2;
        } else val1 += value[i];

        //value2 & value3
        if (val1[i] == 'D') {
            val2 += 'L';
            val3 += 'R';
            y1 += (1 / 2);
            x2 += 1 / 2;
            x3 -= 1 / 2;
        } else if (val1[i] == 'U') {
            val2 += 'R';
            val3 += 'L';
            y1 -= 1 / 2;
            x2 -= 1 / 2;
            x3 += 1 / 2;
        } else if (val1[i] == 'L') {
            val2 += 'U';
            val3 += 'U';
            x1 += 1 / 2;
            y2 -= 1 / 2;
            y3 -= 1 / 2;
        } else if (val1[i] == 'R') {
            val2 += 'D';
            val3 += 'D';
            x1 -= 1 / 2;
            y2 += 1 / 2;
            y3 += 1 / 2;
        }
    }
    maps.insert(val1);
    maps.insert(val2);
    maps.insert(val3);
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    fin >> k;
    queue<pair<pair<int, int>, string>> q;
    set<string> result;
    bool used[2 * k + 1][2 * k + 1];
    for (int i = 0; i < 2 * k + 1; i++)
        for (int j = 0; j < 2 * k + 1; j++)
            used[i][j] = false;
    used[k][k] = true;
    q.push(make_pair(make_pair(k, k - 1), "D"));
    q.push(make_pair(make_pair(k - 1, k), "R"));
    while (!q.empty()) {
        int x = q.front().first.first,
                y = q.front().first.second;
        string value = q.front().second;
        q.pop();
        if (used[x][y])
            continue;
        if (x == 0 || y == 0 || x == 2 * k || y == 2 * k) {
            string temp;
            if ((x == 0 && (y < 2 * k)) || (y == 0 && (x < 2 * k))) {
                temp = value;
                x = x - k;
                y = k - y;
            } else {
                for (int i = 0; i < value.size(); i++) {
                    if (value[i] == 'U')
                        temp += "D";
                    else if (value[i] == 'D')
                        temp += "U";
                    else if (value[i] == 'R')
                        temp += "L";
                    else temp += "R";
                }
                value = temp;
                x = k - x;
                y = y - k;
            }
            reverse(temp.begin(), temp.end());
            maps.insert(temp + value);
            also(temp + value);
            continue;
        }
        q.push(make_pair(make_pair(x, y - 1), value + "D"));
        q.push(make_pair(make_pair(x, y + 1), value + "U"));
        q.push(make_pair(make_pair(x - 1, y), value + "R"));
        q.push(make_pair(make_pair(x + 1, y), value + "L"));
        used[x][y] = true;
    }

    for (auto it = maps.begin(); it != maps.end(); it++) {
        int x0 = -1 * count((*it).begin(), (*it).end(), 'R') / 2 +
                 count((*it).begin(), (*it).end(), 'L') / 2;
        int y0 = count((*it).begin(), (*it).end(), 'D') / 2 -
                 count((*it).begin(), (*it).end(), 'U') / 2;
        if ((x0 == -k && y0 > -k) || (y0 == k && x0 > -k))
            result.insert((*it));
        else {
            string temp;
            for (int i = 0; i < (*it).size(); i++) {
                if ((*it)[i] == 'U')
                    temp += "D";
                else if ((*it)[i] == 'D')
                    temp += "U";
                else if ((*it)[i] == 'R')
                    temp += "L";
                else temp += "R";
            }
            result.insert(temp);
        }
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        int x0 = -1 * count((*it).begin(), (*it).end(), 'R') / 2 +
                 count((*it).begin(), (*it).end(), 'L') / 2;
        int y0 = count((*it).begin(), (*it).end(), 'D') / 2 -
                 count((*it).begin(), (*it).end(), 'U') / 2;
        if ((x0 == -k && y0 > -k) || (y0 == k && x0 > -k))
            fout << x0 << " " << y0 << " " << (*it) << "\n";
    }
    return 0;
}