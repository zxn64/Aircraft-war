#pragma once
#include"player.h"
#include"entity.h"
#include<conio.h>
#include"control.h"
#include"print.h"

void game();

bool deal_player(std::list<Entity*>* enemies, std::list<Bullet*>* bullets, Player* player, int score);

void die(int score);