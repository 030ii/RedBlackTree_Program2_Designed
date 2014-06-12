#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

/*******************************************************************************
								UI �����Լ�
*******************************************************************************/

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

// �ؽ�Ʈ���� ���
void printBox(char txt[])
{
	int i,j,k;
	char width2[] = "������������������������������������������";
	int size1 = (strlen(WIDTH) - strlen(width2)) / 2;
	int size2 = (strlen(width2)-4 - strlen(txt)) / 2;

	alignCenter("������������������������������������������\n");
	alignCenter("��                                      ��\n");

	for (i = 0; i < size1; i++)
	{
		printf(" ");
	}
	printf("��");
	for (j = 0; j < size2; j++)
	{
		printf(" ");
	}
	printf("%s", txt);
	for (k = 0; k < size2; k++)
	{
		printf(" ");
	}
	printf("��\n");

	alignCenter("��           (��:1, �ƴϿ�:0)           ��\n");
	
	alignCenter("��                                      ��\n");
	alignCenter("������������������������������������������\n");
}



/*******************************************************************************
							ȸ�������޴� �����Լ�
*******************************************************************************/

// �ؽ�Ʈ �������� ������ �ε�
void roadData(FILE *fp, Tree *RBT, Tree *RBTForName)
{
	Member *data = NULL;
	Node *curNode = NULL, *curNodeForName = NULL;
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

		// �����͸� Member ����ü�� ����
		data = malloc(sizeof(Member));
		data->id = atoi(id);
		strcpy(data->name, name);
		strcpy(data->addr, addr);
		strcpy(data->phone, phone);

		// ����ü�� ���� �� ������ �Ҵ�
		curNode = createMember(RBT,data);
		curNodeForName = createMember(RBTForName,data);

		// ����ü�� Ʈ���� ����
		insertNode(RBT, curNode, 0);
		insertNode(RBTForName, curNodeForName, 1);
	}

	return;
}


