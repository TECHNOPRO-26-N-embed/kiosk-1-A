#include <stdio.h>
#include "constants.h"

int loop(struct VendingMachine *vm) {

    while (1) {

        // 商品IDの入力
        int scanNum;
        printf("商品IDを入力してください (%d-%d)(終了するには%dを入力): ", MIN_PRODUCT_ID, MAX_PRODUCT_ID, EXITCODE);
        scanf("%d", &scanNum);
        if(scanNum == EXITCODE) return 0;

        if(scanNum < MIN_PRODUCT_ID || scanNum > MAX_PRODUCT_ID) {
            printf("無効な商品IDです。%dから%dの範囲で入力してください。\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID);
            continue;
        }

        // 商品IDが有効な場合の処理
        printf("商品ID: %d の在庫数を入力してください: ", scanNum);
        scanf("%d", &vm[scanNum - 1].stock);
        printf("商品ID: %d の価格を入力してください: ", scanNum);
        scanf("%d", &vm[scanNum - 1].price);
    }

    return 1;
}

