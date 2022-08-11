#pragma once
#include<easyx.h>

#define PI 3.14159265359

class Bullet {
public:
	Bullet(int x, int y, int damage, int direction = 0);
	void move();
	int get(char);
	void print();
	bool edge_checking();
	const static int height = 21, width = 9;
	static void init();
	int damage;
private:
	static IMAGE appearance[2][2];
	int x, y;
	bool direction;
	static int speed;
};