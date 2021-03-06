// Example03.cpp: 定义控制台应用程序的入口点。
//一元多项式的乘法与加法运算

#include "stdafx.h"
#include "stdlib.h"

typedef struct PolyNode *PolyNomial;
struct PolyNode
{
	int coef;
	int expon;
	PolyNomial link;
};


PolyNomial ReadPoly();
void Attach(int c, int e, PolyNomial *pRear);
void PrintPoly(PolyNomial P);
PolyNomial Add(PolyNomial P1, PolyNomial P2);
PolyNomial Mult(PolyNomial P1, PolyNomial P2);

int main()
{
	PolyNomial P1, P2, PS, PP;

	P1 = ReadPoly();
	P2 = ReadPoly();
	PS = Add(P1, P2);
	PrintPoly(PS);
	PP = Mult(P1, P2);
	PrintPoly(PP);

    return 0;
}



PolyNomial ReadPoly()
{
	int c, e, n;
	scanf("%d\n", &n);

	PolyNomial P, Rear, t;
	P = (PolyNomial)malloc(sizeof(struct PolyNode));		//链表头空结点
	P->link = NULL;
	Rear = P;

	while (n--)
	{
		scanf("%d %d\n", &c, &e);
		Attach(c, e, &Rear);		//当前项插入多项式尾部
	}

	t = P;
	P = P->link;
	free(t);		//删除临时生成的头结点

	return P;
}



void Attach(int c, int e, PolyNomial *pRear)
{
	PolyNomial P;
	P = (PolyNomial)malloc(sizeof(struct PolyNode));

	//对新节点赋值
	P->coef = c;
	P->expon = e;

	P->link = NULL;
	(*pRear)->link = P;
	*pRear = P;
}




//输出多项式
void PrintPoly(PolyNomial P)
{
	int flag = 0;

	if (!P)
	{
		printf("0 0");
		return;
	}

	while (P)
	{
		if (!flag)
		{
			flag = 1;
		}
		else
		{
			printf(" ");
		}

		printf("%d %d", P->coef, P->expon);
		P = P->link;
	}

	printf("\n");

}



//多项式加法
PolyNomial Add(PolyNomial P1, PolyNomial P2)
{
	PolyNomial P, Rear, t;
	int sum;
	P = (PolyNomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;

	while (P1 && P2)
	{
		if (P1->expon > P2->expon)
		{
			Attach(P1->coef, P1->expon, &Rear);
			P1 = P1->link;
		}
		else if (P1->expon < P2->expon)
		{
			Attach(P2->coef, P2->expon, &Rear);
			P2 = P2->link;
		}
		else
		{
			sum = P1->coef + P2->coef;
			if (sum)
			{
				Attach(sum, P1->expon, &Rear);
			}
			P1 = P1->link;
			P2 = P2->link;
		}
	}

	while (P1)
	{
		Attach(P1->coef, P1->expon, &Rear);
		P1 = P1->link;
	}

	while (P2)
	{
		Attach(P2->coef, P2->expon, &Rear);
		P2 = P2->link;
	}


	t = P;
	P = P->link;
	free(t);

	return P;
}




//多项式乘法
PolyNomial Mult(PolyNomial P1, PolyNomial P2)
{
	PolyNomial P, Rear, t, t1, t2;
	int c, e;

	if (!P1 || !P2)
	{
		return NULL;
	}

	t1 = P1, t2 = P2;
	P = (PolyNomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;

	while (t2)
	{
		//先用P1的第一项乘以P2，得到初始的P
		Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
		t2 = t2->link;
	}

	t1 = t1->link;

	while (t1)
	{
		t2 = P2;
		Rear = P;

		while (t2)		//P1的当前项乘以P2
		{
			c = t1->coef * t2->coef;
			e = t1->expon + t2->expon;

			while (Rear->link && Rear->link->expon > e)
			{
				Rear = Rear->link;
			}

			if (Rear->link && Rear->link->expon == e)		//指数相等
			{
				if (Rear->link->coef + c)
				{
					//系数相加不为零
					Rear->link->coef += c;
				}
				else
				{
					//系数相加为零，删除节点
					t = Rear->link;
					Rear->link = t->link;
					free(t);
				}
			}
			else
			{
				t = (PolyNomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;
			}
		}
		t1 = t1->link;
	}

	t = P;
	P = P->link;
	free(t);

	return P;
}

