// Example05.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void InsertSort(int A[], int N);
void Duplicate1(int A[], int N);


int main()
{
	int A[] = { 2, 3, 1, 0, 2, 5, 3 };
	int N = sizeof(A) / 4;
	InsertSort(A, N);
	Duplicate1(A, N);
    return 0;
}



void Duplicate1(int A[], int N)
{
	int temp = A[0];
	bool flag = true;
	for (int i = 1; i < N; i++)
	{
		if (A[i] == temp)
		{
			if (flag)
			{
				printf("%d ", A[i]);
			}
			flag = false;
		}
		else
		{
			temp = A[i];
			flag = true;
		}
	}
}



//插入排序
void InsertSort(int A[], int N)
{
	int temp;
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j > 0; j--)
		{
			if (A[j] < A[j-1])
			{
				temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
			}
			else
			{
				break;
			}
		}
	}
}