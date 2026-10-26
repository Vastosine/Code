// Checker template (special judge) for CONSTRUCTIVE problems.
//
// When the answer has many valid forms ("output any sequence such that ..."),
// comparing with a brute force is useless: two different correct answers.
// Instead write a checker that reads (input, output) and validates every
// property the statement demands.
//
// Interface expected by stress.ps1 -Check:
//     checker.exe <input-file> <output-file>
//      exit 0  -> answer accepted
//      exit 1  -> answer rejected, message printed on stdout
//      exit 2  -> checker itself broken (bad arguments / unreadable file)
//
// Workflow:
//   Copy-Item templates\check_construct.cpp .\checker.cpp   # then edit the EDIT parts
//   .\stress.ps1 -Sol ..\OI\codeforces\xxx.cpp -Check checker -N 200
//
// Checklist when writing the validator:
//   * output has exactly the claimed number of tokens (nothing extra, nothing
//     missing) -- "extra tokens" is the most common construct-answer bug
//   * every value is inside the allowed range
//   * the structure is valid (n numbers, permutation, connected, sorted, ...)
//   * the global condition holds (here: all adjacent gcds are distinct)
//
// Example of the last point, from CF 2218D (the 67th OEIS problem):
//     set<ll> seen;
//     for (int i = 1; i < n; i++) {
//         ll g = gcd(a[i - 1], a[i]);
//         if (!seen.insert(g).second) fail("duplicate gcd " + to_string(g) + " at " + to_string(i));
//     }
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <numeric>
#include <cstdlib>
#include <cerrno>
using namespace std;
using ll = long long;

static void fail(const string &why) {
    cout << "WA: " << why << "\n";
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 3) { cout << "usage: checker <input> <output>\n"; return 2; }

    ifstream in(argv[1]);
    ifstream out(argv[2]);
    if (!in) { cout << "cannot open input " << argv[1] << "\n"; return 2; }
    if (!out) { cout << "cannot open output " << argv[2] << "\n"; return 2; }

    // ---- pull every token of the contestant output ----------------------
    vector<string> tok;
    {
        string s;
        while (getline(out, s)) {
            if (!s.empty() && s.back() == '\r') s.pop_back();
            tok.push_back(s);
        }
    }
    size_t p = 0;

    auto nextToken = [&](const char *what) -> string {
        if (p >= tok.size()) fail(string("output ended while expecting ") + what +
                                  " (got " + to_string(tok.size()) + " tokens)");
        return tok[p++];
    };

    auto nextLL = [&](const char *what) -> ll {
        string s = nextToken(what);
        char *end = nullptr;
        errno = 0;
        ll v = strtoll(s.c_str(), &end, 10);
        if (errno != 0 || end == s.c_str() || *end != '\0') fail("not an integer: '" + s + "'");
        return v;
    };

    // ---- read the input the way the solver sees it ----------------------
    int t = 1;
    // if (!(in >> t)) { cout << "cannot read t\n"; return 2; }

    for (int tc = 1; tc <= t; tc++) {
        int k, l, r;
        string s;
        in >> k >> l >> r >> s;
        int n = s.length();
        string ans;
        for (int i = 0; i < k; i++) {
            string input = nextToken("a line");
            if (!i && input == "No solution") {
                return 0;
            }
            if (input.empty()) fail("find empty line");
            if (input.length() < l || input.length() > r) fail("length error");
            ans += input;
        }
        if (ans != s) fail("Wrong");
        // if (!(in >> n)) { cout << "cannot read n\n"; return 2; }
        // // ---- EDIT: read the rest of this test case ----------------------
        // vector<ll> a(n);
        // for (auto &x : a) in >> x;

        // // ---- EDIT: read and validate the answer for this test case ------
        // // (delete this block if the answer is a single number per case)
        // vector<ll> ans(n);
        // for (int i = 0; i < n; i++) ans[i] = nextLL("an answer element");

        // const ll LIM = (ll) 1e18;
        // for (int i = 0; i < n; i++) {
        //     if (ans[i] < 1 || ans[i] > LIM)
        //         fail("case " + to_string(tc) + ": a[" + to_string(i) + "] = " +
        //              to_string(ans[i]) + " out of range [1, 1e18]");
        // }
        // // global condition example: all adjacent gcds distinct
        // set<ll> seen;
        // for (int i = 1; i < n; i++) {
        //     ll g = gcd(ans[i - 1], ans[i]);
        //     if (!seen.insert(g).second)
        //         fail("case " + to_string(tc) + ": duplicate gcd " + to_string(g) +
        //              " between positions " + to_string(i - 1) + " and " + to_string(i));
        // }
    }

    if (p != tok.size()) fail("extra tokens after the answer: " + to_string(tok.size() - p));

    cout << "OK\n";
    return 0;
}
