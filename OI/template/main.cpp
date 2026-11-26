#include "netflow/HLPP.cpp"

int main() {
    szt n, m, s, t;
    cin >> n >> m >> s >> t;
    HLPP g(n + 1);
    while (m--) {
        szt u, v, c;
        cin >> u >> v >> c;
        g.addEdge(u, v, c);
    }
    cout << g.run(s, t);
}