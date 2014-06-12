#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

/*******************************************************************************
								UI 관련함수
*******************************************************************************/

// 문자 가운데 정렬
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

// 색상 글자 출력
void textColor(char txt[], int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | color);
	printf("%s", txt);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 8);
}

// 텍스트상자 출력
void printBox(char txt[])
{
	int i,j,k;
	char width2[] = "┌───────────────────┐";
	int size1 = (strlen(WIDTH) - strlen(width2)) / 2;
	int size2 = (strlen(width2)-4 - strlen(txt)) / 2;

	alignCenter("┏━━━━━━━━━━━━━━━━━━━┓\n");
	alignCenter("┃                                      ┃\n");

	for (i = 0; i < size1; i++)
	{
		printf(" ");
	}
	printf("┃");
	for (j = 0; j < size2; j++)
	{
		printf(" ");
	}
	printf("%s", txt);
	for (k = 0; k < size2; k++)
	{
		printf(" ");
	}
	printf("┃\n");

	alignCenter("┃           (예:1, 아니오:0)           ┃\n");
	
	alignCenter("┃                                      ┃\n");
	alignCenter("┗━━━━━━━━━━━━━━━━━━━┛\n");
}



/*******************************************************************************
							회원관리메뉴 관련함수
*******************************************************************************/

// 텍스트 문서에서 데이터 로드
void roadData(FILE *fp, Tree *RBT, Tree *RBTForName)
{
	Member *data = NULL;
	Node *curNode = NULL, *curNodeForName = NULL;
	char buff[1024];
	int i = 0;
	char *id, *name, *addr, *phone;


	while (fgets(buff, sizeof(buff), fp))
	{
		buff[strlen(buff) - 1] = '\0';	// 버퍼의 마지막 개행을 공백문자로 바꿈

		// 데이터 파일의 첫 행(열머리) 제외
		if (i == 0){
			i++;
			continue;
		}

		// 버퍼의 문자열을 탭으로 나누어 데이터에 저장
		id = strtok(buff, "\t");
		name = strtok(NULL, "\t");
		addr = strtok(NULL, "\t");
		phone = strtok(NULL, "\t");

		// 데이터를 Member 구조체에 저장
		data = malloc(sizeof(Member));
		data->id = atoi(id);
		strcpy(data->name, name);
		strcpy(data->addr, addr);
		strcpy(data->phone, phone);

		// 구조체에 공간 및 데이터 할당
		curNode = createMember(RBT,data);
		curNodeForName = createMember(RBTForName,data);

		// 구조체를 트리에 삽입
		insertNode(RBT, curNode, 0);
		insertNode(RBTForName, curNodeForName, 1);
	}

	return;
}


