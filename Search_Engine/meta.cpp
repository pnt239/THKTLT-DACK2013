/*
 * File chua cac ham khoi tao, load du lieu tu metafile
 */

#include "meta.h"

PDoc loadDoc(int adr, int cout)
{
	FILE *f = fopen("cache\\meta.db", "rb");
	fseek(f, (long)adr, SEEK_SET);

	PDoc dlist = new Doc[cout];
	fread(dlist, sizeof(Doc), cout, f);
	return dlist;
}

PDoc loadMeta(char *keyword, int &DocC)
{
	char *metafile = new char[MAX_STR];
	int slen = 0, adr = 0, dcount = 0;
	char *word;
	bool ok = false;

	sprintf(metafile, "cache\\%c.mta", keyword[0]);

	FILE *f = fopen(metafile, "rb");
	if (f == NULL) return NULL;

	while (!feof(f))
	{
		fread(&slen, 1, 1, f);
		word = new char[slen+1];
		fread(word, 1, slen+1, f);
		fread(&adr, sizeof(int), 1, f);
		fread(&dcount, sizeof(int), 1, f);
		if (strcmp(keyword, word) == 0) {
			ok = true;
			break;
		}
	}
	fclose(f);
	delete metafile;

	if (ok)
	{
		DocC = dcount;
		return loadDoc(adr,  dcount);
	}
	
	DocC = 0;
	return NULL;
}

void updateMeta(AppData &appData)
{
	clock_t begin = clock();
	//createMeta(appData);
	new_createMeta(appData);
	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	printf("Total Time: %lf (seconds)", elapsed_secs);
}

/* ======== since v2.0 ======== */
/* Xu ly voi Doc */
PDoc new_doc_create(int DocID)
{
	PDoc pdoc = new Doc;
	pdoc->DocID = DocID;
	pdoc->occur = 1;
	pdoc->tf = 0;
	return pdoc;
}

/* Ham so sanh 2 doc */
int new_doc_comp(void *a, void *b)
{
	return ((PDoc)a)->DocID - ((PDoc)b)->DocID;
}

/* Tao ra 1 danh doc */
PAVLTree new_docs_create(int DocID)
{
	PAVLTree Docs = NULL;
	PAVLNode tnode;
	avl_insert_node(Docs, new_doc_create(DocID), new_doc_comp, tnode);
	return Docs;
}

void free_doc(void *data)
{
	delete (PDoc)data;
}

/* Xu ly voi Term */
/* Tao ra 1 term_large gom 26 danh sach term */
PAVLTree *new_terms_large_create()
{
	PAVLTree *tllist = new PAVLTree[26];
	for (int i = 0; i < 26; i++)
		tllist[i] = NULL;
	return tllist;
}

/* Tao ra 1 term */
PTerm new_term_create(char *word, int wlen, int DocID)
{
	PTerm pterm = new Term;
	pterm->word = word;
	pterm->wlen = wlen;
	pterm->ndoclist = new_docs_create(DocID);
	return pterm;
}

/* Ham so sanh 2 term */
int new_term_comp(void *a, void *b)
{
	return strcmp(((PTerm)b)->word, ((PTerm)a)->word);
}

/* Giai phong 1 term */
void new_free_term(void *data)
{
	delete ((PTerm)data)->word;
	avl_removeall(((PTerm)data)->ndoclist, free_doc);
	delete (PTerm)data;
}

/* Giai phong toan bo tearm list */
void new_free_terms(PAVLTree tlist)
{
	avl_removeall(tlist, new_free_term);
}

/* Giai phong toan bo terms_large gom 26 tearm list */
void new_free_terms_large(PAVLTree *tllist)
{
	for (int i = 0; i < 26; i++)
		new_free_terms(tllist[i]);
	delete tllist;
}

/* Test Display Don't care */
void new_show_doc(void *data)
{
	printf("->Doc%d(%d)", ((PDoc)data)->DocID, ((PDoc)data)->occur);
}

void new_show_data(void *data)
{
	printf("%s", ((PTerm)data)->word);
	avl_traverse(((PTerm)data)->ndoclist, 2, new_show_doc);
	printf("\n");
}

