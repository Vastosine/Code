#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Milk {
    int p, a;
    bool operator<(const Milk &milk) const { return p < milk.p; }
};

int main() {
    int n, m;
    cin >> m >> n;
    vector<Milk> a(n);
    for (Milk &i : a) cin >> i.p >> i.a;
    std::sort(a.begin(), a.end());
    int ans = 0;
    for (const Milk &i : a) {
        if (i.a >= m) {
            ans += m * i.p;
            break;
        }
        ans += i.p * i.a;
        m -= i.a;
    }
    cout << ans;
}