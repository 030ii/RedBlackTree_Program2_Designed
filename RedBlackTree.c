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
	Node *newNIL;

	// ���ο� Ʈ���� �� �ȿ� �� �� ��带 �����
	newTree = malloc(sizeof(Tree));
	newNIL = malloc(sizeof(Node));

	// �� ����� �Ӽ��� �����ϰ�, Ʈ���� �� ��� ������ �Ҵ��Ѵ�
	newNIL->color = BLACK;
	newTree->NIL = newNIL;
	newTree->root = newTree->NIL;

	return newTree;
}

/* ��� ���� */
Node *createMember(Tree *RBT, Member *data)
{
	Node *newMember = malloc(sizeof(Node));

	newMember->color = RED;
	newMember->left = RBT->NIL;
	newMember->right = RBT->NIL;
	newMember->data = data;

	return newMember;
}

/* ���ο� ��� ���� flag - 0:id����, 1:name���� */
void insertNode(Tree *RBT, Node *node, int flag)
{
	Node *curNode, *tempNode;

	// ���� ��尡 ��Ʈ����� ���
	if (RBT->root == RBT->NIL){
		RBT->root = node;
		node->parent = NULL;
		node->color = BLACK;
		return;
	}

	// ���� ��尡 �� ��ġ�� ã�� NIL���� ��ü
	curNode = RBT->root;
	tempNode = curNode;

	// flag 0 : id���� ����
	if (flag == 0)
	{
		while (curNode != RBT->NIL)
		{
			tempNode = curNode;

			if (curNode->data->id > node->data->id)
				curNode = tempNode->left;
			else
				curNode = tempNode->right;
		}

		node->parent = tempNode;
		if (tempNode->data->id > node->data->id)
		{
			tempNode->left = node;
		}
		else
		{
			tempNode->right = node;
		}
	}
	// flag 1 : name���� ����
	else if (flag == 1)
	{
		while (curNode != RBT->NIL)
		{
			tempNode = curNode;

			if (0 < strcmp(curNode->data->name, node->data->name))
			{
				curNode = tempNode->left;
			}
			else
			{
				curNode = tempNode->right;
			}
		}

		node->parent = tempNode;
		if (0 < strcmp(tempNode->data->name, node->data->name))
		{
			tempNode->left = node;
		}
		else
		{
			tempNode->right = node;
		}
	}
	else
	{
		printf("�÷��װ� �ùٸ��� �ʽ��ϴ�.");
	}

	treeFixUp(RBT, node);
	return;
}

