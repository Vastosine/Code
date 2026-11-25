// MCMF 模板自测：类接口版（对应 OI/template/MCMF.cpp 的 class MCMF）
//
//   g++ -std=c++17 -O0 -g -fsanitize=address,undefined -D_GLIBCXX_ASSERTIONS \
//       -o mcmf_test.exe mcmf_test.cpp
//   ./mcmf_test.exe
//
// 每个用例先打印名字再跑——卡住或崩溃时才能定位到是哪个用例。
// 想单独跑一个用例，把 main 里其余的注释掉。
#include <cstdio>
#include <utility>
#include "../OI/template/netflow/MCMF.cpp"

using pll = std::pair<long long, long long>;

static int fails = 0;
static int total = 0;

static void begin(const char *name) {
    printf("[%d] %-34s", ++total, name);
    fflush(stdout);
}

static void done(pll got, pll want) {
    bool ok = (got.first == want.first && got.second == want.second);
    if (!ok) fails++;
    printf("flow=%-14lld cost=%-16lld want %lld/%lld   %s\n",
           (long long)got.first, (long long)got.second,
           (long long)want.first, (long long)want.second, ok ? "OK" : "**FAIL**");
    fflush(stdout);
}

static void case1() {   // 单条路
    begin("single path");
    MCMF g;
    g.clear(4);
    g.addEdge(0, 1, 1, 1);
    g.addEdge(1, 3, 1, 1);
    done(g.run(0, 3), {1, 2});
}

static void case2() {   // 容量 2：流 2，费用 (1+5)*2
    begin("cap 2");
    MCMF g;
    g.clear(4);
    g.addEdge(0, 1, 2, 1);
    g.addEdge(1, 3, 2, 5);
    done(g.run(0, 3), {2, 12});
}

static void case3() {   // 负费用边（SPFA 必须能吃负边）
    begin("negative cost edge");
    MCMF g;
    g.clear(4);
    g.addEdge(0, 1, 1, -5);
    g.addEdge(1, 3, 1, 1);
    done(g.run(0, 3), {1, -4});
}

static void case4() {   // 有瓶颈时必须选便宜的那条，而不是先找到的
    begin("bottleneck picks cheap");
    MCMF g;
    g.clear(5);
    g.addEdge(0, 1, 1, 1);
    g.addEdge(1, 3, 1, 0);
    g.addEdge(0, 2, 1, 5);
    g.addEdge(2, 3, 1, 0);
    g.addEdge(3, 4, 1, 0);      // 瓶颈：最大流只能是 1，费用取 1 那条
    done(g.run(0, 4), {1, 1});
}

static void case5() {   // 从源可达的负环 -> 约定返回 {-1, 0}
    begin("negative cycle -> {-1,0}");
    MCMF g;
    g.clear(4);
    g.addEdge(0, 1, 1, 0);
    g.addEdge(1, 2, 1, -5);
    g.addEdge(2, 1, 1, 0);       // 1 -> 2 -> 1 费用 -5
    g.addEdge(2, 3, 1, 0);
    done(g.run(0, 3), {-1, 0});
}

static void case6() {   // 同一个对象跑第二次：流已耗尽，必须返回 {0,0}
    begin("second run on exhausted graph");
    MCMF g;
    g.clear(4);
    g.addEdge(0, 1, 1, 0);
    g.addEdge(0, 2, 1, 0);
    g.addEdge(1, 3, 1, 0);
    g.addEdge(2, 3, 1, 0);
    done(g.run(0, 3), {2, 0});
    begin("  ...and again");
    done(g.run(0, 3), {0, 0});
}

static void case7() {   // dir = -1 求最大费用，中间用 clear + 重建当 reset
    // 2x2 费用矩阵：两条完美匹配费用 1+20=21 和 2+10=12
    int c[2][2] = {{1, 2}, {10, 20}};
    auto build = [&](MCMF &g) {
        g.clear(6);
        for (int i = 0; i < 2; i++) {
            g.addEdge(0, 1 + i, 1, 0);
            g.addEdge(3 + i, 5, 1, 0);
            for (int j = 0; j < 2; j++) g.addEdge(1 + i, 3 + j, 1, c[i][j]);
        }
    };
    begin("min cost (scale=1)");
    MCMF g;
    build(g);
    done(g.run(0, 5, 1), {2, 12});
    begin("max cost (scale=-1) after rebuild");
    build(g);                    // 等价于旧接口的 reset
    done(g.run(0, 5, -1), {2, 21});
}

static void case8() {   // 容量超过 int：P1251 的 Σr_i 能到 2e10
    begin("cap > INT_MAX");
    MCMF g;
    g.clear(3);
    g.addEdge(0, 1, 20000000000LL, 3);
    g.addEdge(1, 2, 20000000000LL, 0);
    done(g.run(0, 2), {20000000000LL, 60000000000LL});
}

static void case9() {   // 构造时就给 n，addEdge 必须能直接用（e 必须已被分配）
    begin("ctor allocates adjacency");
    MCMF h(4);
    h.addEdge(0, 1, 1, 1);
    h.addEdge(1, 3, 1, 1);
    done(h.run(0, 3), {1, 2});
}

static void case12() {   // 方案还原：只有 1 的出路通到汇，所以必须选中 a 而不是 b
    begin("scheme recovery via flowOn");
    MCMF g;
    g.clear(4);
    int a = g.addEdge(0, 1, 1, 0);
    int b = g.addEdge(0, 2, 1, 0);
    g.addEdge(1, 3, 1, 0);            // 2 没有出路
    done(g.run(0, 3), {1, 0});
    bool ok = (g.flowOn(a) == 1 && g.flowOn(b) == 0);
    if (!ok) fails++;
    printf("%-34s flowOn(a)=%lld flowOn(b)=%lld   want 1/0   %s\n",
           "  which edge carried flow", (long long)g.flowOn(a),
           (long long)g.flowOn(b), ok ? "OK" : "**FAIL**");
    fflush(stdout);
}

int main() {
    case1(); case2(); case3(); case4();
    case5(); case6(); case7(); case8(); case9(); case12();
    printf("\n%s (%d failure%s of %d checks)\n",
           fails ? "**FAILED**" : "ALL PASS", fails, fails == 1 ? "" : "s", total);
    return fails != 0;
}
