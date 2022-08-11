#include"bullet.h"
#include<iostream>

IMAGE Bullet::appearance[2][2];
int Bullet::speed;

Bullet::Bullet(int x, int y, int damage, int direction) {
	this->x = x;
	this->y = y;
	this->damage = damage;
	this->direction = direction ? 1 : 0;
}

void Bullet::move() {
	int dy = direction ? 1 : -1;
	y += dy * speed;
}

//get 'x' or 'y'
int Bullet::get(char c) {
	switch (c) {
	case 'x':
		return x;
	case 'y':
		return y;
	default:
		std::cout << "EORROR£¡Get wrong input in Large_enemy::get(char c)";
		exit(1);
	}
}

void Bullet::print() {
	putimage(x, y, &appearance[direction][0], SRCAND);
	putimage(x, y, &appearance[direction][1], SRCPAINT);
}

bool Bullet::edge_checking() {
	return y > getheight() || y < -height;
}

void Bullet::init() {
	loadimage(&appearance[0][0], _T("res/0bullet.jpg"));
	loadimage(&appearance[0][1], _T("res/1bullet.jpg"));
	rotateimage(&appearance[1][0], &appearance[0][0], PI);
	rotateimage(&appearance[1][1], &appearance[0][1], PI);
	speed = 10;
}