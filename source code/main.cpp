/*
�汾��������

�ƻ���
    ��ɼ��װ�
	����PVP
	֧���Ѷ�ѡ��
	֧���Զ����Ѷ�
	�����Զ����Ѷȸ߼�ѡ��
	��ҳ�棨��ѧϰ��
	�������ܣ���ѧϰ��
	����
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