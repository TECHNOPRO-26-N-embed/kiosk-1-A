#include "ai_sales_logger.h"
#include <stdio.h>

void ai_log_sale(const AI_Product* product, int quantity, int before_stock) {
    FILE* fp = fopen("sales_ai.csv", "a");
    if (!fp) return;
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    fprintf(fp, "%04d/%02d/%02d %02d:%02d:%02d,%d,%s,%d,%d,%d\n",
        t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,
        product->id, product->name, product->price, quantity, before_stock-quantity);
    fclose(fp);
}

void ai_log_operation(const char* operation, const char* user_id) {
    FILE* fp = fopen("operation_log_ai.csv", "a");
    if (!fp) return;
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    fprintf(fp, "%04d/%02d/%02d %02d:%02d:%02d,%s,%s\n",
        t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,
        operation, user_id ? user_id : "");
    fclose(fp);
}
