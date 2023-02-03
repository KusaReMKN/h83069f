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

[objchg]:  https://kozos.jp/books/makeos/objchg.html
[h8write]: https://mes.osdn.jp/h8/writer-j.html
