#ifndef __REDBLACKTREE_H__
#define __REDBLACKTREE_H__

#define BLACK 1
#define RED 0

typedef struct member{
	int color;
	struct member *parent;
	struct member *left;
	struct member *right;
	int id;
	char name[10];
	char addr[256];
	char phone[15];
}Member;

typedef struct tree{
	struct member *root;
	struct member *NIL;
}Tree;

Tree *createRBT(void);				/* �����Ʈ�� ���� */
Member *createMember(Tree *RBT);	/* ���ο� ��� ���� */

Member *grandparent(Member *Node);	/* ����� �θ��� �θ� ��� */
Member *uncle(Member *Node);		/* ����� �θ��� ���� ��� */
Member *sibling(Member *Node);		/* ����� ���� ��� */

void insertNode(Tree *RBT, Member *Node);	/* Ʈ���� ��� ���� */
void insertNodeForName(Tree *RBT, Member *Node);/* Ʈ���� ��� ���� - �̸� ���� */
void treeFixUp(Tree *RBT, Member *Node);	/* Ʈ�� ���� ���� */
void deleteNode(Tree *RBT, Member *Node);	/* Ʈ�� ��� ���� */
void treeDelFixUp(Tree *RBT, Member *Node);	/* ������ Ʈ�� ���� ����*/

void rotateLeft(Tree *RBT, Member *Node);	/* Ʈ�� ���� ȸ�� */
void rotateRight(Tree *RBT, Member *Node);	/* Ʈ�� ���� ȸ�� */
Member *findSuccessor(Tree *RBT, Member *Node);/* Successor ã�� */
void transPlant(Tree *RBT, Member *Node, Member *Successor);

void printTree(Tree *RBT, Member *Node);	/* Ʈ�� ��� ��� */
void fprintTree(FILE *fp, Tree *RBT, Member *Node);	/* Ʈ�� ��� ���� ��� */
Member *searchValue(Tree *RBT, Member *Node, int id); /* ��� �˻� */
Member *searchValueForName(Tree *RBT, Member *Node, char *name); /* ��� �˻� */

#endif