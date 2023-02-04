# h83069f

12 ステップで組込み OS を自作してみる

[12 ステップで作る 組込み OS 自作入門][makeos]に取り組むリポジトリ

## ホスト環境

よくある普通の Ubuntu 22.04.1 LTS を利用。

```console
$ uname -a
Linux iMacPro 5.15.0-58-generic #64-Ubuntu SMP Thu Jan 5 11:43:13 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
$ cat /etc/os-release 
PRETTY_NAME="Ubuntu 22.04.1 LTS"
NAME="Ubuntu"
VERSION_ID="22.04"
VERSION="22.04.1 LTS (Jammy Jellyfish)"
VERSION_CODENAME=jammy
ID=ubuntu
ID_LIKE=debian
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
UBUNTU_CODENAME=jammy
```

## 使っているマイコンボード

秋月で手に入れることができる。
ボードキットは自分で半田付けする必要がある。
完成してしまえばどちらも同じものなので、時間と技術を金で買うか相談しよう。

私はボードキットを拾ってきたので自分で半田付けしてみた。
H8/3069F の代わりに H8/3068F が載っているボードも拾ったけれど、
これも使えるのかしら。

- [H8/3069F ネット対応マイコン LAN ボード (完成品)][K-01271]
- [H8/3069F ネット対応マイコン LAN ボード (ボードキット)][K-00209]
- [AKI-H8/3068F フラッシュマイコン LAN ボード][K-11207]

[makeos]:  https://kozos.jp/books/makeos/
[K-01271]: https://akizukidenshi.com/catalog/g/gK-01271/
[K-00209]: https://akizukidenshi.com/catalog/g/gK-00209/
[K-11207]: https://akizukidenshi.com/catalog/g/gK-11207/
