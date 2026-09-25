// Problem : $name$ $url$
// Time    : $date$ $time$

#include <bitset>
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }

const int MAX_BIT_SIZE = 32;

typedef std::bitset<MAX_BIT_SIZE> bitset;

int solve() {
    int L, R;
    cin >> L >> R;
    bitset l(L), r(R);
    for (int i = MAX_BIT_SIZE - 1; i + 1; i--) {
        if (l[i] == r[i]) l[i] = r[i] = 0;
        else {
            L = l.to_ullong(), R = r.to_ullong();
            bitset m = l, n = l;
            for (int j = i - 1; j + 1; j--) m[j] = 1, n[j] = 0;
            int M = m.to_ullong() & R, N = n.to_ullong();
            if (M >= L) return R - N + 1;
            while (l[--i]) {
                if (!i) return R - L + M - N + 2;
            }
            for (int j = i; j + 1; j--) l[j] = 0;
            L = l.to_ullong();
            if (M >= L) return R - N + 1;
            else return R - L + M - N + 2;
        }
    }
    return 1;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}