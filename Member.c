#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

// ���� ��� ����
void alignCenter(char txt[])
{
	int i;
	int size = (strlen(WIDTH) - strlen(txt)) / 2;
	for (i = 0; i < size; i++)
	{
		printf(" ");
	}
	printf("%s", txt);
}

// ���� ���� ���
void textColor(char txt[], int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | color);
	printf("%s", txt);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 8);
}

// �ؽ�Ʈ �������� ������ �ε�
void roadData(FILE *fp, Tree *RBT)
{
	Member *curNode = NULL;
	char buff[1024];
	int i = 0;
	char *id, *name, *addr, *phone;


	while (fgets(buff, sizeof(buff), fp))
	{
		buff[strlen(buff) - 1] = '\0';	// ������ ������ ������ ���鹮�ڷ� �ٲ�

		// ������ ������ ù ��(���Ӹ�) ����
		if (i == 0){
			i++;
			continue;
		}

		// ������ ���ڿ��� ������ ������ �����Ϳ� ����
		id = strtok(buff, "\t");
		name = strtok(NULL, "\t");
		addr = strtok(NULL, "\t");
		phone = strtok(NULL, "\t");
		printf("%s %s %s %s\n", id, name, addr, phone);

		// ����ü�� ���� �Ҵ�, ��� ����, �θ�/�ڽĳ�� ���� ����
		curNode = createMember(RBT);

		// �����͸� ����ü�� ����
		curNode->id = atoi(id);
		strcpy(curNode->name, name);
		strcpy(curNode->addr, addr);
		strcpy(curNode->phone, phone);

		// ����ü�� Ʈ���� ����
		insertNode(RBT, curNode);
		treeFixUp(RBT, curNode);
	}

	return;
}


// �޴�1 : ȸ������
void menu1_member_view(Tree *tree)
{
	int input;
	system("cls");

	alignCenter("1. ȸ�� ���\n");
	printf(WIDTH);
	printf("���̵�\t\t �̸�\t\t\t�ּ�\t\t\t  �޴���ȭ\n");
	printf(WIDTH);

	printTree(tree, tree->root);

	printf(WIDTH);
	printf("\n");
	alignCenter("MENU\n");
	alignCenter("0. ����\n");

	alignCenter("��ư�� �Է��ϼ��� : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}

// �޴�2 : ȸ���߰�
void menu2_member_add(Tree *tree)
{
	system("cls");

	alignCenter("2. ȸ�� �߰�\n");
	printf(WIDTH);
	int id;
	char buff[256];
	char name[10], addr[256], phone[15];
	Member *newNode;
	Member *idIsValid;
	int phoneIsValid, addrIsValid;
	int i = 0, j, m, n;

	// ID
	do{
		printf("\n");
		printf("\t\t\t1. ID (* 6�ڸ��� ���ڸ� �Է��ϼ���)\n");
		printf("\t\t\t  : ");
		scanf("%d", &id);
		idIsValid = searchValue(tree, tree->root, id);

		if (id > 200000 || id < 130000)	textColor("\t\t\t* ���� : 130000~200000 ������ ���ڸ� �Է� �����մϴ�.\n", 12);

		if (idIsValid != NULL)	textColor("\t\t\t* ���� : �ߺ��Ǵ� ���̵� �����մϴ�.\n", 12);

	} while (id > 200000 || id < 130000 || idIsValid != NULL);


	// name
	printf("\n");
	printf("\t\t\t2. �̸�\n");;
	printf("\t\t\t  : ");
	scanf_s("%s", &name, 10);


	// address
	do{
		addrIsValid = 0;
		printf("\n");
		printf("\t\t\t3. �ּ�\n");;
		printf("\t\t\t  : ");
		fflush(stdin);
		strcpy(addr, gets_s(buff, 256));

		while (addr[i] != '\0')
		{
			if (addr[i] != ' ')
			{
				addrIsValid = 1;
				break;
			}
			i++;
		}

		if (!addrIsValid) textColor("\t\t\t* ���� : �ּҸ� �Է��ϼ���.\n", 12);
	} while (!addrIsValid);


	// phone number
	do{
		phoneIsValid = 1;
		printf("\n");
		printf("\t\t\t4. ��ȭ��ȣ(* 000-0000-0000 �������� �Է��ϼ���)\n");;
		printf("\t\t\t  : ");
		scanf_s("%s", &phone, 15);

		n = 0;
		m = 0;
		j = 0;
		while (phoneIsValid == 1 && phone[j] != '\0')
		{
			if (phone[j] == '-')
			{
				n++;
				if (m == 0)
				{
					phoneIsValid = 0;
					break;
				}
				m = 0;
			}
			else if (phone[j] < 48 || phone[j] > 57)
			{
				phoneIsValid = 0;
				break;
			}
			else
			{
				m++;
			}
			j++;
		}
		if (n > 2) phoneIsValid = 0;

		if (!phoneIsValid)	textColor("\t\t\t* ���� : ������ �ùٸ��� �ʽ��ϴ�.\n", 12);

	} while (!phoneIsValid);

	// ����ü�� ���� �Ҵ�, ��� ����, �θ�/�ڽĳ�� ���� ����
	newNode = createMember(tree);

	// �����͸� ����ü�� ����
	newNode->id = id;
	strcpy(newNode->name, name);
	strcpy(newNode->addr, addr);
	strcpy(newNode->phone, phone);

	// ����ü�� Ʈ���� ����
	insertNode(tree, newNode);
	treeFixUp(tree, newNode);

	return;
}


// �޴�4 : ȸ������
void menu4_member_delete(Tree *tree)
{
	int input, id;
	Member *delMember;
	system("cls");

	alignCenter("4. ȸ�� ����\n");
	printf(WIDTH);

	printf("\t\t\t���̵�\n");;
	printf("\t\t\t  : ");
	scanf("%d", &id);

	delMember = searchValue(tree, tree->root, id);
	printf("color : %d\n", delMember->color);
	deleteNode(tree, delMember);

	printf(WIDTH);
	printf("\n");
	alignCenter("MENU\n");
	alignCenter("0. ����\n");

	alignCenter("��ư�� �Է��ϼ��� : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}

void menu6_data_save(Tree *tree)
{
	FILE *fp;
	int input;
	fp = fopen("data.txt", "w");

	system("cls");

	alignCenter("3. ���� ����\n");
	printf(WIDTH);

	fprintf(fp, "ȸ�� ���̵�\tȸ���̸�\tȸ���ּ�\t�ڵ��� ��ȣ\n");
	fprintTree(fp, tree, tree->root);

	fclose(fp);

	printf("\n\n");

	alignCenter("���������� ����Ǿ����ϴ�\n\n");

	printf(WIDTH);
	printf("\n");
	alignCenter("MENU\n");
	alignCenter("0. ����\n");

	alignCenter("��ư�� �Է��ϼ��� : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}