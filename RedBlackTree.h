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

Tree *createRBT(void);				/* 레드블랙트리 생성 */
Member *createMember(Tree *RBT);	/* 새로운 노드 생성 */

Member *grandparent(Member *Node);	/* 노드의 부모의 부모 노드 */
Member *uncle(Member *Node);		/* 노드의 부모의 형제 노드 */
Member *sibling(Member *Node);		/* 노드의 형제 노드 */

void insertNode(Tree *RBT, Member *Node);	/* 트리에 노드 삽입 */
void insertNodeForName(Tree *RBT, Member *Node);/* 트리에 노드 삽입 - 이름 기준 */
void treeFixUp(Tree *RBT, Member *Node);	/* 트리 균형 수정 */
void deleteNode(Tree *RBT, Member *Node);	/* 트리 노드 삭제 */
void treeDelFixUp(Tree *RBT, Member *Node);	/* 삭제시 트리 균형 수정*/

void rotateLeft(Tree *RBT, Member *Node);	/* 트리 좌측 회전 */
void rotateRight(Tree *RBT, Member *Node);	/* 트리 우측 회전 */
Member *findSuccessor(Tree *RBT, Member *Node);/* Successor 찾기 */
void transPlant(Tree *RBT, Member *Node, Member *Successor);

void printTree(Tree *RBT, Member *Node);	/* 트리 노드 출력 */
void fprintTree(FILE *fp, Tree *RBT, Member *Node);	/* 트리 노드 파일 출력 */
Member *searchValue(Tree *RBT, Member *Node, int id); /* 노드 검색 */
Member *searchValueForName(Tree *RBT, Member *Node, char *name); /* 노드 검색 */

#endif