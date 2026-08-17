// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

/**
 * =============================================================================
 * 💡【知识点】顺序表/数组 —— 元素删除 (Array/Sequence List Deletion)
 * =============================================================================
 * 
 * 📌【1. 顺序表删除的本质】
 *   由于数组物理内存是紧凑连续的，删除某个下标 index 处的元素，不能像链表那样直接修改指针，
 *   而是必须通过「后续元素集体向前覆盖平移」来填补被删除元素留下的空缺。
 * 
 * 📌【2. 删除过程核心覆盖方向图解 (必须从前往后移！)】
 * 
 *   假设原有数组: [10, 20, 99, 30, 40] (当前 size = 5，要删除 index = 2 处的 99)
 *   
 *   步骤 1: 用 index=3 (30) 覆盖 index=2 (99)  -> [10, 20, 30, 30, 40]
 *   步骤 2: 用 index=4 (40) 覆盖 index=3 (30)  -> [10, 20, 30, 40, 40]
 *   步骤 3: 将逻辑有效长度 size 从 5 减为 4    -> [10, 20, 30, 40 | (40已失效)]
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 末尾遗留的那个数据（上图的40）需要特意清零吗？
 *      👉 解答：不需要！
 *         - 顺序表的有效数据范围完全由 `size` 控制，访问和遍历只会读取 `0` 到 `size-1` 的数据。
 *         - 超过 `size-1` 的内存虽然有旧残留值，但会被下一次插入操作直接覆盖，无需耗费 CPU 时间清零。
 * 
 *   ❓ Q2: 删除操作的时间复杂度是多少？
 *      👉 解答：
 *         - 最好情况（尾删 index == size - 1）：无需搬移任何数据，直接 `size--`，O(1)。
 *         - 最坏情况（头删 index == 0）：后方 N-1 个元素全部前移一位，O(N)。
 *         - 平均情况：综合时间复杂度为 O(N)。
 * =============================================================================
 */

// ==================== 1. 删除算法实现 ====================

/**
 * @brief 删除顺序表指定下标处的元素
 * 
 * @param arr      数组指针
 * @param size     当前有效元素个数的指针
 * @param index    待删除元素的下标 (合法范围: 0 <= index < *size)
 * @param out_val  用于接收被删除元素值的传出指针（若不关心可传 NULL）
 * @return true 删除成功, false 删除失败 (下标越界或表空)
 * 
 * @note 时间复杂度: 最好 O(1)，最坏 O(N)，平均 O(N)
 * @note 空间复杂度: O(1)
 */
bool seq_list_delete_at(int arr[], int *size, int index, int *out_val) {
    // 【步骤 1】防御性校验：
    //  ① 指针不能为空
    //  ② 检查下标是否越界 (注意: index 必须严格小于当前长度 *size)
    if (arr == NULL || size == NULL || index < 0 || index >= *size) {
        printf("⚠️ [删除失败] 顺序表为空或删除下标 %d 超出有效范围！\n", index);
        return false;
    }

    // 【步骤 2】若调用者需要，传出被删除的元素值
    if (out_val != NULL) {
        *out_val = arr[index];
    }

    // 【步骤 3】后续元素依次向前平移覆盖（从 index 开始到末尾前一位）
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1]; // 后一个元素往前覆盖
    }

    // 【步骤 4】有效长度自减 1
    (*size)--;

    return true;
}

/**
 * @brief 格式化打印顺序表内容
 */
void seq_list_print(const int arr[], int size) {
    printf("顺序表当前元素 (%d 个): [ ", size);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf(" ]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int arr[] = {10, 20, 99, 30, 40};
    int size = 5;

    printf("==================== 顺序表删除算法验证 ====================\n");
    printf("【初始状态】\n");
    seq_list_print(arr, size);

    // 测试 1: 中间删除
    int deleted_val;
    printf("\n【测试 1】删除下标 index = 2 (值为 99) 的元素...\n");
    seq_list_delete_at(arr, &size, 2, &deleted_val);
    printf("已成功剔除元素: %d\n", deleted_val);
    seq_list_print(arr, size);

    // 测试 2: 头部删除 (最坏情况 O(N))
    printf("\n【测试 2】删除表头 index = 0 (值为 10) 的元素...\n");
    seq_list_delete_at(arr, &size, 0, &deleted_val);
    printf("已成功剔除元素: %d\n", deleted_val);
    seq_list_print(arr, size);

    // 测试 3: 尾部删除 (最好情况 O(1))
    printf("\n【测试 3】删除表尾 index = %d (值为 40) 的元素...\n", size - 1);
    seq_list_delete_at(arr, &size, size - 1, &deleted_val);
    printf("已成功剔除元素: %d\n", deleted_val);
    seq_list_print(arr, size);

    return 0;
}
