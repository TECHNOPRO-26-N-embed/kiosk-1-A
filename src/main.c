#include <stdio.h>
#include "constants.h"
#include "stockEntry.h"
#include "money.h"


int main(void){
    
    struct VendingMachine vm[MAX_PRODUCT_ID] = {0}; // 商品

    // メインメニュー
    while (1){
        printf("\nメインメニュー:\n");
        printf("1. 商品販売モード\n");
        printf("2. 商品管理モード\n");
        printf("3. キャッシュクリアモード\n");
        printf("4. トータル売り上げ表示\n");
        printf("%d. 終了\n", EXITCODE);
        printf("選択してください (1-4): ");
        
        // ユーザーの選択を取得
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // 商品販売モードの処理
                money(vm);
                break;

            case 2:
                // 商品管理モードの処理
                loop(vm);
                break;

            case 3:
                // キャッシュクリアモードの処理
                while (1) {
                    // 商品IDの入力
                    int scanNum;
                    printf("キャッシュを消したい商品IDを入力してください (%d-%d)(終了するには%dを入力): ", MIN_PRODUCT_ID, MAX_PRODUCT_ID, EXITCODE);
                    scanf("%d", &scanNum);
                    if(scanNum == EXITCODE) break;
                    
                    if(scanNum < MIN_PRODUCT_ID || scanNum > MAX_PRODUCT_ID) {
                        printf("無効な商品IDです。%dから%dの範囲で入力してください。\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID);
                        continue;
                    }
                    
                    // 商品IDが有効な場合の処理
                    vm[scanNum - 1].totalAmount = 0;
                    printf("商品ID: %d のキャッシュをクリアしました。\n", scanNum);
                }
                break;

            case 4:
                // トータル売り上げ表示の処理
                for (int i = 0; i < MAX_PRODUCT_ID; i++) {
                    printf("商品ID: %d のトータル売り上げ: %d\n", i + 1, vm[i].totalAmount);
                }
                break;

            case EXITCODE:
                printf("プログラムを終了します。\n");
                return 0;
                
            default:
                printf("無効な選択です。もう一度入力してください。\n");
                break;
        }
    }
    return 0;
}