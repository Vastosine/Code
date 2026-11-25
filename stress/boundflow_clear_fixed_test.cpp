// Same scenario, but against the proposed fix (_boundflow_fixed.hpp).
#include "_boundflow_fixed.hpp"
#include <cstdio>

int main() {
    {
        BoundFlow a(3);
        a.addEdge(0, 1, 1, 2);
        a.addEdge(1, 2, 1, 2);
        a.addEdge(2, 0, 1, 2);
        printf("fresh      run() = %d\n", (int) a.run());
    }
    {
        BoundFlow a(3);
        a.addEdge(0, 1, 1, 2);
        a.addEdge(1, 2, 1, 2);
        a.addEdge(2, 0, 1, 2);
        a.run();
        printf("reused     clear(3) ...\n");
        a.clear(3);
        a.addEdge(0, 1, 1, 2);
        a.addEdge(1, 2, 1, 2);
        a.addEdge(2, 0, 1, 2);
        printf("reused     run() = %d\n", (int) a.run());
        printf("reused     reassign() ...\n");
        a.reassign();
        a.addEdge(0, 1, 0, 2);
        a.addEdge(1, 2, 0, 2);
        a.addEdge(2, 0, 0, 2);
        printf("reused     run() = %d\n", (int) a.run());
    }
    return 0;
}
