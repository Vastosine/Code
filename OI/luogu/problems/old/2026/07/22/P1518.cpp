#include <iostream>

using std::cin;
using std::cout;
using std::pair;

int a[10][11];
int vis[100][4][100][4], d[2];

typedef pair<int, int> Pair;

Pair p[2], D[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

Pair operator+(const Pair &p1, const Pair &p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

int map(const Pair &x) {
    return x.first * 10 + x.second;
}

int main() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            char c;
            cin >> c;
            a[i][j] = c == '*';
            if (c == 'F') p[0] = {i, j};
            if (c == 'C') p[1] = {i, j};
        }
    }
    for (int i = 1; ; i++) {
        for (int j = 0; j < 2; j++) {
            Pair z = p[j] + D[d[j]];
            if (a[z.first][z.second] || z.first < 0 || z.first >= 10 || z.second < 0 || z.second >= 10) (d[j] += 1) %= 4;
            else p[j] = z;
        }
        // cout << p[0].first << " " << p[0].second << " " << p[1].first << " " << p[1].second << "\n";
        if (vis[map(p[0])][d[0]][map(p[1])][d[1]]) {
            cout << 0;
            return 0;
        }
        vis[map(p[0])][d[0]][map(p[1])][d[1]] = 1;
        if (p[0] == p[1]) {
            cout << i;
            return 0;
        }
    }
}