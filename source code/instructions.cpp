#include"instructions.h"
#include<easyx.h>
#include<conio.h>

void instructions() {
	IMAGE instructions[6];
	int page = 0;
	loadimage(&instructions[0], _T("res/instruction_1.jpg"));
	loadimage(&instructions[1], _T("res/instruction_enemy_1.jpg"));
	loadimage(&instructions[2], _T("res/instruction_enemy_2.jpg"));
	loadimage(&instructions[3], _T("res/instruction_enemy_3.jpg"));
	loadimage(&instructions[4], _T("res/instruction_player.jpg"));
	loadimage(&instructions[5], _T("res/instruction_Tips.jpg"));
	while (page >= 0 && page <= 5) {
		putimage(0, 0, &instructions[page]);
		page += turn_page();
	}
	return;
}

int turn_page() {
	Sleep(200);
	while (1) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			return -1;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			return 1;
		}
	}
}