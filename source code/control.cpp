#include"control.h"
#include<stdlib.h>
#include<conio.h>

//gd: get and deal;true: 继续游戏 false：重新开始
bool gdorder(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets) {
	if (GetAsyncKeyState(0x57) & 0x8000) {
		player->move(UP);
	}
	if (GetAsyncKeyState(0x53) & 0x8000) {
		player->move(DOWN);
	}
	if (GetAsyncKeyState(0x41) & 0x8000) {
		player->move(LEFT);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {
		player->move(RIGHT);
	}
	if (GetAsyncKeyState(0x4b) & 0x8000) {
		player->shoot(bullets);
	}
	if (GetKeyState(VK_SPACE) & 0x8000) {
		pause();
	}
	if (GetAsyncKeyState(0x52) & 0x8000) {
		clear(enemies, bullets);
		clear_in();
		return false;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		clear(enemies, bullets);
		exit(0);
	}
	return true;
}

void clear(std::list<Entity*>* enemies, std::list<Bullet*>* bullets) {
	for (std::list<Entity*>::iterator i = enemies->begin(); i != enemies->end(); i++) {
		delete (*i);
	}
	enemies->clear();
	for (std::list<Bullet*>::iterator i = bullets->begin(); i != bullets->end(); i++) {
		delete (*i);
	}
	bullets->clear();
}

void pause() {
	IMAGE pause_0, pause_1;
	loadimage(&pause_0, _T("res/0pause.jpg"));
	loadimage(&pause_1, _T("res/1pause.jpg"));
	putimage((getwidth() - pause_0.getwidth()) / 2, (getheight() - pause_0.getheight()) / 3, &pause_0, SRCAND);
	putimage((getwidth() - pause_1.getwidth()) / 2, (getheight() - pause_1.getheight()) / 3, &pause_1, SRCPAINT);
	settextcolor(WHITE);
	settextstyle(64, 0, _T("黑体"));
	outtextxy(500, 500, L"按任意键继续");
	Sleep(100);
	system("pause");
	Sleep(50);
	return;
}

void clear_in() {
	while (_getch() != 'r');
}