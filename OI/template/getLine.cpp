#include <iostream>
#include <vector>
#include <string>

using namespace std;
using ll = long long;
using vll = vector<ll>;

vll getvll() {
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
        if (!ans.empty()) break;
    }
    return ans;
}
