#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

int main(void)
{
	FILE *fp;
	Tree *RBT = NULL;
	Tree *RBT_name = NULL;
	int input;

	PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	system("mode con: cols=120");
	system("color F8");

	fp = fopen("data.txt", "r");

	if (fp == NULL)	// ������ �б� ���н�
	{
		printf("������ �ε忡 �����߽��ϴ�!");
		return -1;
	}

	RBT = createRBT();
	RBT_name = createRBT();
	roadData(fp, RBT, RBT_name);

	//return;
	while (1)
	{
		system("cls");

		alignCenter("���� ȭ��\n");
		printf("\n");
		alignCenter("��������������MENU��������������\n");
		alignCenter("1. ȸ�� ���\n");
		alignCenter("2. ȸ�� �߰�\n");
		alignCenter("3. ȸ�� ����\n");
		alignCenter("4. ȸ�� ����\n");
		alignCenter("5. ȸ�� �˻�\n");
		alignCenter("6. ���� ����\n");
		alignCenter("0. ��     ��\n");
		alignCenter("��������������������������������\n");
		printf("\n");

		alignCenter("��ư�� �Է��ϼ��� : ");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			menu1_member_view(RBT);
			break;
		case 2:
			menu2_member_add(RBT,RBT_name);
			break;
		case 3:
			menu3_member_modify(RBT, RBT_name);
			break;
		case 4:
			menu4_member_delete(RBT,RBT_name);
			break;
		case 6:
			menu6_data_save(RBT);
			break;
		case 0:
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	getch();
	return 0;
}