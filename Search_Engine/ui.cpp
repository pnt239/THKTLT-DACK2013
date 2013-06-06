#include "ui.h"

int createMenu(STR menu[])
{
	system("cls");
	showHeader();
	int choice;
	for (int i = 0; menu[i] != NULL; i++)
		printf("%s\n", menu[i]);
	printf("   > ");
	scanf("%d", &choice);
	return choice;
}

STR createInput(STR text)
{
	system("cls");
	showHeader();
	char *str = new char[MAX_STR];
	printf("%s\n", text);
	flushall();
	printf("   > ");
	gets(str);
	return str;
}

int createBox(STR text, int style, bool cont)
{
	if (!cont) {
		system("cls");
		showHeader();
	}
	while (1)
	{
		printf("%s ", text);
		if (style == 1)
			printf("[o] > ");
		else if (style == 2)
			printf("[y/n] > ");

		flushall();
		char bx = getchar();
		if (bx == 'o' && style == 1) return BX_OK;
		else if (bx == 'y' && style == 2) return BX_YES;
		else if (bx == 'n' && style == 2) return BX_NO;
	}
}

void showMsg(int id)
{
	char *MSG[] = {"Da them file vao index thanh cong.", \
					"Da xoa file trong index thanh cong."};
	printf("\nMessage:\n   > ");
	printf("%s\n", MSG[id]);
}

void showHeader()
{
	printf("\nHungry Birds Search Engine v1.0\n");
	for (int i = 0; i < 40; i++)
		printf("%c", 196);
	printf("\n\n");
}

void pause()
{
	printf("\nContinuous...");
	getch();
}