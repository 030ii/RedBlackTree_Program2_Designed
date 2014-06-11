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
<<<<<<< HEAD
	Node *newNIL;

	// ���ο� Ʈ���� �� �ȿ� �� �� ��带 �����
	newTree = malloc(sizeof(Tree));
	newNIL = malloc(sizeof(Node));
=======
	Member *newNIL;

	// ���ο� Ʈ���� �� �ȿ� �� �� ��带 �����
	newTree = malloc(sizeof(Tree));
	newNIL = malloc(sizeof(Member));
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	// �� ����� �Ӽ��� �����ϰ�, Ʈ���� �� ��� ������ �Ҵ��Ѵ�
	newNIL->color = BLACK;
	newTree->NIL = newNIL;
	newTree->root = newTree->NIL;

	return newTree;
}

/* ��� ���� */
<<<<<<< HEAD
Node *createMember(Tree *RBT, Member *data)
{
	Node *newMember = malloc(sizeof(Node));
=======
Member *createMember(Tree *RBT)
{
	Member *newMember = malloc(sizeof(Member));
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	newMember->color = RED;
	newMember->left = RBT->NIL;
	newMember->right = RBT->NIL;
<<<<<<< HEAD
	newMember->data = data;
=======
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	return newMember;
}

<<<<<<< HEAD
/* ���ο� ��� ���� flag - 0:id����, 1:name���� */
void insertNode(Tree *RBT, Node *node, int flag)
{
	Node *curNode, *tempNode;

	// ���� ��尡 ��Ʈ����� ���
	if (RBT->root == RBT->NIL){
		RBT->root = node;
		node->parent = NULL;
		node->color = BLACK;
=======
/* ���ο� ��� ���� */
void insertNode(Tree *RBT, Member *Node)
{
	Member *curNode, *tempNode;

	// ���� ��尡 ��Ʈ����� ���
	if (RBT->root == RBT->NIL){
		RBT->root = Node;
		Node->parent = NULL;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
		return;
	}

	// ���� ��尡 �� ��ġ�� ã�� NIL���� ��ü
	curNode = RBT->root;
	tempNode = curNode;
<<<<<<< HEAD

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
=======
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

>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	return;
}

/* �����Ʈ�� ���� ���� */
<<<<<<< HEAD
void treeFixUp(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *u = uncle(node);
	Node *g = grandparent(node);

	// case1 : ������ ��尡 ��Ʈ ����� ���
	if (node == RBT->root)
	{
		node->color = BLACK;
=======

void treeFixUp(Tree *RBT, Member *Node)
{
	Member *p = Node->parent;
	Member *u = uncle(Node);
	Member *g = grandparent(Node);

	// case1 : ������ ��尡 ��Ʈ ����� ���
	if (Node == RBT->root)
	{
		Node->color = BLACK;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
		return;
	}
	// case2 : ������ ����� �θ� �������� ���
	else if (p->color == BLACK)
	{
		return;
	}
	// case3 : ������ ���� �θ� ����� ���� �������� ���
<<<<<<< HEAD
	else if (node->color == RED && p->color == RED)
=======
	else if (Node->color == RED && p->color == RED)
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	{
		// case 3-1 : ���� ��尡 �������� ���
		if (u->color == BLACK)
		{
			// case 3-1-1 : ���� ���� �θ� ����� ������ �ݴ��� ���
<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

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
<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	}

	// ���� ����� ���� BLACK�� ��� Violation �߻�
	if (nColor == BLACK)
	{
		treeDelFixUp(RBT, fixupNode);
	}

	// �޸� ���� �ع������
<<<<<<< HEAD
	free(node);
=======
	free(Node);
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	return;
}

<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
				if (s->right->color == BLACK)
				{
					s->left->color = BLACK;
					s->color = RED;
<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	return;
}

// ���� ����� �θ��� �θ� ���
<<<<<<< HEAD
Node *grandparent(Node *node)
{
	if ((node != NULL) && (node->parent != NULL))
		return node->parent->parent;
=======
Member *grandparent(Member *Node)
{
	if ((Node != NULL) && (Node->parent != NULL))
		return Node->parent->parent;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	else
		return NULL;
}

// ���� ����� �θ��� ���� ���
<<<<<<< HEAD
Node *uncle(Node *node)
{
	Node *g = grandparent(node);

	if (g == NULL)
		return NULL;
	if (node->parent == g->left)
=======
Member *uncle(Member *Node)
{
	Member *g = grandparent(Node);

	if (g == NULL)
		return NULL;
	if (Node->parent == Node->left)
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
		return g->right;
	else
		return g->left;
}

// ���� ����� ���� ���
<<<<<<< HEAD
Node *sibling(Node *node)
{
	Node *p = node->parent;
=======
Member *sibling(Member *Node)
{
	Member *p = Node->parent;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	if (p == NULL)
	{
		return NULL;
	}

<<<<<<< HEAD
	if (node == p->left)
=======
	if (Node == p->left)
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	{
		return p->right;
	}
	else
	{
		return p->left;
	}
}

// ���� �θ� ����� ��ġ�� �������� ����
<<<<<<< HEAD
void rotateLeft(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *g = grandparent(node);
	Node *temp = node->left;
=======
void rotateLeft(Tree *RBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->left;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	// �θ� ��Ʈ ����� ���
	if (g == NULL)
	{
<<<<<<< HEAD
		RBT->root = node;
=======
		RBT->root = Node;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	}
	else
	{
		if (p == g->left)
<<<<<<< HEAD
			g->left = node;
		else
			g->right = node;  
	}

	node->parent = g;
	node->left = p;
	p->parent = node;
	p->right = temp;
	temp->parent = p;
=======
			g->left = Node;
		else
			g->right = Node;
	}

	Node->parent = g;
	Node->left = p;
	p->parent = Node;
	p->right = temp;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
}


// ���� �θ� ����� ��ġ�� ���������� ����
<<<<<<< HEAD
void rotateRight(Tree *RBT, Node *node)
{
	Node *p = node->parent;
	Node *g = grandparent(node);
	Node *temp = node->right;
=======
void rotateRight(Tree *RBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->right;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f

	// �θ� ��Ʈ ����� ���
	if (g == NULL)
	{
<<<<<<< HEAD
		RBT->root = node;
=======
		RBT->root = Node;
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	}
	else
	{
		if (p == g->left)
<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	}
	return;
}

<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
	}
	return;
}

<<<<<<< HEAD
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
=======
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
>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
}