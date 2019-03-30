#include "马的哈密顿回路（分治）.h"
#include <map>
#include <stdio.h>

Hamilton_DC::Hamilton_DC(int g_row, int g_col, const std::string &inpath)
	:g_row(g_row), g_col(g_col){

	std::ifstream ifs(inpath);
	initBase(6, 6, b66, ifs);
	initBase(6, 8, b68, ifs);
	initBase(8, 6, b86, ifs);
	initBase(8, 8, b88, ifs);
	initBase(8, 10, b810, ifs);
	initBase(10, 8, b108, ifs);
	initBase(10, 10, b1010, ifs);
	initBase(10, 12, b1012, ifs);
	initBase(12, 10, b1210, ifs);
	b_chess = StepBoard(g_row, std::vector<Pos>(g_col, Pos(0, 0)));

}

Hamilton_DC::~Hamilton_DC(){}

bool Hamilton_DC::markChessBoard(StepBoard & cb) {
	bool ok = comp(g_row, g_col, 0, 0);
	cb = b_chess;
	return ok;
}

bool Hamilton_DC::makeStepBoard(MarkedBoard & b_step) {
	if (b_chess.empty()) {
		if (!markChessBoard(b_chess)) 
			return false;
	}
	markBoard(g_row, g_col, 0, 0, b_step);

	return true;;
}

void Hamilton_DC::base(int row, int col, int offx, int offy) {
	if (row == 6 && col == 6) build(row, col, offx, offy, b66);
	else if (row == 6 && col == 8) build(row, col, offx, offy, b68);
	else if (row == 8 && col == 6) build(row, col, offx, offy, b86);
	else if (row == 8 && col == 8) build(row, col, offx, offy, b88);
	else if (row == 8 && col == 10) build(row, col, offx, offy, b810);
	else if (row == 10 && col == 8) build(row, col, offx, offy, b108);
	else if (row == 10 && col == 10) build(row, col, offx, offy, b1010);
	else if (row == 10 && col == 12) build(row, col, offx, offy, b1012);
	else if (row == 12 && col == 10) build(row, col, offx, offy, b1210);
}

void Hamilton_DC::build(int m, int n, int offx, int offy, const StepBoard & b) {
	for (int i = offx; i < offx + m; i++) {
		for (int j = offy; j < offy + n; j++) {
			b_chess[i][j] = b[i - offx][j - offy];
			b_chess[i][j].first += offx;
			b_chess[i][j].second += offy;
		}
	}
}

void Hamilton_DC::initBase(int m, int n, StepBoard & b, std::ifstream &ifs) {
	b = StepBoard(m, std::vector<Pos>(n));
	std::map<int, Pos> m_sortedPos; // key-顺序; Pos-位置

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int num;
			ifs >> num;
			m_sortedPos[num] = Pos(i, j);
		}
	}
	Pos currpos(0, 0), nextpos(0, 0);
	for (int k = 0; k < m * n; k++) {
		currpos = nextpos;
		nextpos = m_sortedPos[(k + 2) % (m * n + 1)]; // range: 1 ~ m*n
		b[currpos.first][currpos.second] = nextpos;
		// the last one is m*n
	}
}

