#include "purchase_service.h"
#include "ai_product_manager.h"
#include "ai_utils.h"
#include "ai_sales_logger.h"
#include <stdio.h>

void runPurchaseService(void) {
    AI_Product products[50];
    int productCount = 0;
    ai_init_products(products, &productCount);
    ai_list_products(products, productCount);
    int id = ai_input_int("商品IDを入力してください: ");
    int idx = ai_find_product_by_id(products, productCount, id);
    if (idx < 0) {
        printf("無効な商品IDです。\n");
        return;
    }
    if (products[idx].stock <= 0) {
        printf("在庫切れです。\n");
        return;
    }
    int qty = ai_input_int("購入個数を入力してください: ");
    if (qty <= 0 || qty > products[idx].stock) {
        printf("在庫数を超えています。\n");
        return;
    }
    int total = products[idx].price * qty;
    int money = ai_input_int("投入金額を入力してください: ");
    if (money < total) {
        printf("金額が不足しています。\n");
        return;
    }
    int change = money - total;
    printf("お釣り: %d円\n", change);
    ai_update_stock(products, productCount, id, products[idx].stock - qty);
    ai_log_sale(&products[idx], qty, products[idx].stock);
    printf("%sを%d個購入しました。\n", products[idx].name, qty);
}
