#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

/*******************************************************************************
								UI 婦溼л熱
*******************************************************************************/

// 僥濠 陛遴等 薑溺
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

// 儀鼻 旋濠 轎溘
void textColor(char txt[], int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | color);
	printf("%s", txt);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 8);
}

// 臢蝶お鼻濠 轎溘
void printBox(char txt[])
{
	int i,j,k;
	char width2[] = "忙式式式式式式式式式式式式式式式式式式式忖";
	int size1 = (strlen(WIDTH) - strlen(width2)) / 2;
	int size2 = (strlen(width2)-4 - strlen(txt)) / 2;

	alignCenter("旨收收收收收收收收收收收收收收收收收收收旬\n");
	alignCenter("早                                      早\n");

	for (i = 0; i < size1; i++)
	{
		printf(" ");
	}
	printf("早");
	for (j = 0; j < size2; j++)
	{
		printf(" ");
	}
	printf("%s", txt);
	for (k = 0; k < size2; k++)
	{
		printf(" ");
	}
	printf("早\n");

	alignCenter("早           (蕨:1, 嬴棲螃:0)           早\n");
	
	alignCenter("早                                      早\n");
	alignCenter("曲收收收收收收收收收收收收收收收收收收收旭\n");
}



/*******************************************************************************
							�蛾灠�葬詭景 婦溼л熱
*******************************************************************************/

// 臢蝶お 僥憮縑憮 等檜攪 煎萄
void roadData(FILE *fp, Tree *RBT, Tree *RBTForName)
{
	Member *data = NULL;
	Node *curNode = NULL, *curNodeForName = NULL;
	char buff[1024];
	int i = 0;
	char *id, *name, *addr, *phone;


	while (fgets(buff, sizeof(buff), fp))
	{
		buff[strlen(buff) - 1] = '\0';	// 幗ぷ曖 葆雖虞 偃ч擊 奢寥僥濠煎 夥翎

		// 等檜攪 だ橾曖 羅 ч(翮該葬) 薯諼
		if (i == 0){
			i++;
			continue;
		}

		// 幗ぷ曖 僥濠翮擊 龔戲煎 釭援橫 等檜攪縑 盪濰
		id = strtok(buff, "\t");
		name = strtok(NULL, "\t");
		addr = strtok(NULL, "\t");
		phone = strtok(NULL, "\t");

		// 等檜攪蒂 Member 掘褻羹縑 盪濰
		data = malloc(sizeof(Member));
		data->id = atoi(id);
		strcpy(data->name, name);
		strcpy(data->addr, addr);
		strcpy(data->phone, phone);

		// 掘褻羹縑 奢除 塽 等檜攪 й渡
		curNode = createMember(RBT,data);
		curNodeForName = createMember(RBTForName,data);

		// 掘褻羹蒂 お葬縑 鳶殮
		insertNode(RBT, curNode, 0);
		insertNode(RBTForName, curNodeForName, 1);
	}

	return;
}


