#pragma once
#include"entity.h"
#include<easyx.h>

class Large_enemy:public Entity {
public:
	Large_enemy(int x, int y);
	void move();
	int get(char c);
	int gchp(int n);
	int gcn_bullet(int n);
	void shoot(std::list<Bullet*>* bullets);
	void print();
	void be_shot();
	bool gs_boom(char c);
	bool edge_checking();
	bool Impact_checking(int x, int y, char t);
	const static int width = 169, height = 258, max_boom = 6;
	static void init(int score, std::chrono::milliseconds shoot_speed);
private:
	static IMAGE usual[2], blow_up[6][2], be_hurt[2];
	int x, y, hp, n_boom, direction;
	bool shot, hurt;
	static int score, n_bullet, speed, damage;
	static std::chrono::milliseconds shoot_speed;
	std::chrono::steady_clock::time_point start;
};