#include "admin_service.h"
#include "ai_utils.h"
#include "ai_product_manager.h"
#include "ai_sales_logger.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define ADMIN_PASS "admin123"

void showAdminMenu(void) {
    printf("==== 管理者メニュー ====\n");
    printf("1. 在庫管理\n2. 売上確認\n3. ログ閲覧\n4. メインメニューに戻る\n");
}

void manageStock(void) {
    AI_Product products[50];
    int productCount = 0;
    ai_init_products(products, &productCount);
    ai_list_products(products, productCount);
    int id = ai_input_int("在庫を変更する商品IDを入力してください: ");
    int idx = ai_find_product_by_id(products, productCount, id);
    if (idx < 0) {
        printf("無効な商品IDです。\n");
        return;
    }
    int newStock = ai_input_int("新しい在庫数を入力してください: ");
    ai_update_stock(products, productCount, id, newStock);
    printf("在庫を更新しました。\n");
}

void viewSales(void) {
    // まず確実に開けるよう通常の読み取りモードを使用
    FILE* fp = fopen("src_ai/sales_ai.csv", "r");
    if (!fp) {
        perror("売上履歴ファイルを開けませんでした");
        return;
    }
    char line[256];
    printf("==== 売上履歴 ====\n");
    while (fgets(line, sizeof(line), fp)) {
#ifdef _WIN32
        int wlen = MultiByteToWideChar(CP_UTF8, 0, line, -1, NULL, 0);
        if (wlen > 0) {
            wchar_t wbuf[256];
            if (wlen <= (int)(sizeof(wbuf) / sizeof(wbuf[0]))) {
                MultiByteToWideChar(CP_UTF8, 0, line, -1, wbuf, wlen);
                int slen = WideCharToMultiByte(932, 0, wbuf, -1, NULL, 0, NULL, NULL);
                if (slen > 0) {
                    char sbuf[256 * 2];
                    if (slen <= (int)sizeof(sbuf)) {
                        WideCharToMultiByte(932, 0, wbuf, -1, sbuf, slen, NULL, NULL);
                        printf("%s", sbuf);
                        continue;
                    }
                }
            }
        }
#endif
        printf("%s", line);
    }
    fclose(fp);
}

void viewLogs(void) {
    FILE* fp = fopen("src_ai/operation_log_ai.csv", "r");
    if (!fp) {
        printf("操作ログファイルを開けませんでした。\n");
        return;
    }
    char line[256];
    printf("==== 操作ログ ====\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

void runAdminService(void) {
    char pass[32];
    printf("パスワードを入力してください: ");
    scanf("%31s", pass);
    ai_clear_stdin();
    if (strcmp(pass, ADMIN_PASS) != 0) {
        printf("パスワードが違います。\n");
        return;
    }
    int running = 1;
    while (running) {
        showAdminMenu();
        int choice = ai_input_int("管理者メニュー番号を入力: ");
        switch (choice) {
            case 1:
                manageStock();
                break;
            case 2:
                viewSales();
                break;
            case 3:
                viewLogs();
                break;
            case 4:
                running = 0;
                break;
            default:
                printf("無効な入力です。\n");
                break;
        }
    }
}
