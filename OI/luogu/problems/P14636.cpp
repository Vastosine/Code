#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const int M = 998224353;

typedef long long ll;

ll pow(ll x, ll n) {
    return n ? pow(x * x % M, n / 2) * (n % 2 ? x : 1) % M : 1;
}

ll solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n, 0);
    for (int &i : a) {
        cin >> i;
    }
    return pow(2, n);
}

int main() {
    int c, t;
    cin >> c >> t;
    while (t--) {
        cout << solve() << "\n";
    }
}