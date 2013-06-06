#pragma once

#include <stdio.h>
#include "appdef.h"

PLList ll_create();
PLNode ll_create_node(void *data);
void ll_insert(PLList pllist, PLNode pos, PLNode val);
void ll_free(PLList pllist, FreeData free);

void ll_show(PLList pllist);