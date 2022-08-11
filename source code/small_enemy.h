#pragma once
#include"entity.h"
#include<easyx.h>

class Small_enemy:public Entity {
public:
	Small_enemy(int x, int y);
	void move();
	int get(char c);
	int gchp(int n);
	int gcn_bullet(int n);
	void print();
	void be_shot();
	bool gs_boom(char c);
	void shoot(std::list<Bullet*>* bullets);
	bool edge_checking();
	bool Impact_checking(int x, int y, char t);
	const static int width = 57, height = 51, max_boom = 4, n_bullet = 0;
	static void init(int score);
private:
	static IMAGE usual[2], blow_up[4][2];
	int x, y, hp, n_boom;
	static int score, speed;
};