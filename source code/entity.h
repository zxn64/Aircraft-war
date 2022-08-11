#pragma once
#include"bullet.h"
#include"player.h"
#include<list>
#include<easyx.h>

#define UP 0, -1
#define DOWN 0, 1
#define LEFT -1, 0
#define RIGHT 1, 0

class Entity {
public:
	virtual void move() = 0;
	virtual int get(char c) = 0;
	virtual void shoot(std::list<Bullet*>* bullets) = 0;
	virtual int gchp(int n = 0) = 0;
	virtual int gcn_bullet(int n = 0) = 0;
	virtual void print() = 0;
	virtual void be_shot() = 0;
	virtual bool gs_boom(char c) = 0;
	virtual bool edge_checking() = 0;
	virtual bool Impact_checking(int x, int y, char t) = 0;
};

void entity(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets, int* score, std::chrono::steady_clock::time_point* start);

void deal_bullets(std::list<Bullet*>* bullets);

void deal_enemies(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets, int* score);

void create_enemy(int n, std::list<Entity*>* enemies, std::chrono::steady_clock::time_point* start);
