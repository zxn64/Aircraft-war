#pragma once
#pragma comment (lib, "winmm.lib")
#include<Windows.h>
#include"bullet.h"
#include<easyx.h>
#include<list>
#include<chrono>

#define PI 3.14159265359

class Player{
public:
	Player(int speed, std::chrono::milliseconds shoot_speed);
	void move(int dx, int dy);
	void shoot(std::list<Bullet*>* bullets);
	int get(char c);
	int gchp(int d = 0);
	int gcclip(int d = 0);
	void print();
	void be_shot();
	bool gs_boom(char c);
	bool edge_checking();
	bool Impact_checking(int x, int y);
	const static int width = 99, height = 124, max_boom = 4;
	static void init();
private:
	static IMAGE usual[2], blow_up[4][2];
	int x, y, hp, n_bullet, damage, speed, n_boom, clip;
	bool shot;
	std::chrono::milliseconds shoot_speed;
	std::chrono::steady_clock::time_point start;
};