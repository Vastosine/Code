#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;

auto bruteSolve(const string &input) {
    int m, d, l, r;
    sscanf(input.c_str(), "%d%d%d%d", &m, &d, &l, &r);
    int n = (int) to_string(l).length();
    auto check = [&] (const string &s) {
        ll x = 0;
        for (int i = 0; i < n; i++) {
            if ((i & 1) ^ (s[i] == '0' + d)) return false;
            x = (x * 10 + s[i] - '0') % m;
        }
        return !x;
    };
    ll ans = 0;
    for (int i = l; i <= r; i++) {
        bool k = check(to_string(i));
        ans += k;
        if (k) cout << i << "\n";
    }
    return ans;
}

int main() {
    string s, t;
    while (cin >> t) s += t + " ";
    bruteSolve(s);
}