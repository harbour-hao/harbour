// 2017-12-experience-5-search.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
struct tree
{ 
	int data;
	struct tree *lchild, *rchild, *back;
};
bool search(struct tree *p,int a,struct tree *&now)//δ�ı�p��ֵ��p���Ǵ�ͷ��ʼ,now��ָ��仯��
{
	//static int i = 0; i++; printf("i=%d\n", i);
	if (p == NULL) 
	{
		return true;
	}		
	else
	{
		
		now = p; //printf("now=%d\n", now->data);
		if (a == p->data)
		{		
			return false;
		}			
		if (a < p->data)
            return(search(p->lchild, a,now));					
		else 
			return(search(p->rchild, a,now));
	}
}
struct tree * createtree(struct tree * &p,int a)
{
	struct tree *q = NULL; static struct tree *head = NULL;
	q = (struct tree *)malloc(sizeof(struct tree)); q->data = a; q->lchild = q->rchild = NULL;
	if (p == NULL)
	{
		p = q; head = p; p->back = NULL;
	}		
	else
	{
		if (a < p->data)
		{
			p->lchild = q; p->lchild->back = p;
		}
		else
		{
			p->rchild = q; p->rchild->back = p;
		}
	}
	return head;
}
void showtree(struct tree *p)
{
	if (p != NULL)
	{
		printf("%d ", p->data);
		showtree(p->lchild);
		showtree(p->rchild);
	}
}
void Delete(struct tree *&p)
{
	struct tree *q;
	if (!p->lchild && !p->rchild)
		p = NULL;
	else if (p->lchild && !p->rchild)
	{
		if (p->data < p->back->data)
			p->back->lchild = p->lchild;
		else
			p->back->rchild = p->lchild;
		free(p);
	}
	else if (!p->lchild && p->rchild)
	{
		if (p->data < p->back->data)
			p->back->lchild = p->rchild;
		else
			p->back->rchild = p->rchild;
		free(p);
	}
	else
	{
		q = p->lchild;
		while (q->rchild)
		{
			q = q->rchild;
		}
		p->data = q->data;
		q->back->rchild = q->lchild;
		free(q);
	}
}
int main()
{
	struct tree *s=NULL, *Head=NULL,*now=NULL; 
	int x,n;
	printf("����������\n");
	scanf("%d", &n);
	for (int i = 0; i <n;i++)
	{
		scanf("%d", &x);
		if (search(s,x,now) == true)//sδ�仯
		{		
			s = createtree(now, x); //printf("data=%d\n", now->data); showtree(s); printf("\n");
		}
	}
	showtree(s);
	printf("��������ɾ���Ľڵ�:"); scanf("%d", &x);
	if (search(s, x, now) == false)
	{
		Delete(now);
	}
	else
		printf("δ�ҵ��˵�");
	showtree(s);
    return 0;
}

