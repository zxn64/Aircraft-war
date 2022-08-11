#include"player.h"
#include"bullet.h"
#include<iostream>
#include<stdlib.h>

IMAGE Player::usual[2], Player::blow_up[4][2];

Player::Player(int speed, std::chrono::milliseconds shoot_speed) {
	x = (getwidth() - Player::width) / 2;
	y = getheight() - Player::height;
	hp = 5;
	n_bullet = 1;
	damage = 1;
	this->speed = 10;
	this->shoot_speed = shoot_speed;
	n_boom = 0;
	clip = 5;
	shot = false;
	start = std::chrono::steady_clock::now();
}

void Player::move(int dx, int dy) {
	x += dx * speed;
	y += dy * speed;
}

//get 'x' or 'y'
int Player::get(char c) {
	switch (c) {
	case 'x':
		return x;
	case 'y':
		return y;
	default:
		std::cout << "EORROR£¡Get wrong input in Player::get(char c);";
		exit(1);
	}
}

void Player::be_shot() {
	shot = true;
}

void Player::print() {
	if (!n_boom) {
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
bool Player::gs_boom(char c) {
	switch (c) {
	case 's':
		mciSendString(_T("close boom"), NULL, 0, 0);
		mciSendString(_T("open res/boom.mp3 alias boom"), NULL, 0, 0);
		mciSendString(_T("play boom"), NULL, 0, 0);
		return n_boom++;
	case 'g':
		return n_boom > max_boom;
	default:
		std::cout << "Eorror in Player::gs_boom(char c)";
		exit(1);
	}
}

//gc:get or change
int Player::gchp(int d) {
	hp += d;
	return hp;
}
int Player::gcclip(int d) {
	clip += d;
	return clip;
}

void Player::shoot(std::list<Bullet*>* bullets) {
	if (std::chrono::steady_clock::now() - start < shoot_speed || clip <= 0) {
		return;
	}
	start = std::chrono::steady_clock::now();
	mciSendString(_T("close shoot"), NULL, 0, 0);
	mciSendString(_T("open res/shoot.mp3 alias shoot"), NULL, 0, 0);
	mciSendString(_T("play shoot"), NULL, 0, 0);
	for (int i = 1; i <= n_bullet; i++) {
		bullets->push_back(new Bullet((double)i * (width - Bullet::width) / (n_bullet + 1) + x, y - Bullet::height, damage));
		clip--;
	}
}

bool Player::edge_checking() {
	return (y > getheight() || y < -height) && (x > getwidth() - width / 2 || x < -width / 2);
}

bool Player::Impact_checking(int x, int y) {
	if (y >= 93) {
		return false;
	}
	if (x + 8 < 1 || x > 97) {
		return false;
	}
	if (x + 8 <= 12) {
		if (y >= 79 - (x + 8)) {
				return true;
		}
		return false;
	}
	if (x + 8 <= 16) {
		if (y >= 60 - (x + 8)) {
			return true;
		}
		return false;
	}
	if (x <= 20) {
		if (y >= 44) {
			return true;
		}
		return false;
	}
	if (x <= 23) {
		if (y >= x + 24) {
			return true;
		}
		return false;
	}
	if (x + 8 <= 37) {
		if (y >= 77 - (x + 8)) {
			return true;
		}
		return false;
	}
	if (x + 8 <= 48) {
		if (y >= 93 - 2 * (x + 8)) {
			return true;
		}
		return false;
	}
	if (x <= 53) {
		if (y >= 1) {
			return true;
		}
		return false;
	}
	if (x <= 62) {
		if (y >= 2 * x - 105) {
			return true;
		}
		return false;
	}
	if (x + 8 <= 76) {
		if (y >= x - 21) {
			return true;
		}
		return false;
	}
	if (x + 8 <= 80) {
		if (y >= 124 - (x + 8)) {
			return true;
		}
		return false;
	}
	if (x <= 83) {
		if (y >= 44) {
			return true;
		}
		return false;
	}
	if (x <= 86) {
		if (y >= x - 39) {
			return true;
		}
		return false;
	}
	if (y >= x + 21) {
		return true;
	}
	return false;
}

void Player::init() {
	loadimage(&usual[0], _T("res/0hero.jpg"));
	loadimage(&usual[1], _T("res/1hero.jpg"));
	loadimage(&blow_up[0][0], _T("res/0hero_blowup_n1.jpg"));
	loadimage(&blow_up[0][1], _T("res/1hero_blowup_n1.jpg"));
	loadimage(&blow_up[1][0], _T("res/0hero_blowup_n2.jpg"));
	loadimage(&blow_up[1][1], _T("res/1hero_blowup_n2.jpg"));
	loadimage(&blow_up[2][0], _T("res/0hero_blowup_n3.jpg"));
	loadimage(&blow_up[2][1], _T("res/1hero_blowup_n3.jpg"));
	loadimage(&blow_up[3][0], _T("res/0hero_blowup_n4.jpg"));
	loadimage(&blow_up[3][1], _T("res/1hero_blowup_n4.jpg"));
}