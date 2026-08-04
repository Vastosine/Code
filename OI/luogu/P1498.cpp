#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using vs = vector<string>;

const vs BASE = {" /\\ ", "/__\\"};

void copy(vs &x, const vs &y, int dx, int dy, int lx, int ly) {
    for (int i = 0; i < lx; i++) {
        for (int j = 0; j < ly; j++) {
            x[i + dx][j + dy] = y[i][j];
        }
    }
}

int main() {
    int n;
    cin >> n;
    vs a = BASE, b;
    int t = 2;
    for (int i = 1; i < n; i++) {
        b.assign(t * 2, string(t * 4, ' '));
        copy(b, a, t, 0, t, t * 2);
        copy(b, a, t, t * 2, t, t * 2);
        copy(b, a, 0, t, t, t * 2);
        a = b;
    }
    for (const string &i : a) cout << i << "\n";
}