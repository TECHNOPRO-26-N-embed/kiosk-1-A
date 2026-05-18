#include <stdio.h>
#include "constants.h"
// 商品ID表示、商品名表示、値段表示、在庫数表示
void displayProductID(int productID) {
    printf("商品ID: %d\n", productID);
}

void displayProductName(const char* productName) {
    printf("商品名: %s\n", productName);
}

void displayProductPrice(double price) {
    printf("値段: %.2f\n", price);
}

void displayProductStock(int stock) {
    printf("在庫数: %d\n", stock);
}
