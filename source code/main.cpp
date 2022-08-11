/*
版本：开发中

计划：
    完成简易版
	增加PVP
	支持难度选择
	支持自定义难度
	增加自定义难度高级选项
	网页版（待学习）
	联机功能（待学习）
	……
*/

#include"start.h"
#include"menu.h"
#include"game.h"
#include<time.h>
#include <stdlib.h>

using namespace std;

int main() {
	srand(unsigned int(time(NULL)));
	initgraph(1366, 768, EW_NOCLOSE);
	while (1) {
		start();
		if (!menu()) {
			return 0;
		}
		game();
	}
	return 0;
}