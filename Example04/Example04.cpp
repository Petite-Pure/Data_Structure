// Example04.cpp: 定义控制台应用程序的入口点。
//数组与指针的区别

#include "stdafx.h"

int GetSize(int data[]);

int main()
{
	int data1[] = { 1, 2, 3, 4, 5 };
	int size1 = sizeof(data1);		//求数组的大小，5个整数，每个整数占4个字节

	int* data2 = data1;		//data2声明为指针
	int size2 = sizeof(data2);		//32位机器上，指针占4个字节

	int size3 = GetSize(data1);		//当数组作为函数的参数进行传递时，数组就会自动退化为同类型的指针

	printf("%d %d %d\n", size1, size2, size3);
    return 0;
}


int GetSize(int data[])
{
	return sizeof(data);
}

