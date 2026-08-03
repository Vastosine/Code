#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::istream;

template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) cin >> i; return in; }

int main() {
    int m, n, ans = 0;
    cin >> m >> n;
    vector<int> seq(m * n), last(n), process(n);
    vector<vector<int>> machine(n, vector<int>(m)), time(n, vector<int>(m)), t(m, vector<int>(20 * 20 * 20));
    cin >> seq >> machine >> time;
    for (int i : seq) {
        i--;
        int pro = process[i]++;
        int x = machine[i][pro] - 1, y = time[i][pro], z = 0;
        for (int j = last[i]; ; j++) {
            z += !t[x][j];
            if (j - last[i] >= y) z -= !t[x][j - y];
            if (z == y) {
                for (int k = 0; k < y; k++) {
                    t[x][j - k] = i + 1;
                }
                last[i] = j + 1;
                break;
            }
        } 
    }
    for (int i : last) {
        if (i > ans) ans = i;
    }
    cout << ans << "\n";
}