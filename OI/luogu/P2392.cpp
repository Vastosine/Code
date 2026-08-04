#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::istream;
using std::max;

template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) cin >> i; return in; }

int dfs(vector<int> &a, int mid, int x = 0, int sum = 0) {
    if (x == a.size()) return sum;
    int ans = dfs(a, mid, x + 1, sum);
    if (sum + a[x] <= mid) ans = max(ans, dfs(a, mid, x + 1, sum + a[x]));
    return ans;
}

int main() {
    int ans = 0;
    vector<int> ns(4);
    cin >> ns;
    for (int n : ns) {
        vector<int> a(n);
        cin >> a;
        int sum = 0;
        for (int i : a) sum += i;
        ans += sum - dfs(a, sum / 2);
    }
    cout << ans;
}