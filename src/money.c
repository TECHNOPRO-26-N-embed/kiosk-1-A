#include <stdio.h>
#include "constants.h"

//投入金額
int inputmoney(int inputamount){
    
    printf("投入金額を入力してください\n");
    scanf("%d",&inputamount);

    //投入金額を表示
    printf("投入金額 : %d\n",inputamount);

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
    printf("お釣 : %d\n",changeamount);
}

int money(struct VendingMachine* vm){

    int input = 0;

    int change = input;
    int ID;

    while(1){

        change = input;
        // 投入金額の入力
        printf("投入金額を入力してください (お釣りを出すには%dを入力)(メインメニューに戻るには%dを入力):\n", -1, EXITCODE);
        scanf("%d",&input);

        if(input == EXITCODE){
            returnmoney(change);
            return 0;
        }
        if(input == -1){
            returnmoney(change);
            return 0;
        }
        
        change = input;

        //投入金額を表示
        printf("投入金額 : %d\n",input);
        
        // 商品IDの入力
        printf("商品IDを入力してください (%d-%d)(お釣りを出すには%dを入力)(メインメニューに戻るには%dを入力): ", MIN_PRODUCT_ID, MAX_PRODUCT_ID,  -1, EXITCODE);
        scanf("%d",&ID);
        
        if(ID == EXITCODE){
            returnmoney(change);
            return 0;
        }
        if(ID == -1){
            returnmoney(change);
            return 0;
        }

        change = changemoney(input, vm[ID - 1].price);
        input = change;
    }
 
    return 1;
}