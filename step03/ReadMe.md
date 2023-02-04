# 3rd Step

## ELF 出力について

objchg を利用して ELF を生成するようにしてみた。
しかし、生成される ELF にはシンボルテーブルなどの情報が載っていないようである。
黙って COFF を眺めた方がよさそうである。

```console
$ h8300-hms-objdump -x kzload.coff
```
