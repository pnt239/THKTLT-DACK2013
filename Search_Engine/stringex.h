#pragma once

#include "appdef.h"
#include <string.h>

void strdelrn(char *str);
char to_lower(char c);
bool is_letter(char c);
bool is_end_signal(char c);
bool is_upper(char c);
int checkChar(char c);
int strdist(char *str1, char *strcp, char *str2);
char **strsplit(char *str, int &wcount);
char *getword(char *line, int &wlen, int &offset);