/* �����Ʈ�� ���� ���� */
void treeFixUp(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *u = uncle(node);
	Node *g = grandparent(node);

	// case1 : ������ ��尡 ��Ʈ ����� ���
	if (node == RBT->root)
	{
		node->color = BLACK;
		return;
	}
	// case2 : ������ ����� �θ� �������� ���
	else if (p->color == BLACK)
	{
		return;
	}
	// case3 : ������ ���� �θ� ����� ���� �������� ���
	else if (node->color == RED && p->color == RED)
	{
		// case 3-1 : ���� ��尡 �������� ���
		if (u->color == BLACK)
		{
			// case 3-1-1 : ���� ���� �θ� ����� ������ �ݴ��� ���
			if (node == p->left && p == g->right)
			{
				rotateRight(RBT, node);
				node = p;
			}
			else if (node == p->right && p == g->left)
			{
				rotateLeft(RBT, node);
				node = p;
			} 

			p = node->parent;
			u = uncle(node);
			g = grandparent(node);

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
void deleteNode(Tree *RBT, Node *node)
{
	Node *successor, *fixupNode;
	Node *left = node->left;
	Node *right = node->right;
	Node *p = node->parent;
	int nColor = node->color;

	// child 0, 1 : ���ʳ�� ���� ���
	if (left == RBT->NIL)
	{
		fixupNode = right;
		transPlant(RBT, node, right);
	}
	// child 1 : �����ʳ�� ���� ���
	else if (right == RBT->NIL)
	{
		fixupNode = left;
		transPlant(RBT, node, left);
	}
	// child 2 : �ڽĳ�� 2���� ��� -> successor�� �����ϴ� ������ ����
	else
	{
		successor = findSuccessor(RBT, right);
		nColor = successor->color;

		fixupNode = successor->right;

		// fixupNode�� successor�� �ڸ��� �̽�
		transPlant(RBT, successor, fixupNode);
		successor->right = node->right;
		successor->right->parent = successor;

		// successor�� node�� �ڸ��� �̽�
		transPlant(RBT, node, successor);
		successor->left = node->left;
		successor->left->parent = successor;

		successor->color = node->color;
	}

	// ���� ����� ���� BLACK�� ��� Violation �߻�
	if (nColor == BLACK)
	{
		treeDelFixUp(RBT, fixupNode);
	}

	// �޸� ���� �ع������
	free(node);

	return;
}

void treeDelFixUp(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *s = sibling(node);

	// case 1 : s->red (sibling ���� ȸ�� -> sibling�� BLACK�� ���·� FixUp)
	if (s->color == RED)
	{
		p->color = RED;
		s->color = BLACK;
		if (node == p->left)
		{
			rotateLeft(RBT, s);
		}
		else
		{
			rotateRight(RBT, s);
		}
		treeDelFixUp(RBT, node);
	}
	else
	{
		// case 2 : left->black, right->black
		if (s->left->color == BLACK && s->right->color == BLACK)
		{
			s->color = RED;
			if (p->color == RED)
			{
				p->color = BLACK;
			}
			else
			{
				treeDelFixUp(RBT,p);
			}
		}
		else
		{
			if (node == p->left)
			{
				// case 3 : left->red, right->black
				if (s->right->color == BLACK)
				{
					s->left->color = BLACK;
					s->color = RED;
					rotateRight(RBT, s->left);
					s = sibling(node);
				}

				// case 4 : left->black/red, right->red
				s->color = p->color;
				p->color = BLACK;
				s->right->color = BLACK;
				rotateLeft(RBT, s);
			}
			else
			{
				// case 3-2 : left->black, right->red
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					rotateLeft(RBT, s->right);
					s = sibling(node);
				}

				// case 4-2 : left->red, right->black/red
				s->color = p->color;
				p->color = BLACK;
				s->left->color = BLACK;
				rotateRight(RBT, s);
			}
		}
	}

	return;
}

// ���� ����� �θ��� �θ� ���
Node *grandparent(Node *node)
{
	if ((node != NULL) && (node->parent != NULL))
		return node->parent->parent;
	else
		return NULL;
}

// ���� ����� �θ��� ���� ���
Node *uncle(Node *node)
{
	Node *g = grandparent(node);

	if (g == NULL)
		return NULL;
	if (node->parent == g->left)
		return g->right;
	else
		return g->left;
}

// ���� ����� ���� ���
Node *sibling(Node *node)
{
	Node *p = node->parent;

	if (p == NULL)
	{
		return NULL;
	}

	if (node == p->left)
	{
		return p->right;
	}
	else
	{
		return p->left;
	}
}

// ���� �θ� ����� ��ġ�� �������� ����
void rotateLeft(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *g = grandparent(node);
	Node *temp = node->left;

	// �θ� ��Ʈ ����� ���
	if (g == NULL)
	{
		RBT->root = node;
	}
	else
	{
		if (p == g->left)
			g->left = node;
		else
			g->right = node;  
	}

	node->parent = g;
	node->left = p;
	p->parent = node;
	p->right = temp;
	temp->parent = p;
}


// ���� �θ� ����� ��ġ�� ���������� ����
void rotateRight(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *g = grandparent(node);
	Node *temp = node->right;

	// �θ� ��Ʈ ����� ���
	if (g == NULL)
	{
		RBT->root = node;
	}
	else
	{
		if (p == g->left)
			g->left = node;
		else
			g->right = node;
	}

	node->parent = g;
	node->right = p;
	p->parent = node;
	p->left = temp;
	temp->parent = p;
}

// Successor ã��
Node *findSuccessor(Tree *RBT, Node *node)
{
	while (node->left != RBT->NIL)
	{
		node = node->left;
	}

	return node;
}

void transPlant(Tree *RBT, Node *node, Node *Successor)
{
	if (node->parent == NULL) // ��Ʈ����� ���
	{
		RBT->root = Successor;
	}
	// ���� ���
	else if (node == node->parent->left)
	{
		node->parent->left = Successor;
	}
	// ���� ���
	else
	{
		node->parent->right = Successor;
	}
	
	Successor->parent = node->parent;
}

// Ʈ�� ���
void printTree(Tree *RBT, Node *node)
{
	if (node->left != RBT->NIL)
	{
		printTree(RBT, node->left);
	}
	printf("\t\t\t%d\t\t%s\t\t%s\t\t%s\n", node->data->id, node->data->name, node->data->phone, node->data->addr);
	if (node->right != RBT->NIL)
	{
		printTree(RBT, node->right);
	}
	return;
}

void fprintTree(FILE *fp, Tree *RBT, Node *node)
{
	if (node->left != RBT->NIL)
	{
		fprintTree(fp, RBT, node->left);
	}
	fprintf(fp, "%d\t%s\t%s\t%s\n", node->data->id, node->data->name, node->data->addr, node->data->phone);
	if (node->right != RBT->NIL)
	{
		fprintTree(fp, RBT, node->right);
	}
	return;
}

// Ʈ�� �˻�
Node *searchValue(Tree *RBT, Node *node, int id, char *name)
{
	// ���̵� �˻�
	if (id != 0)
	{
		while (node != RBT->NIL && node->data->id != id)
		{
			if (node->data->id > id)
				node = node->left;
			else
				node = node->right;
		}
	}
	// �̸� �˻�
	else if (name != '\0')
	{
		while (node != RBT->NIL && strcmp(node->data->name, name) != 0)
		{
			if (0<strcmp(node->data->name, name))
				node = node->left;
			else
				node = node->right;
		}
	}
	else
	{
		node = NULL;
	}

	if (node == RBT->NIL)
		node = NULL;

	return node;
}

// ������ Ű���� �˻�
Node *searchEqualValue(Tree *RBT, Node *node, char *name, Node *nodearr[])
{
	int i = 0;
	// �̸� �˻�
	if (name != '\0')
	{
		do{
			while (node != RBT->NIL && strcmp(node->data->name, name) != 0)
			{
				if (0 < strcmp(node->data->name, name))
					node = node->left;
				else
					node = node->right;
			}
			if (node != RBT->NIL)
			{
				nodearr[i] = node;
				i++;
				node = node->right;
			}
		} while (node != RBT->NIL);
	}
	else
	{
		nodearr[i] = NULL;
	}

	if (node == RBT->NIL)
		nodearr[i] = NULL;

	return nodearr[0];
}

// ������ ���̵� ã��
int findLastId(Tree *RBT)
{
	Node *curnode = RBT->root;

	if (curnode == RBT->NIL) return 0;

	while (curnode->right != RBT->NIL)
	{
		curnode = curnode->right;
	}

	return curnode->data->id;
}

// Ʈ�� ���
void blackHeight(Tree *RBT, Node *node, int height)
{

	if (node->color == BLACK) height++;
	if (node->left != RBT->NIL)
	{
		blackHeight(RBT, node->left, height);
	}
	if (node->right != RBT->NIL)
	{
		blackHeight(RBT, node->right, height);
	}
	if (node->left == RBT->NIL && node->right == RBT->NIL) printf("%s, %d\n", node->data->name, height);
	return;
}