# ⚡ Data Structures & Algorithms (DSA 实战体系)

<p align="left">
  <img src="https://img.shields.io/badge/Language-C99%20%2F%20C11-00599C?style=flat-square&logo=c" alt="Language" />
  <img src="https://img.shields.io/badge/Standard-GCC%20%2F%20Clang-brightgreen?style=flat-square" alt="Compiler" />
  <img src="https://img.shields.io/badge/Code_Quality-Wall%20%26%20Wextra%20Passed-blue?style=flat-square" alt="Quality" />
  <img src="https://img.shields.io/badge/License-MIT-orange?style=flat-square" alt="License" />
</p>

本项目为**经典数据结构与算法 (DSA)** 的现代工业级 C 语言实现体系。全库采用**纯正标准英文命名**，并在每个源文件中配备**保姆级教学注释、ASCII 内存与指针变化图解以及高频疑难 Q&A**，专为高效攻克计算机底层内功设计。

---

## 🌟 核心特色

- 🎨 **ASCII 动画式内存图解**：将抽象复杂的指针移动、断链重连、堆栈分配过程转化为直观的字符结构画，告别生硬死记。
- 🧠 **新手避坑与设计哲学 Q&A**：每个源码头部深度解析“为什么这样写”（如防整型溢出、防 Use-After-Free 悬挂野指针、为什么二叉堆用数组存储更优等）。
- 🛡️ **工业级防御性编程**：严格实行入参空指针检查、上下溢出拦截、内存申请失败保护，代码在 `-Wall -Wextra` 编译下**严格 0 警告、0 报错**。
- 🚀 **零依赖一键自测**：所有文件均为独立自包含的控制台单文件，内置完备的 `main()` 测试用例与格式化可视化打印。

---

## 🧭 知识图谱与全景章节导航

### 📐 第一篇：算法基础与线性表

| 专题模块 | 核心源码与跳转链接 | 核心知识点 | 时空复杂度 |
| :--- | :--- | :--- | :---: |
| **01. 复杂度分析** | [01_time_complexity_linear.c](c/01_complexity_analysis/01_time_complexity_linear.c)<br>[02_time_complexity_nested.c](c/01_complexity_analysis/02_time_complexity_nested.c)<br>[03_space_complexity_dynamic.c](c/01_complexity_analysis/03_space_complexity_dynamic.c) | 线性阶 $O(N)$ 累加、数组退化机制<br>嵌套循环矩阵模型与高斯求和<br>堆区动态数组生命周期与内存闭环 | $O(N) / O(1)$<br>$O(N^2) / O(1)$<br>$O(N) / O(N)$ |
| **02. 顺序表与数组** | [01_seq_list_insertion.c](c/02_array_and_sequence_list/01_seq_list_insertion.c)<br>[02_seq_list_deletion.c](c/02_array_and_sequence_list/02_seq_list_deletion.c)<br>[03_linear_search.c](c/02_array_and_sequence_list/03_linear_search.c) | 从后向前移动插入、防数据被覆盖<br>从前向后平移覆盖、逻辑长度扣减<br>顺序扫描匹配、哨兵机制 | $O(N) / O(1)$<br>$O(N) / O(1)$<br>$O(N) / O(1)$ |
| **03. 单链表体系** | [01_singly_linked_list_lifecycle.c](c/03_singly_linked_list/01_singly_linked_list_lifecycle.c)<br>[02_singly_linked_list_insertions.c](c/03_singly_linked_list/02_singly_linked_list_insertions.c)<br>[03_singly_linked_list_deletions.c](c/03_singly_linked_list/03_singly_linked_list_deletions.c) | 离散内存节点、防 Use-After-Free 回收<br>头插法 $O(1)$、尾插法、二级指针修改<br>前驱节点解绑跨越、头节点与普通节点删除 | $O(N) / O(1)$<br>$O(1) / O(1)$<br>$O(N) / O(1)$ |
| **04. 双向链表** | [01_doubly_linked_list_basics.c](c/04_doubly_linked_list/01_doubly_linked_list_basics.c)<br>[02_doubly_linked_list_insertions.c](c/04_doubly_linked_list/02_doubly_linked_list_insertions.c)<br>[03_doubly_linked_list_deletions.c](c/04_doubly_linked_list/03_doubly_linked_list_deletions.c) | `prev`/`next` 双向互联、正逆双向遍历<br>4 步指针重连黄金律、空表防御<br>已知指针 $O(1)$ 极速脱钩解绑、LRU 应用 | $O(N) / O(1)$<br>$O(1) / O(1)$<br>$O(1) / O(1)$ |
| **05. 循环链表** | [01_singly_circular_linked_list.c](c/05_circular_linked_list/01_singly_circular_linked_list.c)<br>[02_doubly_circular_linked_list.c](c/05_circular_linked_list/02_doubly_circular_linked_list.c)<br>[03_josephus_problem_simulation.c](c/05_circular_linked_list/03_josephus_problem_simulation.c) | 首尾闭环判定、`do-while` 遍历与破环释放<br>对称双向环形结构、`head->prev` 直达尾节点<br>约瑟夫环报数淘汰出圈全仿真 | $O(N) / O(1)$<br>$O(1) / O(1)$<br>$O(N \cdot M) / O(N)$ |