// �޴�1 : ȸ������
void menu1_member_view(Tree *tree)
{
	int input;
	system("cls");

	printf("\n");
	alignCenter("��������������������������������\n");
	alignCenter("1. ȸ�� ���\n");
	alignCenter("��������������������������������\n");
	printf("\n");
	printf("\t\t\t���̵�\t\t �̸�\t\t  �޴���ȭ\t\t\t  �ּ�\n");

	printTree(tree, tree->root);

	printf("\n");
	alignCenter("��������������MENU��������������\n");
	alignCenter("0. ����\n");
	alignCenter("��������������������������������\n");

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
void menu2_member_add(Tree *tree, Tree *treeForName)
{
	int id = 0;
	char buff[256];
	char name[10], addr[256], phone[15];
	Node *newNode, *newNodeForName;
	Member *data;
	int nameIsValid,phoneIsValid, addrIsValid;
	
	system("cls");

	printf("\n");
	alignCenter("��������������������������������\n");
	alignCenter("2. ȸ�� �߰�\n");
	alignCenter("��������������������������������\n");
	alignCenter("0�� �Է��ϸ� ��ҵ˴ϴ�.");

	// ID : �ڵ�����
	printf("\n\n");
	id = findLastId(tree)+1;
	alignCenter("ID : ");
	printf("%d", id);

	// name
	do
	{
		printf("\n\n");
		alignCenter("�̸� : ");
		scanf_s("%s", &buff, 256);
		if (!strcmp(buff, "0")) return;
		nameIsValid = isValidName(buff);

	} while (!nameIsValid);
	strcpy(name, buff);

	// address
	do{
		printf("\n");
		alignCenter("�ּ� : ");
		fflush(stdin);
		gets_s(buff, 256);
		if (!strcmp(buff, "0")) return;
		addrIsValid = isValidAddr(buff);

	} while (!addrIsValid);
	strcpy(addr, buff);

	// phone number
	do{
		printf("\n");
		alignCenter("��ȭ��ȣ : ");;
		scanf_s("%s", &phone, 15);
		if (!strcmp(phone,"0")) return;
		phoneIsValid = isValidPhone(phone);

	} while (!phoneIsValid);

	// �����͸� Member ����ü�� ����
	data = malloc(sizeof(Member));
	data->id = id;
	strcpy(data->name, name);
	strcpy(data->addr, addr);
	strcpy(data->phone, phone);

	// Ʈ�� ��� ����ü�� ���� �� ������ �Ҵ�
	newNode = createMember(tree,data);
	newNodeForName = createMember(treeForName,data);

	// ����ü�� Ʈ���� ����
	insertNode(tree, newNode, 0);



	insertNode(treeForName, newNodeForName, 1);

	return;
}

// �޴�3 : ȸ������
void menu3_member_modify(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *delMember = NULL;
	Member *delData = NULL;
	char buff[256],name[10],addr[256],phone[20];
	Node *newNodeForName;
	int nameIsValid, phoneIsValid, addrIsValid;


	do{
		system("cls");

		printf("\n");
		alignCenter("��������������������������������\n");
		alignCenter("3. ȸ�� ����\n");
		alignCenter("��������������������������������\n");

		alignCenter("� Ű����� �˻��Ͻðڽ��ϱ�?\n\n");

		alignCenter("1. ���̵�˻�\n");
		alignCenter("2. �̸��˻�\n");
		alignCenter("0. ����\n\n");
		alignCenter("��ư�� �Է��ϼ���  : ");
		scanf("%d", &input);


		// �˻� Ű���� �Է�
		do
		{
			alignCenter("��������������������������������\n");
			if (input == 0) return;

			if (input == 1)
			{
				printf("\n");
				alignCenter("���̵� �Է��ϼ��� : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				printf("\n");
				alignCenter("�̸��� �Է��ϼ��� : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0,nameKey);
			}
			if (delMember == NULL)
			{
				system("cls");
				printf("\n");
				alignCenter("��������������������������������\n");
				alignCenter("3. ȸ�� ����\n");
				alignCenter("��������������������������������\n");

				textColor("\t\t\t\t\t   * ���� : Ű���带 ã�� �� �����ϴ�.\n\n", 12);

				alignCenter("1. ���̵�˻�\n");
				alignCenter("2. �̸��˻�\n");
				alignCenter("0. ����\n\n");
				alignCenter("��ư�� �Է��ϼ���  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		// ���� ������ ���
		delData = delMember->data;
		strcpy(name, delData->name);
		strcpy(addr, delData->addr);
		strcpy(phone, delData->phone);

		// ȸ�� ���� ������
		system("cls");

		printf("\n");
		alignCenter("��������������������������������\n");
		alignCenter("3. ȸ�� ����\n");
		alignCenter("��������������������������������\n");
		printf("\n");
		alignCenter("ã�� ȸ�� ����\n\n");
		printf("\t\t\t\t  %d\t%s\t%s\t%s\t\n\n", delData->id, name, addr, phone);
		
		// ������ ���� �Է�
		alignCenter("��������������������������������\n");
		alignCenter("� ������ �����Ͻðڽ��ϱ�?\n");
		printf("\n");
		alignCenter("1. �̸�\n");
		alignCenter("2. �ּ�\n");
		alignCenter("3. ��ȭ��ȣ\n");
		alignCenter("0. ���\n");
		printf("\n");
		alignCenter("��ư�� �Է��ϼ��� : ");
		scanf("%d", &input);
		if (input == 0) return;

		alignCenter("��������������������������������\n");
		switch (input)
		{
		case 1:
			// name
			do{
				printf("\n\n");
				alignCenter("�̸� : ");
				scanf_s("%s", &buff, 256);
				if (!strcmp(buff, "0")) return;
				nameIsValid = isValidName(buff);
			} while (!nameIsValid);
			strcpy(name, buff);
			break;

		case 2:
			// address
			do{
				printf("\n\n");
				alignCenter("�ּ� : ");
				fflush(stdin);
				gets_s(buff, 256);
				if (!strcmp(buff, "0")) return;
				addrIsValid = isValidAddr(buff);
			} while (!addrIsValid);
			strcpy(addr, buff);
			break;

		case 3:
			// phone number
			do{
				printf("\n\n");
				alignCenter("��ȭ��ȣ : ");;
				scanf_s("%s", &buff, 15);
				if (!strcmp(buff, "0")) return;
				phoneIsValid = isValidPhone(buff);

			} while (!phoneIsValid);
			strcpy(phone, buff);
			break;
		case 0:
			return;
		}

		// ���� ������ ����
		delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
		deleteNode(treeForName, delMember);

		// ����ü�� ���� �� ������ �Ҵ�
		newNodeForName = createMember(treeForName, delData);
		newNodeForName->data = delData;

		strcpy(delData->name, name);
		strcpy(delData->addr, addr);
		strcpy(delData->phone, phone);

		// ����ü�� Ʈ���� ����
		insertNode(treeForName, newNodeForName,1);
		treeFixUp(treeForName, newNodeForName);

		// ���� UI
		printf("\n");
		alignCenter("���������� �����Ǿ����ϴ�.\n");
		printf("\n");
		printBox("��� �����Ͻðڽ��ϱ�?");

		alignCenter("��ư�� �Է��ϼ��� : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}


// �޴�4 : ȸ������
void menu4_member_delete(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *delMember = NULL;
	Member *delData = NULL;


	do{
		system("cls");

		printf("\n");
		alignCenter("��������������������������������\n");
		alignCenter("4. ȸ�� ����\n");
		alignCenter("��������������������������������\n");

		alignCenter("� Ű����� �˻��Ͻðڽ��ϱ�?\n\n");
		alignCenter("1. ���̵�˻�\n");
		alignCenter("2. �̸��˻�\n");
		alignCenter("0. ����\n\n");
		alignCenter("��ư�� �Է��ϼ���  : ");
		scanf("%d", &input);

		printf("\n");
		alignCenter("��������������������������������\n");
		printf("\n");

		do
		{
			if (input == 0) return;

			if (input == 1)
			{
				alignCenter("�˻��� ���̵� �Է��ϼ��� : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				alignCenter("�˻��� �̸��� �Է��ϼ��� : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0, nameKey);
			}
			if (delMember == NULL)
			{
				printf("\n\n");
				textColor("\t\t\t\t\t   * ���� : Ű���带 ã�� �� �����ϴ�.\n\n", 12);
				alignCenter("1. ���̵�˻�\n");
				alignCenter("2. �̸��˻�\n");
				alignCenter("0. ����\n");
				printf("\n");
				alignCenter("��ư�� �Է��ϼ���  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		delData = delMember->data;

		printf("\n\n");
		alignCenter("��������������������������������\n");
		alignCenter("ã�� ȸ�� ����\n");
		alignCenter("��������������������������������\n");
		printf("\n\t\t\t\t%d\t%s\t%s\t%s\t\n\n", delData->id, delData->name, delData->addr, delData->phone);
		printBox("�����Ͻðڽ��ϱ�? ");
		alignCenter("��ư�� �Է��ϼ��� : ");
		scanf("%d", &input);

		if (input == 1)
		{	

			// ID Ʈ������ ����
			delMember = searchValue(tree, tree->root, delData->id,'\0');
			deleteNode(tree, delMember);

			// �̸� Ʈ������ ����
			delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
			deleteNode(treeForName, delMember);

			free(delData);
		}
		else
		{
			alignCenter("����ڰ� ����Ͽ����ϴ�.\n");
		}

		printf("\n");
		alignCenter("MENU\n");
		alignCenter("1. �����\n");
		alignCenter("0. ����\n");

		alignCenter("��ư�� �Է��ϼ��� : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}

void menu6_data_save(Tree *tree)
{
	FILE *fp;
	int input;
	fp = fopen("data.txt", "w");

	system("cls");

	printf("\n");
	alignCenter("��������������������������������\n");
	alignCenter("6. ���� ����\n");
	alignCenter("��������������������������������\n");

	printBox("�����Ͻðڽ��ϱ�? ");
	alignCenter("��ư�� �Է��ϼ��� : ");
	scanf("%d", &input);
	if (input == 0) return;

	fprintf(fp, "ȸ�� ���̵�\tȸ���̸�\tȸ���ּ�\t�ڵ��� ��ȣ\n");
	fprintTree(fp, tree, tree->root);

	fclose(fp);

	printf("\n\n");

	alignCenter("���������� ����Ǿ����ϴ�\n\n");

	printf(WIDTH);
	printf("\n");

	alignCenter("�����Ϸ��� �ƹ� Ű�� �Է��ϼ���.");
	scanf("%d", &input);

	return;
}



/*******************************************************************************
								�Է°� ��ȿ�� �˻�
*******************************************************************************/

int isValidName(char txt[])
{
	int isValid = 0;
	if (txt[0] != '\0' && strlen(txt) < 10)
	{
		isValid = 1;
	}

	if (!isValid) textColor("\t\t\t\t\t\t* ���� : �ùٸ� �̸��� �Է��ϼ���.\n", 12);
	
	return isValid;
}
int isValidAddr(char txt[])
{
	int isValid = 0, i = 0;

	while (txt[i] != '\0')
	{
		if (txt[i] != ' ')
		{
			isValid = 1;
			break;
		}
		i++;
	}

	if (!isValid) textColor("\t\t\t\t\t\t* ���� : �ùٸ� �ּҸ� �Է��ϼ���.\n", 12);

	return isValid;
}
int isValidPhone(char txt[])
{
	int isValid = 1;
	int	n = 0, m = 0, j = 0;

	while (isValid == 1 && txt[j] != '\0')
	{
		if (txt[j] == '-')
		{
			n++;
			if (m == 0)
			{
				isValid = 0;
				break;
			}
			m = 0;
		}
		else if (txt[j] < 48 || txt[j] > 57)
		{
			isValid = 0;
			break;
		}
		else
		{
			m++;
		}
		j++;
	}
	if (n != 2 || m == 0) isValid = 0;

	if (!isValid) textColor("\t\t\t\t\t\t* ���� : ������ �ùٸ��� �ʽ��ϴ�.\n", 12);
	
	return isValid;
}