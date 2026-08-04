#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

int main() {
    string s;
    cin >> s;
    int t = 0, x = 0;
    for (char i : s) {
        if (i != '-' && i != 'X') x += (i - '0') * ++t;
        if (i == 'X') x += 10 * ++t;
    }
    int y = x % 11;
    if (!y) {
        cout << "Right\n";
    } else {
        int c = ((s[12] == 'X' ? 10 : s[12] - '0') + y + 11) % 11;
        cout << s.substr(0, 12) + (char) (c == 10 ? 'X' : c + '0');
    }
}