// Does run() still work after clear()/resize()?
// Built with -D_GLIBCXX_DEBUG so vector::operator[] out-of-range aborts.
#include "_boundflow_class.hpp"
#include <cstdio>

int main() {
    {
        // 1) fresh object
        BoundFlow a(3);                     // nodes 0..2, S=3, T=4
        a.addEdge(0, 1, 1, 2);
        a.addEdge(1, 2, 1, 2);
        a.addEdge(2, 0, 1, 2);
        printf("fresh      run() = %d\n", (int) a.run());
    }
    {
        // 2) reuse after clear(3)
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
    }
    return 0;
}
