#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 10 // 顺序表最大物理容量

/**
 * =============================================================================
 * 💡【知识点】顺序表/数组 —— 元素插入 (Array/Sequence List Insertion)
 * =============================================================================
 * 
 * 📌【1. 顺序表的存储本质】
 *   顺序表是用一段「物理地址连续」的存储单元依次存储数据元素的线性结构。
 *   - 物理连续性决定了：逻辑上相邻的元素，物理内存中也紧密相邻。
 *   - 插入代价：在中间某个位置插入新元素时，必须腾出位置，因此后续所有元素必须集体向后平移。
 * 
 * 📌【2. 插入过程核心移动方向图解 (必须从后往前挪！)】
 * 
 *   假设原有数组: [10, 20, 30, 40,  _ ] (当前 size = 4，要在 index = 2 插入 99)
 *   
 *   ❌ 错误示范（从前往后移）：
 *      把 index=2(30) 移到 index=3 -> [10, 20, 30, 30, _]  (原 40 被无情覆盖丢失了！)
 *      
 *   ✅ 正确示范（从后向前移）：
 *      步骤 1: 将 index=3 (40) 移到 index=4 -> [10, 20, 30,  _, 40]
 *      步骤 2: 将 index=2 (30) 移到 index=3 -> [10, 20,  _, 30, 40]
 *      步骤 3: 在空出的 index=2 处写入 99    -> [10, 20, 99, 30, 40]
 *      步骤 4: 有效元素计数 size 从 4 增加到 5
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 插入操作的时间复杂度是多少？
 *      👉 解答：
 *         - 最好情况（尾插 index == size）：无需搬移任何元素，O(1)。
 *         - 最坏情况（头插 index == 0）：全部 N 个元素都要向后移一位，O(N)。
 *         - 平均情况：每个位置插入概率均等，平均移动 N/2 个元素，综合时间复杂度为 O(N)。
 * 
 *   ❓ Q2: 插入时允许 `index == *size` 吗？
 *      👉 解答：允许！当 `index == *size` 时，就是标准的「尾插法」，此时循环不执行，直接将新值写入末尾。
 * =============================================================================
 */

// ==================== 1. 插入算法实现 ====================

/**
 * @brief 在顺序表指定下标处插入新元素
 * 
 * @param arr      数组指针（退化为 int*）
 * @param size     当前有效元素个数的指针（传指针以便修改外部变量）
 * @param capacity 数组最大允许容量
 * @param index    目标插入下标 (合法范围: 0 <= index <= *size)
 * @param value    待插入的新数据
 * @return true 插入成功, false 插入失败 (容量已满或下标越界)
 * 
 * @note 时间复杂度: 最好 O(1)，最坏 O(N)，平均 O(N)
 * @note 空间复杂度: O(1) —— 原地搬移，仅需常数辅助变量
 */
bool seq_list_insert(int arr[], int *size, int capacity, int index, int value) {
    // 【步骤 1】防御性校验：
    //  ① 检查指针有效性
    //  ② 检查当前数组是否已满 (size >= capacity)
    //  ③ 检查插入下标是否越界 (不能小于 0，也不能大于当前有效长度 size)
    if (arr == NULL || size == NULL || *size >= capacity || index < 0 || index > *size) {
        printf("⚠️ [插入失败] 空间已满或插入下标 %d 非法！\n", index);
        return false;
    }

    // 【步骤 2】元素后移腾位（必须从后往前遍历！）
    // 从当前最后一个元素 (下标 *size - 1) 开始，依次赋值到后一个槽位 (i)
    for (int i = *size; i > index; i--) {
        arr[i] = arr[i - 1]; // 将前一个元素挪到当前位置
    }

    // 【步骤 3】在腾出的目标下标处写入新值
    arr[index] = value;

    // 【步骤 4】有效元素计数加 1
    (*size)++;

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
    int arr[CAPACITY] = {10, 20, 30, 40};
    int size = 4; // 当前有效元素为 4 个

    printf("==================== 顺序表插入算法验证 ====================\n");
    printf("【初始状态】\n");
    seq_list_print(arr, size);

    // 测试 1: 中间插入
    printf("\n【测试 1】在下标 index = 2 处插入元素 99...\n");
    seq_list_insert(arr, &size, CAPACITY, 2, 99);
    seq_list_print(arr, size);

    // 测试 2: 头部插入 (最坏情况 O(N))
    printf("\n【测试 2】在头部 index = 0 处插入元素 5...\n");
    seq_list_insert(arr, &size, CAPACITY, 0, 5);
    seq_list_print(arr, size);

    // 测试 3: 尾部插入 (最好情况 O(1))
    printf("\n【测试 3】在尾部 index = %d 处插入元素 100...\n", size);
    seq_list_insert(arr, &size, CAPACITY, size, 100);
    seq_list_print(arr, size);

    return 0;
}
