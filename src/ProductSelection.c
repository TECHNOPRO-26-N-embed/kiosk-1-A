#include <stdio.h>
#include "constants.h"
// 商品ID、値段、在庫数を自販機の並び方のように表示する関数
void displayProducts(struct VendingMachine products[]) {
    printf("商品ID\t値段\t在庫数\n");
    for (int i = 0; i < MAX_PRODUCT_ID; i++) {
        printf("%d\t%d\t%d\n", products[i].productID, products[i].price, products[i].stock);
    }
}


