#pragma once

#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "appdef.h"

#define BX_OK 1
#define BX_YES 2
#define BX_NO 3

void showHeader();
void showMsg(int id);
int createMenu(STR menu[]);
STR createInput(STR text);
int createBox(STR text, int style, bool cont = false);

void pause();