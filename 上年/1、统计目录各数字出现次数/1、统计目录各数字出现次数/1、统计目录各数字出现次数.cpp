#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

void countA(int n, int result[]); //������
void countB(int n, int result[]); 
void countC(int n, int result[10]); //�ݹ鷨
void cRecursion(int n, int result[10]);

int main()
{
	int resultA[10], resultB[10], resultC[10]; //�Ŷ�Ӧ�±��ͳ�ƽ��
	int n;

	ifstream file_in("input.txt");
	file_in >> n;
	file_in.close();

	countA(n, resultA);
	countB(n, resultB);
	countC(n, resultC);

	ofstream file_out("output.txt");
	for (int i = 0; i <= 9; i++)
		file_out << resultA[i] << "\t" << resultB[i] << "\t" << resultC[i] << endl;
	file_out.close();

	system("pause");
	return 0;
}

void countC(int n, int result[10])
{
	for (int i = 0; i <= 9; i++)
		result[i] = 0;

	/*˼·������ҳ��Ϊ43786�������λ��ʼ����ݹ飬һֱ�����λ��ʼ��һ����ۼ����6,86,786������43786ʱ0-9���ֵĴ���*/
	cRecursion(n, result);

	int m = log10((double)n) + 1; //n�ж���λ
	for (int i = 1; i <= m; i++) 
		result[0] -= (int)pow((double)10, (double)(i - 1)); //ȥ����λiǰ����0�����
}

void cRecursion(int n, int result[10])
{
	int m = log10((double)n) + 1; //n�ж���λ
	if (m == 1)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (j > n) result[j] = 0;
			else result[j] = 1;
		}
		return;
	}

	int lowZeros = (int)(pow((double)10, (double)(m - 1))); //��curr�͵��м�λ���м���0
	int low = n % lowZeros; //��ȥ���λ��������λ
	int curr = n / lowZeros; //���һλ
	int fn_1 = (m - 1) * (int)(pow((double)10, (double)(m - 2))); //f(n - 1)

	cRecursion(low, result); //�ȵݹ飬�����lowÿ�����ֵĸ���
	for (int j = 0; j <= 9; j++)
	{
		result[j] += (fn_1 * curr);  //���ڱ�low����1λ������Ҫ���ϴӵ�1��m-1λ������j�³��ֵĴ���
		if (j < curr) result[j] += lowZeros; //�����Ǽ����ٵ�mλ������j�³��ֵĴ���
		else if (j == curr) result[j] += (low + 1);
	}
}

void countA(int n, int result[])
{
	for (int i = 0; i <= 9; i++)
		result[i] = 0;
	
	for (int i = 1; i <= n; i++)
	{
		for (int temp = i; temp > 0; temp /= 10)
			result[temp % 10]++;
	}
}

void countB(int n, int result[])
{
	int low, curr, high; //low��ʾ��λ��curr��λ, high��λ
	int m = log10((double)n) + 1; //n�ж���λ
	int i, j;

	for (i = 0; i <= 9; i++)
		result[i] = 0;

	for (i = 1, high = n; i <= m; i++)
	{
		int lowZeros = (int)(pow((double)10, (double)(i - 1))); //��curr�͵��м�λ���м���0
		low = n % lowZeros; //��Ҫ��졣��
		curr = high % 10; //��iλ
		high /= 10;

		for (j = 0; j <= 9; j++)
		{
			result[j] += high * lowZeros;// __x(��iλ)__ ,iǰ��λ0-42��(43��*lowZeros)�ֿ��ܣ�
			if (j == curr) //����j���ڵ�iλ��ʱ��Ҫ�ټ��ϸ�λ�䵽43ʱ��low(֮���ȡ������)
				result[j] += (low + 1); //Ҫ�ǵ�+1������
			else if(j < curr) //x�ȵ�iλС����2ʱ����λ�䵽����high(43)ʱ��iλҲ��������ȡ�õ�x
				result[j] += lowZeros; //����Ҫ��ǰ��0-42�������ټ�Ϊ43ʱ
		}
	}

	for (i = 1; i <= m; i++) //0
		result[0] -= (int)pow((double)10, (double)(i - 1)); //ȥ���ȵ�iλ�ߵ��Ǽ�λ����0�����
}
