#include <stdio.h>
#include "codecapi.h"

//VendingMachine(種類ID,商品ID,料金,在庫数,合計金額), 購入数,合計金額
void save_history(VendingMachine vm, int purchaseCount, int totalAmount) {
    FILE *file = fopen("history.txt", "a"); // 追記モードでファイルを開く
    if (file == NULL) {
        perror("ファイルを開く際にエラーが発生しました");
        return;
    }

    // ファイルに履歴を書き込む
    fprintf(file, "種類ID: %d, 商品ID: %d, 料金: %d, 在庫数: %d, 合計金額: %d, 購入数: %d, 合計金額: %d\n",
            vm.typeID, vm.productID, vm.price, vm.stock, vm.totalAmount, purchaseCount, totalAmount);

    fclose(file); // ファイルを閉じる
}