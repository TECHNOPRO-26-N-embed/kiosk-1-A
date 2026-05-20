#pragma once
#include "ai_product_manager.h"
#include <time.h>

// 売上記録
void ai_log_sale(const AI_Product* product, int quantity, int before_stock);
// 操作ログ
void ai_log_operation(const char* operation, const char* user_id);
