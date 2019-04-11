#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#define MAX 10000

typedef struct _activity
{
	int start;
	int end;
	int tag;
}Activity;

int compareEnd(const void* act1, const void* act2); //����ʱ������
int countRoom(Activity *(&acts), int actNum);

int main()
{
	int actNum, roomNum;
	ifstream file_in("input.txt");
	file_in >> actNum;

	Activity *acts = (Activity*)malloc(sizeof(Activity) * actNum);
	for (int i = 0; i < actNum; i++)
		file_in >> acts[i].start >> acts[i].end;

	roomNum = countRoom(acts, actNum);
	cout << roomNum << endl;
	ofstream file_out("output.txt");
	file_out << roomNum << endl;

	system("pause");
	return 0;
}

int countRoom(Activity *(&acts), int actNum)
{
	int count = 0; //�����Ѿ����Ż᳡�Ļ����
	int roomNum = 0; //�᳡��Ŀ
	int i;

	qsort(acts, actNum, sizeof(Activity), compareEnd);
	for (i = 0; i < actNum; i++) acts[i].tag = 0;

	while (count < actNum)
	{
		roomNum++; //��ʼ���ŵ�roomNum++���᳡
		bool start = false; //��ʾ��û���Ÿû᳡�ĵ�һ���
		int endTime = MAX; //��ǰ����ʱ��

		for (i = 0; i < actNum; i++)
		{
			if (!acts[i].tag) //������δ���ŵ�
			{
				if (!start) //��ʼ���Ÿû᳡�ĵ�һ���
				{
					start = true;
					acts[i].tag = roomNum;
					endTime = acts[i].end; //��ʼ������ʱ��
					count++;
				}
				else if(acts[i].start > endTime) //�����������ֻҪʱ�����ݾͿ�����ͬһ�᳡
				{
					acts[i].tag = roomNum;
					endTime = acts[i].end; //�ı����ʱ��
					count++;
				}
				//else ʱ�䲻���ݾͲ�������
			}//for ÿһ��
		}//while ȫ�����������
	}

	return roomNum;
}

int compareEnd(const void* act1, const void* act2)
{
	return (((Activity*)act1)->end - ((Activity*)act2)->end);
}