// experience-4-picture-17-11.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
struct vertex//顶点的信息
{
	int num;//顶点编号
	char data;//顶点的所代表的数据
};
struct graph//矩阵集合
{
	int n;//顶点数
	int e;//边数
	struct vertex VEX[20];//顶点集合
	int edges[20][20] = { 0 };//矩阵
};
struct verlist//一个顶点和后面一大串
{
	int num;//邻接点序号
	char info;//邻接点数据
	struct verlist *next;
};
struct Vexlist//多个顶点信息
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
	printf("请输入顶点数和边数\n");
	scanf("%d%d", &sample.n, &sample.e);	
	for (i = 0; i < sample.n; i++)
	{
		getchar();
		sample.VEX[i].num= i;
		printf("请输入编号为%d的顶点数据\n",i);
		scanf("%c", &sample.VEX[i].data);		
	}
	//sample.edges[20][20] = { 0 };
	for (j = 0; j < sample.e; j++)
	{
		printf("请输入边的第一个连接点\n");getchar();
		scanf("%c", &b); 
		printf("请输入边的第二个连接点\n"); getchar();
		scanf("%c", &t);				
		k = 0; l = 0;
		while (k<sample.n&&b!=sample.VEX[k].data)//找到顶点序号，当超过序号范围停止（找不到相应顶点），找到顶点停止
		{
			k++;
		}
		if (k >= sample.n)
		{
			printf("输入边的第一个顶点错误");
			exit(1);
		}
		while (l < sample.n&&sample.VEX[l].data != t)
		{
			l++;
		}
		if (l >= sample.n)
		{
			printf("输入边的第二个顶点错误");
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
struct Vexlist *transform(struct graph b)//邻接矩阵转化
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
			//r=L[j].firstvex;这样不行，因为L[j].firstvex = q，此时L[j].firstvex 已改变，但是r没有变动，它指向一个旧的L[j].firstvex 
			if (b.edges[i][j] != 0)
			{					
				q = (struct verlist *)malloc(sizeof(struct verlist));
				q->num = i;
				q->info = b.VEX[i].data;
				q->next = NULL;//创建结点
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
void showlist(struct Vexlist *b,int n)//邻接表输出
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
void createtree(struct tree *&p, char a)//创建树的结点
{
	static struct tree *q = NULL; static struct tree  *head; static int i = 0, k = 0; static char str[20]; if (i == 0)str[i] = a; int n = 0;
	for (int j = 0; j <= i; j++)//首先判断传入的字符出现的数据是否重复出现过，出现过则入str数组
	{
		if (str[j] == a)//如果出现过n=1,n用来判断出现的数据是否重复出现过
		{
			n = 1;
			if (i == 0)n = 0;
		}
	}	
	if (n == 0)//入数组
	{
		i++; str[i] = a; q = (struct tree *)malloc(sizeof(struct tree)); q->data = a; q->lchild = NULL; q->rchild = NULL;//如果没出现过则不再创造内存
	}
	if (p == NULL)//如果首个结点尚未创造
	{		
		p = q; head = p;  p->back = NULL; HEAD = p;
	}
	else//已经有树的原型
	{
		if (n == 0)
		{
			if (k == 0)//k判断是否是第一次出现入左，还是第二次出现入右
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
			while (a != p->data)//如果需要返回多次，p指针永远指向所需添加的根结点
			{
				p = p->back;
			}
			k = 1;
		}
	}	
}
void DFS(struct Vexlist *q,int v0,int sum)//DFS算法，递归
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
	createtree(ptree, q[v0].data);//重复出现的数，即返回需要加结点的根结点处
}
void Disptree(struct tree *T)//嵌入法
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
void showit(struct tree*T,int i)//凹入法
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
	while (j != thing1.n)//处理那些没有连在一起的点
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

