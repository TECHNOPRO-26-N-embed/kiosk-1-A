#include <stdio.h>
#include "constants.h"
//投入金額
int inputmoney(int inputamount){
    scanf("%d",&inputamount);
    //投入金額を表示
    printf("%d\n",inputamount);

    return inputamount;
}
//お釣計算
int changemoney(int inputamount,int chooseamount){
    int changeamount;
    //お釣計算
    changeamount = inputamount - chooseamount;

    return changeamount;
}
//お釣返却
void returnmoney(int changeamount){
    printf("%d\n",changeamount);
}

int money(struct VendingMachine* vm[MAX_PRODUCT_ID]){
    int input = inputmoney(input);

    while(1){ 
        int ID;
        scanf("%d",&ID);
        int change = input;
        
        if(ID == EXITCODE){
            returnmoney(change);
            return 0;
        }

        change = changemoney(input,vm[ID]->price);
        input = change;
    }
 
    return 1;
}