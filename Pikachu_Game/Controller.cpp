//Moi Sua 
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include"Interface.h"
#include"Controller.h"
#include"Game.h"
#include<utility>
#include <thread>
#include <atomic>
#include <iomanip>
using namespace std;

//Choose one of three mode game(Easy, Medium, Hard)
int Controller::PlayMode()
{
	Controller::PrintRectangle(12, 15, 110, 15);
	Controller::PrintRectangle(49, 19, 14, 7);
	Controller::PrintRectangle(75, 19, 14, 7);
	Controller::PrintRectangle(102, 19, 14, 7);

	Controller::PrintRectangleWithBackgroundColor(22, 19, 14, 7, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(27, 22);
	cout << "EASY";
	Interface::SetConsoleColor(BLACK, YELLOW);
	Interface::GotoXY(53, 22);
	cout << "MEDIUM";
	Interface::GotoXY(80, 22);
	cout << "HARD";
	Interface::GotoXY(107, 22);
	cout << "BACK";
	int choice = _getch();
	int pos = 27;
	if (choice == ENTER)
	{
		Interface::SetMusic(Select);
		Sleep(300);
	}
	else
	{
		choice = _getch();
		Interface::SetMusic(Move);
	}
	while (choice != ENTER)
	{
		if (pos == 27)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(22, 19, 27, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(22, 19, 14, 7);
				Interface::GotoXY(27, 22);
				cout << "EASY";
				pos = 57;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(49, 19, 14, 7, BLUE);
				Interface::GotoXY(53, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "MEDIUM";
			}
		}
		else if (pos == 57)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(49, 19, 53, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(49, 19, 14, 7);
				Interface::GotoXY(53, 22);
				cout << "MEDIUM";
				pos = 27;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(22, 19, 14, 7, BLUE);
				Interface::GotoXY(27, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "EASY";
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(49, 19, 53, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(49, 19, 14, 7);
				Interface::GotoXY(53, 22);
				cout << "MEDIUM";
				pos = 87;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(75, 19, 14, 7, BLUE);
				Interface::GotoXY(80, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "HARD";
			}
		}
		else if (pos == 87)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(75, 19, 80, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(75, 19, 14, 7);
				Interface::GotoXY(80, 22);
				cout << "HARD";
				pos = 57;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(49, 19, 14, 7, BLUE);
				Interface::GotoXY(53, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "MEDIUM";
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(75, 19, 80, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(75, 19, 14, 7);
				Interface::GotoXY(80, 22);
				cout << "HARD";
				pos = 112;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(102, 19, 14, 7, BLUE);
				Interface::GotoXY(107, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "BACK";
			}
		}
		else if (pos == 112)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(102, 19, 107, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(102, 19, 14, 7);
				Interface::GotoXY(107, 22);
				cout << "BACK";
				pos = 87;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(75, 19, 14, 7, BLUE);
				Interface::GotoXY(80, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "HARD";
			}
			else
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
	case 27:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		return EASY;
		break;
	}
	case 57:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		return MEDIUM;
		break;
	}
	case 87:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		return HARD;
		break;
	}
	case 112:
	{

		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		Interface::SetConsoleColor(BLACK, YELLOW);
		Interface::SetInterface();
		return 0;
		break;
	}
	}
}
//Play the game with mode you choose
void Controller::Play()
{
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	Interface::SetConsoleColor(BLACK, YELLOW);
	char** c = NULL;
	Board** board = NULL;
	Node** list = NULL;
	int points = 0;
	int Mode = PlayMode();
	if (Mode == EASY)
	{
		//Draw button
		Game::DrawButton(4, 4);
		//Add character, key, index, position to button
		Game::CreateBoard(board, c, 4, 4);
		//Draw the rectangle enclosing the board
		Game::DrawBoard(2, 0, 32, 22);
		//Draw the rectangle enclosing the record such as time, score
		Game::DrawBoard(57, 0, 26, 22);
		//Print "Score" word and initialize the score equal to 0
		Game::Score();
		//Print score 
		Game::PrintScore(points);
		//Print "Time" word
		Game::Time();
		//Print rectangle of move suggestion
		Game::MoveSuggestionRectangle();
		//Print "Exit" word
		Game::PrintExit();
		//Set the game and play 
		Game::MoveCursorGame(board, 4, 4, points);
	}
	else if (Mode == MEDIUM)
	{
		Game::DrawButton(6, 6);
		Game::CreateBoard(board, c, 6, 6);
		Game::DrawBoard(2, 0, 46, 32);
		Game::DrawBoard(57, 0, 26, 22);
		Game::Score();
		Game::PrintScore(points);
		Game::Time();
		Game::MoveSuggestionRectangle();
		Game::PrintExit();
		Game::MoveCursorGame(board, 6, 6, points);
	}
	else if (Mode == HARD)
	{
		Game::DrawButton(6, 6);
		list = CreateList(c, 6, 6);
		Game::DrawBoard(2, 0, 46, 32);
		Game::DrawBoard(57, 0, 26, 22);
		Game::Score();
		Game::PrintScore(points);
		Game::Time();
		Game::MoveSuggestionRectangle();
		Game::PrintExit();
		MoveCursorGameLinkedList(list, 6, 6, points);
	}
	else if (Mode == 0)
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		Interface::SetConsoleColor(BLACK, YELLOW);
		//Return to menu
		Interface::SetInterface();
	}
}
//Set leaderboard 
void Controller::Rank(int page)
{
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	Interface::SetConsoleColor(BLACK, YELLOW);
	Player x[100];
	int cnt;
	ReadFile(x, cnt);
	SortRank(x, cnt);
	WriteFile(x, cnt);
	//Print Leaderboard word by using ASCII
	Interface::GotoXY(30, 0);
	cout << R"(/================================================================\)" << endl;
	Interface::GotoXY(30, 1);
	cout << R"(|| _                   _           ____                      _  ||)" << endl;
	Interface::GotoXY(30, 2);
	cout << R"(||| |    ___  __ _  __| | ___ _ __| __ )  ___   __ _ _ __ __| | ||)" << endl;
	Interface::GotoXY(30, 3);
	cout << R"(||| |   / _ \/ _` |/ _` |/ _ \ '__|  _ \ / _ \ / _` | '__/ _` | ||)" << endl;
	Interface::GotoXY(30, 4);
	cout << R"(||| |__|  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| | ||)" << endl;
	Interface::GotoXY(30, 5);
	cout << R"(|||_____\___|\__,_|\__,_|\___|_|  |____/ \___/ \__,_|_|  \__,_| ||)" << endl;
	Interface::GotoXY(30, 6);
	cout << R"(\================================================================/)" << endl;

	//Design the leaderboard
	PrintRectangle(4, 8, 123, 5);
	PrintLine(9, 9, 4, Vertical);
	Interface::GotoXY(9, 8);
	putc(194, stdout);
	Interface::GotoXY(9, 12);
	putc(193, stdout);

	Interface::GotoXY(5, 10);
	cout << "Rank";
	for (int i = 1; i < 5; i++)
	{
		PrintLine(12 + 23 * i, 9, 4, Vertical);
		Interface::GotoXY(12 + 23 * i, 8);
		putc(194, stdout);
		Interface::GotoXY(12 + 23 * i, 12);
		putc(193, stdout);
	}
	Interface::GotoXY(20, 10);
	cout << "NAME";
	Interface::GotoXY(47, 10);
	cout << "ID";
	Interface::GotoXY(68, 10);
	cout << "CLASS";
	Interface::GotoXY(91, 10);
	cout << "SCORE";
	Interface::GotoXY(114, 10);
	cout << "TIME";

	//Create Rectangle
	PrintRectangle(4, 14, 123, 22);

	PrintLine(9, 15, 21, Vertical);
	Interface::GotoXY(9, 14);
	putc(194, stdout);
	Interface::GotoXY(9, 35);
	putc(193, stdout);

	for (int i = 1; i < 5; i++)
	{
		PrintLine(12 + 23 * i, 15, 21, Vertical);
		Interface::GotoXY(12 + 23 * i, 14);
		putc(194, stdout);
		Interface::GotoXY(12 + 23 * i, 35);
		putc(193, stdout);
	}
	//Design Back and Next
	Controller::PrintRectangleWithBackgroundColor(47, 37, 10, 3, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(50, 38);
	cout << "BACK";
	Interface::SetConsoleColor(BLACK, YELLOW);
	PrintRectangle(67, 37, 15, 3);
	Interface::GotoXY(70, 38);
	cout << "NEXT PAGE";
	Interface::SetConsoleColor(BLACK, YELLOW);

	for (int i = 0; i < 6; i++)
	{
		PrintLine(5, 17 + i * 3, 121, Horizontal);
		for (int j = 0; j < 6; j++)
		{
			Interface::GotoXY(9, 17 + j * 3);
			putc(197, stdout);
		}
		for (int j = 0; j < 4; j++)
		{
			Interface::GotoXY(35 + j * 23, 17 + i * 3);
			putc(197, stdout);
		}
	}
	for (int i = 0; i < 6; i++)
	{
		Interface::GotoXY(4, 17 + i * 3);
		putc(195, stdout);
		Interface::GotoXY(126, 17 + i * 3);
		putc(180, stdout);
	}
	//Print player 
	for (int i = 0; i < 7; i++)
	{
		if (x[i + (page - 1) * 7].record.hour == 0 && x[i + (page - 1) * 7].record.minute == 0 && x[i + (page - 1) * 7].record.second == 0)
		{
			continue;
		}
		Interface::GotoXY(6, 16 + i * 3);
		cout << (i + 1) + (page - 1) * 7;
		Interface::GotoXY(11, 16 + i * 3);
		cout << x[i + (page - 1) * 7].Name;
		Interface::GotoXY(37, 16 + i * 3);
		cout << x[i + (page - 1) * 7].Id;
		Interface::GotoXY(60, 16 + i * 3);
		cout << x[i + (page - 1) * 7].Class;
		Interface::GotoXY(83, 16 + i * 3);
		cout << x[i + (page - 1) * 7].score;
		Interface::GotoXY(106, 16 + i * 3);
		cout << setfill('0') << setw(2) << x[i + (page - 1) * 7].record.hour << ":"
			<< setfill('0') << setw(2) << x[i + (page - 1) * 7].record.minute << ":"
			<< setfill('0') << setw(2) << x[i + (page - 1) * 7].record.second;
	}
	Interface::GotoXY(52, 38);
	int pos = 50;
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
		if (pos == 50)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 38);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(47, 37, 44, 23, 11, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(47, 37, 10, 3);
				Interface::GotoXY(50, 38);
				cout << "BACK";
				pos = 70;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(67, 37, 15, 3, BLUE);
				Interface::GotoXY(70, 38);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "NEXT PAGE ";
			}
		}
		else if (pos == 70)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(67, 37, 70, 38, 15, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(67, 37, 15, 3);
				Interface::GotoXY(70, 38);
				cout << "NEXT PAGE";
				pos = 70;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(47, 37, 10, 3, BLUE);
				Interface::GotoXY(50, 38);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "BACK ";
				pos = 50;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 38);
			}
			else if (choice == RightArrow)
			{
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 38);
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
	case 50:
	{
		system("cls");
		//If page == 0 return to m
		if (page - 1 == 0)
		{
			system("cls");
			Interface::SetInterface();
		}
		//Go to previous page
		else
		{
			system("cls");
			Rank(page - 1);
		}
	}break;
	//Go to next page
	case 70:
	{
		system("cls");
		Rank(page + 1);
	}break;
	}
}
//Set and Design help
void Controller::Help()
{
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	Interface::SetConsoleColor(BLACK, YELLOW);
	Interface::GotoXY(1, 1);

	Controller::PrintRectangle(1, 1, 130, 3);
	Interface::GotoXY(2, 2);
	cout << "Goal: Match pairs of the same pictures to clear the board.";
	Controller::PrintRectangle(1, 4, 130, 6);
	Interface::GotoXY(2, 5);
	cout << "How to Play:";
	Interface::GotoXY(2, 6);
	cout << "You'll see a board with lots of squares, each with different pictures.";
	Interface::GotoXY(2, 7);
	cout << "Click on one square, then click on another to see if they match.";
	Interface::GotoXY(2, 8);
	cout << "Keep matching pairs until the board is clear.";

	Controller::PrintRectangle(1, 10, 130, 8);
	Interface::GotoXY(2, 11);
	cout << "Moves:";
	Interface::GotoXY(2, 12);
	cout << "Up arrow: Move up";
	Interface::GotoXY(2, 13);
	cout << "Down arrow: Move down";
	Interface::GotoXY(2, 14);
	cout << "Right arrow: Move right";
	Interface::GotoXY(2, 15);
	cout << "Left arrow: Move left";
	Interface::GotoXY(2, 16);
	cout << "Enter : Choose";

	Controller::PrintRectangle(1, 18, 130, 5);
	Interface::GotoXY(2, 19);
	cout << "Rules :";
	Interface::GotoXY(2, 20);
	cout << "You can only match squares that are next to each other or have a clear path with no more than two turns.";
	Interface::GotoXY(2, 21);
	cout << "If you can't find any more matches, the game ends.";

	Controller::PrintRectangle(1, 23, 130, 5);
	Interface::GotoXY(2, 24);
	cout << "Developers :";
	Interface::GotoXY(2, 25);
	cout << "23127541 - Nguyen Duc Tri";
	Interface::GotoXY(2, 26);
	cout << "23127504 - Doan Pham Minh Triet";

	Interface::GotoXY(45, 29);
	cout << "That's it! Have fun playing Pikachu Classic!";

	Controller::PrintRectangleWithBackgroundColor(62, 31, 10, 3, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(65, 32);
	cout << "BACK";

	int choice = _getch();
	if (choice == ENTER)
	{
		Interface::SetMusic(Select);
		Sleep(300);
		Interface::SetConsoleColor(BLACK, BLACK);
		system("cls");
		Interface::SetConsoleColor(BLACK, BLACK);
		Interface::SetInterface();
	}
}
//Set and design exit
void Controller::Exit()
{
	Interface::SetConsoleColor(BLACK, BLACK);
	system("cls");
	Interface::SetConsoleColor(BLACK, YELLOW);
	PrintRectangle(20, 15, 90, 15);

	Interface::GotoXY(50, 17);
	cout << "Do you sure you want to exit?";
	Controller::PrintRectangleWithBackgroundColor(40, 21, 11, 5, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(44, 23);
	cout << "YES";

	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(81, 21, 10, 5);
	Interface::GotoXY(85, 23);
	cout << "NO";

	Interface::GotoXY(45, 23);
	int pos = 45;
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
		if (pos == 45)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 23);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(40, 21, 44, 23, 11, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(40, 21, 11, 5);
				Interface::GotoXY(44, 23);
				cout << "YES ";
				pos = 84;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 23);
				Controller::PrintRectangleWithBackgroundColor(80, 21, 11, 5, BLUE);
				Interface::GotoXY(84, 23);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "NO ";
			}
		}
		else if (pos == 84)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(80, 21, 84, 23, 11, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(80, 21, 11, 5);
				Interface::GotoXY(84, 23);
				cout << "NO  ";
				pos = 45;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 23);
				Controller::PrintRectangleWithBackgroundColor(40, 21, 11, 5, BLUE);
				Controller::WriteMenuAgain(pos, 23, BLACK, YELLOW);
				Interface::GotoXY(44, 23);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "YES ";
			}
			else if (choice == RightArrow)
			{
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 23);
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
	case 45:
	{
		exit(1);
	}
	case 84:
	{
		Interface::SetConsoleColor(BLACK, BLACK);
		system("cls");
		Interface::SetInterface();
	}break;
	}
}
//Set and design setting
void Controller::Setting()
{
	ShowCursor(false);
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	PrintRectangle(12, 15, 110, 15);

	PrintRectangle(49, 19, 15, 7);
	PrintRectangle(75, 19, 17, 7);
	PrintRectangle(102, 19, 14, 7);

	Controller::PrintRectangleWithBackgroundColor(22, 19, 15, 7, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(24, 22);
	if (FullScreen == false)
	{
		cout << "FULL SCREEN";
	}
	else
	{
		cout << "  MINIMIZE";
	}
	Interface::SetConsoleColor(BLACK, YELLOW);
	Interface::GotoXY(52, 22);
	if (Music == false)
	{
		cout << "  MUSIC";
	}
	else
	{
		cout << "NOT MUSIC";
	}
	Interface::SetConsoleColor(BLACK, YELLOW);
	Interface::GotoXY(76, 22);
	cout << "CHANGE PASSWORD";

	Interface::SetConsoleColor(BLACK, YELLOW);
	Interface::GotoXY(107, 22);
	cout << "BACK";
	int choice = _getch();
	int pos = 27;
	if (choice == ENTER)
	{
		Interface::SetMusic(Select);
		Sleep(300);
	}
	else
	{
		choice = _getch();
		Interface::SetMusic(Move);
	}
	while (choice != ENTER)
	{
		if (pos == 27)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(22, 19, 24, 22, 15, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(22, 19, 15, 7);
				Interface::GotoXY(24, 22);
				if (FullScreen == false)
				{
					cout << "FULL SCREEN";
				}
				else
				{
					cout << "  MINIMIZE";
				}
				pos = 57;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
				Controller::PrintRectangleWithBackgroundColor(49, 19, 15, 7, BLUE);
				Interface::GotoXY(52, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				if (Music == true)
				{
					cout << "NOT MUSIC";
				}
				else
				{
					cout << "  MUSIC";
				}
			}
		}
		else if (pos == 57)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(49, 19, 52, 22, 15, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(49, 19, 15, 7);
				Interface::GotoXY(52, 22);
				if (Music == true)
				{
					cout << "NOT MUSIC";
				}
				else
				{
					cout << "  MUSIC";
				}
				pos = 27;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
				Controller::PrintRectangleWithBackgroundColor(22, 19, 15, 7, BLUE);
				Interface::GotoXY(24, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				if (FullScreen == false)
				{
					cout << "FULL SCREEN";
				}
				else
				{
					cout << "  MINIMIZE";
				}
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(49, 19, 52, 22, 15, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(49, 19, 15, 7);
				Interface::GotoXY(52, 22);
				if (Music == true)
				{
					cout << "NOT MUSIC";
				}
				else
				{
					cout << "  MUSIC";
				}
				pos = 87;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
				Controller::PrintRectangleWithBackgroundColor(75, 19, 17, 7, BLUE);
				Interface::GotoXY(76, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "CHANGE PASSWORD";
			}
		}
		else if (pos == 87)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(75, 19, 76, 22, 17, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(75, 19, 17, 7);
				Interface::GotoXY(76, 22);
				cout << "CHANGE PASSWORD";
				pos = 57;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
				Controller::PrintRectangleWithBackgroundColor(49, 19, 15, 7, BLUE);
				Interface::GotoXY(52, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				if (Music == true)
				{
					cout << "NOT MUSIC";
				}
				else
				{
					cout << "  MUSIC";
				}
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(75, 19, 76, 22, 17, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(75, 19, 17, 7);
				Interface::GotoXY(76, 22);
				cout << "CHANGE PASSWORD";
				pos = 112;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
				Controller::PrintRectangleWithBackgroundColor(102, 19, 14, 7, BLUE);
				Interface::GotoXY(107, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "BACK";
			}
		}
		else if (pos == 112)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(102, 19, 107, 22, 14, 7);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(102, 19, 14, 7);
				Interface::GotoXY(107, 22);
				cout << "BACK";
				pos = 87;
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
				Controller::PrintRectangleWithBackgroundColor(75, 19, 17, 7, BLUE);
				Interface::GotoXY(76, 22);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "CHANGE PASSWORD";
			}
			else
			{
				Interface::SetMusic(Move);
				Interface::GotoXY(pos, 22);
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
	case 27:
	{
		if (FullScreen == false)
		{
			Interface::SetConsoleColor(BLACK, YELLOW);
			Interface::FullScreenWindow();
			FullScreen = true;
			Setting();
		}
		else
		{
			Interface::SetConsoleColor(BLACK, YELLOW);
			Interface::CenterWindow();
			FullScreen = false;
			Setting();
		}
	}break;
	case 57:
	{
		if (Music == false)
		{
			Music = true;
			Setting();
		}
		else
		{
			Music = false;
			Setting();
		}
	}break;
	case 87:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		Interface::SetConsoleColor(BLACK, YELLOW);
		Account x[200];
		int cnt;
		ReadFileAccount(x, cnt);
		ChangePassword(x, cnt);
	}break;
	case 112:
	{

		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		Interface::SetConsoleColor(BLACK, YELLOW);
		Interface::SetInterface();
	}break;
	}
}
//Print line with specific type and size
void Controller::PrintLine(int x, int y, int size, int type)
{
	if (type == Horizontal)
	{
		Interface::GotoXY(x, y);
		for (int i = 0; i < size; i++)
		{
			putc(196, stdout);
		}
	}
	else if (type == Vertical)
	{
		for (int i = 0; i < size; i++)
		{
			Interface::GotoXY(x, y + i);
			putc(179, stdout);
		}
	}
}
//Print rectangle
void Controller::PrintRectangle(int x, int y, int width, int height)
{
	Interface::GotoXY(x, y);
	//Draw first row of rectangle
	putc(218, stdout);
	for (int i = 1; i < width - 1; i++)
	{
		putc(196, stdout);
	}
	putc(191, stdout);

	//Draw left row of rectangle
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(x, y + i);
		putc(179, stdout);
	}
	Interface::GotoXY(x, y + height - 1);
	putc(192, stdout);

	//Draw last row of rectangle
	for (int i = 1; i < width - 1; i++)
	{
		putc(196, stdout);
	}
	putc(217, stdout);

	//Draw right row of rectangle 
	for (int i = 1; i < height - 1; i++)
	{
		Interface::GotoXY(x + width - 1, y + i);
		putc(179, stdout);
	}
	cout << endl;
	cout << endl;
}
//Print rectangle with color
void Controller::PrintRectangleWithBackgroundColor(int x, int y, int width, int height, int backgroundColor)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Interface::GotoXY(x + j, y + i);
			SetConsoleTextAttribute(stdOut, backgroundColor * 16 + BLACK);
			cout << ' ';
		}
	}
	SetConsoleTextAttribute(stdOut, 15);
}
//Delete rectangle with background color
void Controller::DeleteRectangleWithBackgroundColor(int x, int y, int width, int height)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Interface::GotoXY(x + j, y + i);
			cout << ' ';
		}
	}
}
//Delete rectangle with color without text
void Controller::DeleteRectangleWithBackgroundColorButText(int x, int y, int xText, int yText, int width, int height)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (!(x + j >= xText && x + j < xText + 4 && y + i == yText))
			{
				Interface::GotoXY(x + j, y + i);
				SetConsoleTextAttribute(stdOut, BLACK * 16 + WHITE);
				cout << ' ';
			}
		}
	}
}
//Write menu again
void Controller::WriteMenuAgain(int x, int y, int backgroundColor, int textColor)
{
	Interface::GotoXY(x, y);
	SetConsoleTextAttribute(stdOut, backgroundColor * 16 + textColor);
	if (y == 28) cout << "PLAY";
	else if (y == 31) cout << "RANK";
	else if (y == 34) cout << "HELP";
	else if (y == 40) cout << "EXIT";
}
//Show cursor
void Controller::ShowCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(stdOut, &info);
}
//Move cursor for menu(Play, Rank, Help, Setting, Exit)
void Controller::MoveCursor()
{
	Interface::SetConsoleColor(BLACK, BLACK);
	ShowCursor(false);
	Interface::GotoXY(65, 28);
	Controller::PrintRectangleWithBackgroundColor(64 - 2, 28 - 1, 10, 3, BLUE);
	Controller::WriteMenuAgain(65, 28, BLUE, YELLOW);
	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(64 - 2, 31 - 1, 10, 3);
	Controller::PrintRectangle(64 - 2, 34 - 1, 10, 3);
	Controller::PrintRectangle(64 - 2, 37 - 1, 10, 3);
	Controller::PrintRectangle(64 - 2, 40 - 1, 10, 3);
	int pos = 28;
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
		if (pos == 28)
		{
			if (choice == DownArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 65, pos, 10, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(64 - 2, pos - 1, 10, 3);
				Controller::WriteMenuAgain(65, pos, BLACK, YELLOW);
				pos += 3;
				Interface::SetMusic(Move);
				Interface::GotoXY(65, pos);
				Controller::PrintRectangleWithBackgroundColor(64 - 2, pos - 1, 10, 3, BLUE);
				Controller::WriteMenuAgain(65, pos, BLUE, YELLOW);
			}
			else if (choice == UpArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 65, pos, 10, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(64 - 2, pos - 1, 10, 3);
				Controller::WriteMenuAgain(65, pos, BLACK, YELLOW);
				pos = 28;
				Interface::SetMusic(Move);
				Interface::GotoXY(65, pos);
				Controller::PrintRectangleWithBackgroundColor(64 - 2, pos - 1, 10, 3, BLUE);
				Controller::WriteMenuAgain(65, pos, BLUE, YELLOW);
			}
		}
		else if (pos > 28 && pos < 40)
		{
			if (choice == UpArrow)
			{
				if (pos == 37)
				{
					Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 64, pos, 10, 3);
				}
				if (pos != 37)
				{
					Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 65, pos, 10, 3);
				}
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(64 - 2, pos - 1, 10, 3);
				if (pos != 37)
				{
					Controller::WriteMenuAgain(65, pos, BLACK, YELLOW);
				}
				if (pos == 37)
				{
					Interface::GotoXY(64, pos);
					Interface::SetConsoleColor(BLACK, YELLOW);
					cout << "SETTING";
				}
				pos -= 3;
				Interface::SetMusic(Move);
				Interface::GotoXY(65, pos);
				Controller::PrintRectangleWithBackgroundColor(64 - 2, pos - 1, 10, 3, BLUE);
				Controller::WriteMenuAgain(65, pos, BLUE, YELLOW);
			}
			else if (choice == DownArrow)
			{
				if (pos == 37)
				{
					Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 64, pos, 10, 3);
				}
				if (pos != 37)
				{
					Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 65, pos, 10, 3);
				}
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(64 - 2, pos - 1, 10, 3);
				Controller::WriteMenuAgain(65, pos, BLACK, YELLOW);
				if (pos == 37)
				{
					Interface::GotoXY(64, pos);
					Interface::SetConsoleColor(BLACK, YELLOW);
					cout << "SETTING";
				}
				pos += 3;
				Interface::SetMusic(Move);
				Interface::GotoXY(65, pos);
				Controller::PrintRectangleWithBackgroundColor(64 - 2, pos - 1, 10, 3, BLUE);
				Controller::WriteMenuAgain(65, pos, BLUE, YELLOW);
				if (pos == 37)
				{
					Interface::GotoXY(64, pos);
					Interface::SetConsoleColor(BLUE, YELLOW);
					cout << "SETTING";
				}
			}
		}
		else if (pos == 40)
		{
			if (choice == UpArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 65, pos, 10, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(64 - 2, pos - 1, 10, 3);
				Controller::WriteMenuAgain(65, pos, BLACK, YELLOW);
				pos -= 3;
				Interface::SetMusic(Move);
				Interface::GotoXY(65, pos);
				Controller::PrintRectangleWithBackgroundColor(64 - 2, pos - 1, 10, 3, BLUE);
				Controller::WriteMenuAgain(65, pos, BLUE, YELLOW);
				Interface::GotoXY(64, pos);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "SETTING";
			}
			else if (choice == DownArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(64 - 2, pos - 1, 65, pos, 10, 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(64 - 2, pos - 1, 10, 3);
				Controller::WriteMenuAgain(65, pos, BLACK, YELLOW);
				pos = 40;
				Interface::SetMusic(Move);
				Interface::GotoXY(65, pos);
				Controller::PrintRectangleWithBackgroundColor(64 - 2, pos - 1, 10, 3, BLUE);
				Controller::WriteMenuAgain(65, pos, BLUE, YELLOW);
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
	case 28:
		Play();
		break;
	case 31:
		Rank(1);
		break;
	case 34:
		Help();
		break;
	case 37:
		Setting();
		break;
	case 40:
		Exit();
		break;
	}
}

