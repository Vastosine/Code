#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

int main () {
    freopen("D:\\code\\IO\\in.in", "w", stdout);
    int l = 4, r = 100, m = 1000;
    cout << (m - 1) * (r - l + 1) << "\n";
    for (int j = l; j <= r; j++) {
        for (int i = 2; i <= m; i++) {
            cout << j << " " << i << "\n";
        }
    }
}