/* Write data */
void new_write_doc(void *data, void *carryD)
{
	PDoc pdoc = (PDoc)data;
	PCarryData pcd = (PCarryData)carryD;
	pcd->dcount++;
	pcd->pcur += fwrite(pdoc, sizeof(Doc), 1, pcd->fMeta)*sizeof(Doc);
}

void new_write_term(void *data, void *carryD)
{
	PTerm pterm = (PTerm)data;
	PCarryData pcd = (PCarryData)carryD;
	// Ghi vao file theo cau truc <so chu trong tu><tu><dia chi><so luong>
	fwrite(&pterm->wlen, 1, 1, pcd->f);
	fwrite(pterm->word, 1, pterm->wlen+1, pcd->f);
	// Ghi dia chi danh sach doc o file meta.db
	fwrite(&pcd->pcur, sizeof(int), 1, pcd->f);
	((PCarryData)carryD)->dcount = 0;
	//Ghi danh sach doc
	avl_ex_traverse(pterm->ndoclist, 2, new_write_doc, carryD);
	// Ghi so luong doc
	fwrite(&pcd->dcount, sizeof(int), 1, pcd->f);
}

/* Doc 1 van van */
int new_readDoc(PAVLTree *tllist, STR docfile, int DocID)
{
	PAVLNode ttnode, tdnode;
	PTerm tterm = NULL;
	PDoc tdoc = NULL;
	char *line = new char[MAX_LINE], *word;
	int offset, wcount = 0, wlen;

	FILE *f = fopen(docfile, "rt");
	if (f == NULL) return 0;
	// Doc dong tieu de
	fgets(line, MAX_LINE, f);
	while (!feof(f))
	{
		fgets(line, MAX_LINE, f);
		offset = 0;
		while (offset != -1 && (word = getword(line, wlen, offset)) != NULL)
		{
			if (word[0] == 0) continue;

			tterm = new_term_create(word, wlen, DocID);
			if (avl_insert_node(tllist[word[0] - 'a'], tterm, new_term_comp, ttnode) == 0) {
				delete tterm;
				tdoc = new_doc_create(DocID);
				if (avl_insert_node(((PTerm)ttnode->data)->ndoclist, tdoc, new_doc_comp, tdnode) == 0) {
					delete tdoc;
					((PDoc)tdnode->data)->occur++;
				}
			}
			wcount++;
			// Den cuoi dong
			if (offset == -1) break;
		}
	}
	fclose(f);
	return wcount;
}

/* Tao meta moi */
void new_createMeta(AppData &appData)
{
	/* Doc van ban lay tu */
	PAVLTree *tllist = new_terms_large_create();
	STR docfile = new char[MAX_STR];
	int cur_add = 0;
	//clock_t begin = clock();
	for (int idoc = 0; appData.idList.id[idoc].filename != NULL; idoc++)
	{
		sprintf(docfile, "%s\\%s", appData.seSetting.dataFolder, appData.idList.id[idoc].filename);
		// Lay tung tu co trong van ban cho vao link list va tra ve so tu trong van ban
		appData.idList.id[idoc].wcount = new_readDoc(tllist, docfile, idoc);
	}
	delete docfile;

	//for (int i = 0; i < 26; i++)
	//	if (tllist[i] != NULL)
	//		avl_traverse(tllist[i], 1, new_show_data);

	/* Luu tu doc duoc vao file meta */
	STR metadict = new char[MAX_STR];
	PCarryData carryD = new CarryData;
	FILE *fMeta = fopen(appData.seSetting.metafile, "wb"), *f = NULL;

	carryD->pcur = 0;
	carryD->fMeta = fMeta;

	for (int i = 0; i < 26; i++) {
		if (tllist[i] == NULL) continue;
		sprintf(metadict, "cache\\%c.mta", i + 'a'); // Khoi tao duong dan
		f = fopen(metadict, "wb"); // Mo file

		carryD->f = f;
		avl_ex_traverse(tllist[i], 1, new_write_term, carryD);

		fclose(f);
	}
	fclose(fMeta);
	//end = clock();
	//elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//printf("Write Time: %lf (seconds)\n", elapsed_secs);
	delete carryD;
	delete metadict;
	new_free_terms_large(tllist);
}

/* ======== since v2.0 ======== */

