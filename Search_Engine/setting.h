#pragma once

#include <string.h>
#include "appdef.h"
#include "file.h"

int loadSetting(SESetting &seSetting);
void writeSetting(SESetting &seSetting);
void freeSetting(SESetting &seSetting);