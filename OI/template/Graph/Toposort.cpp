#include <vector>

using namespace std;
using vi = vector<int>;

vector<vi> e;
vi order;
int n;

// return whether it has no cycle
bool solve() {
    order.clear();
    vi in(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : e[u]) in[v]++;
    }
    for (int u = 1; u <= n; u++) {
        if (!in[u]) order.push_back(u);
    }
    for (int i = 0; i < (int) order.size(); i++) {
        int u = order[i];
        for (int v : e[u]) {
            in[v]--;
            if (!in[v]) order.push_back(v);
        }
    }
    return order.size() == n;
}