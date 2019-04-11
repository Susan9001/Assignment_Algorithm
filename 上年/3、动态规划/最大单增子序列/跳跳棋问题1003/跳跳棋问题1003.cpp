#include <stdio.h>
#include <stdlib.h>

long jump(long *arr, int n);

int main()
{
	int n = 1;
	long *arr;

	while (n > 0)
	{
		printf("���г��ȣ�0�˳�����");
		scanf_s("%d", &n);
		arr = (long*)malloc(sizeof(long) * n);
		printf("���У�");
		for (int i = 0; i < n; i++)
			scanf_s("%ld", &arr[i]);
		printf("����������г��ȣ�%ld\n", jump(arr, n));
	}

	system("pause");
	return 0;
}

long jump(long *arr, int n)
{
	long *f = (long*)malloc(sizeof(long) * n);
	for (int i = 0; i < n; i++)
	{
		f[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (arr[j] < arr[i] && f[i] < 1 + f[j])
			{
				f[i] = 1 + f[j];
			}
		}
	}

	long max = f[0];
	for (int i = 1; i < n; i++)
	{
		if (max < f[i]) max = f[i];
	}
	return max;
}