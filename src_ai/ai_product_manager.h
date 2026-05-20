#pragma once

// 商品情報構造体
typedef struct {
    int id;
    char name[32];
    int price;
    int stock;
} AI_Product;

// 商品管理関数
void ai_init_products(AI_Product* products, int* count);
int ai_find_product_by_id(const AI_Product* products, int count, int id);
void ai_update_stock(AI_Product* products, int count, int id, int new_stock);
void ai_list_products(const AI_Product* products, int count);
