#include <iostream>
#include <string>
#include <vector>
using namespace std;

using vi = vector<int>;

struct CharMap {
    int (*map)(char);
    int size;
    CharMap(int (*map)(char), int size) : map(map), size(size) {}
    int operator()(char c) const { return map(c); }
};
const CharMap LOWERCASE_MAP = CharMap([](char c) { return c - 'a'; }, 26);
const CharMap UPPERCASE_MAP = CharMap([](char c) { return c - 'A'; }, 26);
const CharMap ALL_MAP = CharMap([](char c) { return (int) c; }, 256);

class AC {
  public:
    using vi = vector<int>;
    AC(const vector<string> &strs = {}, CharMap map = LOWERCASE_MAP) : map(map), cnt(0) {
        newNode();
        for (auto &s : strs) insert(s);
    }

    void insert(const string &s, int id) {
        int cur = ROOT;
        for (char c : s) {
            int i = map(c);
            if (!e[cur][i]) e[cur][i] = newNode();
            cur = e[cur][i];
        }
        eme[cur].push_back(id);
        cnt = max(cnt, id + 1);
    }

    void insert(const string &s) { insert(s, cnt); }

    void build() {
        vi o(1, ROOT);
        fail.assign(e.size(), 0);
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int j = 0; j < map.size; j++) {
                if (int v = e[u][j]; v) {
                    o.push_back(v);
                    int x = fail[u];
                    while (x && !e[x][j]) x = fail[x];
                    if (int f = e[x][j]; f && f != v) fail[v] = f;
                }
            }
        }
    }

    vi run(const string &s) {
        if (fail.size() != e.size()) build();
        int cur = ROOT;
        vi ans(cnt), stroke(e.size());
        for (char c : s) {
            int i = map(c);
            while (cur && !e[cur][i]) cur = fail[cur];
            if (e[cur][i]) cur = e[cur][i];
            stroke[cur]++;
        }
        vi o(1, ROOT);
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int j = 0; j < map.size; j++) {
                if (e[u][j]) o.push_back(e[u][j]);
            }
        }
        for (int i = (int) o.size() - 1; ~i; i--) {
            int u = o[i];
            for (int j : eme[u]) ans[j] += stroke[u];
            stroke[fail[u]] += stroke[u];
        }
        return ans;
    }
  private:
    int newNode() { return e.push_back(vi(map.size)), eme.push_back({}), (int) e.size() - 1; }
    
    vector<vi> e, eme;
    vi fail;
    CharMap map;
    int cnt;
    static constexpr int ROOT = 0;
};

int main() {
    int n;
    cin >> n;
    vector<string> t(n);
    for (auto &i : t) cin >> i;
    string s;
    cin >> s;
    AC a(t);
    // a.build();
    vi ans = a.run(s);
    for (auto i : ans) cout << i << "\n";
    // int res = 0;
    // for (auto i : ans) res += !!i;
    // cout << res;
}