// 메뉴1 : 회원보기
void menu1_member_view(Tree *tree)
{
	int input;
	system("cls");

	printf("\n");
	alignCenter("────────────────\n");
	alignCenter("1. 회원 목록\n");
	alignCenter("────────────────\n");
	printf("\n");
	printf("\t\t\t아이디\t\t 이름\t\t  휴대전화\t\t\t  주소\n");

	printTree(tree, tree->root);

	printf("\n");
	alignCenter("───────MENU───────\n");
	alignCenter("0. 종료\n");
	alignCenter("────────────────\n");

	alignCenter("버튼을 입력하세요 : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}

// 메뉴2 : 회원추가
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
	alignCenter("────────────────\n");
	alignCenter("2. 회원 추가\n");
	alignCenter("────────────────\n");
	alignCenter("0을 입력하면 취소됩니다.");

	// ID : 자동생성
	printf("\n\n");
	id = findLastId(tree)+1;
	alignCenter("ID : ");
	printf("%d", id);

	// name
	do
	{
		printf("\n\n");
		alignCenter("이름 : ");
		scanf_s("%s", &buff, 256);
		if (!strcmp(buff, "0")) return;
		nameIsValid = isValidName(buff);

	} while (!nameIsValid);
	strcpy(name, buff);

	// address
	do{
		printf("\n");
		alignCenter("주소 : ");
		fflush(stdin);
		gets_s(buff, 256);
		if (!strcmp(buff, "0")) return;
		addrIsValid = isValidAddr(buff);

	} while (!addrIsValid);
	strcpy(addr, buff);

	// phone number
	do{
		printf("\n");
		alignCenter("전화번호 : ");;
		scanf_s("%s", &phone, 15);
		if (!strcmp(phone,"0")) return;
		phoneIsValid = isValidPhone(phone);

	} while (!phoneIsValid);

	// 데이터를 Member 구조체에 저장
	data = malloc(sizeof(Member));
	data->id = id;
	strcpy(data->name, name);
	strcpy(data->addr, addr);
	strcpy(data->phone, phone);

	// 트리 노드 구조체에 공간 및 데이터 할당
	newNode = createMember(tree,data);
	newNodeForName = createMember(treeForName,data);

	// 구조체를 트리에 삽입
	insertNode(tree, newNode, 0);



	insertNode(treeForName, newNodeForName, 1);

	return;
}

// 메뉴3 : 회원수정
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
		alignCenter("────────────────\n");
		alignCenter("3. 회원 수정\n");
		alignCenter("────────────────\n");

		alignCenter("어떤 키워드로 검색하시겠습니까?\n\n");

		alignCenter("1. 아이디검색\n");
		alignCenter("2. 이름검색\n");
		alignCenter("0. 종료\n\n");
		alignCenter("버튼을 입력하세요  : ");
		scanf("%d", &input);


		// 검색 키워드 입력
		do
		{
			alignCenter("────────────────\n");
			if (input == 0) return;

			if (input == 1)
			{
				printf("\n");
				alignCenter("아이디를 입력하세요 : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				printf("\n");
				alignCenter("이름을 입력하세요 : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0,nameKey);
			}
			if (delMember == NULL)
			{
				system("cls");
				printf("\n");
				alignCenter("────────────────\n");
				alignCenter("3. 회원 수정\n");
				alignCenter("────────────────\n");

				textColor("\t\t\t\t\t   * 오류 : 키워드를 찾을 수 없습니다.\n\n", 12);

				alignCenter("1. 아이디검색\n");
				alignCenter("2. 이름검색\n");
				alignCenter("0. 종료\n\n");
				alignCenter("버튼을 입력하세요  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		// 기존 데이터 백업
		delData = delMember->data;
		strcpy(name, delData->name);
		strcpy(addr, delData->addr);
		strcpy(phone, delData->phone);

		// 회원 정보 보여줌
		system("cls");

		printf("\n");
		alignCenter("────────────────\n");
		alignCenter("3. 회원 수정\n");
		alignCenter("────────────────\n");
		printf("\n");
		alignCenter("찾은 회원 정보\n\n");
		printf("\t\t\t\t  %d\t%s\t%s\t%s\t\n\n", delData->id, name, addr, phone);
		
		// 수정할 정보 입력
		alignCenter("────────────────\n");
		alignCenter("어떤 정보를 수정하시겠습니까?\n");
		printf("\n");
		alignCenter("1. 이름\n");
		alignCenter("2. 주소\n");
		alignCenter("3. 전화번호\n");
		alignCenter("0. 취소\n");
		printf("\n");
		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);
		if (input == 0) return;

		alignCenter("────────────────\n");
		switch (input)
		{
		case 1:
			// name
			do{
				printf("\n\n");
				alignCenter("이름 : ");
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
				alignCenter("주소 : ");
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
				alignCenter("전화번호 : ");;
				scanf_s("%s", &buff, 15);
				if (!strcmp(buff, "0")) return;
				phoneIsValid = isValidPhone(buff);

			} while (!phoneIsValid);
			strcpy(phone, buff);
			break;
		case 0:
			return;
		}

		// 기존 데이터 삭제
		delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
		deleteNode(treeForName, delMember);

		// 구조체에 공간 및 데이터 할당
		newNodeForName = createMember(treeForName, delData);
		newNodeForName->data = delData;

		strcpy(delData->name, name);
		strcpy(delData->addr, addr);
		strcpy(delData->phone, phone);

		// 구조체를 트리에 삽입
		insertNode(treeForName, newNodeForName,1);
		treeFixUp(treeForName, newNodeForName);

		// 종료 UI
		printf("\n");
		alignCenter("성공적으로 수정되었습니다.\n");
		printf("\n");
		printBox("계속 수정하시겠습니까?");

		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}


// 메뉴4 : 회원삭제
void menu4_member_delete(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *delMember = NULL;
	Member *delData = NULL;


	do{
		system("cls");

		printf("\n");
		alignCenter("────────────────\n");
		alignCenter("4. 회원 삭제\n");
		alignCenter("────────────────\n");

		alignCenter("어떤 키워드로 검색하시겠습니까?\n\n");
		alignCenter("1. 아이디검색\n");
		alignCenter("2. 이름검색\n");
		alignCenter("0. 종료\n\n");
		alignCenter("버튼을 입력하세요  : ");
		scanf("%d", &input);

		printf("\n");
		alignCenter("────────────────\n");
		printf("\n");

		do
		{
			if (input == 0) return;

			if (input == 1)
			{
				alignCenter("검색할 아이디를 입력하세요 : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				alignCenter("검색할 이름을 입력하세요 : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0, nameKey);
			}
			if (delMember == NULL)
			{
				printf("\n\n");
				textColor("\t\t\t\t\t   * 오류 : 키워드를 찾을 수 없습니다.\n\n", 12);
				alignCenter("1. 아이디검색\n");
				alignCenter("2. 이름검색\n");
				alignCenter("0. 종료\n");
				printf("\n");
				alignCenter("버튼을 입력하세요  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		delData = delMember->data;

		printf("\n\n");
		alignCenter("────────────────\n");
		alignCenter("찾은 회원 정보\n");
		alignCenter("────────────────\n");
		printf("\n\t\t\t\t%d\t%s\t%s\t%s\t\n\n", delData->id, delData->name, delData->addr, delData->phone);
		printBox("삭제하시겠습니까? ");
		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

		if (input == 1)
		{	

			// ID 트리에서 삭제
			delMember = searchValue(tree, tree->root, delData->id,'\0');
			deleteNode(tree, delMember);

			// 이름 트리에서 삭제
			delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
			deleteNode(treeForName, delMember);

			free(delData);
		}
		else
		{
			alignCenter("사용자가 취소하였습니다.\n");
		}

		printf("\n");
		alignCenter("MENU\n");
		alignCenter("1. 재실행\n");
		alignCenter("0. 종료\n");

		alignCenter("버튼을 입력하세요 : ");
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
	alignCenter("────────────────\n");
	alignCenter("6. 파일 저장\n");
	alignCenter("────────────────\n");

	printBox("저장하시겠습니까? ");
	alignCenter("버튼을 입력하세요 : ");
	scanf("%d", &input);
	if (input == 0) return;

	fprintf(fp, "회원 아이디\t회원이름\t회원주소\t핸드폰 번호\n");
	fprintTree(fp, tree, tree->root);

	fclose(fp);

	printf("\n\n");

	alignCenter("성공적으로 저장되었습니다\n\n");

	printf(WIDTH);
	printf("\n");

	alignCenter("종료하려면 아무 키나 입력하세요.");
	scanf("%d", &input);

	return;
}



/*******************************************************************************
								입력값 유효성 검사
*******************************************************************************/

int isValidName(char txt[])
{
	int isValid = 0;
	if (txt[0] != '\0' && strlen(txt) < 10)
	{
		isValid = 1;
	}

	if (!isValid) textColor("\t\t\t\t\t\t* 오류 : 올바른 이름을 입력하세요.\n", 12);
	
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

	if (!isValid) textColor("\t\t\t\t\t\t* 오류 : 올바른 주소를 입력하세요.\n", 12);

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

	if (!isValid) textColor("\t\t\t\t\t\t* 오류 : 형식이 올바르지 않습니다.\n", 12);
	
	return isValid;
}