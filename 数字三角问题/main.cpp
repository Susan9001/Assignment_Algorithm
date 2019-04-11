#include "TriangleIssue.hpp"
#include <fstream>

#if 1
int main() {
	std::ifstream is("input.txt");
	int n;
	std::vector<std::vector<int> > v;

	is >> n;
	for (int i = 0; i < n; i++) {
		v.push_back(std::vector<int>());
		for (int j = 0; j <= i; j++) {
			int tmp;
			is >> tmp;
			v[i].push_back(tmp);
		}
	}
	is.close();

	int result = Solution().getMaxTriangleSum(n, v);
	std::ofstream os("output.txt");
	os << result;
	os.close();

	return 0;
}
#endif

