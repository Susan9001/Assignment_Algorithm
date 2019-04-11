#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

int* Process(int* arr, int n, int k); //ѡ��k������λ����ӽ�������
int select(int* (&arr), int start, int end, int k); //���ص�kС����
void swap(int &a, int&b);
int partition(int* (&arr), int start, int end, int x); //x��start��end����
int compareInt(const void* a, const void* b);

int main()
{
	int n = 14;
	int k = 3;

	cout << "������һ�����ٸ����֣�";
	cin >> n;
	int *arr = (int*)malloc(sizeof(n) * n);
	cout << "���������룺";
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int k = 1; k < n; k++)
	{
		int* result = Process(arr, n, k);
		printf("��%d�ٽ��ģ�\n", k);
		for (int i = 0; i < k; i++)
			cout << result[i] << "\t";
		cout << endl;
	}

	system("pause");
	return 0;
}

int* Process(int* arr, int n, int k)
{
	int* diff = (int*)malloc(sizeof(int) * n); //�������飬��Ÿ�������λ���Ĵ�С���
	int* result = (int*)malloc(sizeof(int) * k);
	int midNum = select(arr, 0, n - 1, (n + 1) / 2); //��ʾ��λ��

	for (int i = 0; i < n; i++)
		diff[i] = abs(arr[i] - midNum);
	int kSmall = select(diff, 0, n - 1, k);//����λ����KС�ľ���

	//�����ҳ�����λ������<=kSmall����Щ��
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
	int n = end - start + 1; //��ʾһ�����ٸ�Ԫ��
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
	

	int midpos = ((n - 1) / 5) / 2; //��λ�����±�
	int x = select(arr, start, start + (n -1) / 5 , (midpos+1)); //Ҫ����λ���±�ǵ�+1������
	int mid = partition(arr, start, end, x); //�˴����桤��λ����λ��
	if (k <= mid) return select(arr, start, mid, k);
	else return select(arr, mid + 1, end,k - (mid - start + 1));
}

int partition(int*  (&arr), int start, int end, int x)
{
	int i = start, j = end; //iΪͷָ�룬jΪβ
	int target = 0; //���ڷ�x���±�

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

