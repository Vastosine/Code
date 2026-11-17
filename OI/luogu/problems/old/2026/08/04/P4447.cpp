#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::min;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), vis(n);
    for (int &i : a) cin >> i;
    std::sort(a.begin(), a.end());
    int ans = n;
    struct Data {
        int x, n;
    };
    vector<Data> data;
    for (int i : a) {
        if (!data.empty() && data.back().x == i) data.back().n++;
        else data.push_back({i, 1}); 
    }
    int m = data.size();
    for (int i = 0; i < m; i++) {
        while (data[i].n) {
            int y = 1;
            data[i].n--;
            for (int j = i + 1; data[j].x == data[j - 1].x + 1 && data[j].n > data[j - 1].n; j++) {
                data[j].n--;
                y++;
            }
            ans = min(ans, y);
        }
    }
    cout << ans;
}