#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Apple {
    int x, y;
    bool operator<(const Apple &apple) const { return y < apple.y; }
};

int main() {
    int n, s, a, b;
    cin >> n >> s >> a >> b;
    vector<Apple> apple(n);
    for (Apple &i : apple) {
        cin >> i.x >> i.y;
    }
    std::sort(apple.begin(), apple.end());
    int ans = 0;
    for (const Apple &i : apple) {
        if (i.y > s) break;
        if (i.x > a + b) continue;
        ans++;
        s -= i.y;
    }
    cout << ans;
}