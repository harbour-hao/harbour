// experience-4-picture-17-11.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
struct vertex//�������Ϣ
{
	int num;//������
	char data;//����������������
};
struct graph//���󼯺�
{
	int n;//������
	int e;//����
	struct vertex VEX[20];//���㼯��
	int edges[20][20] = { 0 };//����
};
struct verlist//һ������ͺ���һ��
{
	int num;//�ڽӵ����
	char info;//�ڽӵ�����
	struct verlist *next;
};
struct Vexlist//���������Ϣ
{
	char data;
	struct verlist *firstvex;
};
struct tree
{
	char data;
	struct tree *lchild, *rchild,*back;
}*HEAD;
struct graph creategraph()
{
	int i, j, k,l; char b, t;
	struct graph sample;
	printf("�����붥�����ͱ���\n");
	scanf("%d%d", &sample.n, &sample.e);	
	for (i = 0; i < sample.n; i++)
	{
		getchar();
		sample.VEX[i].num= i;
		printf("��������Ϊ%d�Ķ�������\n",i);
		scanf("%c", &sample.VEX[i].data);		
	}
	//sample.edges[20][20] = { 0 };
	for (j = 0; j < sample.e; j++)
	{
		printf("������ߵĵ�һ�����ӵ�\n");getchar();
		scanf("%c", &b); 
		printf("������ߵĵڶ������ӵ�\n"); getchar();
		scanf("%c", &t);				
		k = 0; l = 0;
		while (k<sample.n&&b!=sample.VEX[k].data)//�ҵ�������ţ���������ŷ�Χֹͣ���Ҳ�����Ӧ���㣩���ҵ�����ֹͣ
		{
			k++;
		}
		if (k >= sample.n)
		{
			printf("����ߵĵ�һ���������");
			exit(1);
		}
		while (l < sample.n&&sample.VEX[l].data != t)
		{
			l++;
		}
		if (l >= sample.n)
		{
			printf("����ߵĵڶ����������");
			exit(2);
		}
		sample.edges[l][k]=sample.edges[k][l] = 1;
	}
	return sample;
};
void showgraph(struct graph sample)
{
	int i, j;
	for(i=0;i<sample.n;i++)
	{
		printf("\n");
		for (j = 0; j < sample.n; j++)
		{
				printf("%3d",sample.edges[i][j]);
		}
	}
}
struct Vexlist *transform(struct graph b)//�ڽӾ���ת��
{
	struct Vexlist *L;
	L = (struct Vexlist*)malloc(sizeof(struct Vexlist)*b.n);	
	int i, j;
	for (int k = 0; k < b.n; k++)
	{
		L[k].data = b.VEX[k].data;
		L[k].firstvex = NULL;
	}
	struct verlist *q,*r;
	for (j = 0; j < b.n; j++)
	{
		
		for (i = 0; i < b.n; i++)
		{
			//r=L[j].firstvex;�������У���ΪL[j].firstvex = q����ʱL[j].firstvex �Ѹı䣬����rû�б䶯����ָ��һ���ɵ�L[j].firstvex 
			if (b.edges[i][j] != 0)
			{					
				q = (struct verlist *)malloc(sizeof(struct verlist));
				q->num = i;
				q->info = b.VEX[i].data;
				q->next = NULL;//�������
				if (L[j].firstvex == NULL)
				{
					L[j].firstvex = q;
					r = q;
				}
				else
				{
					r->next = q;	
					r = r->next;			    
				}
			}
		}
		r->next = NULL;
	}
	return L;
}
void showlist(struct Vexlist *b,int n)//�ڽӱ����
{	
	struct verlist *q=b[n].firstvex;
	printf("%c:", b[n].data);
	while (q != NULL)
	{
		printf("%c", q->info);
		q = q->next;
	}
}
int visited[20] = {0};
void createtree(struct tree *&p, char a)//�������Ľ��
{
	static struct tree *q = NULL; static struct tree  *head; static int i = 0, k = 0; static char str[20]; if (i == 0)str[i] = a; int n = 0;
	for (int j = 0; j <= i; j++)//�����жϴ�����ַ����ֵ������Ƿ��ظ����ֹ������ֹ�����str����
	{
		if (str[j] == a)//������ֹ�n=1,n�����жϳ��ֵ������Ƿ��ظ����ֹ�
		{
			n = 1;
			if (i == 0)n = 0;
		}
	}	
	if (n == 0)//������
	{
		i++; str[i] = a; q = (struct tree *)malloc(sizeof(struct tree)); q->data = a; q->lchild = NULL; q->rchild = NULL;//���û���ֹ����ٴ����ڴ�
	}
	if (p == NULL)//����׸������δ����
	{		
		p = q; head = p;  p->back = NULL; HEAD = p;
	}
	else//�Ѿ�������ԭ��
	{
		if (n == 0)
		{
			if (k == 0)//k�ж��Ƿ��ǵ�һ�γ������󣬻��ǵڶ��γ�������
			{
				//printf("p=%c,left=%c\n",p->data, q->data);
				p->lchild = q; p->rchild = NULL; p->lchild->back = p; 			
				p = p->lchild; 
			}
			else
			{ 
				//ndsandapjfbsf;nna
				//printf("p=%c,right=%c\n",p->data, q->data);
				p.rchild = q; p->rchild->back = p;
				p = p->rchild;
				k = 0;
			}
		}
		else
		{
			while (a != p->data)//�����Ҫ���ض�Σ�pָ����Զָ��������ӵĸ����
			{
				p = p->back;
			}
			k = 1;
		}
	}	
}
void DFS(struct Vexlist *q,int v0,int sum)//DFS�㷨���ݹ�
{
	static int i; i++;
	struct verlist *p; char c;static struct tree *ptree=NULL;
	visited[v0] = 1;
	p = q[v0].firstvex;
	createtree(ptree, q[v0].data);
	while (p != NULL)
	{		
		if (visited[p->num] == 0)
			DFS(q, p->num,sum); c = p->info;
		p = p->next;
	}
	createtree(ptree, q[v0].data);//�ظ����ֵ�������������Ҫ�ӽ��ĸ���㴦
}
void Disptree(struct tree *T)//Ƕ�뷨
{
	if (T)
	{
		printf("%c", T->data);
		if (T->lchild|| T->rchild)
		{
			printf("(");
			Disptree(T->lchild);
			if (T->rchild)
				printf(",");
			Disptree(T->rchild);
			printf(")");
		}
	}
}
void showit(struct tree*T,int i)//���뷨
{
	if (T)
	{
		for (int j = i; j>0; j--)
			printf(" ");
		printf("%c", T->data);
		for(int k=15-i;k>0;k--)
		printf("-");
		printf("\n");
		showit(T->lchild,i+1);
		showit(T->rchild,i+1);
	}
}
int main()
{
	struct  graph thing1; int j = 0;
	thing1 = creategraph();
	showgraph(thing1);
	struct Vexlist* thing2;
	thing2 = transform(thing1); int i;
	printf("\n");
	for (i = 0; i < thing1.n; i++)
	{	
		showlist(thing2, i);
		printf("\n");
	}
	DFS(thing2,0,thing1.n);
	while (j != thing1.n)//������Щû������һ��ĵ�
	{
		while (visited[j] != 0)
	    {
		   j++;				
	     }
	    if (j != thing1.n)
		DFS(thing2, j, thing1.n);
	}
	showit(HEAD,0);
    return 0;
}

