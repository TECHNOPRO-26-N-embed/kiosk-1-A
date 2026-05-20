#include "purchase_service.h"
#include "ai_product_manager.h"
#include "ai_utils.h"
#include "ai_sales_logger.h"
#include <stdio.h>


void runPurchaseService(void) {
    AI_Product products[50];
    int productCount = 0;
    ai_init_products(products, &productCount);
    int admin_exit = 0;
    printf("\n==== 商品購入モード ====\n");
    while (!admin_exit) {
        printf("\n--- 新しいお客様の取引を開始します ---\n");
        int balance = 0;
        int user_running = 1;
        while (user_running) {
            printf("\n現在の残額: %d円\n", balance);
            printf("1. 商品購入\n2. お金を追加投入\n3. お釣りを受け取る(取引終了)\n4. 管理者メニューに戻る\n");
            int choice = ai_input_int("操作を選択してください: ");
            switch (choice) {
                case 1: {
                    ai_list_products(products, productCount);
                    int id = ai_input_int("商品IDを入力してください: ");
                    int idx = ai_find_product_by_id(products, productCount, id);
                    if (idx < 0) {
                        printf("無効な商品IDです。\n");
                        break;
                    }
                    if (products[idx].stock <= 0) {
                        printf("在庫切れです。\n");
                        break;
                    }
                    int qty = ai_input_int("購入個数を入力してください: ");
                    if (qty <= 0 || qty > products[idx].stock) {
                        printf("在庫数を超えています。\n");
                        break;
                    }
                    int total = products[idx].price * qty;
                    if (balance < total) {
                        printf("残額が不足しています。\n");
                        break;
                    }
                    balance -= total;
                    ai_update_stock(products, productCount, id, products[idx].stock - qty);
                    ai_log_sale(&products[idx], qty, products[idx].stock);
                    printf("%sを%d個購入しました。\n", products[idx].name, qty);
                    break;
                }
                case 2: {
                    int add = ai_input_int("追加投入金額を入力してください: ");
                    if (add > 0) {
                        balance += add;
                    } else {
                        printf("0円以上を投入してください。\n");
                    }
                    break;
                }
                case 3: {
                    printf("お釣り: %d円を返却します。\n", balance);
                    balance = 0;
                    user_running = 0; // 次のユーザーへ
                    break;
                }
                case 4: {
                    printf("管理者操作によりメインメニューに戻ります。\n");
                    admin_exit = 1;
                    user_running = 0;
                    break;
                }
                default:
                    printf("無効な選択です。\n");
                    break;
            }
        }
    }
}
