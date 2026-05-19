#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MIN_PRODUCT_ID (1)  // 商品IDの最小値
#define MAX_PRODUCT_ID (12) // 商品IDの最大値

#define MAX_TYPES_ID (50)   // 商品タイプの最大値

#define EXITCODE (0)        // 入力などの終了コード

#define CHANGECODE (-1)     // お釣りを出すためのコード

struct VendingMachine{
//種類ID,商品ID,料金,在庫数,合計金額
int typeID;
int productID;
int price;
int stock;
int totalAmount;
};

#endif // CONSTANTS_H