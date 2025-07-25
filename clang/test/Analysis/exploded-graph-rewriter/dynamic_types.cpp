// RUN: %clang_analyze_cc1 -triple x86_64-unknown-linux-gnu \
// RUN:                    -analyzer-checker=core \
// RUN:                    -analyzer-dump-egraph=%t.dot %s
// RUN: %exploded_graph_rewriter %t.dot | FileCheck %s

struct S {};

void test() {
  // CHECK: Dynamic Types:
  // CHECK-SAME: <tr><td align="left"><table border="0"><tr>
  // CHECK-SAME:   <td align="left">HeapSymRegion\{conj_$1\{S *, LC1,
  // CHECK-SAME:       S{{[0-9]*}}, #1\}\}</td>
  // CHECK-SAME:   <td align="left">S</td>
  // CHECK-SAME: </tr></table></td></tr>
  new S;
}
