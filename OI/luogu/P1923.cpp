#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n), l, r;
    l.reserve(n), r.reserve(n);
    for (int &i : a) cin >> i;
    while (a.size() > 1) {
        l.clear(), r.clear();
        for (int i = 1; i < a.size(); i++) {
            if (a[i] > a[0]) r.push_back(a[i]);
            else l.push_back(a[i]);
        }
        if (k > l.size()) {
            k -= l.size() + 1;
            a = r;
        } else if (k < l.size()) a = l;
        else break;
    }
    cout << a[0];
}