#include "file.h"

int getFileSize(char *filename)
{
	FILE *f = fopen(filename, "rb");
	if (f == NULL) return -1;
	fseek(f, 0, SEEK_END);
	int size = (int)ftell(f);
	fclose(f);
	return size;
}

bool fileExist(char *filename)
{
	FILE *f = fopen(filename, "rb");
	if (f == NULL) return false;
	else
	{
		fclose(f);
		return true;
	}
}

char *getFileTitle(char *filename)
{
	char *s = new char[260];
	FILE *f = fopen(filename, "rt");
	if (f == NULL) return NULL;
	fgets(s, 260, f);
	fclose(f);
	return s;
}