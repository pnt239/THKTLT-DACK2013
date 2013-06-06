/*
 * 
 */

#include "avl.h"

/* Tao node moi */
PAVLNode avl_create_node(void *data)
{
	PAVLNode pNode;
	pNode = new AVLNode;
	if (pNode == NULL){
		return NULL;
	}
	pNode->data = data;
	pNode->pLeft = NULL;
	pNode->pRight = NULL;
	pNode->balFactor = 0;
	return pNode;
}

/* Xoay trai */
void avl_left_rotate(PAVLNode &P)
{
	PAVLNode Q;
	Q = P->pRight;
	P->pRight = Q->pLeft;
	Q->pLeft = P;
	P = Q;
}

/* Xoay phai */
void avl_right_rotate(PAVLNode &P)
{
	PAVLNode Q;
	Q = P->pLeft;
	P->pLeft = Q->pRight;
	Q->pRight = P;
	P = Q;
}

/* Can bang trai */
void avl_left_balance(PAVLNode &P)
{
	switch(P->pLeft->balFactor){
	case 1:
		avl_right_rotate(P);
		P->balFactor = 0;
		P->pRight->balFactor = 0;
		break;
	case 2:
		avl_left_rotate(P->pLeft);
		avl_right_rotate(P);
		switch(P->balFactor){
		case 0:
			P->pLeft->balFactor= 0;
			P->pRight->balFactor= 0;
			break;
		case 1:
			P->pLeft->balFactor= 0;
			P->pRight->balFactor= 2;
			break;
		case 2:
			P->pLeft->balFactor= 1;
			P->pRight->balFactor= 0;
			break;
		}
		P->balFactor = 0;
		break;
	}
}

/* Can bang phai */
void avl_right_balance(PAVLNode &P)
{
	switch(P->pRight->balFactor){
	case 1:
		avl_right_rotate(P->pRight);
		avl_left_rotate(P);
		switch(P->balFactor){
		case 0:
			P->pLeft->balFactor= 0;
			P->pRight->balFactor= 0;
			break;
		case 1:
			P->pLeft->balFactor= 1;
			P->pRight->balFactor= 0;
			break;
		case 2:
			P->pLeft->balFactor= 0;
			P->pRight->balFactor= 2;
			break;
		}
		P->balFactor = 0;
		break;
	case 2:
		avl_left_rotate(P);
		P->balFactor = 0;
		P->pLeft->balFactor = 0;
		break;
	}
}

/* Them node moi 
 * Tra ve: 0   : trung du lieu
 *         > 0 : Don't care
 */
int avl_insert_node(PAVLTree &tree, void *data, cbComp comp, PAVLNode &cpnode)
{
	int res;
	if (tree == NULL) {
		tree = avl_create_node(data);
		cpnode = tree;
		if(tree == NULL) return -1;
		return 2;
	} else {
		int cp = comp(tree->data, data);
		if (cp == 0) { //tree->data = data
			cpnode = tree;
			return 0;
		} else if (cp > 0) { //tree->data > data
			res = avl_insert_node(tree->pLeft, data, comp, cpnode);
			if (res < 2) return res;
			switch (tree->balFactor) {
			case 0:
				tree->balFactor = 1;
				return 2;
			case 1:
				avl_left_balance(tree);
				return 1;
			case 2:
				tree->balFactor = 0;
				return 1;
			}
		} else{
			res = avl_insert_node(tree->pRight, data, comp, cpnode);
			if (res<2) return res;
			switch (tree->balFactor) {
			case 0:
				tree->balFactor=2;
				return 2;
			case 1:
				tree->balFactor = 0;
				return 1;
			case 2:
				avl_right_balance(tree);
				return 1;
			}
		}
	}
}

/* Duyet cay AVL*/
void avl_traverse(PAVLNode t, int type, showData showD)
{
	if(t!=NULL)
	{
		if (type == 1) { // RNL
			avl_traverse(t->pRight, type, showD);
			showD(t->data);
			avl_traverse(t->pLeft, type, showD);
		} else if (type == 2) { //LNR
			avl_traverse(t->pLeft, type, showD);
			showD(t->data);
			avl_traverse(t->pRight, type, showD);
		}
	}
}

void avl_ex_traverse(PAVLNode t, int type, processData procD, void *carryD)
{
	int carry;
	if(t!=NULL)
	{
		if (type == 1) { // RNL
			avl_ex_traverse(t->pRight, type, procD, carryD);
			procD(t->data, carryD);
			avl_ex_traverse(t->pLeft, type, procD, carryD);
		} else if (type == 2) { //LNR
			avl_ex_traverse(t->pLeft, type, procD, carryD);
			procD(t->data, carryD);
			avl_ex_traverse(t->pRight, type, procD, carryD);
		}
	}
}

/* Giai phong bo nho */
void avl_removeall(PAVLNode &t, freeData fdata)
{
	if(t!=NULL){
		avl_removeall(t->pLeft, fdata);
		avl_removeall(t->pRight, fdata);
		fdata(t->data);
		delete t;
	}
}