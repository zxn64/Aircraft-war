#include"game.h"
#include"control.h"
#include"large_enemy.h"
#include"medium_enemy.h"
#include"small_enemy.h"

using namespace std::chrono;

void game() {
	mciSendString(_T("open res/background_music_2.mp3 alias bgm2"), NULL, 0, 0);
	mciSendString(_T("play bgm2 repeat"), NULL, 0, 0);
	steady_clock::time_point start = steady_clock::now();
	Bullet::init();
	Player::init();
	Small_enemy::init(1);
	Medium_enemy::init(10, 1s);
	Large_enemy::init(50, 1s);
	std::list<Entity*>* enemies = new std::list<Entity*>;
	std::list<Bullet*>* bullets = new std::list<Bullet*>;
	int score = 0;
	Player* player = new Player(10, 200ms);
	while (1) {
		entity(player, enemies, bullets, &score, &start);
		if (!gdorder(player, enemies, bullets)||!deal_player(enemies, bullets, player, score)) {
			mciSendString(_T("close bgm2"), NULL, 0, 0);
			mciSendString(_T("close shoot"), NULL, 0, 0);
			mciSendString(_T("close boom"), NULL, 0, 0);
			return;
		}
		print(player, enemies, bullets, score);
		Sleep(33);
	}
}

bool deal_player(std::list<Entity*>* enemies, std::list<Bullet*>* bullets, Player* player, int score) {
	if (player->gs_boom('g')) {
		clear(enemies, bullets);
		die(score);
		return false;
	}
	for (std::list<Bullet*>::iterator j = bullets->begin(); j != bullets->end(); j++) {
		if (player->Impact_checking((*j)->get('x') - player->get('x'), (*j)->get('y') - player->get('y'))) {
			player->be_shot();
			if (!player->gchp(-(*j)->damage)) {
				player->gs_boom('s');
			}
			delete (*j);
			if (++j == bullets->end()) {
				bullets->erase(--j);
				return true;
			}
			j = bullets->erase(--j);
		}
	}
	return true;
}

void die(int score) {
	IMAGE game_over;
	loadimage(&game_over, _T("res/game_over.jpg"));
	putimage(0, 0, &game_over);
	TCHAR s[100];
	setbkmode(TRANSPARENT);
	settextcolor(RGB(72, 92, 215));
	settextstyle(64, 0, _T("ºÚÌå"));
	_stprintf_s(s, L"%d", score);
	outtextxy(698, 381, s);
	clear_in();
}