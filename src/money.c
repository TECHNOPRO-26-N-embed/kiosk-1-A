#include <stdio.h>
#include "constants.h"
//投入金額
int inputmoney(int inputamount){
    scanf("%d",&inputamount);
    //投入金額を表示
    printf("投入金額 : %d\n",inputamount);

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
    printf("お釣 : %d\n",changeamount);
}

int money(struct VendingMachine* vm){
    int input = inputmoney(input);

    while(1){ 
        int ID;
        scanf("%d",&ID);
        int change = input;
        
        if(ID == EXITCODE){
            returnmoney(change);
            return 0;
        }

        change = changemoney(input,&vm[ID-1].price);
        input = change;
    }
 
    return 1;
}