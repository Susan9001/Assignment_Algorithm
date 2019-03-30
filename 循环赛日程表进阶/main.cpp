#include "循环赛日程表进阶（分治）.h"

#if 1
int main() 
{
	int n = 6;
	std::vector<std::vector<int>> arr(n + 1, std::vector<int>(n + 1, 0));
	arr = Tournament(n).getResult();

	std::ofstream ofs("循环赛日程表.txt");
	ofs << n << '\n';
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n - 1; j++) {
			ofs << arr[i][j] << '\t';
		}
		ofs << std::endl;
	}
	ofs.close();

	return 0;
}
#endif
