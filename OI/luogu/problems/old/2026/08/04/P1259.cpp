#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::swap;

string s;

void swap(int x, int y) {
    swap(s[x], s[y]);
    swap(s[x + 1], s[y + 1]);
    cout << s << "\n";
}

int main() {
    int n;
    cin >> n;
    s = string(n, 'o') + string(n, '*') + "--";
    cout << s << "\n";
    for (int i = 1; i < n - 3; i++) {
        // cout << s << "\n";
        swap(n - i, (n - i + 1) * 2);
        // cout << s << "\n";
        swap(n - i, (n - i) * 2);
    }
    swap(3, 8);
    swap(3, 7);
    swap(1, 7);
    swap(1, 6);
    swap(0, 6);
}