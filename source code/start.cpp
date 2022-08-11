#pragma comment (lib, "winmm.lib")
#include<Windows.h>
#include"start.h"
#include<easyx.h>

void start() {
	mciSendString(_T("open res/background_music_1.mp3 alias bgm1"), NULL, 0, 0);
	mciSendString(_T("play bgm1 repeat"), NULL, 0, 0);
	IMAGE start;
	loadimage(&start, _T("res/start.jpg"));
	putimage(0,0, &start);
	system("pause");
	return;
}