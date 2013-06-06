#pragma once

#include <stdio.h>
#include "appdef.h"

/* Ham so sanh
 * Tra ve:
 *      -1 - a < b
 *       0 - a = b
 *       1 - a > b
 */
typedef int (*cbComp)(void *, void *);

typedef void (*freeData)(void *);

typedef void (*showData)(void *);

typedef void (*processData)(void *data, void *carry);

int avl_insert_node(PAVLTree &tree, void *data, cbComp comp, PAVLNode &cpnode);
void avl_removeall(PAVLNode &t, freeData fdata);
void avl_traverse(PAVLNode t, int type, showData showD);

void avl_ex_traverse(PAVLNode t, int type, processData procD, void *carry);