# 1st Step

## コンパイラとか

マイコンに付属しているコンパイラをコンパイルすることは面倒なので断念した。
指定されているコンパイラをソースからビルドすることも試みたが、
gcc のコンパイルにどうしても失敗するので断念した。
`apt search h8300` してみたところ、それっぽいものを発見したのでそれを利用する。
ここでインストールされるコンパイラは ELF ではなく COFF を吐くようだ。

```console
$ sudo apt update && sudo apt upgrade -y
$ sudo apt install gcc-h8300-hms	# これで binutils も入る
```

本の内容は ELF を吐くコンパイラを想定しているので、
コンパイラが吐く COFF を ELF に変換してやる必要がある。
objcopy がその仕事をしてくれるはずだが、ホスト側の objcopy は COFF を読めず、
ターゲット側の objcopy は ELF を吐けないので変換できない。
しかし、[添付 CD-ROM の開発環境を利用する方法][objchg]に
ELF ⇔ COFF 変換ツールがあるのでそれを利用できる。

```console
$ wget https://kozos.jp/books/makeos/objchg.zip
$ unzip objchg.zip
$ cd objchg
$ make
$ strip objchg
$ mkdir -p ~/.local/bin
$ install objchg ~/.local/bin/.
```

さらに、マイコンにイメージを書き込むツール **Open SH/H8 writer** を用意する。
これは[配布ページ][h8write]からソースファイルをダウンロードし、
ホスト環境でビルドして利用する。

```console
$ wget https://mes.osdn.jp/h8/h8write.c
$ cc -O -o h8write h8write.c
$ strip h8write
$ mkdir -p ~/.local/bin
$ install h8write ~/.local/bin/.
```

USB シリアルケーブルを利用しているので、
書き込み対象デバイスは `/dev/ttyUSB0` などのように見えている。
これに書き込むために毎回スーパユーザになるのは面倒なので
dialout グループに入れてもらおう。
権限が効力を発揮するのは次回のログイン以降である。

```console
$ sudo usermod -aG dialout mkn	# mkn はユーザ名
```

## コードの読み替えとか

Makefile の一部を修正する必要がある。

- `PREFIX` の値を `/usr` に
- `ARCH` の値を `h8300-hms` に
- \*.elf な拡張子を \*.coff に
- (h8write のインストール場所に合わせて) パスを変更

## ビルドと書き込み

`make` して `make write` すれば書き込まれる。
その際、DIP スイッチの状態を ON/ON/OFF/ON にしておく。

## 実行

実行するために `screen` をインストールする。

```console
$ sudo apt update && sudo apt upgrade -y
$ sudo apt install screen
```

screen を起動してシリアルデバイスを監視しておき、マイコンボードの電源を入れる。
その際、DIP スイッチの状態を ON/OFF/ON/OFF にしておく。
screen を終了するには [Ctrl]+[A] を押下し、[K] を押下し、[Y] を押下する。

```console
$ screen /dev/ttyUSB0 9600
```

[objchg]:  https://kozos.jp/books/makeos/objchg.html
[h8write]: https://mes.osdn.jp/h8/writer-j.html
