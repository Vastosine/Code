#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::sort;

bool cmp(const string &x, const string &y) {
    return x.size() < y.size() || (x.size() == y.size() && x < y);
}

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (string &i : a) cin >> i;
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (cmp(a[m], a[i])) m = i;
    }
    cout << m + 1 << "\n" << a[m];
}