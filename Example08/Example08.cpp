// Example08.cpp: 定义控制台应用程序的入口点。
//堆中的路径

#include "stdafx.h"
#define MAXN 1001
#define MINH -10001

int H[MAXN], size;

void Create();
void Insert(int X);


int main()
{
	int n, m, x, i, j;

	scanf("%d%d", &n, &m);

	Create();

	for (i = 0; i < n; i++)
	{
		scanf("%d", &x);
		Insert(x);
	}

	for (i = 0; i < m; i++)
	{
		scanf("%d", &j);
		printf("%d", H[j]);
		while (j > 1)		//沿根的方向输出各个结点
		{
			j /= 2;
			printf(" %d", H[j]);
		}
		printf("\n");
	}

    return 0;
}


void Create() 
{
	size = 0;
	H[0] = MINH;	//设置岗哨
}

void Insert(int X)
{
	int i;

	if (size >= 1000)	//堆已满
	{
		return;
	}

	for ( i = ++size; H[i / 2] > X; i /= 2)		//把X放在最后与它的父结点比较
	{
		H[i] = H[i / 2];
	}
	H[i] = X;
}