// m, n: the size of current chessboard
bool Hamilton_DC::comp(int m, int n, int offx, int offy) {
	// invalid row / col number
	if (m & 1 || n & 1 || m - n > 2 || n - m > 2 || m < 6 || n < 6)
		return false;

	// basic resolution for the small
	if (m < 12 || n < 12) {
		base(m, n, offx, offy);
		return true;
	}

	// devide
	int rownum_1 = (m % 4 ? m / 2 - 1 : m / 2); // 确保rownum_x为偶数
	int rownum_2 = m - rownum_1;
	int colnum_1 = (n % 4 ? n / 2 - 1 : n / 2);
	int colnum_2 = n - colnum_1;
	comp(rownum_1, colnum_1, offx, offy); // top-left
	comp(rownum_1, colnum_2, offx, offy + colnum_1); // top-right
	comp(rownum_2, colnum_1, offx + rownum_1, offy); // bottom-left
	comp(rownum_2, colnum_2, offx + rownum_1, offy + colnum_1); // bottom-right

	// merge
	// the alter of links equals the rotate of [odd]
	int *pos_x = new int[8], *pos_y = new int[8]; // no.3 is on b_result[pos_x[3]][pos_y[3]]
	pos_x[0] = offx + rownum_1 - 1;	pos_y[0] = offy + colnum_1 - 3; // 见合并步骤中的图2-17 点0 1 2 3 4 5 6 7坐标
	pos_x[1] = pos_x[0] - 1;    	pos_y[1] = pos_y[0] + 2;
	pos_x[2] = pos_x[1] - 1;    	pos_y[2] = pos_y[1] + 2;
	pos_x[3] = pos_x[2] + 2;        pos_y[3] = pos_y[2] - 1;
	pos_x[4] = pos_x[3] + 1;    	pos_y[4] = pos_y[3] + 2;
	pos_x[5] = pos_x[4] + 1;    	pos_y[5] = pos_y[4] - 2;
	pos_x[6] = pos_x[5] + 1;        pos_y[6] = pos_y[5] - 2;
	pos_x[7] = pos_x[6] - 2;    	pos_y[7] = pos_y[6] + 1;
	// alter and make links
	// e.g. 0-1, 2-3, 4-5, 6-7 => 0-7, 2-1, 4-3, 6-5
	// possibly: (0, 0)->..(左上)..->0->7->..(左下)..->6->5->.(右下).->4->3->.(右上).->2->1->.(左上).->(0, 0)

	// 要求必须奇->偶，否则反转
	for (int k = 1; k <= 7; k += 2) {
		Pos odd_nPos = b_chess[pos_x[k]][pos_y[k]];
		if (odd_nPos.first != pos_x[k - 1] || odd_nPos.second != pos_y[k - 1]) {
			switch (k) { 
			case 1: reverseDirection(rownum_1, colnum_1, offx, offy); break;
			case 3: reverseDirection(rownum_1, colnum_2, offx, offy + colnum_1); break;
			case 5: reverseDirection(rownum_2, colnum_2, offx + rownum_1, offy + colnum_1); break;
			case 7: reverseDirection(rownum_2, colnum_1, offx + rownum_1, offy); break;
			}
		}
	}

#if DEBUG
		for (int k = 0; k < 8; k++) {
			printf("k = %d, (%d, %d) => (%d, %d)\n", k, pos_x[k], pos_y[k], 
				b_chess[pos_x[k]][pos_y[k]].first, b_chess[pos_x[k]][pos_y[k]].second);
		}
		std::cout << std::endl;
#endif
	for (int k = 0; k < 4; k++) {
		b_chess[pos_x[k]][pos_y[k]] = Pos(pos_x[(k + 1) % 8], pos_y[(k + 1) % 8]);
	}

#if DEBUG
	for (int k = 0; k < 8; k++) {
		printf("k = %d, (%d, %d) => (%d, %d)\n", k, pos_x[k], pos_y[k], 
			b_chess[pos_x[k]][pos_y[k]].first, b_chess[pos_x[k]][pos_y[k]].second);
	}
	std::cout << std::endl;
#endif

	delete[] pos_x, pos_y;
	return true;
}

void Hamilton_DC::reverseDirection(int m, int n, int offx, int offy) {

	Pos pPos(offx, offy); // previous position
	Pos cPos = b_chess[offx][offy]; // current position

	// cPos->nPos => cPos->pPos 
	while (cPos.first != offx || cPos.second != offy) {
		Pos nPos = b_chess[cPos.first][cPos.second];
		b_chess[cPos.first][cPos.second] = pPos;
		pPos = cPos;
		cPos = nPos;
	}
	b_chess[cPos.first][cPos.second] = pPos;

#if DEBUG
	std::cout << "反转后\n";
	b_mark = MarkedBoard(m, std::vector<int>(n, 0));
	markBoard(m, n, offx, offy, b_mark);
	std::cout << '\t';
	for (int j = 0; j < g_col; j++) {
		//std::cout << j << "\t";
		std::cout << j << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < g_row; i++) {
		std::cout << i << '\t';
		for (int j = 0; j < g_col; j++) {
			//std::cout << b_mark[i][j] << '\t';
			std::cout << "(" <<b_chess[i][j].first << ',' << b_chess[i][j].second << ")"<<"\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
#endif
}

void Hamilton_DC::markBoard(int m, int n, int offx, int offy, MarkedBoard & b_mark) {
	b_mark = MarkedBoard(g_row, std::vector<int>(g_col, 0));
	Pos currpos(offx, offy);
	Pos nextpos = b_chess[currpos.first][currpos.second];
	for (int k = 1; k <= m * n; k++) {
		if (!b_mark[currpos.first][currpos.second])
			b_mark[currpos.first][currpos.second] = k;
		currpos = nextpos;
		nextpos = b_chess[currpos.first][currpos.second];
	}
}
