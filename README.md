# Data Structures and Algorithms (数据结构与算法实战)

本项目为经典数据结构与算法的实现与实战练习合集。全库代码采用**标准纯英文命名**，并在下方提供**全景中文导读与知识点索引**。

---

## 📂 目录结构与模块规划

```text
dsa-projects/
├── c/                      # 1. C 语言基础数据结构核心实现
│   ├── 01_complexity_analysis/
│   ├── 02_array_and_sequence_list/
│   ├── 03_singly_linked_list/
│   ├── 04_doubly_linked_list/
│   └── 05_circular_linked_list/
├── practice_c/             # 2. 独立实战闯关空间 (面向边界测试与手撕算法)
├── python/                 # 3. Python 算法与刷题实现 (预留)
└── README.md               # 算法大纲与中文导读索引
```

---

## 📚 C 语言数据结构中文导读索引 (`c/`)

### 01. 复杂度分析与内存度量 (`c/01_complexity_analysis/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_time_complexity_linear.c` | **线性时间复杂度** | $O(N) / O(1)$ | 单层循环累加、数组作为形参退化为指针的原因剖析 | `gcc c/01_complexity_analysis/01_time_complexity_linear.c -o app && ./app` |
| `02_time_complexity_nested.c` | **平方阶时间复杂度** | $O(N^2) / O(1)$ | 嵌套双循环比对矩阵/网格遍历分析 | `gcc c/01_complexity_analysis/02_time_complexity_nested.c -o app && ./app` |
| `03_space_complexity_dynamic.c` | **线性空间复杂度** | $O(N) / O(N)$ | `malloc` 动态堆内存数组申请与全生命周期回收 | `gcc c/01_complexity_analysis/03_space_complexity_dynamic.c -o app && ./app` |

---

### 02. 顺序表与数组 (`c/02_array_and_sequence_list/`)
| 源文件 | 中文知识点 | 时空复杂度 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- | :--- |
| `01_seq_list_insertion.c` | **顺序表插入元素** | $O(N) / O(1)$ | 边界检查、元素后移腾出空位、容量与长度维护 | `gcc c/02_array_and_sequence_list/01_seq_list_insertion.c -o app && ./app` |
| `02_seq_list_deletion.c` | **顺序表删除元素** | $O(N) / O(1)$ | 下标有效性校验、元素前移覆盖与长度扣减 | `gcc c/02_array_and_sequence_list/02_seq_list_deletion.c -o app && ./app` |
| `03_linear_search.c` | **顺序表线性查找** | $O(N) / O(1)$ | 遍历比对目标值、返回匹配下标或哨兵 `-1` | `gcc c/02_array_and_sequence_list/03_linear_search.c -o app && ./app` |

---

### 03. 单链表 (`c/03_singly_linked_list/`)
| 源文件 | 中文知识点 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- |
| `01_singly_linked_list_lifecycle.c` | **单链表创建与销毁** | 节点结构体定义、动态内存创建、遍历打印与全链表 `free` 闭环 | `gcc c/03_singly_linked_list/01_singly_linked_list_lifecycle.c -o app && ./app` |
| `02_singly_linked_list_insertions.c` | **单链表三大插入操作** | 头部插入 $O(1)$、尾部插入 $O(N)$ 与指定位置后插入核心指针重定向 | `gcc c/03_singly_linked_list/02_singly_linked_list_insertions.c -o app && ./app` |
| `03_singly_linked_list_deletions.c` | **单链表核心删除操作** | 头部节点删除、按值删除、前后驱指针防断链处理 | `gcc c/03_singly_linked_list/03_singly_linked_list_deletions.c -o app && ./app` |

---

### 04. 双向链表 (`c/04_doubly_linked_list/`)
| 源文件 | 中文知识点 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- |
| `01_doubly_linked_list_basics.c` | **双向链表构建与遍历** | `prev` 和 `next` 双向指针结构、正向与逆向遍历 | `gcc c/04_doubly_linked_list/01_doubly_linked_list_basics.c -o app && ./app` |
| `02_doubly_linked_list_insertions.c` | **双向链表插入操作** | 双向 4 步黄金指针重连律、头尾与中间插入 | `gcc c/04_doubly_linked_list/02_doubly_linked_list_insertions.c -o app && ./app` |
| `03_doubly_linked_list_deletions.c` | **双向链表解绑与删除** | 局部 $O(1)$ 节点解绑、前后指针跨越连接与内存释放 | `gcc c/04_doubly_linked_list/03_doubly_linked_list_deletions.c -o app && ./app` |

---

### 05. 循环链表与经典算法 (`c/05_circular_linked_list/`)
| 源文件 | 中文知识点 | 核心考点与底层原理 | 编译运行命令 |
| :--- | :--- | :--- | :--- |
| `01_singly_circular_linked_list.c` | **单向循环链表** | 尾节点指向头节点的闭环条件与 `do-while` 循环遍历 | `gcc c/05_circular_linked_list/01_singly_circular_linked_list.c -o app && ./app` |
| `02_doubly_circular_linked_list.c` | **双向循环链表** | 对称双向闭环结构、$O(1)$ 实现首尾互访 | `gcc c/05_circular_linked_list/02_doubly_circular_linked_list.c -o app && ./app` |
| `03_josephus_problem_simulation.c` | **约瑟夫环经典问题** | 循环链表模拟淘汰出圈算法、节点解绑与环缩容 | `gcc c/05_circular_linked_list/03_josephus_problem_simulation.c -o app && ./app` |
