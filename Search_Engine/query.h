#pragma once

#include <stdio.h>
#include "appdef.h"
#include "stringex.h"
#include "file.h"
#include "meta.h"

typedef struct tagDocMix
{
	int iDoc;
	int count;
} DocMix, *PDocMix;


typedef struct tagResult
{
	int numRes;
	PDocMix pDoxMix;
	double elapsed_secs;
	int numQR;
} Result;

Result qr_search(char *str, AppData appData);
void qr_sort_result(PDocMix docMix, int length);
void qr_show_result(Result res, AppData appData, int num_show = 10);