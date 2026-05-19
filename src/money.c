#include <stdio.h>
#include "constants.h"
#include "save_history.h"
#include "ProductSelection.h"

//投入金額の入力
int inputmoney(int money){
    int inputamount;
    printf("\n【投入金額を入力してください】\n");
    printf("※お釣りを出力の場合 %d を入力\n", CHANGECODE);
    printf("※メインメニューに戻る場合 %d を入力\n", EXITCODE);
    printf("投入金額入力 : ");
    scanf("%d",&inputamount);
        
    return money + inputamount;
}

//お釣計算
int changemoney(int inputamount, int chooseamount){
    int changeamount;
    //お釣計算
    changeamount = inputamount - chooseamount;

    return changeamount;
}

//お釣返却
void returnmoney(int changeamount){
    printf("お釣 : %d 円\n",changeamount);
}

int money(struct VendingMachine* vm){
    int input = 0;
    int change = input;
    int ID;
    
    // 商品の表示
    displayProducts(vm);

    while(1){
        // 商品IDの入力
        printf("\n【商品IDを入力してください】\n");
        printf("※商品ID %d～%d\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID);
        printf("※お釣りを出すには %d を入力\n", CHANGECODE);
        printf("※メインメニューに戻るには %d を入力\n", EXITCODE);
        printf("入力 : ");
        scanf("%d",&ID);
        
        if(ID == EXITCODE){
            returnmoney(change);
            return 0;
        }
        if(ID == CHANGECODE){
            returnmoney(change);
            continue;
        }
        // 商品IDの範囲チェック
        if (ID < MIN_PRODUCT_ID || ID > MAX_PRODUCT_ID) {
            printf("無効な商品IDです。入力しなおしてください。\n");
            continue;
        }
        // 在庫の確認
        if(vm[ID - 1].stock <= 0) {
            printf("商品ID %d は在庫切れです。\n", ID);
            continue;
        }
        
        // 投入金額の追加
        input = inputmoney(input);
        if(input == EXITCODE){
            returnmoney(change);
            return 0;
        }
        if(input == CHANGECODE){
            returnmoney(change);
            continue;
        }
        // 投入金のチェック        
        if(input < vm[ID - 1].price) {
            printf("投入金額が不足しています。\n");
            continue;
        }

        //投入金額を表示
        printf("投入金額 : %d 円\n",input);

        change = changemoney(input, vm[ID - 1].price);

        input = change;
        
        // 商品出力
        printf("種類ID: %d を出力\n", vm[ID - 1].typeID);

        vm[ID - 1].totalAmount += vm[ID - 1].price;
        vm[ID - 1].stock -= 1;
        save_history(vm[ID - 1], 1, vm[ID - 1].totalAmount);
        
        // 商品の表示
        displayProducts(vm);

        //残り金額を表示
        printf("\n残り金額 : %d 円\n",change);
    }
 
    return 1;
}