// 詭景1 : �蛾羉萵�
void menu1_member_view(Tree *tree)
{
	int input;
	system("cls");

	printf("\n");
	alignCenter("式式式式式式式式式式式式式式式式\n");
	alignCenter("1. �蛾� 跡煙\n");
	alignCenter("式式式式式式式式式式式式式式式式\n");
	printf("\n");
	printf("\t\t\t嬴檜蛤\t\t 檜葷\t\t  �瑒蹀��苒t\t\t  輿模\n");

	printTree(tree, tree->root);

	printf("\n");
	alignCenter("式式式式式式式MENU式式式式式式式\n");
	alignCenter("0. 謙猿\n");
	alignCenter("式式式式式式式式式式式式式式式式\n");

	alignCenter("幗が擊 殮溘ж撮蹂 : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}

// 詭景2 : �蛾躞葥�
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
	alignCenter("式式式式式式式式式式式式式式式式\n");
	alignCenter("2. �蛾� 蹺陛\n");
	alignCenter("式式式式式式式式式式式式式式式式\n");
	alignCenter("0擊 殮溘ж賊 鏃模腌棲棻.");

	// ID : 濠翕儅撩
	printf("\n\n");
	id = findLastId(tree)+1;
	alignCenter("ID : ");
	printf("%d", id);

	// name
	do
	{
		printf("\n\n");
		alignCenter("檜葷 : ");
		scanf_s("%s", &buff, 256);
		if (!strcmp(buff, "0")) return;
		nameIsValid = isValidName(buff);

	} while (!nameIsValid);
	strcpy(name, buff);

	// address
	do{
		printf("\n");
		alignCenter("輿模 : ");
		fflush(stdin);
		gets_s(buff, 256);
		if (!strcmp(buff, "0")) return;
		addrIsValid = isValidAddr(buff);

	} while (!addrIsValid);
	strcpy(addr, buff);

	// phone number
	do{
		printf("\n");
		alignCenter("瞪�食醽� : ");;
		scanf_s("%s", &phone, 15);
		if (!strcmp(phone,"0")) return;
		phoneIsValid = isValidPhone(phone);

	} while (!phoneIsValid);

	// 等檜攪蒂 Member 掘褻羹縑 盪濰
	data = malloc(sizeof(Member));
	data->id = id;
	strcpy(data->name, name);
	strcpy(data->addr, addr);
	strcpy(data->phone, phone);

	// お葬 喻萄 掘褻羹縑 奢除 塽 等檜攪 й渡
	newNode = createMember(tree,data);
	newNodeForName = createMember(treeForName,data);

	// 掘褻羹蒂 お葬縑 鳶殮
	insertNode(tree, newNode, 0);



	insertNode(treeForName, newNodeForName, 1);

	return;
}

// 詭景3 : �蛾虃鶬�
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
		alignCenter("式式式式式式式式式式式式式式式式\n");
		alignCenter("3. �蛾� 熱薑\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");

		alignCenter("橫雯 酈錶萄煎 匐儀ж衛啊蝗棲梱?\n\n");

		alignCenter("1. 嬴檜蛤匐儀\n");
		alignCenter("2. 檜葷匐儀\n");
		alignCenter("0. 謙猿\n\n");
		alignCenter("幗が擊 殮溘ж撮蹂  : ");
		scanf("%d", &input);


		// 匐儀 酈錶萄 殮溘
		do
		{
			alignCenter("式式式式式式式式式式式式式式式式\n");
			if (input == 0) return;

			if (input == 1)
			{
				printf("\n");
				alignCenter("嬴檜蛤蒂 殮溘ж撮蹂 : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				printf("\n");
				alignCenter("檜葷擊 殮溘ж撮蹂 : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0,nameKey);
			}
			if (delMember == NULL)
			{
				system("cls");
				printf("\n");
				alignCenter("式式式式式式式式式式式式式式式式\n");
				alignCenter("3. �蛾� 熱薑\n");
				alignCenter("式式式式式式式式式式式式式式式式\n");

				textColor("\t\t\t\t\t   * 螃盟 : 酈錶萄蒂 瓊擊 熱 橈蝗棲棻.\n\n", 12);

				alignCenter("1. 嬴檜蛤匐儀\n");
				alignCenter("2. 檜葷匐儀\n");
				alignCenter("0. 謙猿\n\n");
				alignCenter("幗が擊 殮溘ж撮蹂  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		// 晦襄 等檜攪 寥機
		delData = delMember->data;
		strcpy(name, delData->name);
		strcpy(addr, delData->addr);
		strcpy(phone, delData->phone);

		// �蛾� 薑爾 爾罹邀
		system("cls");

		printf("\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");
		alignCenter("3. �蛾� 熱薑\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");
		printf("\n");
		alignCenter("瓊擎 �蛾� 薑爾\n\n");
		printf("\t\t\t\t  %d\t%s\t%s\t%s\t\n\n", delData->id, name, addr, phone);
		
		// 熱薑й 薑爾 殮溘
		alignCenter("式式式式式式式式式式式式式式式式\n");
		alignCenter("橫雯 薑爾蒂 熱薑ж衛啊蝗棲梱?\n");
		printf("\n");
		alignCenter("1. 檜葷\n");
		alignCenter("2. 輿模\n");
		alignCenter("3. 瞪�食醽αn");
		alignCenter("0. 鏃模\n");
		printf("\n");
		alignCenter("幗が擊 殮溘ж撮蹂 : ");
		scanf("%d", &input);
		if (input == 0) return;

		alignCenter("式式式式式式式式式式式式式式式式\n");
		switch (input)
		{
		case 1:
			// name
			do{
				printf("\n\n");
				alignCenter("檜葷 : ");
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
				alignCenter("輿模 : ");
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
				alignCenter("瞪�食醽� : ");;
				scanf_s("%s", &buff, 15);
				if (!strcmp(buff, "0")) return;
				phoneIsValid = isValidPhone(buff);

			} while (!phoneIsValid);
			strcpy(phone, buff);
			break;
		case 0:
			return;
		}

		// 晦襄 等檜攪 餉薯
		delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
		deleteNode(treeForName, delMember);

		// 掘褻羹縑 奢除 塽 等檜攪 й渡
		newNodeForName = createMember(treeForName, delData);
		newNodeForName->data = delData;

		strcpy(delData->name, name);
		strcpy(delData->addr, addr);
		strcpy(delData->phone, phone);

		// 掘褻羹蒂 お葬縑 鳶殮
		insertNode(treeForName, newNodeForName,1);
		treeFixUp(treeForName, newNodeForName);

		// 謙猿 UI
		printf("\n");
		alignCenter("撩奢瞳戲煎 熱薑腎歷蝗棲棻.\n");
		printf("\n");
		printBox("啗樓 熱薑ж衛啊蝗棲梱?");

		alignCenter("幗が擊 殮溘ж撮蹂 : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}


// 詭景4 : �蛾艭餑�
void menu4_member_delete(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *delMember = NULL;
	Member *delData = NULL;


	do{
		system("cls");

		printf("\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");
		alignCenter("4. �蛾� 餉薯\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");

		alignCenter("橫雯 酈錶萄煎 匐儀ж衛啊蝗棲梱?\n\n");
		alignCenter("1. 嬴檜蛤匐儀\n");
		alignCenter("2. 檜葷匐儀\n");
		alignCenter("0. 謙猿\n\n");
		alignCenter("幗が擊 殮溘ж撮蹂  : ");
		scanf("%d", &input);

		printf("\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");
		printf("\n");

		do
		{
			if (input == 0) return;

			if (input == 1)
			{
				alignCenter("匐儀й 嬴檜蛤蒂 殮溘ж撮蹂 : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				alignCenter("匐儀й 檜葷擊 殮溘ж撮蹂 : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0, nameKey);
			}
			if (delMember == NULL)
			{
				printf("\n\n");
				textColor("\t\t\t\t\t   * 螃盟 : 酈錶萄蒂 瓊擊 熱 橈蝗棲棻.\n\n", 12);
				alignCenter("1. 嬴檜蛤匐儀\n");
				alignCenter("2. 檜葷匐儀\n");
				alignCenter("0. 謙猿\n");
				printf("\n");
				alignCenter("幗が擊 殮溘ж撮蹂  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		delData = delMember->data;

		printf("\n\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");
		alignCenter("瓊擎 �蛾� 薑爾\n");
		alignCenter("式式式式式式式式式式式式式式式式\n");
		printf("\n\t\t\t\t%d\t%s\t%s\t%s\t\n\n", delData->id, delData->name, delData->addr, delData->phone);
		printBox("餉薯ж衛啊蝗棲梱? ");
		alignCenter("幗が擊 殮溘ж撮蹂 : ");
		scanf("%d", &input);

		if (input == 1)
		{	

			// ID お葬縑憮 餉薯
			delMember = searchValue(tree, tree->root, delData->id,'\0');
			deleteNode(tree, delMember);

			// 檜葷 お葬縑憮 餉薯
			delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
			deleteNode(treeForName, delMember);

			free(delData);
		}
		else
		{
			alignCenter("餌辨濠陛 鏃模ж艘蝗棲棻.\n");
		}

		printf("\n");
		alignCenter("MENU\n");
		alignCenter("1. 營褒ч\n");
		alignCenter("0. 謙猿\n");

		alignCenter("幗が擊 殮溘ж撮蹂 : ");
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
	alignCenter("式式式式式式式式式式式式式式式式\n");
	alignCenter("6. だ橾 盪濰\n");
	alignCenter("式式式式式式式式式式式式式式式式\n");

	printBox("盪濰ж衛啊蝗棲梱? ");
	alignCenter("幗が擊 殮溘ж撮蹂 : ");
	scanf("%d", &input);
	if (input == 0) return;

	fprintf(fp, "�蛾� 嬴檜蛤\t�蛾衋抶吭t�蛾讔祤涂tс萄ア 廓�αn");
	fprintTree(fp, tree, tree->root);

	fclose(fp);

	printf("\n\n");

	alignCenter("撩奢瞳戲煎 盪濰腎歷蝗棲棻\n\n");

	printf(WIDTH);
	printf("\n");

	alignCenter("謙猿ж溥賊 嬴鼠 酈釭 殮溘ж撮蹂.");
	scanf("%d", &input);

	return;
}



/*******************************************************************************
								殮溘高 嶸�蕉� 匐餌
*******************************************************************************/

int isValidName(char txt[])
{
	int isValid = 0;
	if (txt[0] != '\0' && strlen(txt) < 10)
	{
		isValid = 1;
	}

	if (!isValid) textColor("\t\t\t\t\t\t* 螃盟 : 螢夥艇 檜葷擊 殮溘ж撮蹂.\n", 12);
	
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

	if (!isValid) textColor("\t\t\t\t\t\t* 螃盟 : 螢夥艇 輿模蒂 殮溘ж撮蹂.\n", 12);

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

	if (!isValid) textColor("\t\t\t\t\t\t* 螃盟 : ⑽衝檜 螢夥腦雖 彊蝗棲棻.\n", 12);
	
	return isValid;
}