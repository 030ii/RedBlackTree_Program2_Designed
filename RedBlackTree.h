#ifndef __REDBLACKTREE_H__
#define __REDBLACKTREE_H__

#define BLACK 1
#define RED 0

typedef struct member{
<<<<<<< HEAD
=======
	int color;
	struct member *parent;
	struct member *left;
	struct member *right;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	int id;
	char name[10];
	char addr[256];
	char phone[15];
}Member;

<<<<<<< HEAD
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
int findLastId(Tree *RBT);
void blackHeight(Tree *RBT, Node *node, int height);
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

#endif