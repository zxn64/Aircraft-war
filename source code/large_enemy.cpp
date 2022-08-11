#include"large_enemy.h"
#include<iostream>

int Large_enemy::score, Large_enemy::n_bullet, Large_enemy::speed, Large_enemy::damage;
IMAGE Large_enemy::usual[2], Large_enemy::blow_up[6][2], Large_enemy::be_hurt[2];
std::chrono::milliseconds Large_enemy::shoot_speed;

Large_enemy::Large_enemy(int x, int y) {
	this->x = x;
	this->y = y;
	hp = score;
	n_bullet = 3;
	damage = 1;
	n_boom = 0;
	speed = 2;
	shot = false;
	hurt = false;
	direction = 1;
	start = std::chrono::steady_clock::now();
}

void Large_enemy::move() {
	if (y <= 0) {
		y += 10;
		return;
	}
	if (x < 0 || x + width >= getwidth()) {
		direction *= -1;
	}
	x += direction * speed;
}

//get 'x' or 'y'
int Large_enemy::get(char c) {
	switch (c) {
	case 'x':
		return x;
	case 'y':
		return y;
	case 's':
		return score;
	default:
		std::cout << "EORROR£¡Get wrong input in Large_enemy::get(char c)";
		exit(1);
	}
}

void Large_enemy::be_shot() {
	shot = true;
}

void Large_enemy::print() {
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
	putimage(x, y, &blow_up[n_boom-1][0], SRCAND);
	putimage(x, y, &blow_up[n_boom - 1][1], SRCPAINT);
	n_boom++;
}

//get n or start
bool Large_enemy::gs_boom(char c) {
	switch (c) {
	case 's':
		return n_boom++;
	case 'g':
		return n_boom > max_boom;
	default:
		std::cout << "Eorror in Large_enemy::gs_boom(char c)";
		exit(1);
	}
}

//gc:get or change
int Large_enemy::gchp(int n = 0) {
	hp += n;
	if (hp <= score / 2) {
		hurt = true;
	}
	return hp;
}

//gc:get or change
int Large_enemy::gcn_bullet(int n = 0) {
	n_bullet += n;
	return n_bullet;
}

void Large_enemy::shoot(std::list<Bullet*>* bullets) {
	if (std::chrono::steady_clock::now() - start < shoot_speed) {
		return;
	}
	start = std::chrono::steady_clock::now();
	for (int i = 1; i <= n_bullet; i++) {
		bullets->push_back(new Bullet((double)i * (width - Bullet::width) / (n_bullet + 1) + x, y + height - 9, damage, 1));
	}
}

bool Large_enemy::edge_checking() {
	return y > getheight() || y < -height;
}

//b:bullet p:player
bool Large_enemy::Impact_checking(int x, int y, char t) {
	//Åö×²¼ì²â±ßÔµ£º3<=x<=45,y=x+196  x<=62,y=241  x<104,y=246  x<=125,y=241  x<=166,y=366-x
	switch (t) {
	case'b':
		if (x + 8 < 3 || x>166) {
			return false;
		}
		if (y <= 2) {
			return false;
		}
		if (y <= 69 && (x >= 46 || x + 8 <= 123)) {
			return false;
		}
		if (y <= x + 22 && x >= 30 && x <= 46) {
			return false;
		}
		if (y <= 192 - (x + 8) && x + 8 >= 123 && x + 8 <= 138) {
			return false;
		}
		if (y <= 190 - (x + 8) && x + 8 <= 16) {
			return false;
		}
		if (y <= x + 22 && x >= 152) {
			return false;
		}
		if (x + 8 <= 45) {
			if (y <= (x + 8) + 196) {
				return true;
			}
			return false;
		}
		if (x + 8 <= 62) {
			if (y <= 241) {
				return true;
			}
			return false;
		}
		if (x <= 104) {
			if (y <= 246) {
				return true;
			}
			return false;
		}
		if (x <= 125) {
			if (y <= 241) {
				return true;
			}
			return false;
		}
		if (y <= 366 - x) {
			return true;
		}
		return false;
	case'p':
		break;
	default:
		std::cout << "Eorror in Large_enemy::Impact_checking(int x, int y, char t)";
		exit(1);
	}
}

void Large_enemy::init(int score, std::chrono::milliseconds shoot_speed) {
	loadimage(&usual[0], _T("res/0enemy3.jpg"));
	loadimage(&usual[1], _T("res/1enemy3.jpg"));
	loadimage(&be_hurt[0], _T("res/0enemy3_hit.jpg"));
	loadimage(&be_hurt[1], _T("res/1enemy3_hit.jpg"));
	loadimage(&blow_up[0][0], _T("res/0enemy3_down1.jpg"));
	loadimage(&blow_up[0][1], _T("res/1enemy3_down1.jpg"));
	loadimage(&blow_up[1][0], _T("res/0enemy3_down2.jpg"));
	loadimage(&blow_up[1][1], _T("res/1enemy3_down2.jpg"));
	loadimage(&blow_up[2][0], _T("res/0enemy3_down3.jpg"));
	loadimage(&blow_up[2][1], _T("res/1enemy3_down3.jpg"));
	loadimage(&blow_up[3][0], _T("res/0enemy3_down4.jpg"));
	loadimage(&blow_up[3][1], _T("res/1enemy3_down4.jpg"));
	loadimage(&blow_up[4][0], _T("res/0enemy3_down5.jpg"));
	loadimage(&blow_up[4][1], _T("res/1enemy3_down5.jpg"));
	loadimage(&blow_up[5][0], _T("res/0enemy3_down6.jpg"));
	loadimage(&blow_up[5][1], _T("res/1enemy3_down6.jpg"));
	Large_enemy::score = score;
	Large_enemy::shoot_speed = shoot_speed;
}