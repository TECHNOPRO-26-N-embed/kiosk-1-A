#include "kiosk_application.h"
#include "purchase_service.h"
#include "admin_service.h"
#include "ai_utils.h"
#include <stdio.h>
#include <stdlib.h>

int runMainLoop(void) {
    int running = 1;
    while (running) {
        int menuChoice = showMainMenu();
        handleMainMenuChoice(menuChoice);
        if (menuChoice == 3) running = 0;
    }
    return 0;
}

int showMainMenu(void) {
    printf("==== AI自動販売機 メインメニュー ====\n");
    printf("1. 商品購入\n2. 管理者モード\n3. 終了\n");
    int choice = ai_input_int("メニュー番号を入力してください: ");
    return choice;
}

void handleMainMenuChoice(int menuChoice) {
    switch (menuChoice) {
        case 1:
            runPurchaseService();
            break;
        case 2:
            runAdminService();
            break;
        case 3:
            printf("終了します。\n");
            break;
        default:
            printf("無効な入力です。\n");
            break;
    }
}
