#include "循环赛日程表进阶（分治）.h"

Tournament::Tournament(int n) 
	:n(n) {
	this->arr = std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1, 0));
	tournament(n);
}

std::vector<std::vector<int>> Tournament::getResult() {
	return arr;
}

void Tournament::tournament(int n) {
	if (n == 1) {
		arr[1][0] = 1;
		return;
	}
	if (n == 2) {
		arr[1][0] = 1;
		arr[2][0] = 2;
		// 第一天: 1号 vs 2号
		arr[1][1] = 2;
		arr[2][1] = 1;
		return;
	}

	if (isOdd(n)) {
		tournament(n + 1); // 奇数补成偶数
	}
	else {
		int m = n >> 1;
		tournament(m);
		if (isOdd(m))
			mergeOdd(n);
		else
			mergeEven(n);
	}
}

void Tournament::mergeEven(int n) {
	int m = n >> 1;
	for (int i = 1; i <= m; i++) { // player no.i
		for (int j = 0; j < m; j++) { // the jth day (plus the line numbers)
			arr[i + m][j] = arr[i][j + m] = arr[i][j] + m;
			arr[i + m][j + m] = arr[i][j];
		}
	}
}

void Tournament::mergeOdd(int n) {
	int m = n >> 1;

	/**
	 * group1: 1 ~ m; group2: m+1 ~ n
	 * for the first m days, there is a player in each groups,
	 * who would be vacant if they do not play with the guy in the other group.
	 */

	int j;
	for (j = 0; j <= m; j++) { // for each day (and line num):
		for (int i = 1; i <= m; i++) { // for each one in group1
			if (arr[i][j] < 1 || arr[i][j] > m) {
				// used to play with a fake player, so now has to play with the guy in group2(m+i)
				arr[i][j] = m + i;
				arr[m + i][j] = i;
			}
			else {
				arr[m + i][j] = arr[i][j] + m; // i's copy in group2
			}
		}
	}

	/** for the next m days, group1(i) play with group2((i+j+1)mod m + m) */
	for (; j <= n-1; j++) {
		for (int i = 1; i <= m; i++) {
			int k = (i + j + 2) % m + m + 1; // not quite understand....
			arr[i][j] = k;
			arr[k][j] = i;
		}
	}

#if DEBUG
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n - 1; j++) {
			std::cout << arr[i][j] << '\t';
		}
		std::cout << std::endl;
	}
#endif
}

bool Tournament::isOdd(int n) {
	return n & 1;
}
