// Dinic 模板自测
#include <cstdio>
#include <algorithm>
#include <iostream>
#include "../OI/template/netflow/Dinic.cpp"

using ll = long long;   

static int fails = 0;
void check(const char *name, ll got, ll want) {
    bool ok = got == want;
    if (!ok) fails++;
    printf("%-24s flow=%lld  want=%lld   %s\n", name, (long long)got, (long long)want, ok ? "OK" : "**FAIL**");
}

int main() {
    {   // 单条路
        Dinic d(4);
        d.addEdge(0, 1, 1); d.addEdge(1, 3, 1);
        check("single path", d.run(0, 3), 1);
    }
    {   // 容量 2
        Dinic d(4);
        d.addEdge(0, 1, 2); d.addEdge(1, 3, 2);
        check("cap 2", d.run(0, 3), 2);
    }
    {   // 两条独立路
        Dinic d(4);
        d.addEdge(0, 1, 1); d.addEdge(1, 3, 1);
        d.addEdge(0, 2, 1); d.addEdge(2, 3, 1);
        check("two disjoint paths", d.run(0, 3), 2);
    }
    {   // 瓶颈
        Dinic d(5);
        d.addEdge(0, 1, 5); d.addEdge(1, 3, 5);
        d.addEdge(0, 2, 5); d.addEdge(2, 3, 5);
        d.addEdge(3, 4, 1);
        check("bottleneck", d.run(0, 4), 1);
    }
    {   // 需要多轮增广的层状图：0->1,2 ; 1->3 ; 2->3 ; 3->4
        Dinic d(6);
        d.addEdge(0, 1, 1); d.addEdge(0, 2, 1);
        d.addEdge(1, 3, 1); d.addEdge(2, 3, 1);
        d.addEdge(3, 4, 1); d.addEdge(3, 5, 1);
        check("layered", d.run(0, 4), 1);
    }
    {   // 容量超过 int
        Dinic d(3);
        d.addEdge(0, 1, 20000000000LL); d.addEdge(1, 2, 20000000000LL);
        check("cap > INT_MAX", d.run(0, 2), 20000000000LL);
    }
    {   // 不连通
        Dinic d(3);
        d.addEdge(0, 1, 1);
        check("unreachable", d.run(0, 2), 0);
    }
    {   // 反向边不该被当成残余
        Dinic d(3);
        d.addEdge(0, 1, 0); d.addEdge(1, 2, 1);
        check("zero-cap edge", d.run(0, 2), 0);
    }
    {   // 方案还原：只有 1 的出路通到汇，所以必须选中 a 而不是 b
        Dinic d(4);
        int a = d.addEdge(0, 1, 1);
        int b = d.addEdge(0, 2, 1);
        d.addEdge(1, 3, 1);
        ll f = d.run(0, 3);
        bool ok = f == 1 && d.flowOn(a) == 1 && d.flowOn(b) == 0;
        if (!ok) fails++;
        printf("%-24s flow=%lld flowOn(a)=%lld flowOn(b)=%lld  want 1/1/0   %s\n",
               "scheme recovery", (long long)f, (long long)d.flowOn(a),
               (long long)d.flowOn(b), ok ? "OK" : "**FAIL**");
    }
    {   // 最小割 S 侧（门：不实现 reachable 就编译不过）
        // P2762 的图：0=源 1,2=实验 3,4,5=仪器 6=汇
        Dinic d(7);
        struct E { int u, v; ll c; };
        std::vector<E> es;
        auto add = [&](int u, int v, ll c) { d.addEdge(u, v, c); es.push_back({u, v, c}); };
        add(0, 1, 10); add(0, 2, 25);
        add(1, 3, Dinic::INF); add(1, 4, Dinic::INF);
        add(2, 4, Dinic::INF); add(2, 5, Dinic::INF);
        add(3, 6, 5); add(4, 6, 6); add(5, 6, 7);
        ll f = d.run(0, 6);
        std::vector<int> dep = d.reachable(0);
        ll cut = 0;
        for (auto &e : es) if (~dep[e.u] && !~dep[e.v]) cut += e.c;
        bool sideOK = !~dep[6];                       // 汇必然不可达
        for (int i = 0; i <= 5; i++) if (!~dep[i]) sideOK = false;
        bool ok = (f == 18) && (cut == f) && sideOK;
        if (!ok) fails++;
        printf("%-24s flow=%lld cut=%lld side=%s  want 18/18/all-but-sink   %s\n",
               "min-cut side P2762", (long long)f, (long long)cut,
               sideOK ? "ok" : "**BAD**", ok ? "OK" : "**FAIL**");
    }
    {   // S 侧不能退化成"全可达"：0 出去两条路都各自满掉
        Dinic d(4);
        struct E { int u, v; ll c; };
        std::vector<E> es;
        auto add = [&](int u, int v, ll c) { d.addEdge(u, v, c); es.push_back({u, v, c}); };
        add(0, 1, 1); add(1, 3, 1);
        add(0, 2, 5); add(2, 3, 5);
        ll f = d.run(0, 3);
        std::vector<int> dep = d.reachable(0);
        ll cut = 0;
        for (auto &e : es) if (~dep[e.u] && !~dep[e.v]) cut += e.c;
        bool ok = (f == 6) && (cut == f) && (~dep[0]) && (!~dep[1]) && (!~dep[2]);
        if (!ok) fails++;
        printf("%-24s flow=%lld cut=%lld side={0}=%d/%d  want 6/6/only-src   %s\n",
               "min-cut side tiny", (long long)f, (long long)cut,
               (~dep[0]) ? 1 : 0, (!~dep[1]) ? 1 : 0, ok ? "OK" : "**FAIL**");
    }
    printf("\n%s (%d failure%s)\n", fails ? "**FAILED**" : "ALL PASS", fails, fails == 1 ? "" : "s");
    return fails != 0;
}
