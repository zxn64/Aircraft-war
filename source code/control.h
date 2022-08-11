#pragma once
#include"game.h"

bool gdorder(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets);

void clear(std::list<Entity*>* enemies, std::list<Bullet*>* bullets);

void pause();

void clear_in();