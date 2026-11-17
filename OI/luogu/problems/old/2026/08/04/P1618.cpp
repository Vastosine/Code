#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::__gcd;
using std::to_string;
using std::string;

int gcd(int x, int y, int z) {
    return __gcd(x, __gcd(y, z));
}

int main() {
    int a[3], b[3]{};
    for (int &i : a) cin >> i;
    int x = gcd(a[0], a[1], a[2]);
    for (int &i : a) i /= x;    
    int ans = 0;
    for (int i = 1; i < 1000; i++) {
        string s = "";
        for (int j = 0; j < 3; j++) b[j] += a[j], s += to_string(b[j]);
        if (s.length() > 9) break;
        if (s.length() < 9) continue;
        int p[9]{}, t = 0;
        for (int j : s) 
            t += !(p[j - '0' - 1]++);
        if (t == 9) cout << b[0] << " " << b[1] << " " << b[2] << "\n", ans++;
    }
    if (!ans) cout << "No!!!";
}