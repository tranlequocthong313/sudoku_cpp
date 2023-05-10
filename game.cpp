#include "game.h"
#include <iostream>
#include <string>
#include <cstdlib>

void Game::init()
{
	markedCounter = 0;
	teardown();

	board = new char*[size];
	for (int i = 0; i < size; i++)
	{
		board[i] = new char[size];
	}

	srand((int)time(0));
	for (int i = 0; i < size; i++)
	{
		for (auto j = 0; j < size; j++)
		{
			int val = rand() % 9 + 1;
			bool valid = checkValidMark(i, j, val + '0');
			if (!valid)
			{
				board[i][j] = '.';
			}
		}
	}
}

bool Game::gameOver()
{
	cout << markedCounter << " " << size*size << endl;
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
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << " ";
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
			cout << "Nhap x (1-" + to_string(size) + ") : ";
			cin >> x;
			cout << "Nhap y (1-" + to_string(size) + ") : ";
			cin >> y;
			if (x < 1 || x > size || y < 1 || y > size)
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
			if (val < '1')
			{
				cout << "Gia tri khong hop le!" << endl;
			}
			else
			{
				break;
			}
		} while (true);
		if (board[x-1][y-1] != '.')
		{
			continue;
		}
		if (!checkValidMark(x-1, y-1, val))
		{
			cout << "So da duoc danh!" << endl;
		}
	}
}

void Game::changeSize(int newSize)
{
	play(newSize);
}

bool Game::checkValidMark(int x, int y, char val)
{
	int boxDiv = size / 3;
	int boxIndex = (x / boxDiv) * boxDiv + (y / boxDiv);
	if (rows[x].count(val) || cols[y].count(val) || subBoxes[boxIndex].count(val))
	{
		return false;
	}
	markedCounter++;
	rows[x].insert(val);
	cols[y].insert(val);
	subBoxes[boxIndex].insert(val);
	board[x][y] = val;
	return true;
}

void Game::teardown()
{
	if (board == nullptr)
	{
		return;
	}
	for (auto i = 0; i < size; i++)
	{
		delete [] board[i];
	}
	delete [] board;
}

