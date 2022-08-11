#include"print.h"
#include<easyx.h>

void print(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets, int score) {
	IMAGE background;
	loadimage(&background, _T("res/background.jpg"), getwidth(), getheight());
	SetWorkingImage(&background);
	for (std::list<Bullet*>::iterator i = bullets->begin(); i != bullets->end(); i++) {
		(*i)->print();
	}
	player->print();
	for (std::list<Entity*>::iterator i = enemies->begin(); i != enemies->end(); i++) {
		(*i)->print();
	}
	setbkmode(TRANSPARENT);
	settextcolor(RGB(72, 92, 215));
	settextstyle(32, 0, _T("ºÚÌå"));
	TCHAR s[100];
	_stprintf_s(s, L"·ÖÊý£º%d", score);
	outtextxy(0, 0, s);
	_stprintf_s(s, L"HP£º%d", player->gchp());
	outtextxy(0, 32, s);
	_stprintf_s(s, L"µ¯¼Ð£º%d", player->gcclip());
	outtextxy(0, 64, s);
	SetWorkingImage();
	putimage(0, 0, &background);
}