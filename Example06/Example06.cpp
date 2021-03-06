// Example06.cpp: 定义控制台应用程序的入口点。
//树的同构
//给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。


#include "stdafx.h"
#define MaxTree 10
#define Null -1
#define ElementType char
#define Tree int

//typedef char ElementType;
//typedef int Tree;

struct TreeNode
{
	ElementType Element;
	Tree Left;
	Tree Right;
}T1[MaxTree], T2[MaxTree];


Tree BuildTree(struct TreeNode T[]);
int Isomorphic(Tree R1, Tree R2);


int main()
{
	Tree R1, R2;

	R1 = BuildTree(T1);
	R2 = BuildTree(T2);
	if (Isomorphic(R1, R2))
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
    return 0;
}




//建二叉树
Tree BuildTree(struct TreeNode T[])
{
	int i, N = 0, check[MaxTree], Root = Null;
	char cl, cr;

	scanf("%d\n", &N);

	if (N)
	{
		for (i = 0; i < N; i++)
		{
			check[i] = 0;
		}

		for (i = 0; i < N; i++)
		{
			scanf("%c %c %c\n", &T[i].Element, &cl, &cr);
			if (cl != '-')
			{
				T[i].Left = cl - '0';
				check[T[i].Left] = 1;
			}
			else
			{
				T[i].Left = Null;
			}

			if (cr != '-')
			{
				T[i].Right = cr - '0';
				check[T[i].Right] = 1;
			}
			else
			{
				T[i].Right = Null;
			}
		}

		for (i = 0; i < N; i++)
		{
			if (!check[i])
			{
				break;
			}
		}

		Root = i;
	}

	return Root;
}




int Isomorphic(Tree R1, Tree R2)
{
	if (R1 == Null && R2 == Null)		//若两棵树皆为空树，则两棵树同构
	{
		return 1;
	}

	if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null))		//一棵为空树，另一棵不空，则不同构
	{
		return 0;
	}

	if (T1[R1].Element != T2[R2].Element)		//根不相等，则不同构
	{
		return 0;
	}

	if (T1[R1].Left == Null && T2[R2].Left == Null)		//左子树皆为空
	{
		return Isomorphic(T1[R1].Right, T2[R2].Right);
	}

	if (T1[R1].Left != Null && T2[R2].Left != Null &&
		T1[T1[R1].Left].Element == T2[T2[R2].Left].Element)		//不需要交换
	{
		return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
	}
	else
	{
		return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
	}
}