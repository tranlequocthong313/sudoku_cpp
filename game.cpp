#include "game.h"
#include <iostream>

void Game::init()
{
	markedCounter = 0;
	for (int i = 0; i < size; i++)
	{
		for (auto j = 0; j < size; j++)
		{
			board[i][j] = '.';
		}
	}
}

bool Game::gameOver()
{
	return markedCounter == (size*size);
}

void Game::checkValidBoardSize(int size)
{
	if (size <= 0)
	{
		cout << "Kich thuoc ban phai lon hon 0!" << endl;
		return;
	}
	if (size % 3 != 0)
	{
		cout << "Kich thuoc ban phai chia het cho 3! VD: (3, 6, 9...)" << endl;
		return;
	}
	this->size = size;
}

void Game::draw()
{
	for (auto& rows : board)
	{
		for (auto& cell : rows)
		{
			cout << cell << " ";
		}
		cout << endl;
	}
}

void Game::play(int size)
{
	checkValidBoardSize(size);
	init();

	while (!gameOver())
	{
		cout << "--- SUDOKU ---" << endl;
		draw();
		int x, y;
		char val;
		do
		{
			cout << "Chon o (x, y): ";
			cin >> x >> y;
			if (x < 0 || x >= size || y < 0 || y >= size)
			{
				cout << "Vi tri o khong hop le!" << endl;
			}
			else
			{
				break;
			}
		} while (true);
		do
		{
			cout << "Gia tri (1-9): ";
			cin >> val;
			if (val < 1 || val > 9)
			{
				cout << "Gia tri khong hop le!" << endl;
			}
			else
			{
				break;
			}
		} while (true);
		checkValidMark(x, y, val);
	}
}

void Game::changeSize(int newSize)
{
	play(newSize);
}

void Game::checkValidMark(int x, int y, char val)
{
	int boxDiv = size / 3;
	int boxIndex = (x / boxDiv) * boxDiv + (y / boxDiv);
	if (rows[x].count(val) || cols[y].count(val) || subBoxes[boxIndex].count(val))
	{
		cout << "So da duoc danh!" << endl;
		return;
	}
	markedCounter++;
	rows[x].insert(val);
	cols[y].insert(val);
	subBoxes[boxIndex].insert(val);
}

