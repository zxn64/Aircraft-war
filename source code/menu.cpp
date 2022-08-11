#include"menu.h"
#include"instructions.h"
#include<easyx.h>
#include<conio.h>
#include<stdlib.h>

void showmenu() {
	IMAGE main_menu;
	loadimage(&main_menu, _T("res/menu.jpg"));
	putimage(0, 0, &main_menu);
}

bool menu() {
	char option;
select1:
	showmenu();
select2:
	option = _getch();
	switch (option) {
	case '1':
		instructions();
		goto select1;
		break;
	case '2':
		mciSendString(_T("close bgm1"), NULL, 0, 0);
		return true;
	case '3':
		mciSendString(_T("close bgm1"), NULL, 0, 0);
		return false;
	default:
		goto select2;
	}
}