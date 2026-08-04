#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Contest {
    int begin, end;
    bool operator<(const Contest &contest) const {
        return end < contest.end;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Contest> a(n);
    for (Contest &i : a) cin >> i.begin >> i.end;
    std::sort(a.begin(), a.end());
    int ans = 0, time = 0;
    for (const Contest &i : a) {
        if (i.begin >= time) {
            ans++;
            time = i.end;
        }
    }
    cout << ans;
}