#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

void *	memset(void *b, int c, long len);
void *	memcpy(void *dest, const void *src, long len);
int	memcmp(const void *b1, const void *b2, long len);
int	strlen(const char *s);
char *	strcpy(char *dest, const char *src);
int	strcmp(const char *s1, const char *s2);
int	strncmp(const char *s1, const char *s2, int len);

int	putc(unsigned char c);	/* 一文字送信 */
unsigned char
	getc(void);		/* 一文字受信 */
int	puts(unsigned char *s);	/* 文字列送信 */
int	gets(unsigned char *s);	/* 文字列受信 */
int	putxval(unsigned long value, int column);	/* 数値の 16 進表示 */

#endif	/* !LIB_H_INCLUDED */
