#pragma once

#define CON_WIDTH 80
#define CON_HEIGHT 20

#define MAX_STR 260
#define MAX_LINE 65536
#define MAX_WORD 40

#define STR char*

#define IS_TERML 0.00001f
#define IS_TERMR 0.5f

typedef struct tagIndex
{
	STR filename;
	int wcount;
} Index, *PIndex;

typedef struct tagIDList
{
	PIndex id;
} IDList;

typedef struct tagSESetting
{
	char *dataFolder, *indexFile, *metafile;
	int indexSize;
	int numfile;
} SESetting;

typedef struct tagAppData
{
	IDList idList;
	SESetting seSetting;
} AppData;

typedef struct tagLNode LNode, *PLNode;
struct tagLNode {
	void *data;
	PLNode next;
	PLNode prev;
};

typedef struct tagLList LList, *PLList;
struct tagLList {
	void *data;
	PLNode head;
	PLNode tail;
};

typedef struct tagAVLNode AVLNode, *PAVLNode, *PAVLTree;
struct tagAVLNode
{
	void *data;
	int balFactor; // 0: can bang, 1: lech trai, 2: lech phai
	PAVLNode pLeft;
	PAVLNode pRight;
};

typedef struct tagDoc
{
	int DocID;
	float tf;
	int occur;
} Doc, *PDoc;

typedef struct tagTerm
{
	char *word;
	int wlen;
	PLList doclist;
	PAVLTree ndoclist;
} Term, *PTerm;

typedef struct tagMap
{
	char *wbegin, *wend;
	int dbegin, dend;
} Map;

typedef void (*FreeData)(void *data);