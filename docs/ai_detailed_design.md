# 詳細設計（AI版）

## メインループ
### メニュー表示 → 入力受付 → 処理分岐 → ループの流れ

1. **メインメニューを表示する**
   - 「1. 商品選択」
   - 「2. 管理者モード」
   - 「3. 終了」
2. **ユーザーの入力を受け取る**
3. **入力に応じて分岐する**
   - **1の場合**: 商品選択画面に移動する
     - 商品リストを表示
     - ユーザーが商品を選択
     - 購入処理を実行
     - メインメニューに戻る
   - **2の場合**: 管理者モードに移動する
     - パスワードを入力させる
     - パスワードが正しい場合:
       1. 管理者メニューを表示
          - 「1. 在庫管理」
          - 「2. 売上確認」
          - 「3. ログ閲覧」
          - 「4. メインメニューに戻る」
       2. 管理者メニューの入力を受け取る
       3. 入力に応じて分岐する
          - **1の場合**: 在庫管理画面に移動
          - **2の場合**: 売上確認画面に移動
          - **3の場合**: ログ閲覧画面に移動
          - **4の場合**: メインメニューに戻る
     - パスワードが間違っている場合: エラーメッセージを表示し、メインメニューに戻る
   - **3の場合**: プログラムを終了する
   - **その他の場合**: 無効な入力としてエラーメッセージを表示し、メインメニューに戻る
4. **メインメニューに戻る（1へ）**

## 個別機能のアルゴリズム

### 1. 商品選択・購入処理
1. 商品リストを表示する
2. ユーザーに商品番号を入力させる
3. 入力された商品番号が有効か判定する
   - 無効な場合はエラーメッセージを表示し再入力
4. 商品の在庫数を確認する
   - 在庫がない場合はエラーメッセージを表示しメインメニューに戻る
5. 購入個数を入力させる
6. 投入金額を入力させる
7. 金額が足りているか判定する
   - 不足している場合はエラーメッセージを表示し再入力
8. お釣りを計算する
9. 在庫数を減算し、売上履歴に記録する
10. お釣りと商品を渡すメッセージを表示
11. メインメニューに戻る

### 2. 管理者モード
1. パスワード入力を促す
2. 正しい場合、管理者メニューを表示
   - 1. 在庫管理
   - 2. 売上確認
   - 3. ログ閲覧
   - 4. メインメニューに戻る
3. 入力に応じて分岐
   - 1の場合: 在庫管理処理へ
   - 2の場合: 売上確認処理へ
   - 3の場合: ログ閲覧処理へ
   - 4の場合: メインメニューに戻る
4. パスワードが間違っている場合はエラーメッセージを表示しメインメニューに戻る

### 3. 在庫管理
1. 商品リストと在庫数を表示
2. 補充または在庫変更する商品を選択させる
3. 新しい在庫数を入力させる
4. 在庫数を更新し、操作ログに記録
5. 管理者メニューに戻る

### 4. 売上確認
1. 売上履歴（CSV等）を読み込む
2. 日付や商品ごとに集計し表示
3. 管理者メニューに戻る

### 5. ログ閲覧
1. 操作ログ（CSV等）を読み込む
2. ログ内容を表示
3. 管理者メニューに戻る

---

## エラーハンドリング（想定される異常系）

| 異常系シナリオ | 対処方針 |
| :--- | :--- |
| 数字以外の文字が入力された場合 | エラーメッセージを表示し、再入力を促す |
| 金額が不足している場合 | 不足金額を表示し、再度金額入力を促す |
| 存在しない商品番号が入力された場合 | エラーメッセージを表示し、商品選択画面に戻す |
| 在庫が0の商品が選択された場合 | 「在庫切れ」と表示し、商品選択画面に戻す |
| 購入個数が在庫数を超えている場合 | 「在庫数を超えています」と表示し、再入力を促す |
| パスワードが間違っている場合 | 「パスワードが違います」と表示し、管理者メニューに戻さずメインメニューに戻す |
| ファイル（売上・ログ）が読み込めない場合 | 「ファイルが読み込めません」と表示し、メニューに戻す |
| 想定外の入力や操作があった場合 | 「無効な入力です」と表示し、直前の画面またはメインメニューに戻す |
| システムエラーや予期せぬ例外 | 「システムエラーが発生しました」と表示し、メインメニューに戻す |

## 共通変数名リスト（プロジェクト全体）

