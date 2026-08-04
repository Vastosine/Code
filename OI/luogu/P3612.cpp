#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

int main() {
    long long n;
    string s;
    cin >> s >> n;
    int m = s.length();
    long long x = m;
    n--;
    while (x * 2 <= n) x *= 2;
    s.push_back(s.back());
    while (n >= m) {
        while (x > n) x /= 2;
        if (x == n) {
            n--;
            continue;
        }
        n -= x + 1;
    }
    cout << s[n];
}