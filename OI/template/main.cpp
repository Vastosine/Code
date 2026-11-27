#include "Graph/TreeDivide.cpp"

int main() {
    szt n, m;
    cin >> n >> m;
    SampleTreeDivide g(n + 1);
    for (szt i = 1; i < n; i++) {
        szt u, v;
        ll w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    vst q(m);
    cin >> q;
    g.query = q;
    g.run();
}