#pragma once
#include"entity.h"
#include"player.h"
#include"bullet.h"
#include<list>

void print(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets, int score);