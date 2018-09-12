// thire-experience-2017-10-tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
typedef struct tree
{
	char data;
	struct tree *lchild, *rchild;
}Bitree;

Bitree* createtree()
{
	char ch; 
	scanf("%c", &ch); //i++;
	Bitree *T=NULL;	
	if (ch == ' ') T = NULL;
	else
	{
		
		T = (Bitree*)malloc(sizeof(Bitree));
		T->data = ch;
		T->lchild=createtree();
		T->rchild=createtree();
	}
	return T;
}
void preorder(Bitree *p)
{	
	if (p != NULL)
	{
		printf("%c", p->data);
		preorder(p->lchild);
		preorder(p->rchild);
	}
	else
		printf(" ");	
}
void midorder(Bitree *p)
{
	if (p != NULL)
	{
		preorder(p->lchild);
		printf("%c", p->data);
		preorder(p->rchild);
	}
	else
		printf(" ");
}
void backorder(Bitree *p)
{
	if (p != NULL)
	{
		preorder(p->lchild);
		preorder(p->rchild);
		printf("%c", p->data);
	}
	else
		printf(" ");
}
int main()
{
	Bitree *s;	
	s = createtree();
	
	preorder(s); printf("\n");
	midorder(s); printf("\n");
	backorder(s);
    return 0;
}

