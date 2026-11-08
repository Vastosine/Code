#include <bits/stdc++.h>
using namespace std;
#define main sol_main
#include "../../OI/codeforces/1036C.cpp"
#undef main
#include "gen.cpp"
#include "brute.cpp"

int main() {
    init();                                   // 手动调，main 被改名了
    auto *saved = cin.rdbuf();
    long long cases = 0;
    INIT();
    for (int scale = 1; scale <= 55; scale++) {       // 先小后大
        for (unsigned seed = 0; seed < 200; seed++) {
            string input = gen(Case(scale), seed);

            istringstream in(input);
            cin.rdbuf(in.rdbuf());
            cin.clear();                            // failbit 不会自己清
            auto got = Main(0);
            cin.rdbuf(saved);

            auto exp = bruteSolve(input);
            cases++;
            if (!(got == exp)) {
                cout << "MISMATCH scale=" << scale << " seed=" << seed << "\n";
                cout << input << "\n";
                cout << "brute = " << exp << "   yours = " << got << "\n";
                return 1;
            }
        }
    }
    cout << "OK " << cases << " cases\n";
    return 0;
}