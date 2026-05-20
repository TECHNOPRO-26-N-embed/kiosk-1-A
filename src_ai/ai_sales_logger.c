#include "ai_sales_logger.h"
#include <stdio.h>
#include <windows.h> // Windows環境での文字コード変換用

void ai_log_sale(const AI_Product* product, int quantity, int before_stock) {
    FILE* fp = fopen("src_ai/sales_ai.csv", "a");
    if (!fp) return;
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    // UTF-8でフォーマットされた文字列を作成
    char utf8_line[512];
    snprintf(utf8_line, sizeof(utf8_line), "%04d/%02d/%02d %02d:%02d:%02d,%d,%s,%d,%d,%d\n",
        t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,
        product->id, product->name, product->price, quantity, before_stock-quantity);

    // UTF-8からCP932に変換
    int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_line, -1, NULL, 0);
    if (wlen > 0) {
        wchar_t wbuf[512];
        MultiByteToWideChar(CP_UTF8, 0, utf8_line, -1, wbuf, wlen);
        int slen = WideCharToMultiByte(932, 0, wbuf, -1, NULL, 0, NULL, NULL);
        if (slen > 0) {
            char sbuf[512];
            WideCharToMultiByte(932, 0, wbuf, -1, sbuf, slen, NULL, NULL);
            fprintf(fp, "%s", sbuf);
        }
    }

    fclose(fp);
}

void ai_log_operation(const char* operation, const char* user_id) {
    FILE* fp = fopen("src_ai/operation_log_ai.csv", "a");
    if (!fp) return;
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    fprintf(fp, "%04d/%02d/%02d %02d:%02d:%02d,%s,%s\n",
        t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,
        operation, user_id ? user_id : "");
    fclose(fp);
}
