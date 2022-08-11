#include"entity.h"
#include"large_enemy.h"
#include"medium_enemy.h"
#include"small_enemy.h"
#include<algorithm>

using namespace std::chrono;

void entity(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets, int* score, steady_clock::time_point* start) {
	create_enemy(*score, enemies, start);
	deal_bullets(bullets);
	deal_enemies(player, enemies, bullets, score);
}

void deal_bullets(std::list<Bullet*>* bullets)
{
	for (std::list<Bullet*>::iterator i = bullets->begin(); i != bullets->end();) {
		(*i)->move();
		if ((*i)->edge_checking()) {
			delete (*i);
			if (++i == bullets->end()) {
		        bullets->erase(--i);
				return;
			}
			i = bullets->erase(--i);
		}
		else {
			i++;
		}
	}
}

void deal_enemies(Player* player, std::list<Entity*>* enemies, std::list<Bullet*>* bullets, int* score) {
	for (std::list<Entity*>::iterator i = enemies->begin(); i != enemies->end();) {
		if ((*i)->gs_boom('g')) {
			delete (*i);
			if (++i == enemies->end()) {
				enemies->erase(--i);
				break;
			}
			i = enemies->erase(--i);
		}
		(*i)->move();
		for (std::list<Bullet*>::iterator j = bullets->begin(); j != bullets->end(); j++) {
			if ((*i)->Impact_checking((*j)->get('x') - (*i)->get('x'), (*j)->get('y') - (*i)->get('y'), 'b')) {
				(*i)->be_shot();
				if (!(*i)->gchp(-(*j)->damage)) {
					*score += (*i)->get('s');
					player->gcclip((*i)->get('s') * 2);
					delete (*j);
					bullets->erase(j);
					(*i)->gs_boom('s');
					mciSendString(_T("close boom"), NULL, 0, 0);
					mciSendString(_T("open res/boom.mp3 alias boom"), NULL, 0, 0);
					mciSendString(_T("play boom"), NULL, 0, 0);
					break;
				}
				delete (*j);
				if (++j == bullets->end()) {
					bullets->erase(--j);
					break;
				}
				j = bullets->erase(--j);
			}
		}
		(*i)->shoot(bullets);
		if ((*i)->edge_checking()) {
			delete (*i);
			if (++i == enemies->end()) {
				enemies->erase(--i);
				break;
			}
			i = enemies->erase(--i);
		}
		else {
			i++;
		}
	}
}

void create_enemy(int score, std::list<Entity*>* enemies, steady_clock::time_point* start) {
	if (enemies->empty()) {
		for (int i = 0; i < score / 10 % 5; i++) {
			enemies->push_back(new Medium_enemy(rand() % (getwidth() - Medium_enemy::width), -Medium_enemy::height));
		}
		for (int i = 0; i < score / 100; i++) {
			enemies->push_back(new Large_enemy(rand() % (getwidth() - Large_enemy::width), -Large_enemy::height));
		}
	}
	if (steady_clock::now() - *start >=3s) {
		enemies->push_back(new Small_enemy(rand() % (getwidth() - Small_enemy::width), -Small_enemy::height));
		*start = steady_clock::now();
	}
}