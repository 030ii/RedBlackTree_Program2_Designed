#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

/* �����Ʈ�� ���� */
Tree *createRBT(void)
{
	Tree *newTree;
	Member *newNIL;

	// ���ο� Ʈ���� �� �ȿ� �� �� ��带 �����
	newTree = malloc(sizeof(Tree));
	newNIL = malloc(sizeof(Member));

	// �� ����� �Ӽ��� �����ϰ�, Ʈ���� �� ��� ������ �Ҵ��Ѵ�
	newNIL->color = BLACK;
	newTree->NIL = newNIL;
	newTree->root = newTree->NIL;

	return newTree;
}

/* ��� ���� */
Member *createMember(Tree *RBT)
{
	Member *newMember = malloc(sizeof(Member));

	newMember->color = RED;
	newMember->left = RBT->NIL;
	newMember->right = RBT->NIL;

	return newMember;
}

/* ���ο� ��� ���� */
void insertNode(Tree *RBT, Member *Node)
{
	Member *curNode, *tempNode;

	// ���� ��尡 ��Ʈ����� ���
	if (RBT->root == RBT->NIL){
		RBT->root = Node;
		Node->parent = NULL;
		return;
	}

	// ���� ��尡 �� ��ġ�� ã�� NIL���� ��ü
	curNode = RBT->root;
	tempNode = curNode;
	while (curNode != RBT->NIL)
	{
		tempNode = curNode;
		if (curNode->id > Node->id)
			curNode = tempNode->left;
		else
			curNode = tempNode->right;
	}

	Node->parent = tempNode;
	if (tempNode->id > Node->id)
		tempNode->left = Node;
	else
		tempNode->right = Node;


	return;
}

/* ���ο� ��� ���� - name ���� */
void insertNodeForName(Tree *RBT, Member *Node)
{
	Member *curNode, *tempNode;

	// ���� ��尡 ��Ʈ����� ���
	if (RBT->root == RBT->NIL){
		RBT->root = Node;
		Node->parent = NULL;
		return;
	}

	// ���� ��尡 �� ��ġ�� ã�� NIL���� ��ü
	curNode = RBT->root;
	tempNode = curNode;
	while (curNode != RBT->NIL)
	{
		tempNode = curNode;

		if (0 < strcmp(curNode->name, Node->name))
			curNode = tempNode->left;
		else
			curNode = tempNode->right;
	}

	Node->parent = tempNode;
	if (0 < strcmp(tempNode->name, Node->name))
	{
		tempNode->left = Node;
	}
	else
	{
		tempNode->right = Node;
	}

	return;
}

/* �����Ʈ�� ���� ���� */

void treeFixUp(Tree *RBT, Member *Node)
{
	Member *p = Node->parent;
	Member *u = uncle(Node);
	Member *g = grandparent(Node);

	// case1 : ������ ��尡 ��Ʈ ����� ���
	if (Node == RBT->root)
	{
		Node->color = BLACK;
		return;
	}
	// case2 : ������ ����� �θ� �������� ���
	else if (p->color == BLACK)
	{
		return;
	}
	// case3 : ������ ���� �θ� ����� ���� �������� ���
	else if (Node->color == RED && p->color == RED)
	{
		// case 3-1 : ���� ��尡 �������� ���
		if (u->color == BLACK)
		{
			// case 3-1-1 : ���� ���� �θ� ����� ������ �ݴ��� ���
			if (Node == p->left && p == g->right)
			{
				rotateRight(RBT, Node);
				Node = p;
			}
			else if (Node == p->right && p == g->left)
			{
				rotateLeft(RBT, Node);
				Node = p;
			} 

			p = Node->parent;
			u = uncle(Node);
			g = grandparent(Node);

			// case 3-1-2 : ���� ���� �θ� ����� ������ ������ ���
			p->color = BLACK;
			g->color = RED;
			if (p == g->left)
			{
				rotateRight(RBT, p);
			}
			else if (p == g->right)
			{
				rotateLeft(RBT, p);
			}
		}
		// case 3-2 : ���� ��尡 �������� ���
		else
		{
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			treeFixUp(RBT, g);
		}
	}

	return;
}

// Ʈ�� ��� ���� 
void deleteNode(Tree *RBT, Member *Node)
{
	Member *successor, *fixupNode;
	int nColor = Node->color;
	Member *left = Node->left;
	Member *right = Node->right;
	Member *p = Node->parent;

	// ���ʳ�� ���� ���
	if (left == RBT->NIL)
	{
		fixupNode = right;
		transPlant(RBT, Node, right);
	}
	// �����ʳ�� ���� ���
	else if (right == RBT->NIL)
	{
		fixupNode = left;
		transPlant(RBT, Node, left);
	}
	// �ڽĳ�� 2���� ���
	else
	{
		successor = findSuccessor(RBT, Node);
		nColor = successor->color;
		fixupNode = successor->right;
		if (successor->parent == Node)
		{
			fixupNode->parent = successor;
		}
		else
		{
			transPlant(RBT, successor, fixupNode);
			successor->right = Node->right;
			successor->right->parent = successor;
		}
		transPlant(RBT, Node, successor);
		successor->left = Node->left;
		successor->left->parent = successor;
		successor->color = Node->color;
	}

	// ���� ����� ���� BLACK�� ��� Violation �߻�
	if (nColor == BLACK)
	{
		treeDelFixUp(RBT, fixupNode);
	}

	// �޸� ���� �ع������
	free(Node);

	return;
}