---

### 🥞 第二篇：栈、队列与表达式解析

| 专题模块 | 核心源码与跳转链接 | 核心知识点 | 时空复杂度 |
| :--- | :--- | :--- | :---: |
| **06. 栈结构体系** | [01_array_stack.c](c/06_stack/01_array_stack.c)<br>[02_linked_stack.c](c/06_stack/02_linked_stack.c)<br>[03_parentheses_matching.c](c/06_stack/03_parentheses_matching.c) | 顺序栈 top 游标模型、上溢与下溢防御<br>链式栈头插/头删 $O(1)$、传出参数设计<br>有效括号匹配状态机 (LeetCode 20) | $O(1) / O(1)$<br>$O(1) / O(1)$<br>$O(N) / O(N)$ |
| **07. 表达式解析** | [01_postfix_evaluation.c](c/07_expression_parsing/01_postfix_evaluation.c)<br>[02_infix_to_postfix.c](c/07_expression_parsing/02_infix_to_postfix.c) | 逆波兰数值栈计算、操作数左右出栈顺序<br>Dijkstra 调度场算法、运算符优先级表 | $O(N) / O(N)$<br>$O(N) / O(N)$ |
| **08. 队列体系** | [01_circular_array_queue.c](c/08_queue/01_circular_array_queue.c)<br>[02_linked_queue.c](c/08_queue/02_linked_queue.c)<br>[03_deque_double_ended.c](c/08_queue/03_deque_double_ended.c) | 环形缓冲区破除假溢出、牺牲一单元判满<br>链式队列 front/rear 双指针、队空置空防野指针<br>双端队列 Deque (4 种操作)、工作窃取应用 | $O(1) / O(1)$<br>$O(1) / O(1)$<br>$O(1) / O(1)$ |

---

### 🌲 第三篇：树、堆与散列表

| 专题模块 | 核心源码与跳转链接 | 核心知识点 | 时空复杂度 |
| :--- | :--- | :--- | :---: |
| **09. 堆与优先队列** | [01_binary_heap_operations.c](c/09_priority_queue_and_heap/01_binary_heap_operations.c)<br>[02_priority_queue.c](c/09_priority_queue_and_heap/02_priority_queue.c) | 完全二叉树数组映射、Sift Up/Down 平衡调整<br>基于最大堆的优先队列、操作系统中断调度模拟 | $O(\log N) / O(1)$<br>$O(\log N) / O(1)$ |
| **10. 二叉树与 BST** | [01_binary_tree_traversals.c](c/10_binary_tree/01_binary_tree_traversals.c)<br>[02_binary_search_tree.c](c/10_binary_tree/02_binary_search_tree.c) | 前序/中序/后序递归遍历、后序释放整树内存<br>BST 增删查、中序严格单调递增、双孩子后继节点替换 | $O(N) / O(H)$<br>$O(\log N) / O(H)$ |
| **11. 哈希表散列** | [01_hash_table_chaining.c](c/11_hash_table/01_hash_table_chaining.c)<br>[02_hash_table_open_addressing.c](c/11_hash_table/02_hash_table_open_addressing.c) | 拉链法 Separate Chaining、djb2 经典字符串哈希<br>开放寻址线性探测、主聚集效应与墓碑标记删除 | $O(1) / O(N)$<br>$O(1) / O(1)$ |

