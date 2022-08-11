#include"small_enemy.h"
#include<iostream>

int Small_enemy::score, Small_enemy::speed;
IMAGE Small_enemy::usual[2], Small_enemy::blow_up[4][2];

Small_enemy::Small_enemy(int x, int y) {
	this->x = x;
	this->y = y;
	hp = score;
	n_boom = 0;
	speed = 8;
}

void Small_enemy::move() {
	y += speed;
}

//get 'x'¡¢'y'¡¢'s':score
int Small_enemy::get(char c) {
	switch (c) {
	case 'x':
		return x;
	case 'y':
		return y;
	case 's':
		return score;
	default:
		std::cout << "EORROR£¡Get wrong input in Small_enemy::get(char c)";
		exit(1);
	}
}

void Small_enemy::be_shot() {
	return;
}

void Small_enemy::print() {
	if (!n_boom) {
		putimage(x, y, &usual[0], SRCAND);
		putimage(x, y, &usual[1], SRCPAINT);
		return;
	}
	putimage(x, y, &blow_up[n_boom - 1][0], SRCAND);
	putimage(x, y, &blow_up[n_boom - 1][1], SRCPAINT);
	n_boom++;
}

bool Small_enemy::gs_boom(char c) {
	switch (c) {
	case 's':
		return n_boom++;
	case 'g':
		return n_boom > max_boom;
	default:
		std::cout << "Eorror in Small_enemy::gs_boom(char c)";
		exit(1);
	}
}

//gc:get or change
int Small_enemy::gchp(int n = 0) {
	hp += n;
	return hp;
}

//gc:get or change
int Small_enemy::gcn_bullet(int n = 0) {
	return n_bullet;
}

void Small_enemy::shoot(std::list<Bullet*>* bullets) {
	return;
}

bool Small_enemy::edge_checking() {
	return y > getheight() || y < -height;
}

//b:bullet p:player
bool Small_enemy::Impact_checking(int x, int y, char t) {
	switch (t) {
	case'b':
		if (x + 8 < 6 || x>52) {
			return false;
		}
		if (y + 16 <= 8) {
			return false;
		}
		else if (y + 16 <= 16 && (x + 8 <= 15 || x >= 42)) {
			return false;
		}
		if (x + 8 < 25) {
			if (y <= (x + 8) + 8) {
				return true;
			}
			return false;
		}
		else if (x <= 33) {
			if (y <= 42) {
				return true;
			}
			return false;
		}
		else {
			if (y <= 70 - x) {
				return true;
			}
			return false;
		}
	case'p':
		break;
	default:
		std::cout << "Eorror in Small_enemy::Impact_checking(int x, int y, char t)";
		exit(1);
	}
}

void Small_enemy::init(int score) {
	loadimage(&usual[0], _T("res/0enemy1.jpg"));
	loadimage(&usual[1], _T("res/1enemy1.jpg"));
	loadimage(&blow_up[0][0], _T("res/0enemy1_down1.jpg"));
	loadimage(&blow_up[0][1], _T("res/1enemy1_down1.jpg"));
	loadimage(&blow_up[1][0], _T("res/0enemy1_down2.jpg"));
	loadimage(&blow_up[1][1], _T("res/1enemy1_down2.jpg"));
	loadimage(&blow_up[2][0], _T("res/0enemy1_down3.jpg"));
	loadimage(&blow_up[2][1], _T("res/1enemy1_down3.jpg"));
	loadimage(&blow_up[3][0], _T("res/0enemy1_down4.jpg"));
	loadimage(&blow_up[3][1], _T("res/1enemy1_down4.jpg"));
	Small_enemy::score = score;
}