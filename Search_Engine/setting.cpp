/*
 * File chua cac ham khoi tao, load du lieu tu setting file
 */

#include "setting.h"

int loadSetting(SESetting &seSetting)
{
	FILE *f = fopen("setting.dat", "rt");
	if (f == NULL) return 1;
	fgets(seSetting.dataFolder, MAX_STR, f);
	fscanf(f, "%d", &seSetting.indexSize);
	fscanf(f, "%d", &seSetting.numfile);
	fclose(f);

	seSetting.dataFolder[strlen(seSetting.dataFolder)-1] = 0;

	sprintf(seSetting.indexFile, "%s\\index.txt", seSetting.dataFolder);
	sprintf(seSetting.metafile, "cache\\meta.db");
	return 0;
}

void writeSetting(SESetting &seSetting)
{
	FILE *f = fopen("setting.dat", "wt");
	fprintf(f, "%s\n%d\n%d", seSetting.dataFolder, seSetting.indexSize, seSetting.numfile);
	fclose(f);
}

void freeSetting(SESetting &seSetting)
{
	delete seSetting.dataFolder;
	delete seSetting.indexFile;
}