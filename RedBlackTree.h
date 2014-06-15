#ifndef __REDBLACKTREE_H__
#define __REDBLACKTREE_H__

#define BLACK 1
#define RED 0

typedef struct member{
	int id;
	char name[10];
	char addr[256];
	char phone[15];
}Member;

typedef struct node{
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
	Member *data;
}Node;

typedef struct tree{
	Node *root;
	Node *NIL;
}Tree;

Tree *createRBT(void);							/* �����Ʈ�� ���� */
Node *createMember(Tree *RBT, Member *data);	/* ���ο� ��� ���� */

Node *grandparent(Node *node);	/* ����� �θ��� �θ� ��� */
Node *uncle(Node *node);		/* ����� �θ��� ���� ��� */
Node *sibling(Node *node);		/* ����� ���� ��� */

void insertNode(Tree *RBT, Node *node, int flag);	/* Ʈ���� ��� ���� */
void treeFixUp(Tree *RBT, Node *node);	/* Ʈ�� ���� ���� */
void deleteNode(Tree *RBT, Node *node);	/* Ʈ�� ��� ���� */
void treeDelFixUp(Tree *RBT, Node *node);	/* ������ Ʈ�� ���� ����*/

void rotateLeft(Tree *RBT, Node *node);	/* Ʈ�� ���� ȸ�� */
void rotateRight(Tree *RBT, Node *node);	/* Ʈ�� ���� ȸ�� */
Node *findSuccessor(Tree *RBT, Node *node);/* Successor ã�� */
void transPlant(Tree *RBT, Node *node, Node *successor);

void printTree(Tree *RBT, Node *node);	/* Ʈ�� ��� ��� */
void fprintTree(FILE *fp, Tree *RBT, Node *node);	/* Ʈ�� ��� ���� ��� */
Node *searchValue(Tree *RBT, Node *node, int id, char name[]); /* ��� �˻� */
Node *searchEqualValue(Tree *RBT, Node *node, char name[], Node *nodearr[]); /* �ߺ��Ǵ� Ű���� ��� �˻� */
int findLastId(Tree *RBT);
void blackHeight(Tree *RBT, Node *node, int height);

#endif