| 変数名 | 型（想定） | 用途 |
| :--- | :--- | :--- |
| productCount | int | 管理対象の商品数 |
| maxProductCount | int | 取り扱い可能な最大商品数（要件上は50） |
| maxStockPerProduct | int | 商品ごとの最大在庫数（要件上は50） |
| selectedProductId | int | ユーザーが選択した商品ID |
| selectedQuantity | int | ユーザーが選択した購入個数 |
| unitPrice | int | 商品単価 |
| insertedAmount | int | 投入金額 |
| totalPrice | int | 合計金額（単価 x 個数） |
| changeAmount | int | つり銭額 |
| currentStock | int | 選択商品の現在在庫数 |
| updatedStock | int | 更新後の在庫数 |
| menuChoice | int | メニュー選択値 |
| adminAuthenticated | int | 管理者認証結果（0:失敗, 1:成功） |
| inputBuffer | char[] | キーボード入力の一時受け取り |
| adminPasswordInput | char[] | 管理者パスワード入力値 |
| salesCsvPath | const char* | 売上CSVファイルパス |
| operationLogCsvPath | const char* | 操作ログCSVファイルパス |
| productCsvPath | const char* | 商品・在庫データCSVファイルパス |
| fileOpenOk | int | ファイルオープン成否（0:失敗, 1:成功） |
| errorCode | int | エラー種別コード |

## 機能ごとの関数一覧（引数・返り値コメント付き）

### メイン制御

```c
int runMainLoop(void);
// 引数: なし
// 返り値: 終了ステータス（0:正常終了、0以外:異常終了）

int showMainMenu(void);
// 引数: なし
// 返り値: ユーザーが選択したメニュー番号

void handleMainMenuChoice(int menuChoice);
// 引数: menuChoice - メインメニューの選択値
// 返り値: なし
```

### 商品選択・購入

```c
int showProductList(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）

int selectProductId(void);
// 引数: なし
// 返り値: 選択された商品ID（無効入力時は負値）

int inputPurchaseQuantity(int selectedProductId);
// 引数: selectedProductId - 対象商品ID
// 返り値: 入力された購入個数（無効入力時は負値）

int inputInsertedAmount(void);
// 引数: なし
// 返り値: 投入金額（無効入力時は負値）

int canPurchase(int selectedProductId, int selectedQuantity, int insertedAmount);
// 引数: selectedProductId - 対象商品ID
//       selectedQuantity - 購入個数
//       insertedAmount - 投入金額
// 返り値: 購入可否（1:購入可能、0:購入不可）

int calculateTotalPrice(int unitPrice, int selectedQuantity);
// 引数: unitPrice - 商品単価
//       selectedQuantity - 購入個数
// 返り値: 合計金額

int calculateChange(int insertedAmount, int totalPrice);
// 引数: insertedAmount - 投入金額
//       totalPrice - 合計金額
// 返り値: つり銭額

int executePurchase(int selectedProductId, int selectedQuantity, int insertedAmount);
// 引数: selectedProductId - 対象商品ID
//       selectedQuantity - 購入個数
//       insertedAmount - 投入金額
// 返り値: 購入処理結果（0:成功、0以外:失敗）
```

### 在庫管理

```c
int showStockList(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）

int updateStock(int selectedProductId, int updatedStock);
// 引数: selectedProductId - 更新対象の商品ID
//       updatedStock - 更新後在庫数
// 返り値: 更新処理結果（0:成功、0以外:失敗）

int restockProduct(int selectedProductId, int addQuantity);
// 引数: selectedProductId - 補充対象の商品ID
//       addQuantity - 追加補充数
// 返り値: 補充処理結果（0:成功、0以外:失敗）
```

### 管理者モード

```c
int authenticateAdmin(const char* adminPasswordInput);
// 引数: adminPasswordInput - 入力された管理者パスワード
// 返り値: 認証結果（1:成功、0:失敗）

int showAdminMenu(void);
// 引数: なし
// 返り値: 管理者メニューの選択値

void handleAdminMenuChoice(int menuChoice);
// 引数: menuChoice - 管理者メニューの選択値
// 返り値: なし
```

### 売上確認・ログ閲覧

```c
int loadSalesHistory(const char* salesCsvPath);
// 引数: salesCsvPath - 売上CSVパス
// 返り値: 読み込み結果（0:成功、0以外:失敗）

int showSalesSummary(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）

int loadOperationLog(const char* operationLogCsvPath);
// 引数: operationLogCsvPath - 操作ログCSVパス
// 返り値: 読み込み結果（0:成功、0以外:失敗）

int showOperationLog(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）
```

### CSV入出力・記録

```c
int appendSalesRecord(int selectedProductId, int selectedQuantity, int unitPrice, int remainingStock);
// 引数: selectedProductId - 購入商品ID
//       selectedQuantity - 購入個数
//       unitPrice - 商品単価
//       remainingStock - 購入後在庫
// 返り値: 書き込み結果（0:成功、0以外:失敗）

int appendOperationLog(const char* actionLabel);
// 引数: actionLabel - 操作内容ラベル
// 返り値: 書き込み結果（0:成功、0以外:失敗）

int saveProductMaster(void);
// 引数: なし
// 返り値: 保存処理結果（0:成功、0以外:失敗）
```


## クラス設計

※ 本システムはC言語実装のため、実装時は「構造体 + 関数群（モジュール）」で同等の責務分割を行う。

### 1. KioskApplication

- 役割: アプリケーション全体の起動、メインループ、メニュー分岐の制御
- 担当関数:

```c
int runMainLoop(void);
// 引数: なし
// 返り値: 終了ステータス（0:正常終了、0以外:異常終了）

int showMainMenu(void);
// 引数: なし
// 返り値: ユーザーが選択したメニュー番号

void handleMainMenuChoice(int menuChoice);
// 引数: menuChoice - メインメニューの選択値
// 返り値: なし
```

