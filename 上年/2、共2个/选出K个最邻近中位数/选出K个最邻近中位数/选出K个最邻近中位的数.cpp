#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

int* Process(int* arr, int n, int k); //选出k个跟中位数最接近的数字
int select(int* (&arr), int start, int end, int k); //返回第k小的数
void swap(int &a, int&b);
int partition(int* (&arr), int start, int end, int x); //x在start到end里面
int compareInt(const void* a, const void* b);

int main()
{
	int n = 14;
	int k = 3;

	cout << "请输入一共多少个数字：";
	cin >> n;
	int *arr = (int*)malloc(sizeof(n) * n);
	cout << "请依次输入：";
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int k = 1; k < n; k++)
	{
		int* result = Process(arr, n, k);
		printf("第%d临近的：\n", k);
		for (int i = 0; i < k; i++)
			cout << result[i] << "\t";
		cout << endl;
	}

	system("pause");
	return 0;
}

int* Process(int* arr, int n, int k)
{
	int* diff = (int*)malloc(sizeof(int) * n); //辅助数组，存放各数跟中位数的大小差距
	int* result = (int*)malloc(sizeof(int) * k);
	int midNum = select(arr, 0, n - 1, (n + 1) / 2); //表示中位数

	for (int i = 0; i < n; i++)
		diff[i] = abs(arr[i] - midNum);
	int kSmall = select(diff, 0, n - 1, k);//跟中位数第K小的距离

	//以下找出跟中位数距离<=kSmall的那些数
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (abs(arr[i] - midNum) <= kSmall)
		{
			result[j] = arr[i];
			j++;
		}
	}
	
	return result;
}

int select(int* (&arr), int start, int end, int k)
{
	int n = end - start + 1; //表示一共多少个元素
	int i;

	if (n < 10)
	{
		sort(arr + start, arr + end + 1);
		return arr[start + k - 1];
	}

	for (i = 0; i < n / 5; i++)
	{
		sort(arr + start + 5 * i, arr + start + 5 * i + 4 + 1);
		swap(arr[start + i], arr[start + 5 * i + 2]);
	}
	

	int midpos = ((n - 1) / 5) / 2; //中位数的下标
	int x = select(arr, start, start + (n -1) / 5 , (midpos+1)); //要求中位。下标记得+1！！！
	int mid = partition(arr, start, end, x); //此处是真·中位数的位置
	if (k <= mid) return select(arr, start, mid, k);
	else return select(arr, mid + 1, end,k - (mid - start + 1));
}

int partition(int*  (&arr), int start, int end, int x)
{
	int i = start, j = end; //i为头指针，j为尾
	int target = 0; //用于放x的下标

	while (i < j)
	{
		for (; i <= end && arr[i] < x; i++);
		for (; j >= 0 && arr[j] > x; j--);
		if (i >= j) break;
		if (arr[i] == x)
		{
			target = i;
			i++;
			continue;
		}
		else if (arr[j] == x)
		{
			target = j;
			j--;
			continue;
		}
		swap(arr[i], arr[j]);
	}
	if (target > i)
	{
		swap(arr[target], arr[i]);
		return i;
	}
	else if (target < j)
	{
		swap(arr[target], arr[j]);
		return j;
	}
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int compareInt(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

