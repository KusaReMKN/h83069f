#include "defines.h"
#include "serial.h"
#include "xmodem.h"
#include "elf.h"
#include "lib.h"

static int
init(void)
{
	/* 以下はリンカスクリプトで定義してあるシンボル */
	extern int erodata, data_start, edata, bss_start, ebss;

	/*
	 * データ領域と BSS 領域を初期化する
	 * この処理以降でないと広域変数が初期化されていないので注意
	 */
	memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
	memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

	/* シリアルの初期化 */
	serial_init(SERIAL_DEFAULT_DEVICE);

	return 0;
}

static int
dump(char *buf, long size)
{
	long i;

	if (size < 0) {
		puts("No data.\n");
		return -1;
	}
	for (i = 0; i < size; i++) {
		putxval(buf[i], 2);
		if ((i & 0x0F) == 0x0F) {
			puts("\n");
		} else {
			if ((i & 0x0F) == 0x07)
				puts(" ");
			puts(" ");
		}
	}
	puts("\n");

	return 0;
}

static void
wait(void)
{
	volatile long i;
	for (i = 0; i < 300000L; i++)
		;
}

int
main(void)
{
	static char buf[16];
	static long size = -1;
	static unsigned char *loadbuf = NULL;
	extern int buffer_start;

	init();

	puts("kzload (kozos boot loader) started.\n");

	while (1) {
		puts("kzload> ");	/* プロンプト表示 */
		gets(buf);	/* シリアルからのコマンド受信 */

		/* XMODEM でのファイルダウンロード */
		if (!strcmp(buf, "load")) {
			loadbuf = (char *)(&buffer_start);
			size = xmodem_recv(loadbuf);
			wait();
			if (size < 0)
				puts("\nXMODEM receive error!\n");
			else
				puts("\nXMODEM receive succeeded.\n");
		}
		/* メモリの 16 進ダンプ出力 */
		else if (!strcmp(buf, "dump")) {
			puts("size: "); putxval(size, 0); puts("\n");
			dump(loadbuf, size);
		}
		/* ELF 形式ファイルの実行 */
		else if (!strcmp(buf, "run")) {
			/* メモリ上に展開 */
			elf_load(loadbuf);
		} else {
			puts("Unknown.\n");
		}
	}

	return 0;
}
