# 对拍暴力模板

写暴力不等于重写一遍正解。这四份模板覆盖绝大多数小数据暴力，用法统一：

```powershell
# 1. 拷一份到 stress 根目录，改名 brute.cpp（覆盖旧的）
Copy-Item .\templates\brute_subset.cpp .\brute.cpp

# 2. 改里面标了 // ---- EDIT 的地方（读取输入、评分方式）

# 3. 跑对拍（gen.cpp 读 argv[1] 当种子）
powershell -ExecutionPolicy Bypass -File .\stress.ps1 -Sol ..\..\OI\codeforces\xxx.cpp -N 300
```

## 选哪个

| 模板 | 什么时候用 | 规模上限 | 核心 |
|---|---|---|---|
| `brute_perm.cpp` | 答案与**顺序**有关 | `n ≤ 8`（8! = 4e4） | `next_permutation` |
| `brute_subset.cpp` | 要决定**选哪些元素** | `n ≤ 20`（2^n），或 `n ≤ 12` 配子集枚举 | `mask` / 子掩码 `(sub-1) & mask` |
| `brute_partition.cpp` | 要把元素**分成若干组** | `n ≤ 9`（Bell(9) = 21147） | 受限增长串 DFS |
| `brute_grid.cpp` | 棋盘 / 连通块 / 走格子 | 连通块 `n·m ≤ 1e6`；枚举路径 `n·m ≤ 25` | 四方向 DFS + 回溯 |

## 构造题 / 多解题：别用暴力，用 checker

「输出任意一个满足条件的序列」这类题，两个正确答案可以完全不同，**暴力对比必然误报**。这时写一个 checker（评测里的 special judge）：

```powershell
Copy-Item .\templates\check_construct.cpp .\checker.cpp
# 改标了 ---- EDIT 的两处：读输入、验证答案
powershell -ExecutionPolicy Bypass -File .\stress.ps1 -Sol ..\..\OI\codeforces\xxx.cpp -Check checker -N 200
```

接口固定：`checker.exe <输入文件> <输出文件>`，合法 `exit 0`，非法 `exit 1` 并打印原因。

checker 要查的四件事，写的时候逐条过：

1. **token 数对不对** —— 多输出一个数、少输出一个数，是构造题最常见的 WA；
2. **每个值在范围内** —— 比如 `1 ≤ a_i ≤ 1e18`；
3. **结构合法** —— n 个数、是排列、下标从 1 开始、图连通；
4. **全局条件成立** —— 这题真正的约束（相邻 gcd 两两不同、字典序最小、和为 X）。

第 4 条别忘了用 `set` 去重检验，只查前三条等于没查。

### 特别提醒：「无解」分支不能直接放行

题目允许「无解时输出 `No solution`」时，checker **不能**看到这四个字就 `return 0` —— 否则解答只要永远打印 `No solution` 就能通过一切测试。checker 必须自己判可行性：

```cpp
if (firstLine == "No solution") {
    if (feasible(k, l, r, n)) fail("said No solution but a split exists");
    return 0;   // 确实无解，接受
}
```

44E 的可行性判据是 `k*l <= n && n <= k*r`。

### 用正确解对拍，验证不了 checker 的拒绝能力

拿一个 AC 的解去跑对拍，checker 永远只走「接受」那条路径。它的**拒绝**能力必须用手工构造的错误输出单独验证，至少四个用例：

| 用例 | 期望 |
|---|---|
| 正确答案 | `exit 0` |
| 少一行 / 多一行 | `exit 1` |
| 某一段长度越界（`r+1`） | `exit 1` |
| 在有解的数据上报 `No solution` | `exit 1` |

只接受、不拒绝的 checker 比没有更危险：它给你一个假的绿灯。



## 三条规矩

1. **暴力必须和正解思路无关。** 如果暴力里也用到了“排序后取前缀”这个假设，它验不出任何东西。
2. **10 分钟时间盒。** 写不出来就放弃对拍，改成手推 3 组小数据 + 随机小数据肉眼比对。1100–1500 的题，对拍经常是过度投入。
3. **先去估暴力成本再动手。** 如果“买一组的花费”本身就需要子集 DP 才能算，那这题的暴力写起来和正解一样久——这时候手推更快。

## 数据规模怎么选

对拍要能**暴露**错误，不是越大越好：

- 边界：`n = 1`、`n = 2`、全相同、严格递增、严格递减
- 让贪心失效的构造：局部最优和全局最优冲突的小例子
- 生成器里直接写死几个这样的特例，再混随机

模板里 `solve()` 的读入格式按题目自己改，`gen.cpp` 的输出格式必须和它一致。
