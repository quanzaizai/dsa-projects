# Data Structures and Algorithms (数据结构与算法实战体系)

本项目为经典数据结构与算法的工业级实现与教学级实战练习库。全库代码采用**标准纯英文命名**，并在每个源文件中配备**黄金教学级注释（带 Emoji 结构化卡片与行级深度剖析）**。

下方提供**全景章节大纲与中文知识点导读索引**。

---

## 📂 目录结构与模块规划

```text
dsa-projects/
├── c/                                 # C 语言核心数据结构与经典算法体系
│   ├── 01_complexity_analysis/        # 01. 复杂度分析与内存模型
│   ├── 02_array_and_sequence_list/    # 02. 顺序表与数组核心操作
│   ├── 03_singly_linked_list/         # 03. 单链表全生命周期
│   ├── 04_doubly_linked_list/         # 04. 双向链表与双向互联
│   ├── 05_circular_linked_list/       # 05. 循环链表与约瑟夫环
│   ├── 06_stack/                      # 06. 栈结构与括号匹配实战
│   ├── 07_expression_parsing/         # 07. 后缀表达式与调度场转换
│   ├── 08_queue/                      # 08. 循环队列、链式队列与双端队列
│   ├── 09_priority_queue_and_heap/    # 09. 二叉堆与优先队列调度
│   ├── 10_binary_tree/                # 10. 二叉树四大遍历与二叉搜索树 BST
│   ├── 11_hash_table/                 # 11. 哈希表 (拉链法与开放寻址法)
│   ├── 12_graph/                      # 12. 图结构 (BFS/DFS 与 Dijkstra 最短路)
│   ├── 13_search_algorithms/          # 13. 经典二分查找与边界判定
│   └── 14_advanced_sorting_algorithms/# 14. 快速排序、归并排序与堆排序
├── practice_c/                        # 实战手撕算法空间
├── python/                            # Python 算法拓展空间 (预留)
└── README.md                          # 课程大纲与中文导读索引
```

---

## 📚 全景中文知识点索引表 (`c/`)

### 01. 复杂度分析与内存度量 (`01_complexity_analysis/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_time_complexity_linear.c` | **线性时间复杂度** | $O(N) / O(1)$ | 单层循环累加、数组作为形参退化为指针的原因剖析 | `gcc c/01_complexity_analysis/01_time_complexity_linear.c -o app && ./app` |
| `02_time_complexity_nested.c` | **平方阶时间复杂度** | $O(N^2) / O(1)$ | 嵌套双循环比对矩阵/网格遍历分析 | `gcc c/01_complexity_analysis/02_time_complexity_nested.c -o app && ./app` |
| `03_space_complexity_dynamic.c` | **线性空间复杂度** | $O(N) / O(N)$ | `malloc` 动态堆内存数组申请与全生命周期回收 | `gcc c/01_complexity_analysis/03_space_complexity_dynamic.c -o app && ./app` |

---

### 02. 顺序表与数组 (`02_array_and_sequence_list/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_seq_list_insertion.c` | **顺序表插入元素** | $O(N) / O(1)$ | 边界检查、元素后移腾出空位、容量与长度维护 | `gcc c/02_array_and_sequence_list/01_seq_list_insertion.c -o app && ./app` |
| `02_seq_list_deletion.c` | **顺序表删除元素** | $O(N) / O(1)$ | 下标有效性校验、元素前移覆盖与长度扣减 | `gcc c/02_array_and_sequence_list/02_seq_list_deletion.c -o app && ./app` |
| `03_linear_search.c` | **顺序表线性查找** | $O(N) / O(1)$ | 遍历比对目标值、返回匹配下标或哨兵 `-1` | `gcc c/02_array_and_sequence_list/03_linear_search.c -o app && ./app` |

---

### 03. 单链表 (`03_singly_linked_list/`)
| 源文件 | 中文知识点 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- |
| `01_singly_linked_list_lifecycle.c` | **单链表创建与销毁** | 节点结构体定义、动态内存创建、遍历打印与全链表 `free` 闭环 | `gcc c/03_singly_linked_list/01_singly_linked_list_lifecycle.c -o app && ./app` |
| `02_singly_linked_list_insertions.c` | **单链表三大插入操作** | 头部插入 $O(1)$、尾部插入 $O(N)$ 与指定位置后插入核心指针重定向 | `gcc c/03_singly_linked_list/02_singly_linked_list_insertions.c -o app && ./app` |
| `03_singly_linked_list_deletions.c` | **单链表核心删除操作** | 头部节点删除、按值删除、前后驱指针防断链处理 | `gcc c/03_singly_linked_list/03_singly_linked_list_deletions.c -o app && ./app` |

