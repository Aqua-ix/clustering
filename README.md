# ディレクトリ
## src
ソースコード
## data/result_data
実験結果出力
## data/dataset
実験用データセット
## documents
論文・概要書・プレゼン資料
## .o
コンパイル時中間ファイル出力

# ファイル
## setup.sh
セットアップコマンド
詳しくはファイルの中身参照
## .dir-locals.el
emacs設定ファイル
## Makefile
コンパイル実行ファイル

# プログラムコンパイル方法

vectorクラス等の中間ファイル作成、-Bで強制コンパイル

```sh
$ make
```

実行ファイルのコンパイル

```sh
$ make ターゲット data=データ名
```

### ターゲット名

- `overlap`: オーバーラップあり
- `crisp`: オーバーラップなし
- `grouplens.out`: GroupLens
- `bfcs_overlap.out`のように個別指定することも可能
- ※注意: `qpcs_crisp.out`のみ中村方式のオーバーラップ

## 例
### 人工データのをまとめてコンパイルする場合

```sh
$ make overlap data=BOOK
```

### bfcsをBookCrossingに適用する場合

```sh
$ make bfcs.out data=BOOK
```

### クラスの呼び出し等デバグしたいとき

```sh
$ make ターゲット data=データ名 class=1
```

# プログラム実行方法
## run.sh

プログラム実行用スクリプトファイル

```sh
$ sh run.sh [プログラム名]
```

でバックグラウンド実行開始

## 例

```sh
$ sh run.sh overlap
```

(他の引数は中身参照)

# 実験結果抽出方法
## 各オーバーラップ閾値ごとに最良パラメータの結果を抽出するPythonスクリプト
### result_overlap_artificiality.py

- 人工データ実験結果の抽出(オーバーラップ有り)
- 引数不要

### result_overlap_actuality.py

- 人工データ実験結果の抽出(オーバーラップ有り)
- 第1引数: データ名
- 第2, 3, 4引数: 抽出するBFCS, EFCS, QFCSのクラスタ数

#### 例

```sh
$ python result_overlap_actuality.py book 2 2 2
```

### result_crisp_artificiality.py

- 実データ実験結果の抽出(オーバーラップ無し)
- 引数不要

### result_crisp_actuality.py

- 実データ実験結果の抽出(オーバーラップ無し)
- 第1引数: データ名
- 第2, 3, 4引数: 抽出するBFCS, EFCS, QFCSのクラスタ数

#### 例

```sh
$ python result_crisp_actuality.py book 2 2 2
```

# 実験結果ディレクトリの説明
## data/result_data/MAE

抽出済MAE実験結果

### 結果加工・グラフ出力用スクリプト
#### 閾値ごとに抽出されたファイルを欠損数ごとにまとめる

```sh
$ python result1.py
```

#### 横軸欠損数・縦軸MAEのグラフ出力

```sh
$ sh plot1.sh
```

#### TeX用に表を出力

```sh
$ python result2.py
```

#### 横軸閾値・縦軸MAEのグラフ出力

```sh
$ sh plot2.sh
```

## data/result_data/AUC

- 抽出済AUC実験結果
- スクリプトの扱いはMAEと同様

## data/result_data/ROC

抽出済ROC実験結果

### 結果加工・グラフ出力用スクリプト
#### 欠損パターンごとのディレクトリにまとめる

```sh
$ sh convert.sh [データ名]
```

#### ROC曲線出力

```sh
$ sh plot.sh
```

