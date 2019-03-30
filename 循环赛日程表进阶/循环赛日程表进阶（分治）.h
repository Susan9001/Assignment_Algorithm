#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Tournament {
public:
	Tournament(int n);
	std::vector<std::vector<int>> getResult();

private:
	int n;
	std::vector<std::vector<int>> arr;
	void tournament(int n);
	bool isOdd(int n);
	void mergeEven(int n);
	void mergeOdd(int n);
};

