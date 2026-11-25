src = open(r"D:\code\OI\template\netflow\BoundFlow.cpp", encoding="utf-8-sig").read().splitlines(True)
cut = next(i for i, l in enumerate(src) if l.strip().startswith("#include <iostream>"))
body = "".join(src[:cut]).replace('#include "Dinic.cpp"',
                                  '#include "../OI/template/netflow/Dinic.cpp"')
open(r"D:\code\stress\_boundflow_class.hpp", "w", encoding="utf-8", newline="\n").write(body)

# proposed fix: clear/resize must keep the two extra nodes for S and T
fixed = body.replace("Dinic::clear(n);", "Dinic::clear(n + 2);") \
            .replace("Dinic::resize(N);", "Dinic::resize(N + 2);")
assert fixed != body
open(r"D:\code\stress\_boundflow_fixed.hpp", "w", encoding="utf-8", newline="\n").write(fixed)
print("wrote _boundflow_class.hpp and _boundflow_fixed.hpp (%d lines)" % cut)
