/*
 * File chua cac ham khoi tao, load du lieu tu index file va cache
 */

#include "index.h"

void addID(char *filename, AppData appData)
{
	FILE *f = fopen(appData.seSetting.indexFile, "a");
	fprintf(f, "\n%s", filename);
	fclose(f);
}

void delID(char *filename, AppData appData)
{
	FILE *f = fopen(appData.seSetting.indexFile, "w");

	if (strcmp(filename, appData.idList.id[0].filename) != 0)
		fprintf(f, "%s", appData.idList.id[0].filename);
	else
		return;

	for (int i = 1; appData.idList.id[i].filename != NULL; i++)
		if (strcmp(filename, appData.idList.id[i].filename) != 0)
			fprintf(f, "\n%s", appData.idList.id[i].filename);
	fclose(f);
}

/* 
 * Load voi dieu kien file index va file meta da duoc cap nhap
 */
int loadIndex(AppData &appData)
{
	int i;
	bool no_cache;

	if (appData.idList.id != NULL)
		freeIndex(appData);
	appData.idList.id = new Index[appData.seSetting.numfile+1];
	FILE *f = fopen(appData.seSetting.indexFile, "rb");
	FILE *fCache = fopen("cache\\index.dat", "rb");
	if (fCache == NULL) no_cache = true;
	else no_cache = false;

	if (f == NULL) return 1;
	for (i = 0; i < appData.seSetting.numfile; i++)
	{
		appData.idList.id[i].filename = new char[MAX_STR];
		fgets(appData.idList.id[i].filename, MAX_STR, f);
		strdelrn(appData.idList.id[i].filename);

		if (!no_cache) fread(&appData.idList.id[i].wcount, sizeof(int), 1, fCache);
	}
	appData.idList.id[i].filename = NULL;
	if (!no_cache) fclose(fCache);
	fclose(f);
	return 0;
}

int updateIndex(AppData &appData)
{
	char *line = new char[MAX_STR];
	int countL = 0;

	FILE *f = fopen(appData.seSetting.indexFile, "rt");
	if (f == NULL) return 1;
	do
	{
		fgets(line, MAX_STR, f);
		countL++;
	} while (!feof(f));
	fclose(f);
	appData.seSetting.numfile = countL;
	delete line;
	return 0;
}

void createIndexCache(AppData appData)
{
	int wcount;
	FILE *f = fopen("cache//index.dat", "wb");
	for (int i = 0 ; appData.idList.id[i].filename != NULL; i++)
	{
		wcount = appData.idList.id[i].wcount;
		fwrite((void*)&wcount, sizeof(int), 1, f);
	}
	fclose(f);
}
/* 
 * Giai phong bo nho
 */
void freeIndex(AppData &appData)
{
	for (int i = 0; appData.idList.id[i].filename != NULL; i++)
		delete appData.idList.id[i].filename;
	delete appData.idList.id;
}