/*
 * File chua cac ham xu ly chuoi mo rong
 */

#include "stringex.h"

/* Xoa ky tu \r va \n o cuoi file */
void strdelrn(char *str)
{
	int slen = strlen(str);
	for (int i = slen - 1; i >= 0; i--)
		if (str[i] == '\n' || str[i] == '\r')
			str[i] = 0;
		else
			break;
}

char to_lower(char c)
{
	if (is_upper(c))
		c += 0x20;
	return c;
}

bool is_letter(char c)
{
	return (c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a);
}

bool is_end_signal(char c)
{
	return (c == 0 || c == '\r' || c == '\n');
}

bool is_upper(char c)
{
	return (c >= 0x41 && c <= 0x5a);
}

/*
 * Kiem tra ky tu c thuoc loai nao
 * Tra ve: 1 - chu cai
 *         2 - ' (dau viet tat)
 *         3 - dau gach ngang '-'
 *         4 - dau cau + ky tu khac
 *         5 - ky tu ket thuc
 */
int checkChar(char c)
{
	if (is_letter(c))
		return 1;
	else if (c == 0x27)
		return 2;
	else if (c == '-')
		return 3;
	else if (is_end_signal(c))
		return 5;
	else
		return 4;
}
/*
 * Xet khoang cach tu strcp den str1 vaf str2
 * Tra ve 1: Neu str1 gan strcp hon
 * Tra ve 2: Neu str2 gan strcp hon
 */
int strdist(char *str1, char *strcp, char *str2)
{
	int slen1 = strlen(str1);
	int slencp = strlen(strcp);
	int slen2 = strlen(str2);
	// Tim ra chuoi co chieu dai ngan nhat trong 3 chuoi
	int minl = slen1;
	if (minl > slencp) minl = slencp;
	if (minl > slen2) minl = slen2;
	for (int i = 0; i < minl; i++)
		if ((strcp[i] - str1[i]) > (str2[i] - strcp[i]))
			return 2;
		else if ((strcp[i] - str1[i]) < (str2[i] - strcp[i]))
			return 1;
	return 1;
}

/* 
 * Ham cat chuoi nhap vao thanh danh sach tu 
 * Phan tu cuoi trong mang mang gia tri null -> dung vong lap cho de
 */
char **strsplit(char *str, int &wcount)
{
	char **ret = new char*[100];
	char *word;
	int offset = 0, ipos = 0, wlen;

	wcount = 0;
	while (offset != -1 && (word = getword(str, wlen, offset)) != NULL)
	{
		if (word[0] == 0) continue;
		ret[ipos] = word;
		ipos++;
		wcount++;
		if (offset == -1) break;
	}
	ret[ipos] = NULL;
	return ret;
}

/* Lay tung tu ra tu 1 dong van ban */
char *getword(char *line, int &wlen, int &offset)
{
	char *word = new char[MAX_WORD];
	bool begin = true;
	int i = 0, ctype, nhyphen = 0;
	wlen = 0;
	// Kiem tra ki tu ket thuc chuoi
	if (is_end_signal(line[offset])) {
		delete word;
		return NULL;
	}
	// word == ""
	word[0] = 0;
	// Tach tu o offset
	if (is_letter(line[offset])) {
		word[i++] = to_lower(line[offset++]);
		while (1)
		{
			ctype = checkChar(line[offset]);
			if (ctype == 1) { // La chu cai
				word[i++] = to_lower(line[offset++]);
			} else if (ctype == 2) { // La dau viet tat
				word[i] = 0;
				offset++;
				while (!is_letter(line[offset++]));
				break;
			} else if (ctype == 3) { // La dau gach ngang '-'
				if (nhyphen > 2) {
					delete word;
					word = "";
					while (is_letter(line[offset]) || line[offset] == '-')
						offset++;
					break;
				} else {
					nhyphen++;
					word[i++] = to_lower(line[offset++]);
				}
			} else if (ctype == 4) { // La dau cau, ky tu khac
				word[i] = 0;
				break;
			} else if (ctype == 5) { // La ky tu ket thuc chuoi
				word[i] = 0;
				offset = -1;
				break;
			}
		}
	} 
	// Tim chu dau tien.
	while (offset != -1)
	{
		if (is_end_signal(line[offset])) {
			offset = -1;
			break;
		}
		if (is_letter(line[offset])) break;
		offset++;
	}
	wlen = i;
	return word;
}