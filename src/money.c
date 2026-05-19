#include <stdio.h>
#include "constants.h"
#include "save_history.h"
#include "ProductSelection.h"
//投入金額の入力
int inputmoney(int inputamount){
    printf("投入金額を入力してください\n");
    printf("(%d-%d)(お釣りを出すには%dを入力)(メインメニューに戻るには%dを入力) : ", MIN_PRODUCT_ID, MAX_PRODUCT_ID,  CHANGECODE, EXITCODE);
    scanf("%d",&inputamount);
        
    return inputamount;
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

    while(1){
        // 商品IDの入力
        printf("商品IDを入力してください\n");
        displayProducts(vm);
        printf("(%d-%d)(お釣りを出すには%dを入力)(メインメニューに戻るには%dを入力) : ", MIN_PRODUCT_ID, MAX_PRODUCT_ID,  CHANGECODE, EXITCODE);
        scanf("%d",&ID);
        
        if(ID == EXITCODE){
            returnmoney(change);
            return 0;
        }
        if(ID == CHANGECODE){
            returnmoney(change);
            return 0;
        }

        input = inputmoney(input);
        if(input == EXITCODE){
            returnmoney(change);
            return 0;
        }
        if(input == CHANGECODE){
            returnmoney(change);
            return 0;
        }

        //投入金額を表示
        printf("投入金額 : %d 円\n",input);

        change = changemoney(input, vm[ID - 1].price);

        input = change;

        vm[ID - 1].totalAmount += vm[ID - 1].price;
        save_history(vm[ID - 1], 1, vm[ID - 1].totalAmount);
    }
 
    return 1;
}