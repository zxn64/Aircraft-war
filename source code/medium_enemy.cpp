#include"medium_enemy.h"
#include<iostream>

int Medium_enemy::score, Medium_enemy::n_bullet, Medium_enemy::speed, Medium_enemy::damage;
IMAGE Medium_enemy::usual[2], Medium_enemy::blow_up[4][2], Medium_enemy::be_hurt[2];
std::chrono::milliseconds Medium_enemy::shoot_speed;

Medium_enemy::Medium_enemy(int x, int y) {
	this->x = x;
	this->y = y;
	hp = score;
	n_bullet = 1;
	damage = 1;
	n_boom = 0;
	speed = 3;
	shot = false;
	hurt = false;
	direction = -1;
	start = std::chrono::steady_clock::now();
}

void Medium_enemy::move() {
	if (y <= 0) {
		y += 10;
		return;
	}
	if (x <= 0 || x + width >= getwidth()) {
		direction *= -1;
		y += 5;
	}
	x += direction * speed;
}

//get 'x' or 'y'
int Medium_enemy::get(char c) {
	switch (c) {
	case 'x':
		return x;
	case 'y':
		return y;
	case 's':
		return score;
	default:
		std::cout << "EORROR£¡Get wrong input in Medium_enemy::get(char c)";
		exit(1);
	}
}

void Medium_enemy::be_shot() {
	shot = true;
}

void Medium_enemy::print() {
	if (!n_boom) {
		if (hurt) {
			putimage(x, y, &be_hurt[0], SRCAND);
			if (!shot) {
				putimage(x, y, &be_hurt[1], SRCPAINT);
			}
			shot = false;
			return;
		}
		putimage(x, y, &usual[0], SRCAND);
		if (!shot) {
			putimage(x, y, &usual[1], SRCPAINT);
		}
		shot = false;
		return;
	}
	putimage(x, y, &blow_up[n_boom - 1][0], SRCAND);
	putimage(x, y, &blow_up[n_boom - 1][1], SRCPAINT);
	n_boom++;
}

//get n or start
bool Medium_enemy::gs_boom(char c) {
	switch (c) {
	case 's':
		return n_boom++;
	case 'g':
		return n_boom > max_boom;
	default:
		std::cout << "Eorror in Medium_enemy::gs_boom(char c)";
		exit(1);
	}
}

//gc:get or change
int Medium_enemy::gchp(int n = 0) {
	hp += n;
	if (hp <= score / 2) {
		hurt = true;
	}
	return hp;
}

//gc:get or change
int Medium_enemy::gcn_bullet(int n = 0) {
	n_bullet += n;
	return n_bullet;
}

void Medium_enemy::shoot(std::list<Bullet*>* bullets) {
	if (std::chrono::steady_clock::now() - start < shoot_speed) {
		return;
	}
	start = std::chrono::steady_clock::now();
	for (int i = 1; i <= n_bullet; i++) {
		bullets->push_back(new Bullet((double)i * (width - Bullet::width) / (n_bullet + 1) + x, y + height, damage, 1));
	}
}

bool Medium_enemy::edge_checking() {
	return y > getheight() || y < -height;
}

//b:bullet p:player
bool Medium_enemy::Impact_checking(int x, int y, char t) {
	//Åö×²¼ì²â±ßÔµ£º0<x<13,y=61  13<=x<=20,y=x+88  21<=x<=28,y=2x+24  28<x<40,y=88  40<=x<=47,y=179-2x  48<=x<=55,y=102-0.7x   x<=69,y=61
	switch (t) {
	case'b':
		if (x + 8 <= 0 || x > 66) {
			return false;
		}
		if (y <= 2) {
			return false;
		}
		if (y <= 9 && (x + 8 <= 28 || x >= 40)) {
			return false;
		}
		if (y <= 27 && (x + 8 <= 22 || x >= 46)) {
			return false;
		}
		if (y <= 30 && (x + 8 <= 15 || x >= 52)) {
			return false;
		}
		if (x + 8 < 13) {
			if (y <= (x + 8) + 68) {
				return true;
			}
			return false;
		}
		if (x + 8 <= 20) {
			if (y <= (x + 8) + 88) {
				return true;
			}
			return false;
		}
		if (x + 8 <= 28) {
			if (y <= 2 * (x + 8) + 24) {
				return true;
			}
			return false;
		}
		if (x < 40) {
			if (y <= 88) {
				return true;
			}
			return false;
		}
		if (x <= 47) {
			if (y <= 179 - 2 * x) {
				return true;
			}
			return false;
		}
		if (x <= 55) {
			if (y <= 102 - 0.7 * x) {
				return true;
			}
			return false;
		}
		if (y <= 61) {
			return true;
		}
		return false;
	case'p':
		break;
	default:
		std::cout << "Eorror in Medium_enemy::Impact_checking(int x, int y, char t)";
		exit(1);
	}
}

void Medium_enemy::init(int score, std::chrono::milliseconds shoot_speed) {
	loadimage(&usual[0], _T("res/0enemy2.jpg"));
	loadimage(&usual[1], _T("res/1enemy2.jpg"));
	loadimage(&be_hurt[0], _T("res/0enemy2_hit.jpg"));
	loadimage(&be_hurt[1], _T("res/1enemy2_hit.jpg"));
	loadimage(&blow_up[0][0], _T("res/0enemy2_down1.jpg"));
	loadimage(&blow_up[0][1], _T("res/1enemy2_down1.jpg"));
	loadimage(&blow_up[1][0], _T("res/0enemy2_down2.jpg"));
	loadimage(&blow_up[1][1], _T("res/1enemy2_down2.jpg"));
	loadimage(&blow_up[2][0], _T("res/0enemy2_down3.jpg"));
	loadimage(&blow_up[2][1], _T("res/1enemy2_down3.jpg"));
	loadimage(&blow_up[3][0], _T("res/0enemy2_down4.jpg"));
	loadimage(&blow_up[3][1], _T("res/1enemy2_down4.jpg"));
	Medium_enemy::score = score;
	Medium_enemy::shoot_speed = shoot_speed;
}