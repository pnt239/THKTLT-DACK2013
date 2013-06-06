/*
 * File chua cac ham khoi tao, chen, giai phong danh sach lien ket
 */

#include "linklist.h"

/*
 * Tao 1 node voi data cho truoc khong biet kieu
 */
PLNode ll_create_node(void *data)
{
	PLNode pnode = new LNode;
	pnode->data = data;
	pnode->prev = pnode->next = NULL;
	return pnode;
}

/*
 * Tao 1 danh sach lien ket
 */
PLList ll_create()
{
	PLList pllist = new LList;
	pllist->head = pllist->tail = NULL;
	return pllist;
}

/*
 * Chen vao node val truoc node pos
 * pos == NULL : Them vao cuoi
 * pllist->head == NULL : Them vao dau
 */
void ll_insert(PLList pllist, PLNode pos, PLNode val)
{
	if (pllist->head == NULL)
		pllist->head = pllist->tail = val;
	else
	{
		if (pos == NULL) { // Them vao cuoi danh sach
			PLNode plast = pllist->tail;
			pllist->tail = plast->next = val;
			val->prev = plast;
		} else if (pos == pllist->head) { // Tham vao dau danh sach
			val->next = pos;
			pllist->head = pos->prev = val;
		} else { // Them o giua danh sach
			PLNode pprev = pos->prev;
			pos->prev = pprev->next = val;
			val->prev = pprev;
			val->next = pos;
		}
	}
}

void ll_free(PLList pllist, FreeData free)
{
	PLNode pnext = NULL;
	for (PLNode pnode = pllist->head; pnode != NULL; pnode = pnext) 
	{
		pnext = pnode->next;
		free(pnode->data);
		delete pnode;
	}
	delete pllist;
}

void temp_showdoc(PLList pllist)
{
	for (PLNode plnode = pllist->head; plnode != NULL; plnode = plnode->next)
	{
		printf("->Doc%d(%d)", ((PDoc)plnode->data)->DocID, ((PDoc)plnode->data)->occur);
	}
}

void ll_show(PLList pllist)
{
	for (PLNode plnode = pllist->head; plnode != NULL; plnode = plnode->next)
	{
		printf("%s", ((PTerm)plnode->data)->word);
		temp_showdoc(((PTerm)plnode->data)->doclist);
		printf("\n");
	}
}