### 2. PurchaseService

- 役割: 商品選択、購入可否判定、金額計算、購入実行
- 担当関数:

```c
int showProductList(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）

int selectProductId(void);
// 引数: なし
// 返り値: 選択された商品ID（無効入力時は負値）

int inputPurchaseQuantity(int selectedProductId);
// 引数: selectedProductId - 対象商品ID
// 返り値: 入力された購入個数（無効入力時は負値）

int inputInsertedAmount(void);
// 引数: なし
// 返り値: 投入金額（無効入力時は負値）

int canPurchase(int selectedProductId, int selectedQuantity, int insertedAmount);
// 引数: selectedProductId - 対象商品ID
//       selectedQuantity - 購入個数
//       insertedAmount - 投入金額
// 返り値: 購入可否（1:購入可能、0:購入不可）

int calculateTotalPrice(int unitPrice, int selectedQuantity);
// 引数: unitPrice - 商品単価
//       selectedQuantity - 購入個数
// 返り値: 合計金額

int calculateChange(int insertedAmount, int totalPrice);
// 引数: insertedAmount - 投入金額
//       totalPrice - 合計金額
// 返り値: つり銭額

int executePurchase(int selectedProductId, int selectedQuantity, int insertedAmount);
// 引数: selectedProductId - 対象商品ID
//       selectedQuantity - 購入個数
//       insertedAmount - 投入金額
// 返り値: 購入処理結果（0:成功、0以外:失敗）
```

### 3. AdminService

- 役割: 管理者認証と管理メニュー分岐制御
- 担当関数:

```c
int authenticateAdmin(const char* adminPasswordInput);
// 引数: adminPasswordInput - 入力された管理者パスワード
// 返り値: 認証結果（1:成功、0:失敗）

int showAdminMenu(void);
// 引数: なし
// 返り値: 管理者メニューの選択値

void handleAdminMenuChoice(int menuChoice);
// 引数: menuChoice - 管理者メニューの選択値
// 返り値: なし
```

### 4. StockService

- 役割: 在庫一覧表示、在庫更新、補充
- 担当関数:

```c
int showStockList(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）

int updateStock(int selectedProductId, int updatedStock);
// 引数: selectedProductId - 更新対象の商品ID
//       updatedStock - 更新後在庫数
// 返り値: 更新処理結果（0:成功、0以外:失敗）

int restockProduct(int selectedProductId, int addQuantity);
// 引数: selectedProductId - 補充対象の商品ID
//       addQuantity - 追加補充数
// 返り値: 補充処理結果（0:成功、0以外:失敗）
```

### 5. ReportService

- 役割: 売上履歴・操作ログの読み込みと表示
- 担当関数:

```c
int loadSalesHistory(const char* salesCsvPath);
// 引数: salesCsvPath - 売上CSVパス
// 返り値: 読み込み結果（0:成功、0以外:失敗）

int showSalesSummary(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）

int loadOperationLog(const char* operationLogCsvPath);
// 引数: operationLogCsvPath - 操作ログCSVパス
// 返り値: 読み込み結果（0:成功、0以外:失敗）

int showOperationLog(void);
// 引数: なし
// 返り値: 表示処理結果（0:成功、0以外:失敗）
```

### 6. CsvRepository

- 役割: 売上記録・操作ログ・商品マスタの永続化処理
- 担当関数:

```c
int appendSalesRecord(int selectedProductId, int selectedQuantity, int unitPrice, int remainingStock);
// 引数: selectedProductId - 購入商品ID
//       selectedQuantity - 購入個数
//       unitPrice - 商品単価
//       remainingStock - 購入後在庫
// 返り値: 書き込み結果（0:成功、0以外:失敗）

int appendOperationLog(const char* actionLabel);
// 引数: actionLabel - 操作内容ラベル
// 返り値: 書き込み結果（0:成功、0以外:失敗）

int saveProductMaster(void);
// 引数: なし
// 返り値: 保存処理結果（0:成功、0以外:失敗）
```

---

## 備考メモ
- 本システムは飲料自動販売機を想定し、最大50種類・各50個までの商品管理を行う。
- 売上履歴・操作ログはCSVファイルで管理し、障害時の復旧や集計が容易になるよう配慮する。
- 季節ごとに商品入れ替えが発生するため、商品マスタの更新や在庫リセットの運用を考慮する必要がある。
- セキュリティ上、管理者パスワードはハードコーディングせず、将来的には外部ファイルや環境変数での管理も検討する。
- システムの安定稼働を重視し、異常時は必ずメインメニューに戻す設計とする。
- 想定外の操作やエラー発生時もシステム停止を避け、ユーザーに分かりやすいメッセージを表示する。
- 複数ユーザーが連続利用できるよう、1回の取引終了後は必ずメインメニューに戻る。
- ファイル入出力エラーやデータ不整合時のログ記録も将来的な拡張ポイントとする。