#include <iostream>
#include <fstream>
#include <vector>

class Hamilton_DFS {
public:
	Hamilton_DFS();
	std::vector<std::vector<int>> getChessBox();
	std::vector<std::pair<int, int>> getTrack();
	void makeHamilton(const int &m, const int &n); // m行n列
private:
	int m, n; // chessBox size
	std::vector<std::pair<int, int>> jumps; // 马走日
	std::vector<std::vector<int>> chessBox;
	std::vector<std::pair<int, int>> trackPath;
	bool ok; // has return to (0, 0) ?
	bool isFinished();
	void move(int x, int y, int count); // no.count step
	bool validMove(const int &x, const int &y); // no outside or already went

	std::ofstream ofs;
};

Hamilton_DFS::Hamilton_DFS() {
	jumps = { {1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1} };
	ofs = std::ofstream("log.txt");
}

void Hamilton_DFS::makeHamilton(const int &m, const int &n) {
	this->m = m;
	this->n = n;
	chessBox = std::vector<std::vector<int>>(m, std::vector<int>(n, 0)); // from 1
	ok = false;

	chessBox[0][0] = -1;
	move(0, 0, 1);
	ofs.close();
}

bool Hamilton_DFS::isFinished() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (chessBox[i][j] == 0) return false;
		}
	}
	return true;
}

void Hamilton_DFS::move(int x, int y, int count) {

#if 1
	if (x == 0 && y == 0) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				ofs << chessBox[i][j] << '\t';
			}
			ofs << std::endl;
		}
		ofs << std::endl;
	}
#endif

	if (!validMove(x, y) || (chessBox[x][y] != 0 && (x != 0 || y != 0)) ) 
		return;

# if 0
	if (x == 0 && y == 0) {
		if (isFinished()) {
			ok = true;
		}
		return;
	}
#endif

#if 1
	if (isFinished()) { // 全部遍历完了
		if (x == 0 && y == 0)
			ok = true;
		else 
			chessBox[x][y] = 0; // dont forget to trace back
		return;
	}
#endif

	chessBox[x][y] = -1;
	for (auto jump : jumps) {
		move(x + jump.first, y + jump.second, count + 1);
		if (ok) {
			chessBox[x][y] = count;
			trackPath.push_back(std::pair<int, int>(x, y));
			return;
		}
	}
	chessBox[x][y] = (x != 0 || y != 0) ? 0 : -1;
}

bool Hamilton_DFS::validMove(const int &m, const int &n) {
	return (m >= 0 && n >= 0 && m <= this->m - 1 && n <= this->n - 1);
}


std::vector<std::vector<int>> Hamilton_DFS::getChessBox() {
	return chessBox;
}

std::vector<std::pair<int, int>> Hamilton_DFS::getTrack() {
	return trackPath;
}

