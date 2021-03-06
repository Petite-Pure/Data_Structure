// Example01.cpp: 定义控制台应用程序的入口点。
//最大子列和问题

#include "stdafx.h"
#include "time.h"

clock_t start, stop;
double duration;


int MaxSubSeqSum1(int A[], int N);
int MaxSubSeqSum2(int A[], int N);
int MaxSubSeqSum3(int A[], int N);
int MaxSubSeqSum4(int A[], int N);
int Max4(int A, int B, int C);
int DivideAndConquer(int List[], int left, int right);


int main()
{
	int N = 6;
	int A[] = {-2, 11, -4, 13, -5, -2};
	int Max;

	start = clock();
	Max = MaxSubSeqSum1(A, N);
	stop = clock();
	printf_s("算法一：%d\n", Max);
	duration = ((double)(stop - start)) / CLK_TCK;
	printf_s("ticks: %lf\n", (double)(stop - start));
	printf_s("耗时：%lf\n\n", duration);

	start = clock();
	Max = MaxSubSeqSum2(A, N);
	stop = clock();
	printf_s("算法二：%d\n", Max);
	duration = ((double)(stop - start)) / CLK_TCK;
	printf_s("ticks: %lf\n", (double)(stop - start));
	printf_s("耗时：%lf\n\n", duration);

	start = clock();
	Max = MaxSubSeqSum3(A, N);
	stop = clock();
	printf_s("算法三：%d\n", Max);
	duration = ((double)(stop - start)) / CLK_TCK;
	printf_s("ticks: %lf\n", (double)(stop - start));
	printf_s("耗时：%lf\n\n", duration);

	start = clock();
	Max = MaxSubSeqSum4(A, N);
	stop = clock();
	printf_s("算法四：%d\n", Max);
	duration = ((double)(stop - start)) / CLK_TCK;
	printf_s("ticks: %lf\n", (double)(stop - start));
	printf_s("耗时：%lf\n\n", duration);

    return 0;
}



//算法一：比较所有的连续子列和
int MaxSubSeqSum1(int A[], int N)
{
	int ThisSum, MaxSum = 0;
	int i, j, k;

	for (i = 0; i < N; i++)		//i是子列的左端
	{
		for (j = i; j < N; j++)		//j是子列的右端
		{
			ThisSum = 0;		//ThisSum归零

			for (k = i; k < j; k++)		//ThisSum是A[i]到A[j]的子列和
			{
				ThisSum += A[k];
			}

			if (ThisSum > MaxSum)		//如果新得到的子列和更大，则更新结果
			{
				MaxSum = ThisSum;
			}
		}
	}

	return MaxSum;
}




//算法二：优化算法一，通过改变记录方式，减少一个for循环
int MaxSubSeqSum2(int A[], int N)
{
	int ThisSum, MaxSum = 0;
	int i, j;

	for (i = 0; i < N; i++)		//i是子列的左端
	{

		ThisSum = 0;

		for (j = i; j < N; j++)		//j是子列的右端
		{
			ThisSum += A[j];		//对于相同i,的不同j,只要在j-1次循环的基础上累加1项即可

			if (ThisSum > MaxSum)		//如果新得到的子列和更大，则更新结果
			{
				MaxSum = ThisSum;
			}
		}
	}

	return MaxSum;
}




//算法三：在线处理
int MaxSubSeqSum3(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i;

	for (i = 0; i < N; i++)
	{

		ThisSum += A[i];		//向右累加

		if (ThisSum > MaxSum)
		{		
			//发现更大和则更新当前结果
			MaxSum = ThisSum;
		}
		else if (ThisSum < 0)
		{		
			//如果当前子列和为负数
			ThisSum = 0;		//则不可能使后面部分和增大，抛弃之
		}

	}

	return MaxSum;
}






//算法四：分而治之
int Max4(int A, int B, int C)
{
	//返回3个整数中的最大值
	return A > B ? A > C ? A : C : B > C ? B : C;
}

int DivideAndConquer(int List[], int left, int right)
{
	//分治法求List[left]到List[right]的最大子列和
	int MaxLeftSum, MaxRightSum;		//存放左右子问题的解
	int MaxLeftBorderSum, MaxRightBorderSum;		//存放跨分界线的结果

	int LeftBorderSum, RightBorderSum;
	int center;

	if (left == right)		//递归的终止条件，子列只有1个数字
	{
		if (List[left] > 0)
		{
			return List[left];
		} 
		else
		{
			return 0;
		}
	}

	center = (left + right) / 2;		//找到中分点

	//递归求得两边子列的最大和
	MaxLeftSum = DivideAndConquer(List, left, center);
	MaxRightSum = DivideAndConquer(List, center + 1, right);

	//求跨边界的最大子列和
	LeftBorderSum = 0, MaxLeftBorderSum = 0;
	for (int i = center; i >= left; i--)		//从中线开始向左扫描
	{
		LeftBorderSum += List[i];
		if (LeftBorderSum > MaxLeftBorderSum)
		{
			MaxLeftBorderSum = LeftBorderSum;
		}
	}

	RightBorderSum = 0, MaxRightBorderSum = 0;
	for (int i = center + 1; i <= right; i++)		//从中线开始向右扫描
	{
		RightBorderSum += List[i];
		if (RightBorderSum > MaxRightBorderSum)
		{
			MaxRightBorderSum = RightBorderSum;
		}
	}

	return Max4(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);

}

int MaxSubSeqSum4(int List[], int N)
{
	//保持与前2种算法相同的函数接口
	return DivideAndConquer(List, 0, N - 1);
}
