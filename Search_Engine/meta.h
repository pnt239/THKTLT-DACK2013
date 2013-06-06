#pragma once

#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "appdef.h"
#include "linklist.h"
#include "avl.h"
#include "stringex.h"

typedef struct tagCarryData
{
	FILE *f, *fMeta;
	int pcur, dcount;
} CarryData, *PCarryData;



PDoc loadDoc(int adr, int cout);
PDoc loadMeta(char *keyword, int &dcout);

void updateMeta(AppData &appData);
void new_createMeta(AppData &appData);
// Term

// Docs
