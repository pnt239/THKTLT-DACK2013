#pragma once

#include "setting.h"
#include "ui.h"

#include "index.h"
#include "meta.h"
#include "query.h"

void showMenu(AppData &appData);
void initApp(AppData &appData);
void onExit(AppData &appData);
void runApp(int argc,char *argv[], AppData &appData);

void addIndex(AppData &appData);
void delIndex(AppData &appData);
void startSearch(AppData &appData);
void updateIndex_Meta(AppData &appData);
void updateProgress(float percent);