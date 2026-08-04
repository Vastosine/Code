#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::istream;

struct Item {
    int m, v;
    double w;
};

int main() {
    int n, t;
    cin >> n >> t;
    vector<Item> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].m >> a[i].v;
        a[i].w = a[i].v * 1.0 / a[i].m;
    }
    std::sort(a.begin(), a.end(), [](const Item &x, const Item &y) {
        return x.w > y.w;
    });
    double ans = 0;
    for (const Item &i : a) {
        if (i.m > t) {
            ans += t * i.w;
            break;
        }
        t -= i.m;
        ans += i.v;
    }
    cout << std::fixed << std::setprecision(2) << ans;
}