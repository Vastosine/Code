#include <iostream>
#include <map>

using std::cin;
using std::cout;
using std::map;
using std::string;

int main() {
    int n;
    while (cin >> n && n) {
        map<string, int> a;
        string s;
        while (n--) {
            cin >> s;
            a[s]++;
        }
        std::pair<string, int> ans = *a.begin();
        for (std::pair<string, int> i : a) {
            if (i.second > ans.second) ans = i;
        }
        cout << ans.first << "\n";
    }
}
