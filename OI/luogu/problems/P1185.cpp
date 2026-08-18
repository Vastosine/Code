// Problem : P1185 绘制二叉树 https://www.luogu.com.cn/problem/P1185
// Time    : 2026-08-05 20:14:31

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
using std::string;
vector<string> ans;
vector<int> line;
vector<vector<int>> ps;

void del(int u, int v) {
    if (u < 0 || v < 0 || u >= ans.size() || v >= ans[u].length() || ans[u][v] == ' ') return;
    ans[u][v] = ' ';
    del(u - 1, v - 1);
    del(u - 1, v + 1);
}

void solve() {
    int n, m;
    cin >> n >> m;
    line.assign(n + 1, -1);
    ps.assign(n + 1, {});
    line[n] = 0;
    vector<int> p((1 << (n - 1)));
    string s = "o";
    p[0] = 0;
    for (int i = 1; i < (1 << (n - 1)); i++) {
        s += string(1 + 2 * (i % 2), ' ') + 'o';
        p[i] = s.length() - 1;
    }
    ans.push_back(s);
    ps[n] = p;
    int ml = s.size();
    for (int i = 1; i < n; i++) {
        while (true) {
            string next(ml, ' ');
            bool br = false;
            for (int j = 0; j < (1 << (n - i)); j += 2) {
                p[j]++;
                p[j + 1]--;
                next[p[j]] = '/';
                next[p[j + 1]] = '\\';
                if ((br |= (p[j + 1] == p[j]))) {
                    next[p[j]] = 'o';
                    p[j / 2] = p[j];
                }
            }
            ans.push_back(next);
            if (br) {
                // for (int i : p) cout << i << " ";
                break;
            }
        }
        ps[n - i] = p;
        line[n - i] = ans.size() - 1;
        // cout << "\n";
    }
    while (m--) {
        int x, y;
        cin >> x >> y;
        if (x == 1) {
            return;
        }
        int u = line[x];
        int v = ps[x][y - 1];
        if (ans[u][v] == ' ') continue;
        int k = (v + 1 < ans[u + 1].size() && ans[u + 1][v + 1] != ' ') ? 1 : -1;
        int i;
        char *z;
        for (i = 1; u + i < ans.size() && *(z = &ans[u + i][v + k * i]) != 'o'; i++) {
            *z = ' ';
        }   
        del(u, v);
    }
    for (int i = ans.size() - 1; i + 1; i--) {
        cout << ans[i] + '\n';
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}