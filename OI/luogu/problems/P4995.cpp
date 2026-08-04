#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

long long f(long long x) { return x * x; }

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    std::sort(a.begin(), a.end());
    long long ans = 0;
    for (int i[2] = {0, n - 1}, h = 0, k = 1; i[0] <= i[1]; ) {
        ans += f(a[i[k]] - h);
        h = a[i[k]];
        if (k) i[1]--;
        else i[0]++;
        k = !k;
    }
    cout << ans;
}