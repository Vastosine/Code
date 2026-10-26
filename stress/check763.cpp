// checker for 763A (Timofey and a tree).
//   checker.exe <input> <output>
// Accepts "NO" only when no vertex is valid, and "YES v" only when v is valid.
// Both directions are checked by brute force over all vertices: n <= 9 here.
#include <bits/stdc++.h>
using namespace std;

static void fail(const string &why) {
    cout << "WA: " << why << "\n";
    exit(1);
}

int n;
vector<pair<int, int>> edges;
vector<int> c;

// valid(v): every edge not touching v joins two equal colours
static bool valid(int v) {
    for (auto &e : edges) {
        if (e.first == v || e.second == v) continue;
        if (c[e.first] != c[e.second]) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc < 3) { cout << "usage: checker <input> <output>\n"; return 2; }
    ifstream in(argv[1]), out(argv[2]);
    if (!in) { cout << "cannot open input\n"; return 2; }
    if (!out) { cout << "cannot open output\n"; return 2; }

    in >> n;
    edges.resize(n - 1);
    for (auto &e : edges) in >> e.first >> e.second;
    c.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) in >> c[i];

    vector<string> tok;
    string s;
    while (getline(out, s)) {
        if (!s.empty() && s.back() == '\r') s.pop_back();
        stringstream ss(s);
        string w;
        while (ss >> w) tok.push_back(w);
    }

    if (tok.empty()) fail("empty output");
    if (tok[0] == "NO") {
        if (tok.size() != 1) fail("extra tokens after NO");
        for (int v = 1; v <= n; v++)
            if (valid(v)) fail("said NO but vertex " + to_string(v) + " works");
        return 0;
    }
    if (tok[0] != "YES") fail("expected YES or NO, got '" + tok[0] + "'");
    if (tok.size() != 2) fail("expected exactly one vertex after YES");
    int v = atoi(tok[1].c_str());
    if (v < 1 || v > n) fail("vertex " + to_string(v) + " out of range");
    if (!valid(v)) fail("vertex " + to_string(v) + " does not leave monochromatic components");
    return 0;
}
