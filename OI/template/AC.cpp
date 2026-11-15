#include <iostream>
#include <string>
#include <vector>
using namespace std;

using vi = vector<int>;

int lowercase(char c) { return c - 'a'; }
int uppercase(char c) { return c - 'A'; }

template<typename MAP>
struct AC {
    vector<vi> e;
    vi fail, cnt;
    MAP map;
    int mapSize;
    static constexpr int ROOT = 0;
    
    AC(const vector<string> &strs = {}, MAP map = lowercase, int mapSize = 26) : map(map), mapSize(mapSize) {
        newNode();
        for (auto &s : strs) insert(s);
    }

    int newNode() { return e.push_back(vi(mapSize)), cnt.push_back(0), (int) e.size() - 1; }

    void insert(const string &s) {
        int cur = ROOT;
        for (char c : s) {
            int i = map(c);
            if (!e[cur][i]) e[cur][i] = newNode();
            cur = e[cur][i];
        }
        cnt[cur]++;
    }

    void build() {
        vi o(1, ROOT);
        fail.assign(e.size(), 0);
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int j = 0; j < mapSize; j++) {
                if (int v = e[u][j]; v) {
                    o.push_back(v);
                    int x = fail[u];
                    while (x && !e[x][j]) x = fail[x];
                    if (int f = e[x][j]; f && f != v) fail[v] = f;
                }
            }
        }
    }

    int run(const string &s) {
        int cur = ROOT, ans = 0;
        for (char c : s) {
            int i = map(c);
            while (cur && !e[cur][i]) cur = fail[cur];
            if (e[cur][i]) cur = e[cur][i];
            ans += cnt[cur];
            cnt[cur] = 0;
        }
        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> t(n);
    for (auto &i : t) cin >> i;
    string s;
    cin >> s;
    
    AC a(t, lowercase);
    a.build();
    cout << a.run(s);
}