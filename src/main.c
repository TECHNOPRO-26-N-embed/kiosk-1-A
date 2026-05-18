#include <stdio.h>
#include "constants.h"

int main(void){

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

                break;

            case 2:
                // 商品管理モードの処理

                break;

            case 3:
                // キャッシュクリアモードの処理

                break;

            case 4:
                // トータル売り上げ表示の処理

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