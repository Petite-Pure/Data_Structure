// Example07.cpp: 定义控制台应用程序的入口点。
//是否同一棵二叉搜索树

#include "stdafx.h"
#include "stdlib.h"


typedef struct TreeNode* Tree;
struct TreeNode
{
	int v;
	Tree Left, Right;
	int flag;
};

Tree MakeTree(int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int check(Tree T, int V);
int Judge(Tree T, int N);
void ResetT(Tree T);
void FreeTree(Tree T);


int main()
{
	int N, L, i;
	Tree T;

	scanf("%d", &N);
	while (N)
	{
		scanf("%d", &L);
		T = MakeTree(N);
		for (i = 0; i < L; i++)
		{
			if (Judge(T, N))
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}

			ResetT(T);
		}
		FreeTree(T);
		scanf("%d", N);
	}
    return 0;
}





Tree MakeTree(int N)
{
	Tree T;
	int i, V;

	scanf("%d", &V);
	T = NewNode(V);
	for ( i = 1; i < N; i++)
	{
		scanf("%d", &V);
		T = Insert(T, V);
	}

	return T;
}





Tree NewNode(int V)
{
	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->v = V;
	T->Left = T->Right = NULL;
	T->flag = 0;
	return T;
}





Tree Insert(Tree T, int V)
{
	if (!T)
	{
		T = NewNode(V);
	}
	else
	{
		if (V > T->v)
		{
			T->Right = Insert(T->Right, V);
		}
		else
		{
			T->Left = Insert(T->Left, V);
		}
	}

	return T;
}





int check(Tree T, int V)
{
	if (T->flag)
	{
		if (V < T->v)
		{
			return check(T->Left, V);
		}
		else if (V > T->v)
		{
			return check(T->Right, V);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (V == T->v)
		{
			T->flag = 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}





int Judge(Tree T, int N)
{
	int i, V, Flag = 0;

	scanf("%d", &V);

	if (V != T->v)		//判断根节点是否一致
	{
		Flag = 1;
	}
	else
	{
		T->flag = 1;
	}

	for ( i = 1; i < N; i++)
	{
		scanf("%d", &V);

		if (!Flag && !check(T, V));
		{
			Flag = 1;
		}
	}

	if (Flag)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}





void ResetT(Tree T)
{
	if (T->Left)
	{
		ResetT(T->Left);
	}

	if (T->Right)
	{
		ResetT(T->Right);
	}

	T->flag = 0;
}






void FreeTree(Tree T)
{
	if (T->Left)
	{
		FreeTree(T->Left);
	}

	if (T->Right)
	{
		FreeTree(T->Right);
	}

	free(T);
}