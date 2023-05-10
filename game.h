#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

class Game
{
	private:
		unordered_map<int, unordered_set<char>> rows, cols, subBoxes;
		int markedCounter = 0;
		int size = 0;
		char** board = nullptr;
		void init();
		bool checkValidMark(int x, int y, char val);
		bool gameOver();
		void checkValidBoardSize(int size);
		void draw();
		void teardown();
	public:
		void play(int size = 9);
		void changeSize(int newSize);
};
