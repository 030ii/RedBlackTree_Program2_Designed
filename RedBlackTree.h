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

Tree *createRBT(void);							/* 레드블랙트리 생성 */
Node *createMember(Tree *RBT, Member *data);	/* 새로운 노드 생성 */

Node *grandparent(Node *node);	/* 노드의 부모의 부모 노드 */
Node *uncle(Node *node);		/* 노드의 부모의 형제 노드 */
Node *sibling(Node *node);		/* 노드의 형제 노드 */

void insertNode(Tree *RBT, Node *node, int flag);	/* 트리에 노드 삽입 */
void treeFixUp(Tree *RBT, Node *node);	/* 트리 균형 수정 */
void deleteNode(Tree *RBT, Node *node);	/* 트리 노드 삭제 */
void treeDelFixUp(Tree *RBT, Node *node);	/* 삭제시 트리 균형 수정*/

void rotateLeft(Tree *RBT, Node *node);	/* 트리 좌측 회전 */
void rotateRight(Tree *RBT, Node *node);	/* 트리 우측 회전 */
Node *findSuccessor(Tree *RBT, Node *node);/* Successor 찾기 */
void transPlant(Tree *RBT, Node *node, Node *successor);

void printTree(Tree *RBT, Node *node);	/* 트리 노드 출력 */
void fprintTree(FILE *fp, Tree *RBT, Node *node);	/* 트리 노드 파일 출력 */
Node *searchValue(Tree *RBT, Node *node, int id, char name[]); /* 노드 검색 */
Node *searchEqualValue(Tree *RBT, Node *node, char name[], Node *nodearr[]); /* 중복되는 키워드 노드 검색 */
int findLastId(Tree *RBT);
void blackHeight(Tree *RBT, Node *node, int height);

#endif