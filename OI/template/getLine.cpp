#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

// skip: Skip (Ignore) the empty line, set false to input exactly one line
vll getvll(bool skip = true) {
    string s;
    vll ans;
    while (getline(cin, s)) {
        int f = 1, ed = 1;
        for (int i : s) {
            if (i == '-') f = -1;
            else if (i >= '0' && i <= '9') {
                if (ed) ed = 0, ans.push_back(0);
                (ans.back() *= 10) += f * (i - '0');
            } else ed = 1, f = 1;
        }
        if (!skip || !ans.empty()) break;
    }
    return ans;
}

template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
int main() {
    cout << getvll(0);
}