---

### 04. 双向链表 (`04_doubly_linked_list/`)
| 源文件 | 中文知识点 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- |
| `01_doubly_linked_list_basics.c` | **双向链表构建与遍历** | `prev` 和 `next` 双向指针结构、正向与逆向遍历 | `gcc c/04_doubly_linked_list/01_doubly_linked_list_basics.c -o app && ./app` |
| `02_doubly_linked_list_insertions.c` | **双向链表插入操作** | 双向 4 步黄金指针重连律、头尾与中间插入 | `gcc c/04_doubly_linked_list/02_doubly_linked_list_insertions.c -o app && ./app` |
| `03_doubly_linked_list_deletions.c` | **双向链表解绑与删除** | 局部 $O(1)$ 节点解绑、前后指针跨越连接与内存释放 | `gcc c/04_doubly_linked_list/03_doubly_linked_list_deletions.c -o app && ./app` |

---

### 05. 循环链表与经典算法 (`05_circular_linked_list/`)
| 源文件 | 中文知识点 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- |
| `01_singly_circular_linked_list.c` | **单向循环链表** | 尾节点指向头节点的闭环条件与 `do-while` 循环遍历 | `gcc c/05_circular_linked_list/01_singly_circular_linked_list.c -o app && ./app` |
| `02_doubly_circular_linked_list.c` | **双向循环链表** | 对称双向闭环结构、$O(1)$ 实现首尾互访 | `gcc c/05_circular_linked_list/02_doubly_circular_linked_list.c -o app && ./app` |
| `03_josephus_problem_simulation.c` | **约瑟夫环经典问题** | 循环链表模拟淘汰出圈算法、节点解绑与环缩容 | `gcc c/05_circular_linked_list/03_josephus_problem_simulation.c -o app && ./app` |

---

### 06. 栈结构与实战算法 (`06_stack/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_array_stack.c` | **顺序栈 (数组实现)** | $O(1) / O(1)$ | 栈顶指针 `top` 维护、入栈 `++top` 与出栈 `top--`、溢出与下溢防御 | `gcc c/06_stack/01_array_stack.c -o app && ./app` |
| `02_linked_stack.c` | **链式栈 (链表实现)** | $O(1) / O(1)$ | 头插法入栈与头删法出栈、动态扩容、全栈内存安全销毁 `destroy` | `gcc c/06_stack/02_linked_stack.c -o app && ./app` |
| `03_parentheses_matching.c` | **有效括号匹配算法** | $O(N) / O(N)$ | LeetCode 20 经典题、字符辅助栈、成对匹配消除与最终空栈判定 | `gcc c/06_stack/03_parentheses_matching.c -o app && ./app` |

---

### 07. 表达式解析 (`07_expression_parsing/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_postfix_evaluation.c` | **逆波兰 / 后缀表达式求值** | $O(N) / O(N)$ | 辅助数值栈、数字压栈、遇到运算符弹出两操作数计算后压回 | `gcc c/07_expression_parsing/01_postfix_evaluation.c -o app && ./app` |
| `02_infix_to_postfix.c` | **中缀转后缀 (调度场算法)** | $O(N) / O(N)$ | 运算符栈调度、优先级比对出栈输出、括号匹配消除 | `gcc c/07_expression_parsing/02_infix_to_postfix.c -o app && ./app` |

---

### 08. 队列体系 (`08_queue/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_circular_array_queue.c` | **循环队列 (顺序环形缓冲)** | $O(1) / O(1)$ | 取模运算处理下标绕回、牺牲 1 单元区分队空与队满 | `gcc c/08_queue/01_circular_array_queue.c -o app && ./app` |
| `02_linked_queue.c` | **链式队列 (单链表实现)** | $O(1) / O(1)$ | `front`/`rear` 双指针维护、头删尾插、全生命周期销毁 | `gcc c/08_queue/02_linked_queue.c -o app && ./app` |
| `03_deque_double_ended.c` | **双端队列 (Deque)** | $O(1) / O(1)$ | 双向链表实现两端皆可 $O(1)$ 出入队、滑动窗口最大值基础 | `gcc c/08_queue/03_deque_double_ended.c -o app && ./app` |

