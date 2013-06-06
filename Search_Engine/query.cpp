/*
 * File chua cac truy van, tim kiem du lieu
 */

#include "query.h"

int qr_search_mix(PDocMix docMix, int ipos, int idDoc)
{
	for (int i = 0; i < ipos; i++)
		if (docMix[i].iDoc == idDoc)
			return i;
	return -1;
}

void qr_mix(PDocMix docMix, int &ipos, PDoc pdoc, int ndoc)
{
	int j;
	for (int i = 0; i < ndoc; i++)
		if ((j = qr_search_mix(docMix, ipos, pdoc[i].DocID)) > -1)
			docMix[j].count++;
		else
		{
			docMix[ipos].iDoc = pdoc[i].DocID;
			docMix[ipos].count = 1;
			ipos++;
		}
}

Result qr_search(char *str, AppData appData)
{
	int wcount, dcout, max_dcout = 0;
	char **list = strsplit(str, wcount);
	PDoc *dlist = new PDoc[wcount];
	int *dclist = new int[wcount];

	clock_t begin = clock();

	// Load cac document lien quan
	for (int i = 0; list[i] != NULL; i++)
	{
		dlist[i] = loadMeta(list[i], dcout);
		dclist[i] = dcout;
		if (dcout > max_dcout) max_dcout = dcout;
	}

	PDocMix docMix = new DocMix[wcount*max_dcout];
	int ipos = 0;
	
	// Tim phan giao + xep hang
	for (int i = 0; i < wcount; i++)
		qr_mix(docMix, ipos, dlist[i], dclist[i]);

	// Sap xep ket qua
	qr_sort_result(docMix, ipos);
	clock_t end = clock();

	Result ret = {ipos, docMix, double(end - begin) / CLOCKS_PER_SEC, wcount};
	return ret;
}

void qr_sort_result(PDocMix docMix, int length)
{
	//Algorithm
	for(int i = 0; i < (length -1); i++)
	{
		for (int j=(i + 1); j < length; j++)
		{
			if (docMix[i].count < docMix[j].count)
			{
				DocMix temp = docMix[i];
				docMix[i] = docMix[j];
				docMix[j] = temp;
			}
		}
	}
}

void qr_show_result(Result res, AppData appData, int num_show)
{
	int showall = (num_show != -1)?num_show:res.numRes;
	if (showall > res.numRes) showall = res.numRes;
	char *filename = new char[MAX_STR];
	printf("\n");
	for (int i = 0; i < showall; i++)
	{
		sprintf(filename, "%s\\%s", appData.seSetting.dataFolder, appData.idList.id[res.pDoxMix[i].iDoc].filename);
		char *title = getFileTitle(filename);
		strdelrn(title);
		printf("%d. %s\n\tin '%s' | %d match\n", i+1, title, appData.idList.id[res.pDoxMix[i].iDoc].filename, res.pDoxMix[i].count);
	}
	delete filename;
}