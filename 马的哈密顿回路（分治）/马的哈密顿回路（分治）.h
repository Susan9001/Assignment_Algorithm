#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

typedef std::pair<int, int> Pos;
typedef std::vector<std::vector<Pos>> StepBoard; // the next step
typedef std::vector<std::vector<int>> MarkedBoard; // the num of step of curr pos

class Hamilton_DC {
public:
	Hamilton_DC(int g_row, int g_col, const std::string &inpath = "board_path.txt");
	~Hamilton_DC();
	bool markChessBoard(StepBoard &cb); 
	bool makeStepBoard(MarkedBoard &stepB); // 每一格子标记是目前第几步
	
private:
	int g_row, g_col; // total row / col
	StepBoard b66, b68, b86, b88, b810, b108, b1010, b1012, b1210;
	StepBoard b_chess;
	
	void base(int m, int n, int offx, int offy); // 在b_result上面构建基础的棋盘
	void build(int m, int n, int offx, int offy, const StepBoard &b); // help base
	void initBase(int m, int n, StepBoard &b, std::ifstream &ifs); // 初始化bxx
	bool comp(int m, int n, int offx, int offy); // 分治; True-找到; False-找不到
	void reverseDirection(int m, int n, int offx, int offy); // 
	void markBoard(int m, int n, int offx, int offy, MarkedBoard & b_mark); // mark 1, 2, 3, ...m*n (relative)

};