---

### 09. 优先队列与二叉堆 (`09_priority_queue_and_heap/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_binary_heap_operations.c` | **最大堆底层实现** | $O(\log N) / O(1)$ | 完全二叉树数组映射、上浮 `sift_up` 与下沉 `sift_down` | `gcc c/09_priority_queue_and_heap/01_binary_heap_operations.c -o app && ./app` |
| `02_priority_queue.c` | **基于堆的优先队列** | $O(\log N) / O(1)$ | 优先级调度、系统任务抢占与最高优先级快速弹出 | `gcc c/09_priority_queue_and_heap/02_priority_queue.c -o app && ./app` |

---

### 10. 二叉树体系 (`10_binary_tree/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_binary_tree_traversals.c` | **二叉树三大递归遍历** | $O(N) / O(H)$ | 前序 (根左右)、中序 (左根右)、后序 (左右根) 与后序内存安全释放 | `gcc c/10_binary_tree/01_binary_tree_traversals.c -o app && ./app` |
| `02_binary_search_tree.c` | **二叉搜索树 (BST) 增删查** | $O(\log N) / O(H)$ | 左小右大二分决策、中序自动有序、双孩子节点后继替换删除 | `gcc c/10_binary_tree/02_binary_search_tree.c -o app && ./app` |

---

### 11. 哈希表 (`11_hash_table/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_hash_table_chaining.c` | **哈希表 (拉链法)** | $O(1) / O(N)$ | djb2 哈希函数、哈希槽单链表挂载冲突项、动态全表销毁 | `gcc c/11_hash_table/01_hash_table_chaining.c -o app && ./app` |
| `02_hash_table_open_addressing.c` | **哈希表 (开放寻址/线性探测)** | $O(1) / O(1)$ | 连续数组槽位存储、发生冲突顺延探测下一个空槽 | `gcc c/11_hash_table/02_hash_table_open_addressing.c -o app && ./app` |

---

### 12. 图结构与算法 (`12_graph/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_graph_adjacency_matrix.c` | **邻接矩阵与 BFS / DFS** | $O(V^2) / O(V)$ | 二维矩阵存储、递归深度优先 DFS 与辅助队列广度优先 BFS | `gcc c/12_graph/01_graph_adjacency_matrix.c -o app && ./app` |
| `02_graph_adjacency_list.c` | **邻接表表示法** | $O(V+E) / O(V+E)$ | 稀疏图空间优化、链表头插法存储邻接顶点 | `gcc c/12_graph/02_graph_adjacency_list.c -o app && ./app` |
| `03_dijkstra_shortest_path.c` | **Dijkstra 单源最短路径** | $O(V^2) / O(V)$ | 贪心策略、松弛操作 `dist[u] + w < dist[v]` 逐步收敛最短距离 | `gcc c/12_graph/03_dijkstra_shortest_path.c -o app && ./app` |

---

### 13. 查找算法 (`13_search_algorithms/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_binary_search.c` | **二分查找 (折半查找)** | $O(\log N) / O(1)$ | 有序前提、中点防溢出计算 `left + (right - left) / 2` | `gcc c/13_search_algorithms/01_binary_search.c -o app && ./app` |

---

### 14. 高级排序算法 (`14_advanced_sorting_algorithms/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_quick_sort.c` | **快速排序 (Quick Sort)** | $O(N \log N) / O(\log N)$ | 分治思想、基准值选取与双向双指针分区 `partition` | `gcc c/14_advanced_sorting_algorithms/01_quick_sort.c -o app && ./app` |
| `02_merge_sort.c` | **归并排序 (Merge Sort)** | $O(N \log N) / O(N)$ | 分治对半拆解、稳定排序、辅助数组双指针有序归并 | `gcc c/14_advanced_sorting_algorithms/02_merge_sort.c -o app && ./app` |
| `03_heap_sort.c` | **堆排序 (Heap Sort)** | $O(N \log N) / O(1)$ | 原地构建最大堆、堆顶与末尾交换下沉、原地 $O(1)$ 空间 | `gcc c/14_advanced_sorting_algorithms/03_heap_sort.c -o app && ./app` |
