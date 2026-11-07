# Code —— 竞赛侧仓库

**本仓只放竞赛代码与工具。** 学业、课程、英语、计划与日志全在另一个工作区：

> **`D:\study\main`** —— 非竞赛工作区，文档入口 `D:\study\main\README.md`

## 代码位置约定

| 类型 | 路径 |
|---|---|
| 比赛 | `OI/contests/CF/<比赛号>/<比赛号><题号>.cpp` |
| 练习（当前） | `OI/codeforces/<题号>.cpp`（平铺） |
| 练习（归档） | `OI/codeforces/old/<年>/<月>/<日>/<题号>.cpp` |
| `.cph` | 跟着 `.cpp` 走；在 `.gitignore` 里，`git status` 看不见，要单独搬 |

## 硬规则

- **AC 的题按首次 AC 日期归档**到 `OI/codeforces/old/<年>/<月>/<日>/`，`.cph` 一并迁移（`organize.ps1 -Apply`）。
- **只按第一次 AC 记账**；后来的优化重交不计提交数。
- `tmp/`、`stress/` 不入库。
- 一题一 commit，**commit 之后必须 push**。
