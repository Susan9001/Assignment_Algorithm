#include "马的哈密顿回路（分治）.h"

#if 1
int main() {
	int g_col = 14, g_row = 12;
	std::ofstream ofs_step("马走哈密顿(分治)-每步.txt");
	std::ofstream ofs_mark("马走哈密顿(分治)-顺序.txt");

	Hamilton_DC ham_dc(g_row, g_col);
	StepBoard b_nextStep;
	MarkedBoard b_mark;
	bool isOk = ham_dc.markChessBoard(b_nextStep);
	ham_dc.makeStepBoard(b_mark);

	if (isOk) {
		// 标记最中间
		// 列号
		ofs_step << '\t';
		ofs_mark << '\t';
		for (int j = 0; j < g_col; j++) {
			ofs_step << j << "\t\t\t";
			ofs_mark << j << "\t\t";
		}
		ofs_step << std::endl;
		ofs_mark << std::endl;
		// 正式输出动作
		for (int i = 0; i < g_row; i++) {
			ofs_step << i << '\t';
			ofs_mark << i << '\t';
			for (int j = 0; j < g_col; j++) {
				ofs_step << "(" <<b_nextStep[i][j].first << ',' << b_nextStep[i][j].second << ")"<<"\t\t";
				ofs_mark << b_mark[i][j] << "\t\t";
			}
			ofs_step << std::endl;
			ofs_mark << std::endl;
		}
	} else {
		ofs_step << "not ok!" << std::endl;
		ofs_mark<< "not ok!" << std::endl;
	}

	ofs_step.close();
	ofs_mark.close();
	return 0;
}
#endif

#if 0
//#include "马的哈密顿回路（深度优先）.cpp"
int main() {
	int m = 6, n = 6;
	Hamilton ham;
	ham.makeHamilton(m, n);
	
	std::ofstream ofs("马走哈密顿(回溯).txt");
	ofs << m << '\t' << n << '\n';
	std::vector<std::vector<int>> chessBox = ham.getChessBox();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			ofs << chessBox[i][j] << '\t';
		}
		ofs << std::endl;
	}
	ofs << std::endl;
	ofs.close();

	return 0;
}
#endif

