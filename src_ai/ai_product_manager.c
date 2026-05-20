#include "ai_product_manager.h"
#include <stdio.h>
#include <string.h>

void ai_init_products(AI_Product* products, int* count) {
    // 仮の商品初期化（例）
    *count = 3;
    products[0] = (AI_Product){1, "コーラ", 120, 25};
    products[1] = (AI_Product){2, "緑茶", 110, 30};
    products[2] = (AI_Product){3, "コーヒー", 130, 20};
}

int ai_find_product_by_id(const AI_Product* products, int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (products[i].id == id) return i;
    }
    return -1;
}

void ai_update_stock(AI_Product* products, int count, int id, int new_stock) {
    int idx = ai_find_product_by_id(products, count, id);
    if (idx >= 0) {
        products[idx].stock = new_stock;
    }
}

void ai_list_products(const AI_Product* products, int count) {
    printf("ID\t商品名\t価格\t在庫\n");
    for (int i = 0; i < count; ++i) {
        printf("%d\t%s\t%d\t%d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
    }
}
