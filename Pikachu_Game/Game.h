#pragma once
using namespace std;
#include<utility>
struct Board
{
	pair<int, int>index;
	pair<int, int>coordinate;                            //All of references is appeared in our report
	char c;
	int key;

};
struct Node
{
	Board data;
	Node* next;
};
struct Game
{
	static void CreateBoard(Board**& board, char**& c, int row, int col);
	static void DrawButton(int row, int col);
	static void DrawBoard(int x, int y, int width, int height);
	static void AddCharToButton(char**& c, int row, int col);
	static bool IsMatching(Board** board, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols);
	static bool IsWin(Board** board, int row, int col);
	static void MoveSuggestion(Board** board, int row, int col);
	static void DeleteTwoRectangle(pair<int, int>index1, pair<int, int>index2, int width, int height);
	static void	PrintTwoRectangle(pair<int, int>index1, pair<int, int>index2, int width, int height);
	static void PrintTime(tm Distance);
	static void MoveCursorGame(Board** board, int row, int col, int& points);
	static void DeleteLine(int x, int y, int size, int type);
	static void DrawBackGround(Board** board, int row, int col);
	static void DeleteBoard(Board**& board, int row);
	static void DeleteChar(char**& c, int row);
	static void PrintScore(int points);
	static void PrintExit();
	static void GameExit(Board** board, int row, int points, tm timeDistance);
	static void PrintSaveGame(int points, tm timeDistance);
	static void Score();
	static void MoveSuggestionRectangle();
	static void Time();
	static bool IsContinue(Board** board, int row, int col);
};
void DrawI(pair<int, int>index1, pair<int, int>index2);
void DeleteI(pair<int, int>index1, pair<int, int>index2);
void MoveCursorGameLinkedList(Node**& list, int row, int col, int points);
Node* CreateNode(Board board);
Node** CreateList(char**& c, int row, int col);
void AddTail(Node*& pHead, Board board);
Node* GetNode(Node** list, int indexRow, int indexCol);
void DeleteNode(Node**& list, int row, int col);
void GameExitLinkedList(Node**& list, int row, int col, int points, tm timeDistance);
