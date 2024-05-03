#include<iostream>
#include"Interface.h"
#include"Controller.h"
#include"Game.h";
#include<algorithm>
#include<conio.h>
#include<map>
#include<utility>
#include<string>

//For time
#include <chrono>
#include <iomanip>
#include <thread>
#include <atomic>
using namespace std;

//Create board and add character, key, index, coordinate to the board
void Game::CreateBoard(Board**& board, char**& c, int row, int col)
{
	AddCharToButton(c, row, col);
	board = new Board * [row + 2];
	for (int i = 0; i <= row + 1; i++)
	{
		board[i] = new Board[col + 2];
	}
	for (int i = 0; i <= row + 1; i++)
	{
		for (int j = 0; j <= col + 1; j++)
		{
			if (i == 0 || j == 0 || i == row + 1 || j == col + 1)
			{
				board[i][j].c = ' ';
				board[i][j].coordinate = { -1, -1 };
				board[i][j].index = { -1, -1 };
				board[i][j].key = 0;
			}
			else
			{
				board[i][j].c = c[i - 1][j - 1];
				board[i][j].index = { i, j };
				board[i][j].coordinate = { 7 * (j - 1) + 7, 5 * (i - 1) + 3 };
				board[i][j].key = 1;
			}
		}
	}
	//Delete character after add to board
	DeleteChar(c, row);
}
//Draw button 
void Game::DrawButton(int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Controller::PrintRectangle(7 * j + 4, 5 * i + 1, 7, 5);
		}
	}
}
//Draw board with specific width and height
void Game::DrawBoard(int x, int y, int width, int height)
{
	Interface::GotoXY(x, y);
	//Draw first row of rectangle
	putc(201, stdout);
	for (int i = 1; i < width - 1; i++)
	{
		putc(205, stdout);
	}
	putc(187, stdout);

	//Draw left row of rectangle
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(x, y + i);
		putc(186, stdout);
	}
	Interface::GotoXY(x, y + height - 1);
	putc(200, stdout);

	//Draw last row of rectangle
	for (int i = 1; i < width - 1; i++)
	{
		putc(205, stdout);
	}
	putc(188, stdout);

	//Draw last row of rectangle
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(x + width - 1, y + i);
		putc(186, stdout);
	}
	cout << endl;
	cout << endl;
}
//Create character to button
void Game::AddCharToButton(char**& c, int row, int col)
{
	srand(time(NULL));
	if (row == 4 && col == 4)
	{
		c = new char* [4];
		for (int i = 0; i < 4; i++)
		{
			c[i] = new char[5];
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				c[i][j] = 65 + i;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				swap(c[i][j], c[rand() % 4][rand() % 4]);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Interface::GotoXY(7 * j + 7, 5 * i + 3);
				cout << c[i][j];
			}
		}
	}
	else if (row == 6 && col == 6)
	{
		c = new char* [6];
		for (int i = 0; i < 6; i++)
		{
			c[i] = new char[7];
		}
		int x = 0, cnt = 0;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				c[i][j] = 65 + x;
				cnt++;
				if (cnt == 4)
				{
					x++;
					cnt = 0;
				}
			}
		}
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				swap(c[i][j], c[rand() % 6][rand() % 6]);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				Interface::GotoXY(7 * j + 7, 5 * i + 3);
				cout << c[i][j];
			}
		}
	}
}
//Check I matching 
bool CheckIsMatchingI(Board** board, pair<int, int>index1, pair<int, int>index2)
{
	if (index1.first == index2.first && index1.second == index2.second)
	{
		return false;
	}
	bool KT = true;
	//Check the same row
	if (index1.first == index2.first)
	{
		//Check from the min column to the max column
		for (int i = min(index1.second, index2.second) + 1; i < max(index1.second, index2.second); i++)
		{
			if (board[index1.first][i].key != 0)
			{
				KT = false;
				break;
			}
		}
		if (KT == true)
		{
			return true;
		}
	}
	//Check the same col
	if (index1.second == index2.second)
	{
		//Check from the min row to the max row
		for (int i = min(index1.first, index2.first) + 1; i < max(index1.first, index2.first); i++)
		{
			if (board[i][index1.second].key != 0)
			{
				KT = false;
				break;
			}
		}
		if (KT == true)
		{
			return true;
		}
	}
	return false;
}
//Check L matching
bool CheckIsMatchingL(Board** board, pair<int, int>index1, pair<int, int>index2)
{
	int index;
	if (min(index1.second, index2.second) == index1.second)
	{
		index = index1.first;
	}
	else
	{
		index = index2.first;
	}
	if (CheckIsMatchingI(board, { index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) + 1 }) == true) // cộng 1 là do hàm isMatchingI chỉ lấy ở giữa đoạn
	{
		if (CheckIsMatchingI(board, { min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) }) == true)
		{
			return true;
		}
	}


	if (max(index1.second, index2.second) == index1.second)
	{
		index = index1.first;
	}
	else
	{
		index = index2.first;
	}
	if (CheckIsMatchingI(board, { index, min(index1.second, index2.second) - 1 }, { index, max(index1.second, index2.second) }) == true)
	{
		if (CheckIsMatchingI(board, { min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) }) == true)
		{
			return true;
		}
	}
	return false;
}
//Check U and Z matching
bool CheckIsMatchingUAndZ(Board** board, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	for (int j = 0; j < numOfCols + 2; j++)
	{
		if (j < index1.second)
		{
			if (CheckIsMatchingI(board, { index1.first, j - 1 }, { index1.first, index1.second }) == true)
			{
				if (CheckIsMatchingL(board, { index1.first, j }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
		else if (j > index1.second)
		{
			if (CheckIsMatchingI(board, { index1.first, index1.second }, { index1.first, j + 1 }) == true)
			{
				if (CheckIsMatchingL(board, { index1.first, j }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
	}

	for (int i = 0; i < numOfRows + 2; i++)
	{
		if (i < index1.first)
		{
			if (CheckIsMatchingI(board, { i - 1, index1.second }, { index1.first, index1.second }) == true)
			{
				if (CheckIsMatchingL(board, { i, index1.second }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
		else if (i > index1.first)
		{
			if (CheckIsMatchingI(board, { index1.first, index1.second }, { i + 1, index1.second }) == true)
			{
				if (CheckIsMatchingL(board, { i, index1.second }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//Draw I arrow(algorithm is the same as check I matching)
void DrawI(pair<int, int>index1, pair<int, int>index2)
{
	if (index1.first == index2.first)
	{
		Controller::PrintLine(7 * (min(index1.second, index2.second) - 1) + 8, 5 * (index1.first - 1) + 3, abs(((7 * (index1.second - 1) + 7) - (7 * (index2.second - 1) + 7))) - 1, Horizontal);
		Interface::GotoXY(7 * (min(index1.second, index2.second) - 1) + 8, 5 * (index1.first - 1) + 3);
		cout << "<";
		Interface::GotoXY(7 * (max(index1.second, index2.second) - 1) + 6, 5 * (index1.first - 1) + 3);
		cout << ">";
		return;
	}
	else
	{
		Controller::PrintLine(7 * (index1.second - 1) + 7, 5 * (min(index1.first, index2.first) - 1) + 4, abs(((5 * (index1.first - 1) + 3) - (5 * (index2.first - 1) + 3))) - 1, Vertical);
		Interface::GotoXY(7 * (index1.second - 1) + 7, 5 * (min(index1.first, index2.first) - 1) + 4);
		cout << "^";
		Interface::GotoXY(7 * (index1.second - 1) + 7, 5 * (max(index1.first, index2.first) - 1) + 2);
		cout << "v";
		return;
	}
}
//Draw L arrow(algorithm is the same as check L matching)
void DrawL(Board** board, pair<int, int>index1, pair<int, int>index2)
{
	int index;
	if (min(index1.second, index2.second) == index1.second)
	{
		index = index1.first;
	}
	else
	{
		index = index2.first;
	}
	if (CheckIsMatchingI(board, { index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) + 1 }) == true) // cộng 1 là do hàm isMatchingI chỉ lấy ở giữa đoạn
	{
		if (CheckIsMatchingI(board, { min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) }) == true)
		{
			DrawI({ index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) });
			DrawI({ min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) });
			return;
		}
	}
	if (max(index1.second, index2.second) == index1.second)
	{
		index = index1.first;
	}
	else
	{
		index = index2.first;
	}
	if (CheckIsMatchingI(board, { index, min(index1.second, index2.second) - 1 }, { index, max(index1.second, index2.second) }) == true)
	{
		if (CheckIsMatchingI(board, { min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) }) == true)
		{
			DrawI({ index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) });
			DrawI({ min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) });
			return;
		}
	}
}
//Draw U and Z arrow(algorithm is the same as check U and Z matching)
void DrawUAndZ(Board** board, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	for (int j = index1.second - 1; j >= 0; j--)
	{
		if (CheckIsMatchingI(board, { index1.first, j - 1 }, { index1.first, index1.second }) == true)
		{
			if (CheckIsMatchingL(board, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DrawI({ index1.first, j }, { index1.first, index1.second });
				DrawL(board, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}
	for (int j = index1.second + 1; j < numOfCols + 2; j++)
	{
		if (CheckIsMatchingI(board, { index1.first, index1.second }, { index1.first, j + 1 }) == true)
		{
			if (CheckIsMatchingL(board, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DrawI({ index1.first, index1.second }, { index1.first, j });
				DrawL(board, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}

	for (int i = index1.first - 1; i >= 0; i--)
	{
		if (CheckIsMatchingI(board, { i - 1, index1.second }, { index1.first, index1.second }) == true)
		{
			if (CheckIsMatchingL(board, { i, index1.second }, { index2.first, index2.second }) == true)
			{

				if (i != 0)
				{
					DrawI({ i, index1.second }, { index1.first, index1.second });
					DrawL(board, { i, index1.second }, { index2.first, index2.second });
				}
				else
				{
					Controller::PrintLine(7 * (index1.second - 1) + 7, 5 * 0 + 0, abs(5 * index1.first) - 2, Vertical);
					Interface::GotoXY(7 * (index1.second - 1) + 7, 5 * index1.first - 3);
					cout << "v";
					if (index1.second < index2.second)
					{
						if (CheckIsMatchingI(board, { 0, index1.second }, { 0, index2.second + 1 }) == true)
						{
							if (CheckIsMatchingI(board, { 0, index2.second }, { index2.first, index2.second }) == true)
							{
								Controller::PrintLine(7 * (index1.second - 1) + 8, (5 * 0 + 0), abs(((7 * (index1.second - 1) + 7) - (7 * (index2.second - 1) + 7))) - 1, Horizontal);
								Controller::PrintLine(7 * (index2.second - 1) + 7, 5 * 0 + 1, abs(((5 * (0 - 1) + 3) - (5 * (index2.first - 1) + 3))) - 3, Vertical);
								Interface::GotoXY(7 * (index2.second - 1) + 7, abs((5 * (0 - 1) + 3) - (5 * (index2.first - 1) + 3)) - 3);
								cout << "v";
								return;
							}
						}
					}
					else
					{
						if (CheckIsMatchingI(board, { 0, index2.second - 1 }, { 0, index1.second }) == true)
						{
							if (CheckIsMatchingI(board, { 0, index2.second }, { index2.first, index2.second }) == true)
							{
								Controller::PrintLine(7 * (index2.second - 1) + 8, (5 * 0 + 0), abs(((7 * index1.second + 0) - (7 * index2.second + 0))) - 1, Horizontal);
								Controller::PrintLine(7 * (index2.second - 1) + 7, 5 * 0 + 1, abs(((5 * 0 - 2) - (5 * index2.first - 2))) - 3, Vertical);
								return;
							}
						}
					}
				}
				return;
			}
		}
	}
	for (int i = index1.first + 1; i < numOfRows + 2; i++)
	{
		if (CheckIsMatchingI(board, { index1.first, index1.second }, { i + 1, index1.second }) == true)
		{
			if (CheckIsMatchingL(board, { i, index1.second }, { index2.first, index2.second }) == true)
			{
				DrawI({ index1.first, index1.second }, { i, index1.second });
				DrawL(board, { i, index1.second }, { index2.first, index2.second });
				return;
			}
		}
	}
}
//Delete I Arrow(algorithm is the same as draw I)
void DeleteI(pair<int, int>index1, pair<int, int>index2)
{
	if (index1.first == index2.first)
	{
		Game::DeleteLine(7 * (min(index1.second, index2.second) - 1) + 8, 5 * (index1.first - 1) + 3, abs(((7 * (index1.second - 1) + 7) - (7 * (index2.second - 1) + 7))) - 1, Horizontal);
		return;
	}
	else
	{
		Game::DeleteLine(7 * (index1.second - 1) + 7, 5 * (min(index1.first, index2.first) - 1) + 4, abs(((5 * (index1.first - 1) + 3) - (5 * (index2.first - 1) + 3))) - 1, Vertical);
		return;
	}
}
//Delete L Arrow(algorithm is the same as draw L)
void DeleteL(Board** board, pair<int, int>index1, pair<int, int>index2)
{
	int index;
	if (min(index1.second, index2.second) == index1.second)
	{
		index = index1.first;
	}
	else
	{
		index = index2.first;
	}
	if (CheckIsMatchingI(board, { index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) + 1 }) == true)
	{
		if (CheckIsMatchingI(board, { min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) }) == true)
		{
			DeleteI({ index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) });
			DeleteI({ min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) });
			return;
		}
	}

	if (max(index1.second, index2.second) == index1.second)
	{
		index = index1.first;
	}
	else
	{
		index = index2.first;
	}
	if (CheckIsMatchingI(board, { index, min(index1.second, index2.second) - 1 }, { index, max(index1.second, index2.second) }) == true)
	{
		if (CheckIsMatchingI(board, { min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) }) == true)
		{
			DeleteI({ index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) });
			DeleteI({ min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) });
			return;
		}
	}
}
//Delete U and Z Arrow(algorithm is the same as draw U and Z)
void DeleteUAndZ(Board** board, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	for (int j = index1.second - 1; j >= 0; j--)
	{
		if (CheckIsMatchingI(board, { index1.first, j - 1 }, { index1.first, index1.second }) == true)
		{
			if (CheckIsMatchingL(board, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DeleteI({ index1.first, j }, { index1.first, index1.second });
				DeleteL(board, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}
	for (int j = index1.second + 1; j < numOfCols + 2; j++)
	{
		if (CheckIsMatchingI(board, { index1.first, index1.second }, { index1.first, j + 1 }) == true)
		{
			if (CheckIsMatchingL(board, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DeleteI({ index1.first, index1.second }, { index1.first, j });
				DeleteL(board, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}

	for (int i = index1.first - 1; i >= 0; i--)
	{
		if (CheckIsMatchingI(board, { i - 1, index1.second }, { index1.first, index1.second }) == true)
		{
			if (CheckIsMatchingL(board, { i, index1.second }, { index2.first, index2.second }) == true)
			{

				if (i != 0)
				{
					DeleteI({ i, index1.second }, { index1.first, index1.second });
					DeleteL(board, { i, index1.second }, { index2.first, index2.second });
				}
				else
				{
					Game::DeleteLine(7 * (index1.second - 1) + 7, 5 * 0 + 0, abs(5 * index1.first) - 2, Vertical);
					if (index1.second < index2.second)
					{
						if (CheckIsMatchingI(board, { 0, index1.second }, { 0, index2.second + 1 }) == true)
						{
							if (CheckIsMatchingI(board, { 0, index2.second }, { index2.first, index2.second }) == true)
							{
								Game::DeleteLine(7 * (index1.second - 1) + 8, (5 * 0 + 0), abs(((7 * (index1.second - 1) + 7) - (7 * (index2.second - 1) + 7))) - 1, Horizontal);
								Game::DeleteLine(7 * (index2.second - 1) + 7, 5 * 0 + 1, abs(((5 * (0 - 1) + 3) - (5 * (index2.first - 1) + 3))) - 3, Vertical);
								return;
							}
						}
					}
					else
					{
						if (CheckIsMatchingI(board, { 0, index2.second - 1 }, { 0, index1.second }) == true)
						{
							if (CheckIsMatchingI(board, { 0, index2.second }, { index2.first, index2.second }) == true)
							{
								Game::DeleteLine(7 * (index2.second - 1) + 8, (5 * 0 + 0), abs(((7 * index1.second + 0) - (7 * index2.second + 0))) - 1, Horizontal);
								Game::DeleteLine(7 * (index2.second - 1) + 7, 5 * 0 + 1, abs(((5 * 0 - 2) - (5 * index2.first - 2))) - 3, Vertical);
								return;
							}
						}
					}
				}
				return;
			}
		}
	}
	for (int i = index1.first + 1; i < numOfRows + 2; i++)
	{
		if (CheckIsMatchingI(board, { index1.first, index1.second }, { i + 1, index1.second }) == true)
		{
			if (CheckIsMatchingL(board, { i, index1.second }, { index2.first, index2.second }) == true)
			{
				DeleteI({ index1.first, index1.second }, { i, index1.second });
				DeleteL(board, { i, index1.second }, { index2.first, index2.second });
				return;
			}
		}
	}
}
//Check is matching
bool Game::IsMatching(Board** board, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	if (CheckIsMatchingI(board, index1, index2) == true || CheckIsMatchingL(board, index1, index2) == true || CheckIsMatchingUAndZ(board, index1, index2, numOfRows, numOfCols) == true)
	{
		return true;
	}
	return false;
}
//Print time during playing game
void Game::PrintTime(tm timeDistance)
{
	Interface::GotoXY(63, 10);
	Interface::SetConsoleColor(BLACK, GREEN);
	cout << "Time: " << setfill('0') << setw(2) << 0 << ":"
		<< setfill('0') << setw(2) << timeDistance.tm_min << ":"
		<< setfill('0') << setw(2) << timeDistance.tm_sec;
	cout.flush();
	Interface::SetConsoleColor(BLUE, YELLOW);
}
//Play game
void Game::MoveCursorGame(Board** board, int row, int col, int& points)
{
	Controller::ShowCursor(false);
	//get the time when the game start
	// Refer to "Nguyen Minh Luan (23127414) and Do Nguyen Minh Tri (23127502)
	time_t timeStart;
	time(&timeStart);
	//Playing game during win or lose
	while (true)
	{
		//If win break away while loop
		if (IsWin(board, row, col) == true)
		{
			Interface::SetMusic(Win);
			break;
		}
		//If lose break away while loop
		if (IsContinue(board, row, col) == false)
		{
			Interface::SetMusic(Lose);
			break;
		}
		//Get the time current
		time_t timeCurr;
		time(&timeCurr);
		//Get the time current - time start 
		time_t Distance;
		Distance = timeCurr - timeStart;
		tm timeDistance;
		localtime_s(&timeDistance, &Distance);
		PrintTime(timeDistance);

		//Find out the first blank in the board
		int i, j;
		bool check = false;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				if (board[i + 1][j + 1].key == 1)
				{
					Interface::GotoXY(7 * j + 7, 5 * i + 3);
					check = true;
				}
				if (check == true) break;
			}
			if (check == true) break;
		}
		//The rectangle with color in this blank
		Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
		//Print character again
		Interface::GotoXY(7 * j + 7, 5 * i + 3);
		Interface::SetConsoleColor(BLUE, YELLOW);
		cout << board[i + 1][j + 1].c;
		int choice;
		bool enter = false;
		Board index[2];
		index[0].index = { -1, -1 };
		//Check any key is pressed
		if (_kbhit())
		{
			//2 Enter
			for (int cnt = 0; cnt < 2; cnt++)
			{
				//Run during click on Enter
				while (true)
				{
					//Get the time current
					time_t timeCurr;
					time(&timeCurr);
					time_t Distance;
					Distance = timeCurr - timeStart;
					tm timeDistance;
					localtime_s(&timeDistance, &Distance);
					PrintTime(timeDistance);
					//Check any key is pressed
					if (_kbhit())
					{
						choice = _getch();
						if (choice == ENTER || choice == m || choice == e)
						{
							break;
						}
						if (choice != ENTER && choice != m)
						{
							choice = _getch();
							Interface::SetMusic(Move);
							break;
						}
					}
				}
				//To continue the time if no event occurs
				while (true)
				{
					if (choice == LeftArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							cout << board[i + 1][j + 1].c << "  ";
						}
						else enter = false;
						j--;
						//Go to edge
						if (j < 0)
						{
							j++;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int left;
						//If in the left, having the button
						for (left = j; left >= 0; left--)
						{
							if (board[i + 1][left + 1].key == 1)
							{
								check = true;
								break;
							}
						}
						//If check is true, go to the rectangle with color to this position
						if (check == true)
						{
							j = left;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						//If check is false
						else
						{
							j++;
							bool CheckPath = false;
							int maxLength = 1000;
							int indexRow = i, indexCol = j;
							//If in the left side, having the button
							for (int tmpRow = 0; tmpRow < row; tmpRow++)
							{
								for (int tmpCol = 0; tmpCol < j; tmpCol++)
								{
									//Go to the nearest button
									if (board[tmpRow + 1][tmpCol + 1].key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
									{
										maxLength = pow(i - tmpRow, 2) + pow(j - tmpCol, 2);
										CheckPath = true;
										indexRow = tmpRow;
										indexCol = tmpCol;
									}
								}
							}
							//If checkPath is true, go to this position
							if (CheckPath == true)
							{
								i = indexRow;
								j = indexCol;
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							//Can't go
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c; // ki tu
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					//Similar to choice equal to left arrow
					else if (choice == RightArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							cout << board[i + 1][j + 1].c << "  ";
						}
						else enter = false;
						j++;
						if (j >= col)
						{
							j--;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int right;
						for (right = j; right < col; right++)
						{
							if (board[i + 1][right + 1].key == 1)
							{
								check = true;
								break;
							}
						}
						if (check == true)
						{
							j = right;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						else
						{
							j--;
							bool CheckPath = false;
							int maxLength = 1000;
							int indexRow = 0, indexCol = 0;
							for (int tmpRow = 0; tmpRow < row; tmpRow++)
							{
								for (int tmpCol = j + 1; tmpCol < col; tmpCol++)
								{
									if (board[tmpRow + 1][tmpCol + 1].key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
									{
										CheckPath = true;
										maxLength = pow(i - tmpRow, 2) + pow(j - tmpCol, 2);
										indexRow = tmpRow;
										indexCol = tmpCol;
									}
								}
							}
							if (CheckPath == true)
							{
								i = indexRow;
								j = indexCol;
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					//Similar to choice equal to left arrow
					else if (choice == UpArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							cout << board[i + 1][j + 1].c << "  ";
						}
						else enter = false;
						i--;
						if (j < 0)
						{
							i++;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int up;
						for (up = i; up >= 0; up--)
						{
							if (board[up + 1][j + 1].key == 1)
							{
								check = true;
								break;
							}
						}
						if (check == true)
						{
							i = up;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						else
						{
							i++;
							bool CheckPath = false;
							int maxLength = 1000;
							int indexRow = 0, indexCol = 0;
							for (int tmpRow = 0; tmpRow < i; tmpRow++)
							{
								for (int tmpCol = 0; tmpCol < col; tmpCol++)
								{
									if (board[tmpRow + 1][tmpCol + 1].key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
									{
										CheckPath = true;
										maxLength = pow(i - tmpRow, 2) + pow(j - tmpCol, 2);
										indexRow = tmpRow;
										indexCol = tmpCol;
									}
								}
							}
							if (CheckPath == true)
							{
								i = indexRow;
								j = indexCol;
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					//Similar to choice equal to left arrow
					else if (choice == DownArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							cout << board[i + 1][j + 1].c << "  ";
						}
						else enter = false;
						i++;
						if (j < 0)
						{
							i--;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int down;
						for (down = i; down < row; down++)
						{
							if (board[down + 1][j + 1].key == 1)
							{
								check = true;
								break;
							}
						}
						if (check == true)
						{
							i = down;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							cout << board[i + 1][j + 1].c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						else
						{
							i--;
							int maxLength = 1000;
							int indexRow = 0, indexCol = 0;
							bool CheckPath = false;
							for (int tmpRow = i + 1; tmpRow < row; tmpRow++)
							{
								for (int tmpCol = 0; tmpCol < col; tmpCol++)
								{
									if (board[tmpRow + 1][tmpCol + 1].key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
									{
										CheckPath = true;
										maxLength = pow(i - tmpRow, 2) + pow(j - tmpCol, 2);
										indexRow = tmpRow;
										indexCol = tmpCol;
									}
								}
							}
							if (CheckPath == true)
							{
								i = indexRow;
								j = indexCol;
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								cout << board[i + 1][j + 1].c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					//If user presses m
					else if (choice == m)
					{
						Interface::SetMusic(Select);
						//Move suggestion
						Game::MoveSuggestion(board, row, col);
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						cout << board[i + 1][j + 1].c;
						//If point >= 2, point - 2
						if (points >= 2)
						{
							points = points - 2;
							Game::PrintScore(points);

						}
						//If point < 2 , point = 0
						else if (points < 2)
						{
							points = 0;
							Game::PrintScore(points);
						}
						Sleep(300);
						//Run time if no event occurs
						while (true)
						{
							//get current time
							time_t timeCurr;
							time(&timeCurr);
							time_t Distance;
							Distance = timeCurr - timeStart;
							tm timeDistance;
							localtime_s(&timeDistance, &Distance);
							PrintTime(timeDistance);
							//If any key is pressed
							if (_kbhit())
							{
								if (choice != ENTER && choice != m)
								{
									choice = _getch();
									break;
								}
								break;
							}
						}
					}
					//If user choose e, the time will be stopped and show the exit board
					else if (choice == e)
					{
						Interface::SetMusic(Select);
						Game::GameExit(board, row, points, timeDistance);
					}
					//If user don't choose Enter
					if (choice != ENTER)
					{
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						cout << board[i + 1][j + 1].c;
						Interface::SetConsoleColor(BLACK, YELLOW);
						//Run time if no event occurs
						while (true)
						{
							time_t timeCurr;
							time(&timeCurr);
							time_t Distance;
							Distance = timeCurr - timeStart;
							tm timeDistance;
							localtime_s(&timeDistance, &Distance);
							PrintTime(timeDistance);
							if (_kbhit())
							{
								choice = _getch();
								break;
							}
						}
					}
					//if click on enter firstly
					else if (choice == ENTER && cnt == 0)
					{
						enter = true;
						//print rectangle with color in this position
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						//print character again
						cout << board[i + 1][j + 1].c;
						Interface::SetMusic(Select);
						Interface::SetConsoleColor(BLACK, YELLOW);
						Sleep(300);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						//update index[0]
						index[0].c = board[i + 1][j + 1].c;
						index[0].coordinate = { 7 * j + 7, 5 * i + 3 };
						index[0].index = { i + 1, j + 1 };
						index[0].key = 1;
						break;
					}
					//if click on enter secondly
					else if (choice == ENTER && cnt == 1)
					{
						enter = true;
						//print rectangle with color in this position
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						//print character again
						cout << board[i + 1][j + 1].c;
						Interface::SetMusic(Select);
						Interface::SetConsoleColor(BLACK, YELLOW);
						Sleep(300);
						Interface::GotoXY(2, 30);
						//update index[1]
						index[1].c = board[i + 1][j + 1].c;
						index[1].coordinate = { 7 * j + 7, 5 * i + 3 };
						index[1].index = { i + 1, j + 1 };
						index[1].key = 1;
						break;
					}
				}
			}
			//If choose 2 button with the same character, have key = 1 and have the different position
			if (index[0].c == index[1].c && index[0].key == 1 && index[1].key == 1 && !(index[0].index.first == index[1].index.first && index[0].index.second == index[1].index.second))
			{
				//If the matching is true
				if (IsMatching(board, index[0].index, index[1].index, row, col) == true)
				{
					//Check each matching to draw arrow
					if (CheckIsMatchingI(board, index[0].index, index[1].index) == true)
					{
						Interface::SetConsoleColor(BLACK, LIGHTRED);
						//Draw I
						DrawI(index[0].index, index[1].index);
						Sleep(300);
						//Delete I after draw
						DeleteI(index[0].index, index[1].index);
						Interface::SetConsoleColor(BLACK, YELLOW);
					}
					else if (CheckIsMatchingL(board, index[0].index, index[1].index) == true)
					{
						Interface::SetConsoleColor(BLACK, LIGHTRED);
						DrawL(board, index[0].index, index[1].index);
						Sleep(300);
						DeleteL(board, index[0].index, index[1].index);
						Interface::SetConsoleColor(BLACK, YELLOW);
					}
					else
					{
						Interface::SetConsoleColor(BLACK, LIGHTRED);
						DrawUAndZ(board, index[0].index, index[1].index, row, col);
						Sleep(300);
						DeleteUAndZ(board, index[0].index, index[1].index, row, col);
						Interface::SetConsoleColor(BLACK, YELLOW);
					}
					//If row = 4 and col = 4, draw board again
					if (row == 4 && col == 4)
					{
						Game::DrawBoard(2, 0, 32, 22);
					}
					else
					{
						Game::DrawBoard(2, 0, 46, 32);
					}
					//Delete two rectangle
					Game::DeleteTwoRectangle(index[0].index, index[1].index, 7, 5);
					//Update key = 0 for 2 button
					board[index[0].index.first][index[0].index.second].key = 0;
					board[index[1].index.first][index[1].index.second].key = 0;
					//Draw background
					DrawBackGround(board, row, col);
					points = points + 10;
					//print score
					Game::PrintScore(points);
				}
				//If the matching is false
				else
				{
					//Delete two rectangle
					Game::DeleteTwoRectangle(index[0].index, index[1].index, 7, 5);
					//Print two rectangle again
					Game::PrintTwoRectangle(index[0].index, index[1].index, 7, 5);
					//Write the first character
					Interface::GotoXY(index[0].coordinate.first, index[0].coordinate.second);
					cout << board[index[0].index.first][index[0].index.second].c;

					//Write the second character
					Interface::GotoXY(7 * j + 7, 5 * i + 3);
					Interface::SetConsoleColor(BLACK, YELLOW);
					cout << board[i + 1][j + 1].c;
					Interface::SetMusic(Error);
					Sleep(200);
					Interface::SetConsoleColor(BLACK, YELLOW);
					if (points >= 5)
					{
						points = points - 5;
						Game::PrintScore(points);
					}
					else if (points < 5)
					{
						points = 0;
						Game::PrintScore(points);
					}
				}
			}
			//If choosing 2 button having difference of character
			else
			{
				//The same as the matching is false
				Game::DeleteTwoRectangle(index[0].index, index[1].index, 7, 5);
				Game::PrintTwoRectangle(index[0].index, index[1].index, 7, 5);
				Interface::GotoXY(index[0].coordinate.first, index[0].coordinate.second);
				cout << board[index[0].index.first][index[0].index.second].c;
				Interface::GotoXY(7 * j + 7, 5 * i + 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				cout << board[i + 1][j + 1].c;
				Interface::SetMusic(Error);
				Sleep(200);
				Interface::SetConsoleColor(BLACK, YELLOW);
				if (points >= 5)
				{
					points = points - 5;
					Game::PrintScore(points);
				}
				else if (points < 5)
				{
					points = 0;
					Game::PrintScore(points);
				}
			}
		}
	}
	//run time if the game finishes
	time_t timeCurr;
	time(&timeCurr);
	time_t Distance;
	Distance = timeCurr - timeStart;
	tm timeDistance;
	localtime_s(&timeDistance, &Distance);
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	//Print win
	if (IsWin(board, row, col) == true)
	{
		Interface::PrintWin(GREEN);
	}
	//Print lose
	else if (IsContinue(board, row, col) == false)
	{
		Interface::PrintLose(GREEN);
	}
	//Delete board 
	DeleteBoard(board, row);
	//Print save game
	Game::PrintSaveGame(points, timeDistance);
}
//Check the game have any buttons. If the board doesn't have button, you win the game
bool Game::IsWin(Board** board, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i + 1][j + 1].key != 0)
			{
				return false;
			}
		}
	}
	return true;
}
//Check all of buttons having 2 button can match, if can't, you lose the game
bool Game::IsContinue(Board** board, int row, int col)
{
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			for (int k = 1; k <= row; k++)
			{
				for (int l = 1; l <= col; l++)
				{
					if (!(i == k && j == l))
					{
						if (board[i][j].key != 0 && board[k][l].key != 0 && board[i][j].c == board[k][l].c)
						{
							if (IsMatching(board, board[i][j].index, board[k][l].index, row, col))
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

//Move suggestion
void Game::MoveSuggestion(Board** board, int row, int col)
{
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			for (int k = 1; k <= row; k++)
			{
				for (int l = 1; l <= col; l++)
				{
					if (!(i == k && j == l))
					{
						if (board[i][j].key != 0 && board[k][l].key != 0 && board[i][j].c == board[k][l].c)
						{
							if (IsMatching(board, board[i][j].index, board[k][l].index, row, col))
							{
								//print background with color
								Controller::PrintRectangleWithBackgroundColor(7 * (j - 1) + 6 - 2, 5 * (i - 1) + 3 - 2, 7, 5, PURPLE);
								Interface::GotoXY(7 * (j - 1) + 7, 5 * (i - 1) + 3);
								Interface::SetConsoleColor(PURPLE, YELLOW);
								cout << board[i][j].c;

								//print background with color
								Controller::PrintRectangleWithBackgroundColor(7 * (l - 1) + 6 - 2, 5 * (k - 1) + 3 - 2, 7, 5, PURPLE);
								Interface::GotoXY(7 * (l - 1) + 7, 5 * (k - 1) + 3);
								Interface::SetConsoleColor(PURPLE, YELLOW);
								cout << board[k][l].c;
								Sleep(500);

								//Delete background after printing
								Controller::DeleteRectangleWithBackgroundColorButText(7 * (j - 1) + 6 - 2, 5 * (i - 1) + 3 - 2, 7 * (j - 1) + 7, 5 * (i - 1) + 3, 7, 5);
								Interface::SetConsoleColor(BLACK, YELLOW);
								Controller::PrintRectangle(7 * (j - 1) + 6 - 2, 5 * (i - 1) + 3 - 2, 7, 5);
								Interface::GotoXY(7 * (j - 1) + 7, 5 * (i - 1) + 3);
								cout << board[i][j].c << "  ";

								//Delete background after printing
								Controller::DeleteRectangleWithBackgroundColorButText(7 * (l - 1) + 6 - 2, 5 * (k - 1) + 3 - 2, 7 * (l - 1) + 7, 5 * (k - 1) + 3, 7, 5);
								Interface::SetConsoleColor(BLACK, YELLOW);
								Controller::PrintRectangle(7 * (l - 1) + 6 - 2, 5 * (k - 1) + 3 - 2, 7, 5);
								Interface::GotoXY(7 * (l - 1) + 7, 5 * (k - 1) + 3);
								cout << board[k][l].c << "  ";
								return;
							}
						}
					}
				}
			}
		}
	}
}
//Delete two rectangle
void Game::DeleteTwoRectangle(pair<int, int>index1, pair<int, int>index2, int width, int height)
{
	// Delete the first rectangle
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Interface::GotoXY((7 * index1.second + 4) - 7 + j, (5 * index1.first + 1) - 5 + i);
			cout << ' ';
		}
	}

	// Delete the second rectangle
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Interface::GotoXY((7 * index2.second + 4) - 7 + j, (5 * index2.first + 1) - 5 + i);
			cout << ' ';
		}
	}
}
//Print 2 rectangles 
void Game::PrintTwoRectangle(pair<int, int>index1, pair<int, int>index2, int width, int height)
{
	//Rectangle 1
	Interface::GotoXY(7 * index1.second + 7 - 10, 5 * index1.first + 3 - 7);
	//print the first row
	putc(218, stdout);
	for (int i = 1; i < width - 1; i++)
	{
		putc(196, stdout);
	}
	putc(191, stdout);
	//print the left row
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(7 * index1.second + 7 - 10, 5 * index1.first + 3 - 7 + i);
		putc(179, stdout);
	}
	Interface::GotoXY(7 * index1.second + 7 - 10, 5 * index1.first + 3 - 7 + height - 1);
	putc(192, stdout);
	//print the last row
	for (int i = 1; i < width - 1; i++)
	{
		putc(196, stdout);
	}
	putc(217, stdout);
	//print the right row
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(7 * index1.second + 7 - 10 + width - 1, 5 * index1.first + 3 - 7 + i);
		putc(179, stdout);
	}
	cout << endl;
	cout << endl;


	//Rectangle 2
	Interface::GotoXY(7 * index2.second + 7 - 10, 5 * index2.first + 3 - 7);
	putc(218, stdout);
	for (int i = 1; i < width - 1; i++)
	{
		putc(196, stdout);
	}
	putc(191, stdout);
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(7 * index2.second + 7 - 10, 5 * index2.first + 3 - 7 + i);
		putc(179, stdout);
	}
	Interface::GotoXY(7 * index2.second + 7 - 10, 5 * index2.first + 3 - 7 + height - 1);
	putc(192, stdout);
	for (int i = 1; i < width - 1; i++)
	{
		putc(196, stdout);
	}
	putc(217, stdout);
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(7 * index2.second + 7 - 10 + width - 1, 5 * index2.first + 3 - 7 + i);
		putc(179, stdout);
	}
	cout << endl;
	cout << endl;

}
//Draw background
void Game::DrawBackGround(Board** board, int row, int col)
{
	if (row == 4 && col == 4)
	{
		char background[50][50] =
		{ "                 ",
		 "                  ",
		 "                  ",
		 "                  ",
		 "                    ____",
		 "            /^\\   / -- )",
		 "           / | \\ (____/",
		 "          / | | \\ / /",
		 "         /_|_|_|_/ /",
		 "          |     / /",
		 " __    __ |    / /__    __  ",
		 "[  ]__[  ].   / /[  ]__[  ]",
		 "|__      ____/ /___     __|",
		 "   |    / .------  )   |    ",
		 "   |   / /        /    |    ",
		 "   |  / /        /     |   ",
		 "  ~~~~~~-----------~~~~~~~ " };
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (board[i + 1][j + 1].key == 0)
				{
					Interface::SetConsoleColor(BLACK, LIGHTGREEN);
					for (int k = 0; k < 5; k++)
					{
						for (int l = 0; l < 7; l++)
						{
							Interface::GotoXY(7 * (j + 1) - 3 + l, 5 * (i + 1) - 4 + k);
							cout << background[5 * i + k][7 * j + l];
						}
					}
					Interface::SetConsoleColor(BLACK, YELLOW);
				}
			}
		}
	}
	else if (row == 6 && col == 6)
	{
		char background[50][50] =
		{ "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "                    ",
		 "         ___    ____",
		 "        /' --;^/ ,-_\\      \\ | /",
		 "       / / --o\\ o-\\ \\\\   --(_)--",
		 "      /-/-/|o|-|\\-\\\\|\\\\   / | \\",
		 "       '`  ` |-|   `` '",
		 "             |-|",
		 "             |-|O",
		 "             |-(\\,__",
		 "          ...|-|\\--,\\_....",
		 "      ,;;;;;;;;;;;;;;;;;;;;;;;;,.",
		 "~~,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;",
		 "~;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;," };
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (board[i + 1][j + 1].key == 0)
				{
					Interface::SetConsoleColor(BLACK, LIGHTGREEN);
					for (int k = 0; k < 5; k++)
					{
						for (int l = 0; l < 7; l++)
						{
							Interface::GotoXY(7 * (j + 1) - 3 + l, 5 * (i + 1) - 4 + k);
							cout << background[5 * i + k][7 * j + l];
						}
					}
					Interface::SetConsoleColor(BLACK, YELLOW);
				}
			}
		}
	}
}
//Delete line
void Game::DeleteLine(int x, int y, int size, int type)
{
	if (type == Horizontal)
	{
		Interface::GotoXY(x, y);
		for (int i = 0; i < size; i++)
		{
			cout << ' ';
		}
	}
	else if (type == Vertical)
	{
		for (int i = 0; i < size; i++)
		{
			Interface::GotoXY(x, y + i);
			cout << ' ';
		}
	}
}
//Delete board
void Game::DeleteBoard(Board**& board, int row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}
//Delete character
void Game::DeleteChar(char**& c, int row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] c[i];
	}
	delete[] c;
}
//Print "Score" word and initialize the score
void Game::Score()
{
	Interface::SetConsoleColor(BLACK, WHITE);
	Controller::PrintRectangle(60, 1, 20, 5);
	Interface::GotoXY(67, 2);
	cout << "SCORE";
	Game::PrintScore(0);
	Interface::SetConsoleColor(BLACK, YELLOW);
}
//Print score
void Game::PrintScore(int points)
{
	Interface::SetConsoleColor(BLACK, WHITE);
	Interface::GotoXY(69, 4);
	cout << "    ";
	Interface::GotoXY(69, 4);
	cout << points;
	Interface::SetConsoleColor(BLACK, YELLOW);
}
//Print "Exit" word
void Game::PrintExit()
{
	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(60, 18, 20, 3);
	Interface::GotoXY(66, 19);
	cout << "E: Exit";
}
//Print exit if user presses e
void Game::GameExit(Board** board, int row, int points, tm timeDistance)
{
	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(54, 24, 32, 7);

	Interface::GotoXY(56, 25);
	cout << "Do you sure you want to exit?";
	Controller::PrintRectangleWithBackgroundColor(59, 27, 7, 3, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(61, 28);
	cout << "YES";

	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(74, 27, 7, 3);
	Interface::GotoXY(76, 28);
	cout << "NO";

	int pos = 61;
	int choice = _getch();
	if (choice != ENTER)
	{
		Interface::SetMusic(Move);
		choice = _getch();
	}
	else if (choice == ENTER)
	{
		Interface::SetMusic(Select);
		Sleep(300);
	}
	while (choice != ENTER)
	{
		if (pos == 61)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(59, 27, 61, 28, 7, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(59, 27, 7, 3);
				Interface::GotoXY(61, 28);
				cout << "YES ";
				pos = 76;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(74, 27, 7, 3, BLUE);
				Interface::GotoXY(pos, 28);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "NO ";
			}
		}
		else if (pos == 76)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(74, 27, 76, 28, 7, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(74, 27, 7, 3);
				Interface::GotoXY(76, 28);
				cout << "NO  ";
				pos = 61;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(59, 27, 7, 3, BLUE);
				Interface::GotoXY(pos, 28);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "YES ";
			}
			else if (choice == RightArrow)
			{
				Interface::SetMusic(Move);
			}
		}
		choice = _getch();
		if (choice != ENTER)
		{
			choice = _getch();
		}
		else if (choice == ENTER)
		{
			Interface::SetMusic(Select);
			Sleep(300);
		}
	}
	switch (pos)
	{
	case 61:
	{
		DeleteBoard(board, row);
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		Game::PrintSaveGame(points, timeDistance);
		break;
	}
	case 76:
	{
		Interface::SetConsoleColor(BLACK, BLACK);
		Controller::DeleteRectangleWithBackgroundColor(54, 24, 32, 7);
		Interface::SetConsoleColor(BLACK, YELLOW);
		break;
	}
	}
}
//Print interface of save game
void Game::PrintSaveGame(int points, tm timeDistance)
{
	Controller::ShowCursor(true);
	Player x[200];
	int cnt;
	ReadFile(x, cnt);
	string name, id, Class;
	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(20, 15, 70, 10);
	Interface::GotoXY(22, 17);
	cout << "Enter your name: ";
	Interface::GotoXY(22, 19);
	cout << "Enter your id: ";
	Interface::GotoXY(22, 21);
	cout << "Enter your class: ";
	Interface::GotoXY(39, 17);
	getline(cin, name);
	Interface::GotoXY(37, 19);
	getline(cin, id);
	Interface::GotoXY(40, 21);
	getline(cin, Class);

	//Update the record
	bool IsExist = false;
	for (int i = 0; i < cnt; i++)
	{
		//If the basic information is existed
		if (x[i].Name == name && x[i].Id == id && x[i].Class == Class)
		{
			IsExist = true;
			//Update if your record now is better than this previous
			if (points > x[i].score)
			{
				x[i].score = points;
				x[i].record.minute = timeDistance.tm_min;
				x[i].record.second = timeDistance.tm_sec;
			}
			else if (points == x[i].score)
			{
				if (timeDistance.tm_min < x[i].record.minute)
				{
					x[i].record.minute = timeDistance.tm_min;
					x[i].record.second = timeDistance.tm_sec;
				}
				else if (timeDistance.tm_min == x[i].record.minute)
				{
					if (timeDistance.tm_sec < x[i].record.second)
					{
						x[i].record.second = timeDistance.tm_sec;
					}
				}
			}
		}
	}
	//If the basic information isn't existed
	if (IsExist == false)
	{
		//If user can't input 1 of three basic information
		if (name.empty() || id.empty() || Class.empty())
		{
			x[cnt].Name = "UNKNOWN";
			x[cnt].Id = "UNKNOWN";
			x[cnt].Class = "UNKNOWN";
		}
		else
		{
			x[cnt].Name = name;
			x[cnt].Id = id;
			x[cnt].Class = Class;
		}
		x[cnt].score = points;
		x[cnt].record.second = timeDistance.tm_sec;
		x[cnt].record.minute = timeDistance.tm_min;
		x[cnt].record.hour = 0;
		cnt++;
	}
	//Write to the file
	WriteFile(x, cnt);
	Controller::DeleteRectangleWithBackgroundColor(21, 16, 68, 8);
	Interface::GotoXY(40, 17);
	cout << "Information saved succesfully";
	Interface::SetMusic(Select);

	Controller::ShowCursor(false);
	Controller::PrintRectangleWithBackgroundColor(48, 19, 10, 5, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(49, 21);
	cout << "Continue";
	int choice = _getch();
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	Interface::SetInterface();
}
//Print rectangle containing "Move suggestion" word
void Game::MoveSuggestionRectangle()
{
	Interface::SetConsoleColor(BLACK, PURPLE);
	Controller::PrintRectangle(60, 13, 20, 3);
	Interface::GotoXY(61, 14);
	cout << "M: Move suggestion";
	Interface::SetConsoleColor(BLACK, YELLOW);
}
//Print "Time" word
void Game::Time()
{
	Interface::SetConsoleColor(BLACK, WHITE);
	Controller::PrintRectangle(60, 7, 20, 5);
	Interface::GotoXY(68, 8);
	cout << "TIME";
	Interface::SetConsoleColor(BLACK, YELLOW);
}