---

### 🕸️ 第四篇：图论、查找与高级排序

| 专题模块 | 核心源码与跳转链接 | 核心知识点 | 时空复杂度 |
| :--- | :--- | :--- | :---: |
| **12. 图结构与算法** | [01_graph_adjacency_matrix.c](c/12_graph/01_graph_adjacency_matrix.c)<br>[02_graph_adjacency_list.c](c/12_graph/02_graph_adjacency_list.c)<br>[03_dijkstra_shortest_path.c](c/12_graph/03_dijkstra_shortest_path.c) | 邻接矩阵表示、DFS 递归回溯与 BFS 队列水波扩散<br>邻接表稀疏图空间优化 $O(V+E)$<br>Dijkstra 单源最短路径、贪心松弛、负权边失效剖析 | $O(V^2) / O(V)$<br>$O(V+E) / O(V+E)$<br>$O(V^2) / O(V)$ |
| **13. 查找算法** | [01_binary_search.c](c/13_search_algorithms/01_binary_search.c) | 经典二分查找、中点防溢出 `left + (right - left)/2`、双闭区间 | $O(\log N) / O(1)$ |
| **14. 高级排序算法** | [01_quick_sort.c](c/14_advanced_sorting_algorithms/01_quick_sort.c)<br>[02_merge_sort.c](c/14_advanced_sorting_algorithms/02_merge_sort.c)<br>[03_heap_sort.c](c/14_advanced_sorting_algorithms/03_heap_sort.c) | 快速排序 Lomuto 双指针分区、分治递归模型<br>归并排序对半拆解、稳定合并、辅助空间分配<br>堆排序原地建堆与极值下沉提取、原地 $O(1)$ 空间 | $O(N \log N) / O(\log N)$<br>$O(N \log N) / O(N)$<br>$O(N \log N) / O(1)$ |

---

## ⚡ 快速上手与运行指南

本项目所有 `.c` 源文件均为**自包含可运行单元**，无需任何第三方构建工具或 Makefile。

### 1. 编译并运行单文件示例
以编译运行快速排序为例：
```bash
# 编译源文件
gcc -Wall -Wextra c/14_advanced_sorting_algorithms/01_quick_sort.c -o app

# 执行生成程序
./app
```

### 2. 批量全量语法与警告校验
若需一次性检查所有章节源码的编译合规性：
```bash
gcc -Wall -Wextra -fsyntax-only c/*/*.c
```

---

## 📁 仓库结构

```text
dsa-projects/
├── c/                                 # C 语言核心数据结构与算法源码实现
│   ├── 01_complexity_analysis/        # 01. 复杂度分析与内存模型
│   ├── 02_array_and_sequence_list/    # 02. 顺序表与数组操作
│   ├── 03_singly_linked_list/         # 03. 单链表体系
│   ├── 04_doubly_linked_list/         # 04. 双向链表体系
│   ├── 05_circular_linked_list/       # 05. 循环链表与约瑟夫环
│   ├── 06_stack/                      # 06. 栈结构与括号匹配
│   ├── 07_expression_parsing/         # 07. 表达式解析与调度场
│   ├── 08_queue/                      # 08. 队列 (循环/链式/双端)
│   ├── 09_priority_queue_and_heap/    # 09. 二叉堆与优先队列
│   ├── 10_binary_tree/                # 10. 二叉树与二叉搜索树 BST
│   ├── 11_hash_table/                 # 11. 哈希表 (拉链/开放寻址)
│   ├── 12_graph/                      # 12. 图论 (BFS/DFS/Dijkstra)
│   ├── 13_search_algorithms/          # 13. 二分查找与变体
│   └── 14_advanced_sorting_algorithms/# 14. 高级排序 (快排/归并/堆排)
├── python/                            # Python 算法拓展区 (规划中)
├── .gitignore                         # Git 过滤规则 (已自动保护本地练习目录)
└── README.md                          # 体系导读与全景导航索引
```

---

## 📄 开源许可证

本项目基于 [MIT License](https://opensource.org/licenses/MIT) 开源共享，欢迎自由学习、研究与引用。
