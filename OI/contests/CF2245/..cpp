#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
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
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }
int rand(int l, int r) {
    return rand() % (r - l) + l;
}

void Main() {
    freopen("in.in", "w", stdout);
    cout << 1 << "\n";
    int n = rand(3, 5);
    cout << n << " " << n * (n + 1) / 2 << "\n";
    vi a(n);
    for (int &i : a) i = rand(-10, 10);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (a[i] + a[j] < 0) cout << "2 ";
            else cout << "1 ";
            cout << i + 1 << " " << j + 1 << "\n";
        }
    }
    freopen("ans.out", "w", stdout);
    cout << a << "\n";
    freopen("con", "w", stdout);
    system("main.exe < in.in > out.out");
    freopen("out.out", "r", stdin);
    string s;
    cin >> s;
    int k = true;
    if (s == "NO") k = false;
    vi b(n);
    cin >> b;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((a[i] + a[j] < 0) != (b[i] + b[j] < 0)) {
                k = false;
                break;
            }
        }
    }
    if (!k) std::cerr << "1", exit(0);
    freopen("con", "r", stdin);
}

signed main(signed argc, char **args) {
    srand(time(0));
    system("g++ 2245D1.cpp -o main.exe");
    int c = 10;
    if (c > 1) sscanf(args[1], "%lld", &c);
    while (c--) Main();
}