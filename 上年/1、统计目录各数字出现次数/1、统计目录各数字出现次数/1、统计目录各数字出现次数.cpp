#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

void countA(int n, int result[]); //笨方法
void countB(int n, int result[]); 
void countC(int n, int result[10]); //递归法
void cRecursion(int n, int result[10]);

int main()
{
	int resultA[10], resultB[10], resultC[10]; //放对应下标的统计结果
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

	/*思路：假设页码为43786：从最高位开始进入递归，一直进入个位开始，一层层累加算出6,86,786···43786时0-9出现的次数*/
	cRecursion(n, result);

	int m = log10((double)n) + 1; //n有多少位
	for (int i = 1; i <= m; i++) 
		result[0] -= (int)pow((double)10, (double)(i - 1)); //去除本位i前都是0的情况
}

void cRecursion(int n, int result[10])
{
	int m = log10((double)n) + 1; //n有多少位
	if (m == 1)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (j > n) result[j] = 0;
			else result[j] = 1;
		}
		return;
	}

	int lowZeros = (int)(pow((double)10, (double)(m - 1))); //比curr低的有几位就有几个0
	int low = n % lowZeros; //除去最高位的其他几位
	int curr = n / lowZeros; //最高一位
	int fn_1 = (m - 1) * (int)(pow((double)10, (double)(m - 2))); //f(n - 1)

	cRecursion(low, result); //先递归，算出对low每个数字的个数
	for (int j = 0; j <= 9; j++)
	{
		result[j] += (fn_1 * curr);  //由于比low多了1位，所以要加上从第1到m-1位上数字j新出现的次数
		if (j < curr) result[j] += lowZeros; //以下是加上再第m位处数字j新出现的次数
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
	int low, curr, high; //low表示低位，curr本位, high高位
	int m = log10((double)n) + 1; //n有多少位
	int i, j;

	for (i = 0; i <= 9; i++)
		result[i] = 0;

	for (i = 1, high = n; i <= m; i++)
	{
		int lowZeros = (int)(pow((double)10, (double)(i - 1))); //比curr低的有几位就有几个0
		low = n % lowZeros; //不要搞混。。
		curr = high % 10; //第i位
		high /= 10;

		for (j = 0; j <= 9; j++)
		{
			result[j] += high * lowZeros;// __x(第i位)__ ,i前几位0-42共(43个*lowZeros)种可能，
			if (j == curr) //数字j等于第i位数时，要再加上高位变到43时的low(之后就取不到了)
				result[j] += (low + 1); //要记得+1！！！
			else if(j < curr) //x比第i位小，如2时，高位变到最大的high(43)时第i位也能完整地取得到x
				result[j] += lowZeros; //所以要在前面0-42基础上再加为43时
		}
	}

	for (i = 1; i <= m; i++) //0
		result[0] -= (int)pow((double)10, (double)(i - 1)); //去除比第i位高的那几位都是0的情况
}
