#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

/**
 * 💡【知识点】哈希表 / 散列表 (Hash Table) —— 拉链法解决冲突 (Chaining)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 哈希函数：将键 (Key 字符串) 映射为哈希槽下标 (0 ~ TABLE_SIZE - 1)。常用经典 djb2 算法。
 *   2. 冲突解决 (Chaining)：每个哈希槽维护一个单链表。当不同 Key 映射到同一槽位时，挂载到对应链表上。
 *   3. 时空复杂度：理想情况下插入、查找、删除均为常数时间 $O(1)$，最坏退化为 $O(N)$。
 * -----------------------------------------------------------------------------
 */

typedef struct HashNode {
    char key[32];
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode *buckets[TABLE_SIZE];
} HashTable;

// 经典 djb2 字符串哈希函数
static unsigned int hash_function(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

void ht_init(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) ht->buckets[i] = NULL;
}

// 插入或更新键值对
void ht_insert(HashTable *ht, const char *key, int value) {
    unsigned int index = hash_function(key);
    HashNode *curr = ht->buckets[index];

    // 检查 Key 是否已存在，存在则更新
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    // 头插法挂载新节点
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    snprintf(newNode->key, sizeof(newNode->key), "%s", key);
    newNode->value = value;
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
}

// 查找 Key
bool ht_search(const HashTable *ht, const char *key, int *out_val) {
    unsigned int index = hash_function(key);
    HashNode *curr = ht->buckets[index];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (out_val) *out_val = curr->value;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// 释放全表内存
void ht_destroy(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *curr = ht->buckets[i];
        while (curr) {
            HashNode *next = curr->next;
            free(curr);
            curr = next;
        }
        ht->buckets[i] = NULL;
    }
}

int main(void) {
    HashTable ht;
    ht_init(&ht);

    printf("=== 哈希表 (拉链法) 键值存储测试 ===\n\n");
    ht_insert(&ht, "apple", 15);
    ht_insert(&ht, "banana", 28);
    ht_insert(&ht, "orange", 32);
    ht_insert(&ht, "grape", 50);

    int val;
    if (ht_search(&ht, "banana", &val)) {
        printf("🔍 查找 \"banana\": %d 元/箱\n", val);
    }
    if (ht_search(&ht, "apple", &val)) {
        printf("🔍 查找 \"apple\":  %d 元/箱\n", val);
    }
    printf("🔍 查找 \"pear\":   %s\n", ht_search(&ht, "pear", &val) ? "找到" : "未找到");

    ht_destroy(&ht);
    return 0;
}
