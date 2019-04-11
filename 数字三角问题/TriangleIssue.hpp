#include <iostream>
#include <vector>
#include <stdio.h>

class Solution {
public:
	int getMaxTriangleSum(int n, std::vector<std::vector<int>> v) {
		for (int i = n - 2; i >= 0; i--) {
			for (int j = 0; j <= i; j++) {
				v[i][j] += max(v[i + 1][j], v[i + 1][j + 1]);
			}
		}
		return v[0][0];
	}
private:
	int max(int a, int b, int c) {
		if (a > b && a > c)
			return a;
		else
			return (b > c ? b : c);
	}
	int max(int a, int b) {
		return (a > b ? a : b);
	}
};