// ������ Ʈ�� ���� ����
void treeDelFixUp(Tree *RBT, Member *Node)
{
	Member *s;
	while (Node != RBT->root && Node->color == BLACK)
	{
		if (Node == Node->parent->left)
		{
			s = Node->parent->right;
			if (s->color == RED)
			{
				s->color = BLACK;
				Node->parent->color = RED;
				rotateLeft(RBT, Node->parent);
				s = Node->parent->right;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				Node = Node->parent;
			}
			else
			{
				if (s->right->color == BLACK)
				{
					s->left->color = BLACK;
					s->color = RED;
					rotateRight(RBT, s);
					s = Node->parent->right;
				}

				s->color = Node->parent->color;
				Node->parent->color = BLACK;
				s->right->color = BLACK;
				rotateLeft(RBT, Node->parent);
				Node = RBT->root;
			}
		}
		else
		{
			s = Node->parent->left;
			if (s->color == RED)
			{
				s->color = BLACK;
				Node->parent->color = RED;
				rotateRight(RBT, Node->parent);
				s = Node->parent->left;
			}
			if (s->right->color == BLACK && s->left->color == BLACK)
			{
				s->color = RED;
				Node = Node->parent;
			}
			else
			{
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					rotateLeft(RBT, s);
					s = Node->parent->left;
				}

				s->color = Node->parent->color;
				Node->parent->color = BLACK;
				s->left->color = BLACK;
				rotateRight(RBT, Node->parent);
				Node = RBT->root;
			}
		}
	}
	Node->color = BLACK;

	return;
}

// ���� ����� �θ��� �θ� ���
Member *grandparent(Member *Node)
{
	if ((Node != NULL) && (Node->parent != NULL))
		return Node->parent->parent;
	else
		return NULL;
}

// ���� ����� �θ��� ���� ���
Member *uncle(Member *Node)
{
	Member *g = grandparent(Node);

	if (g == NULL)
		return NULL;
	if (Node->parent == Node->left)
		return g->right;
	else
		return g->left;
}

// ���� ����� ���� ���
Member *sibling(Member *Node)
{
	Member *p = Node->parent;

	if (p == NULL)
	{
		return NULL;
	}

	if (Node == p->left)
	{
		return p->right;
	}
	else
	{
		return p->left;
	}
}

// ���� �θ� ����� ��ġ�� �������� ����
void rotateLeft(Tree *RBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->left;

	// �θ� ��Ʈ ����� ���
	if (g == NULL)
	{
		RBT->root = Node;
	}
	else
	{
		if (p == g->left)
			g->left = Node;
		else
			g->right = Node;
	}

	Node->parent = g;
	Node->left = p;
	p->parent = Node;
	p->right = temp;
}


// ���� �θ� ����� ��ġ�� ���������� ����
void rotateRight(Tree *RBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->right;

	// �θ� ��Ʈ ����� ���
	if (g == NULL)
	{
		RBT->root = Node;
	}
	else
	{
		if (p == g->left)
			g->left = Node;
		else
			g->right = Node;
	}

	Node->parent = g;
	Node->right = p;
	p->parent = Node;
	p->left = temp;
}

// Successor ã��
Member *findSuccessor(Tree *RBT, Member *Node)
{
	Member *successor = Node->right;

	while (successor->left != RBT->NIL)
	{
		successor = successor->left;
	}

	return successor;
}

void transPlant(Tree *RBT, Member *Node, Member *Successor)
{
	if (Node->parent == NULL)
	{
		RBT->root = Successor;
	}
	else if (Node == Node->parent->left)
	{
		Node->parent->left = Successor;
	}
	else
	{
		Node->parent->right = Successor;
	}
	Successor->parent = Node->parent;
}

// Ʈ�� ���
void printTree(Tree *RBT, Member *Node)
{
	if (Node->left != RBT->NIL)
	{
		printTree(RBT, Node->left);
	}
	printf("%d\t\t%s\t\t%s\t\t%s\n", Node->id, Node->name, Node->addr, Node->phone);
	if (Node->right != RBT->NIL)
	{
		printTree(RBT, Node->right);
	}
	return;
}

void fprintTree(FILE *fp, Tree *RBT, Member *Node)
{
	if (Node->left != RBT->NIL)
	{
		fprintTree(fp, RBT, Node->left);
	}
	fprintf(fp, "%d\t%s\t%s\t%s\n", Node->id, Node->name, Node->addr, Node->phone);
	if (Node->right != RBT->NIL)
	{
		fprintTree(fp, RBT, Node->right);
	}
	return;
}

Member *searchValue(Tree *RBT, Member *Node, int id)
{
	while (Node != RBT->NIL && Node->id != id)
	{
		if (Node->id > id)
			Node = Node->left;
		else
			Node = Node->right;
	}

	if (Node == RBT->NIL)
		Node = NULL;

	return Node;
}

Member *searchValueForName(Tree *RBT, Member *Node, char *name)
{
	while (Node != RBT->NIL && strcmp(Node->name,name)!=0)
	{
		if (0<strcmp(Node->name, name))
			Node = Node->left;
		else
			Node = Node->right;
	}

	if (Node == RBT->NIL)
		Node = NULL;

	return Node;
}