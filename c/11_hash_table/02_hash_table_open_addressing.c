#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 7

/**
 * 💡【知识点】哈希表 —— 开放寻址法 / 线性探测 (Linear Probing)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 开放寻址机制：所有元素直接存放在连续数组槽位中。
 *   2. 线性探测：若当前哈希槽已被占用，则顺延探测下一个槽位 `(index + 1) % TABLE_SIZE`，直到找到空槽。
 * -----------------------------------------------------------------------------
 */

typedef struct Entry {
    char key[32];
    int value;
    bool occupied;
} Entry;

typedef struct OpenHashTable {
    Entry table[TABLE_SIZE];
} OpenHashTable;

void oht_init(OpenHashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) ht->table[i].occupied = false;
}

static unsigned int hash_func(const char *key) {
    unsigned int hash = 0;
    while (*key) hash = (hash * 31) + *key++;
    return hash % TABLE_SIZE;
}

bool oht_insert(OpenHashTable *ht, const char *key, int value) {
    unsigned int start_idx = hash_func(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (start_idx + i) % TABLE_SIZE;
        if (!ht->table[idx].occupied || strcmp(ht->table[idx].key, key) == 0) {
            snprintf(ht->table[idx].key, sizeof(ht->table[idx].key), "%s", key);
            ht->table[idx].value = value;
            ht->table[idx].occupied = true;
            return true;
        }
    }
    return false; // 散列表已满
}

bool oht_search(const OpenHashTable *ht, const char *key, int *out_val) {
    unsigned int start_idx = hash_func(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (start_idx + i) % TABLE_SIZE;
        if (!ht->table[idx].occupied) return false;
        if (strcmp(ht->table[idx].key, key) == 0) {
            if (out_val) *out_val = ht->table[idx].value;
            return true;
        }
    }
    return false;
}

int main(void) {
    OpenHashTable ht;
    oht_init(&ht);

    oht_insert(&ht, "Tom", 95);
    oht_insert(&ht, "Jerry", 88);
    oht_insert(&ht, "Spike", 76);

    int score;
    if (oht_search(&ht, "Jerry", &score)) {
        printf("Jerry 成绩: %d 分\n", score);
    }
    return 0;
}
