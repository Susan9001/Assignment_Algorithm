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

int compareEnd(const void* act1, const void* act2); //结束时间升序
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
	int count = 0; //计算已经安排会场的活动个数
	int roomNum = 0; //会场数目
	int i;

	qsort(acts, actNum, sizeof(Activity), compareEnd);
	for (i = 0; i < actNum; i++) acts[i].tag = 0;

	while (count < actNum)
	{
		roomNum++; //开始安排第roomNum++个会场
		bool start = false; //表示还没安排该会场的第一个活动
		int endTime = MAX; //当前结束时间

		for (i = 0; i < actNum; i++)
		{
			if (!acts[i].tag) //对于尚未安排的
			{
				if (!start) //开始安排该会场的第一个活动
				{
					start = true;
					acts[i].tag = roomNum;
					endTime = acts[i].end; //初始化结束时间
					count++;
				}
				else if(acts[i].start > endTime) //对于其他活动，只要时间相容就可以在同一会场
				{
					acts[i].tag = roomNum;
					endTime = acts[i].end; //改变结束时间
					count++;
				}
				//else 时间不相容就不管他先
			}//for 每一个
		}//while 全部活动都被安排
	}

	return roomNum;
}

int compareEnd(const void* act1, const void* act2)
{
	return (((Activity*)act1)->end - ((Activity*)act2)->end);
}