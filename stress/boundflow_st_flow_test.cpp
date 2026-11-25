// "zero code change" claim: 有源汇下界可行流 = 加一条 t->s 容量 INF，然后 run()
#include "_boundflow_class.hpp"
#include <cstdio>

int main() {
    // s = 0, t = 3 ; bounds force 3 units from s to t
    //   s -> 1 [3,5]
    //   1 -> t [3,5]
    const long long INF = 1LL << 60;
    BoundFlow a(4);                        // nodes 0..3, S=4, T=5
    int e01 = a.addEdge(0, 1, 3, 5);
    int e13 = a.addEdge(1, 3, 3, 5);
    int ets = a.addEdge(3, 0, 0, INF);     // <-- the only addition

    bool ok = a.run();
    printf("feasible = %s\n", ok ? "Yes" : "No");
    if (ok) {
        printf("f(s->1) = %lld\n", a.flowOn(e01) + 3);
        printf("f(1->t) = %lld\n", a.flowOn(e13) + 3);
        printf("f(t->s) = %lld   <- this is the s->t flow value\n", a.flowOn(ets));
    }
    return 0;
}
