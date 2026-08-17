// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <string.h>   // 字符串与内存操作库：提供 strlen(), strcpy(), strcmp(), memset() 等内存/文本处理函数
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

#define TABLE_SIZE 7 // 槽位数

/**
 * =============================================================================
 * 💡【知识点】哈希表 / 散列表 —— 开放寻址法 (Open Addressing / 线性探测)
 * =============================================================================
 * 
 * 📌【1. 什么是开放寻址法？】
 *   与拉链法不同，开放寻址法**不使用任何外挂链表**，所有的键值对都直接存放在一维数组槽位中！
 *   - 当发生哈希冲突时，按照某种探测规则去寻找下一个空闲槽位：
 *     - **线性探测 (Linear Probing)**：依次探测 `(hash + 1) % SIZE`, `(hash + 2) % SIZE`...
 *     - 直到找到空闲槽位写入，或循环一整圈确认表已满。
 * 
 * 📌【2. 线性探测冲突寻找过程图解】
 * 
 *   插入 Key="Spike"，假设 hash("Spike") = 1
 *   
 *   槽位:  [0]     [1]          [2]          [3]
 *   状态: |空 | |Tom (占用)| |Jerry (占用)| |Spike (空槽写入！)|
 *                  ▲            ▲            ▲
 *            ① hash=1冲突   ② 顺延探测冲突   ③ 探测成功入驻！
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 开放寻址法中的「主聚集效应 (Primary Clustering)」是什么？
 *      👉 解答：多个发生冲突的 Key 连续占据相邻槽位，形成长长的“连续块”。
 *         后续任何映射到该区域附近的 Key 都必须一步一步顺延跨过整个长块，导致查找效率严重下降。
 * 
 *   ❓ Q2: 开放寻址法的删除操作为什么不能简单地把 `occupied` 置为 false？
 *      👉 解答（经典墓碑机制 Tombstone）：
 *         - 如果直接把槽位清空，后续依靠线性探测跨过此槽位去查找其他元素的链条就会被“截断”！
 *         - 必须使用特殊的「已删除 / 墓碑 (Deleted)」状态标记，表示“此处曾经有数据被删，查找时需继续向后探测”。
 * =============================================================================
 */

// ==================== 1. 算法与结构实现 ====================

typedef struct Entry {
    char key[32];
    int value;
    bool occupied; // 是否被有效元素占用
} Entry;

typedef struct OpenHashTable {
    Entry table[TABLE_SIZE];
} OpenHashTable;

void oht_init(OpenHashTable *ht) {
    if (ht) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            ht->table[i].occupied = false;
        }
    }
}

static unsigned int hash_func(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (unsigned char)*key++;
    }
    return hash % TABLE_SIZE;
}

/**
 * @brief 线性探测插入或更新键值对
 * @return true 插入成功, false 散列表已全满
 */
bool oht_insert(OpenHashTable *ht, const char *key, int value) {
    if (ht == NULL || key == NULL) return false;

    unsigned int start_idx = hash_func(key);

    // 最多探测 TABLE_SIZE 轮（转满一整圈）
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (start_idx + i) % TABLE_SIZE;

        // 遇到空槽，或者遇到相同的 Key 进行更新
        if (!ht->table[idx].occupied || strcmp(ht->table[idx].key, key) == 0) {
            snprintf(ht->table[idx].key, sizeof(ht->table[idx].key), "%s", key);
            ht->table[idx].value = value;
            ht->table[idx].occupied = true;
            return true;
        }
    }

    return false; // 整个数组都被占满，无空位可插
}

/**
 * @brief 线性探测查找 Key
 * @return true 找到, false 未找到
 */
bool oht_search(const OpenHashTable *ht, const char *key, int *out_val) {
    if (ht == NULL || key == NULL) return false;

    unsigned int start_idx = hash_func(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (start_idx + i) % TABLE_SIZE;

        // 遇到未占用的纯空槽位，说明目标 Key 必定从未插入过，直接终止查找
        if (!ht->table[idx].occupied) {
            return false;
        }

        // 匹配成功
        if (strcmp(ht->table[idx].key, key) == 0) {
            if (out_val) *out_val = ht->table[idx].value;
            return true;
        }
    }

    return false;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    OpenHashTable ht;
    oht_init(&ht);

    printf("==================== 开放寻址 (线性探测) 散列表验证 ====================\n\n");
    oht_insert(&ht, "Tom", 95);
    oht_insert(&ht, "Jerry", 88);
    oht_insert(&ht, "Spike", 76);

    int score;
    if (oht_search(&ht, "Jerry", &score)) {
        printf("🔍 查找 Jerry 考试成绩: %d 分\n", score);
    }
    if (oht_search(&ht, "Tom", &score)) {
        printf("🔍 查找 Tom   考试成绩: %d 分\n", score);
    }

    return 0;
}
