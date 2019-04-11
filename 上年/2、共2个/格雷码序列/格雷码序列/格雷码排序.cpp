#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

int** manageGray(int n);
void gray(int **(&gArr), int n);

int main()
{
	int n;
	cout << "请输入格雷码位数：";
	cin >> n;

	int grayNum = (int)pow((double)2, (double)n);
	int **gArr = manageGray(n);
	for (int i = 0; i < grayNum; i++)
	{
		for (int j = 0; j < n; j++)
			cout << gArr[i][j];
		cout << endl;
	}

	system("pause");
	return 0;
}

int ** manageGray(int n)
{
	int grayNum = (int)pow((double)2, (double)n);
	int **gArr = (int**)malloc(sizeof(int*) * grayNum);
	for (int i = 0; i < grayNum; i++)
		gArr[i] = (int*)malloc(sizeof(int) * n);

	gray(gArr, n);
	return gArr;
}

void gray(int **(&gArr), int n)
{
	if (n == 1)
	{
		gArr[0][0] = 0;
		gArr[1][0] = 1;
		return;
	}

	int grayNum = (int)pow((double)2, (double)(n));
	gray(gArr, n - 1);

	for (int i = 0; i < grayNum / 2; i++)
	{
		//首先把前面的往后挪一位，然后复制到后面去
		for (int j = n - 1; j >= 0; j--)
		{
			gArr[i][j + 1] = gArr[i][j];
			gArr[grayNum - 1 - i][j + 1] = gArr[i][j + 1];
		}
		gArr[i][0] = 0; //补0
		gArr[grayNum - 1 - i][0] = 1; //补1
	}

}

