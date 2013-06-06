/*
 * File chua cac ham thu thi chuong trinh
 */

#include "doaction.h"

void runApp(int argc,char *argv[], AppData &appData)
{
	initApp(appData);
	if (argc == 1)
	{
		showMenu(appData);
	}
	onExit(appData);
}

void initApp(AppData &appData)
{
	appData.seSetting.dataFolder = new char[MAX_STR];
	appData.seSetting.indexFile = new char[MAX_STR];
	appData.seSetting.metafile = new char[MAX_STR];
	appData.seSetting.indexSize = 0;
	appData.idList.id = NULL;

	if (loadSetting(appData.seSetting) == 1)
	{
		// Khong tim thay file thiet lap
		char *folder = createInput("Nhap thu muc chua file index (khong co \\ dang sau)");
		sprintf(appData.seSetting.indexFile, "%s\\index.txt", folder);
		sprintf(appData.seSetting.metafile, "cache\\meta.db");
		appData.seSetting.dataFolder = folder;
	}

	// Lay kich thuoc file index hien tai
	int indexSize = getFileSize(appData.seSetting.indexFile);
	if (indexSize > appData.seSetting.indexSize || indexSize < appData.seSetting.indexSize)
	{
		appData.seSetting.indexSize = indexSize;
		updateIndex_Meta(appData);
	}
	
	loadIndex(appData);
}

void onExit(AppData &appData)
{
	// Luu setting vao file
	writeSetting(appData.seSetting);
	// Giai phong Setting
	freeSetting(appData.seSetting);
	// Giai phong index
	freeIndex(appData);
}

void showMenu(AppData &appData)
{
	int choice = -1;
	char *menu[5] = {"1. Them van ban", "2. Xoa van ban", "3. Tim kiem", "0. Thoat", NULL};
	while (1)
	{
		choice = createMenu(menu);
		switch(choice)
		{
		case 1:
			addIndex(appData);
			break;
		case 2:
			delIndex(appData);
			break;
		case 3:
			startSearch(appData);
			break;
		}
		if (choice == 0)
			break;
	}
}

void updateIndex_Meta(AppData &appData)
{
	// Update index
	updateIndex(appData);
	createBox("There is a new index. Program will update automatically!", 1);
	printf("\nUpdating!\n");
	// Load index
	loadIndex(appData);
	// Update meta
	updateMeta(appData);
	// Update index cache
	createIndexCache(appData);
	pause();
}

void addIndex(AppData &appData)
{
	STR input = createInput("Nhap ten file can them vao:");
	printf("Log:\n   > Them du lieu vao index...\n");
	addID(input, appData);
	appData.seSetting.indexSize = getFileSize(appData.seSetting.indexFile);
	appData.seSetting.numfile++;
	printf("   > Cap nhap cache file...");
	pause();
	// Update index & meta
	updateIndex_Meta(appData);
	showMsg(0);
	pause();
	delete input;
}

void delIndex(AppData &appData)
{
	STR input = createInput("Nhap ten file can xoa vao:");
	printf("Log:\n   > Xoa du lieu file index...\n");
	delID(input, appData);
	appData.seSetting.indexSize = getFileSize(appData.seSetting.indexFile);
	appData.seSetting.numfile--;
	printf("   > Cap nhap cache file...");
	pause();
	// Update index & meta
	updateIndex_Meta(appData);
	showMsg(1);
	pause();
	delete input;
}

void startSearch(AppData &appData)
{
	system("cls");
	showHeader();
	STR input = createInput("Nhap tu khoa vao:");
	Result res = qr_search(input, appData);

	printf("Tim thay %d ket qua trong %lf (sec). Duoi day la vai ket qua mo dau:\n", res.numRes, res.elapsed_secs);
	qr_show_result(res, appData, 10);
	if (createBox("Ban co muon xem het khong?", 2, true) == BX_YES)
	{
		clock_t begin = clock();
		qr_show_result(res, appData, -1);
		clock_t end = clock();

		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Hien thi %d ket qua, trong %lf (seconds)\n",res.numRes, elapsed_secs);
	} 
	pause();
	delete input;
}
