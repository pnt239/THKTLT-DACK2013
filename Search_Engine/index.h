#pragma once

#include <stdio.h>
#include <string.h>
#include "appdef.h"
#include "stringex.h"
#include "file.h"

void addID(char *filename, AppData appData);
void delID(char *filename, AppData appData);
int updateIndex(AppData &appData);
int loadIndex(AppData &appData);
void createIndexCache(AppData appData);
void freeIndex(AppData &appData);
