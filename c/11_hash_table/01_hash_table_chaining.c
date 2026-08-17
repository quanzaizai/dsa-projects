#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10 // 哈希桶数组槽位大小

/**
 * =============================================================================
 * 💡【知识点】哈希表 / 散列表 (Hash Table) —— 拉链法解决冲突 (Separate Chaining)
 * =============================================================================
 * 
 * 📌【1. 哈希表的核心思想】
 *   哈希表通过「哈希函数」将任意长度的键 (Key) 计算为一个固定范围的整数索引（哈希值）。
 *   - 理想状态：每个 Key 独占一个槽位，增删查改均为严苛的 **O(1)** 常数时间！
 *   - 哈希冲突 (Hash Collision)：当不同的 Key 计算出了相同的槽位下标时，必须有冲突解决机制。
 * 
 * 📌【2. 拉链法 (Chaining) 内存模型图解】
 * 
 *   [Buckets 桶数组]
 *   [0] -> NULL
 *   [1] -> ["apple": 15] -> ["grape": 50] -> NULL  <--- 发生了哈希冲突，以单链表形式挂载！
 *   [2] -> NULL
 *   [3] -> ["banana": 28] -> NULL
 *   ...
 *   [9] -> ["orange": 32] -> NULL
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: djb2 哈希算法中的魔数 5381 和 33 是什么来头？
 *      👉 解答：由 Daniel J. Bernstein 发明的经典字符串哈希算法。
 *         - 5381 是一个神奇的奇素数。
 *         - `hash * 33 + c` 可以通过位运算 `((hash << 5) + hash) + c` 极速完成，
 *           在保证计算极快的同时，能产生极其均匀的雪崩散列分布，大幅降低冲突概率。
 * 
 *   ❓ Q2: 什么是负载因子 (Load Factor)？
 *      👉 解答：$\alpha = \text{元素总数} / \text{桶总数}$。
 *         - 当 $\alpha > 0.75$ 时，链表变长，查找性能退化。工业级哈希表通常会自动触发 **2 倍扩容 (Rehash)**。
 * =============================================================================
 */

// ==================== 1. 结构定义与算法实现 ====================

typedef struct HashNode {
    char key[32];           // 字符串键 (Key)
    int value;              // 存储的数值 (Value)
    struct HashNode *next;  // 冲突链表指针域
} HashNode;

typedef struct HashTable {
    HashNode *buckets[TABLE_SIZE]; // 哈希桶指针数组
} HashTable;

/**
 * @brief 经典工业级 djb2 字符串哈希函数
 */
static unsigned int hash_function(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // 即 hash * 33 + c
    }
    return (unsigned int)(hash % TABLE_SIZE);
}

/**
 * @brief 初始化哈希表（所有桶置空）
 */
void ht_init(HashTable *ht) {
    if (ht) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            ht->buckets[i] = NULL;
        }
    }
}

/**
 * @brief 插入或更新键值对 (Insert or Update)
 * 
 * @note 时间复杂度: 平均 O(1)，最坏 O(N)
 */
void ht_insert(HashTable *ht, const char *key, int value) {
    if (ht == NULL || key == NULL) return;

    // 【步骤 1】通过哈希函数计算目标槽位索引
    unsigned int index = hash_function(key);

    // 【步骤 2】在对应的链表中查找是否已存在相同 Key
    HashNode *curr = ht->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            // Key 已存在，直接更新其 Value 并退出
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    // 【步骤 3】Key 不存在，采用「头插法」将新节点插入到当前桶链表最前端
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    if (!newNode) return;
    
    snprintf(newNode->key, sizeof(newNode->key), "%s", key);
    newNode->value = value;
    
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
}

/**
 * @brief 根据 Key 查找 Value
 * 
 * @return true 找到, false 未找到
 * @note 时间复杂度: 平均 O(1)
 */
bool ht_search(const HashTable *ht, const char *key, int *out_val) {
    if (ht == NULL || key == NULL) return false;

    // 计算槽位
    unsigned int index = hash_function(key);

    // 在对应单链表中遍历比对字符串
    HashNode *curr = ht->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (out_val) *out_val = curr->value;
            return true; // 命中！
        }
        curr = curr->next;
    }

    return false; // 未找到
}

/**
 * @brief 销毁哈希表，释放所有桶中全部链表节点的堆内存
 */
void ht_destroy(HashTable *ht) {
    if (ht == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *curr = ht->buckets[i];
        while (curr != NULL) {
            HashNode *next = curr->next;
            free(curr);
            curr = next;
        }
        ht->buckets[i] = NULL;
    }
    printf("🧹 [销毁] 哈希表所有拉链节点内存已安全释放\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    HashTable ht;
    ht_init(&ht);

    printf("==================== 哈希表 (拉链法) 键值存储验证 ====================\n\n");
    ht_insert(&ht, "apple", 15);
    ht_insert(&ht, "banana", 28);
    ht_insert(&ht, "orange", 32);
    ht_insert(&ht, "grape", 50);

    // 查找测试
    int val;
    if (ht_search(&ht, "banana", &val)) {
        printf("🔍 查找 \"banana\": %d 元/箱\n", val);
    }
    if (ht_search(&ht, "apple", &val)) {
        printf("🔍 查找 \"apple\":  %d 元/箱\n", val);
    }
    printf("🔍 查找 \"pear\":   %s\n", ht_search(&ht, "pear", &val) ? "找到" : "❌ 未找到 (未录入)");

    ht_destroy(&ht);
    return 0;
}
