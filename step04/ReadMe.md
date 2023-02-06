# 4th Step

## ファイルの転送について

cu と lsx が Ubuntu に入っておらず、
それらのインストールされている FreeBSD が近くにあったのでそちらで動作させた。
Ubuntu の cu (`sudo apt install cu` で入るもの) は
FreeBSD のそれとは異なるようで、`~C` が仕事をしてくれない。

screen を利用しても同様の仕事を実現できるようである。
まずは lrzsz をインストールする。

```console
$ sudo apt update && sudo apt upgrade -y
$ sudo apt instalk lrzsz
```

いつも通りに screen で接続する。
cu で `~C` を入力する場面では
<kbd><Kbd>Ctrl</kbd>+<kbd>A</kbd></kbd>, <kbd><kbd>:</kbd></kbd> と押下し、
`exec !! sx filename` と実行する。
