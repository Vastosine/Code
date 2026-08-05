// Problem : $name$ $url$
// Time    : $data$ $time$

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    $CURSOR_PLACEHOLDER
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}