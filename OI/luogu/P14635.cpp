#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

typedef long long ll;

int n;
ll m, ans;
struct Data {
    int odd, even, sum;
    bool operator<(const Data &data) const {
        return sum < data.sum || ((sum == data.sum) && (odd < data.sum));
    }
};
vector<Data> a;

int main() {
    cin >> n >> m;
    a.assign(n, {});
    for (Data &i : a) {
        cin >> i.odd >> i.even;
        i.sum = i.odd + i.even;
    }
    sort(a.begin(), a.end());
    Data min_sum = a[0];
    sort(a.begin(), a.end(), [](const Data &x, const Data &y) {
        return x.odd < y.odd;
    });
    int i;
    for (i = 0; i < n; i++) {
        if (a[i].odd * 2 >= min_sum.odd + min_sum.even || a[i].odd > m) break;
        m -= a[i].odd;
        ans++;
    }
    ans += m / min_sum.sum * 2;
    m %= min_sum.sum;
    for (; i < n; i++) {
        if (a[i].odd > m) break;
        m -= a[i].odd;
        ans++;
    }
    if (a[i - 1].odd + m >= min_sum.sum) ans++;
    cout << ans;
}