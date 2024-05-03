#include<iostream>
#include<conio.h>
#include"Interface.h"
#include"Controller.h"
#include"Game.h"
using namespace std;

//Delete button 
void DeleteButton(Node** list, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//Get node with specific index row and col
			Node* pCurr = GetNode(list, i + 1, j + 1);
			if (pCurr->data.key == 0)
			{
				Controller::DeleteRectangleWithBackgroundColor(7 * j + 4, 5 * i + 1, 7, 5);
				Interface::GotoXY(7 * j + 7, 5 * i + 3);
			}
		}
	}
}
//Draw button again
void DrawButtonAgain(Node** list, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Node* pCurr = GetNode(list, i + 1, j + 1);
			if (pCurr->data.key == 1)
			{
				Controller::PrintRectangle(7 * j + 4, 5 * i + 1, 7, 5);
				Interface::GotoXY(7 * j + 7, 5 * i + 3);
				cout << pCurr->data.c;
			}
		}
	}
}
//Create list with board data containing key, character, coordinate, index
Node** CreateList(char**& c, int row, int col)
{
	Game::AddCharToButton(c, row, col);
	Node** newNode = new Node * [row + 2];
	for (int i = 0; i < row + 2; i++)
	{
		newNode[i] = NULL;
	}
	for (int i = 0; i <= row + 1; i++)
	{
		for (int j = 0; j <= col + 1; j++)
		{
			Board board;
			if (i == 0 || j == 0 || i == row + 1 || j == col + 1)
			{
				board.c = ' ';
				board.coordinate = { -1, -1 };
				board.index = { -1, -1 };
				board.key = 0;
			}
			else
			{
				board.c = c[i - 1][j - 1];
				board.index = { i, j };
				board.coordinate = { 7 * (j - 1) + 7, 5 * (i - 1) + 3 };
				board.key = 1;
			}
			//Add tail of node
			AddTail(newNode[i], board);
		}
	}
	return newNode;
}
//Create node
Node* CreateNode(Board board)
{
	Node* newNode = new Node;
	newNode->data = board;
	newNode->next = NULL;
	return newNode;
}
//Add tail of node
void AddTail(Node*& pHead, Board board)
{
	Node* newNode = CreateNode(board);
	if (pHead == NULL)
	{
		pHead = newNode;
		return;
	}
	Node* pCurr = pHead;
	while (pCurr->next != NULL)
	{
		pCurr = pCurr->next;
	}
	pCurr->next = newNode;
}
//Update all of nodes after delete
void UpdateNodeAfterDelete(Node**& list, pair<int, int>index1, pair<int, int>index2)
{
	//If 2 button have the same row
	if (index1.first == index2.first)
	{
		//If the first button is next to the second button
		if (abs(index1.second - index2.second) == 1)
		{
			//Get node having min column of two buttons
			Node* pCurr = GetNode(list, index1.first, min(index1.second, index2.second));
			//Shift the data of the next next node
			while (pCurr->next->next != NULL)
			{
				//Shift the data of the next next node to the current node
				pCurr->data.c = pCurr->next->next->data.c;
				pCurr->data.key = pCurr->next->next->data.key;
				pCurr = pCurr->next;
			}
			//The node lie down at last button
			pCurr->data.c = ' ';
			pCurr->data.key = 0;
		}
		//If the first button isn't next to the second button
		else
		{
			//Get first button
			Node* pCurr1 = GetNode(list, index1.first, min(index1.second, index2.second));
			//Get second button
			Node* pCurr2 = GetNode(list, index1.first, max(index1.second, index2.second));
			while (pCurr1->next != pCurr2)
			{
				//Shift the data of the next node to the first node
				pCurr1->data.c = pCurr1->next->data.c;
				pCurr1->data.key = pCurr1->next->data.key;
				pCurr1 = pCurr1->next;
			}
			//Shift the data of the next of second node to the first node
			while (pCurr2->next->next != NULL)
			{
				pCurr1->data.c = pCurr2->next->data.c;
				pCurr1->data.key = pCurr2->next->data.key;
				pCurr2 = pCurr2->next;
				pCurr1 = pCurr1->next;
			}
			//If the first node and second node is before the last and the last respectively
			pCurr1->data.c = ' ';
			pCurr1->data.key = 0;
			pCurr2->data.c = ' ';
			pCurr2->data.key = 0;
		}
	}
	//If the first button and second button isn't the same row
	else
	{
		//Get first button
		Node* pCurr1 = GetNode(list, index1.first, index1.second);
		//Get second button
		Node* pCurr2 = GetNode(list, index2.first, index2.second);
		//Shift the data of the next node of first node to the first node
		while (pCurr1->next != NULL)
		{
			pCurr1->data.c = pCurr1->next->data.c;
			pCurr1->data.key = pCurr1->next->data.key;
			pCurr1 = pCurr1->next;
		}
		//Shift the data of the next node of second node to the second node
		while (pCurr2->next != NULL)
		{
			pCurr2->data.c = pCurr2->next->data.c;
			pCurr2->data.key = pCurr2->next->data.key;
			pCurr2 = pCurr2->next;
		}
	}
}
//Get node
Node* GetNode(Node** list, int indexRow, int indexCol)
{
	Node* pCurr = list[indexRow];
	//Chú ý hàm GetNode;
	int cnt = 0;
	while (cnt != indexCol)
	{
		pCurr = pCurr->next;
		cnt++;
	}
	return pCurr;
}
//Update node by boardUpdate
void UpdateNode(Node**& list, Board boardUpdate, int indexRow, int indexCol)
{
	Node* pUpdate = list[indexRow];
	int cnt = 0;
	while (cnt != indexCol)
	{
		pUpdate = pUpdate->next;
		cnt++;
	}
	pUpdate->data = boardUpdate;
}
//It is the same as Check I without linkedlist, just change Board** board to Node** list
bool CheckMatchingILinkedList(Node** list, pair<int, int>index1, pair<int, int>index2)
{
	Node* pRes = NULL;
	if (index1.first == index2.first && index1.second == index2.second)
	{
		return false;
	}
	bool KT = true;
	if (index1.first == index2.first)
	{
		for (int i = min(index1.second, index2.second) + 1; i < max(index1.second, index2.second); i++)
		{
			pRes = GetNode(list, index1.first, i);
			if (pRes->data.key != 0)
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
	if (index1.second == index2.second)
	{
		for (int i = min(index1.first, index2.first) + 1; i < max(index1.first, index2.first); i++)
		{
			pRes = GetNode(list, i, index1.second);
			if (pRes->data.key != 0)
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
//It is the same as Check L without linkedlist, just change Board** board to Node** list
bool CheckMatchingLLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2)
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
	if (CheckMatchingILinkedList(list, { index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) + 1 }) == true)
	{
		if (CheckMatchingILinkedList(list, { min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) }) == true)
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
	if (CheckMatchingILinkedList(list, { index, min(index1.second, index2.second) - 1 }, { index, max(index1.second, index2.second) }) == true)
	{
		if (CheckMatchingILinkedList(list, { min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) }) == true)
		{
			return true;
		}
	}
	return false;
}

//It is the same as Check U and Z without linkedlist, just change Board** board to Node** list
bool CheckMatchingUAndZLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	for (int j = 0; j < numOfCols + 2; j++)
	{
		if (j < index1.second)
		{
			if (CheckMatchingILinkedList(list, { index1.first, j - 1 }, { index1.first, index1.second }) == true)
			{
				if (CheckMatchingLLinkedList(list, { index1.first, j }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
		else if (j > index1.second)
		{
			if (CheckMatchingILinkedList(list, { index1.first, index1.second }, { index1.first, j + 1 }) == true)
			{
				if (CheckMatchingLLinkedList(list, { index1.first, j }, { index2.first, index2.second }) == true)
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
			if (CheckMatchingILinkedList(list, { i - 1, index1.second }, { index1.first, index1.second }) == true)
			{
				if (CheckMatchingLLinkedList(list, { i, index1.second }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
		else if (i > index1.first)
		{
			if (CheckMatchingILinkedList(list, { index1.first, index1.second }, { i + 1, index1.second }) == true)
			{
				if (CheckMatchingLLinkedList(list, { i, index1.second }, { index2.first, index2.second }) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}

//It is the same as Check Matching without linkedlist, just change Board** board to Node** list
bool IsMatchingLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	if (CheckMatchingILinkedList(list, index1, index2) == true || CheckMatchingLLinkedList(list, index1, index2) == true || CheckMatchingUAndZLinkedList(list, index1, index2, numOfRows, numOfCols) == true)
	{
		return true;
	}
	return false;
}

//It is the same as Delete L without linkedlist, just change Board** board to Node** list
void DeleteLLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2)
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
	if (CheckMatchingILinkedList(list, { index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) + 1 }) == true)
	{
		if (CheckMatchingILinkedList(list, { min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) }) == true)
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
	if (CheckMatchingILinkedList(list, { index, min(index1.second, index2.second) - 1 }, { index, max(index1.second, index2.second) }) == true)
	{
		if (CheckMatchingILinkedList(list, { min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) }) == true)
		{
			DeleteI({ index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) });
			DeleteI({ min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) });
			return;
		}
	}
}

//It is the same as Delete U and Z without linkedlist, just change Board** board to Node** list
void DeleteUAndZLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	for (int j = index1.second - 1; j >= 0; j--)
	{
		if (CheckMatchingILinkedList(list, { index1.first, j - 1 }, { index1.first, index1.second }) == true)
		{
			if (CheckMatchingLLinkedList(list, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DeleteI({ index1.first, j }, { index1.first, index1.second });
				DeleteLLinkedList(list, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}
	for (int j = index1.second + 1; j < numOfCols + 2; j++)
	{
		if (CheckMatchingILinkedList(list, { index1.first, index1.second }, { index1.first, j + 1 }) == true)
		{
			if (CheckMatchingLLinkedList(list, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DeleteI({ index1.first, index1.second }, { index1.first, j });
				DeleteLLinkedList(list, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}

	for (int i = index1.first - 1; i >= 0; i--)
	{
		if (CheckMatchingILinkedList(list, { i - 1, index1.second }, { index1.first, index1.second }) == true)
		{
			if (CheckMatchingLLinkedList(list, { i, index1.second }, { index2.first, index2.second }) == true)
			{

				if (i != 0)
				{
					DeleteI({ i, index1.second }, { index1.first, index1.second });
					DeleteLLinkedList(list, { i, index1.second }, { index2.first, index2.second });
				}
				else
				{
					Game::DeleteLine(7 * (index1.second - 1) + 7, 5 * 0 + 0, abs(5 * index1.first) - 2, Vertical);
					if (index1.second < index2.second)
					{
						if (CheckMatchingILinkedList(list, { 0, index1.second }, { 0, index2.second + 1 }) == true)
						{
							if (CheckMatchingILinkedList(list, { 0, index2.second }, { index2.first, index2.second }) == true)
							{
								Game::DeleteLine(7 * (index1.second - 1) + 8, (5 * 0 + 0), abs(((7 * (index1.second - 1) + 7) - (7 * (index2.second - 1) + 7))) - 1, Horizontal);
								Game::DeleteLine(7 * (index2.second - 1) + 7, 5 * 0 + 1, abs(((5 * (0 - 1) + 3) - (5 * (index2.first - 1) + 3))) - 3, Vertical);
								return;
							}
						}
					}
					else
					{
						if (CheckMatchingILinkedList(list, { 0, index2.second - 1 }, { 0, index1.second }) == true)
						{
							if (CheckMatchingILinkedList(list, { 0, index2.second }, { index2.first, index2.second }) == true)
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
		if (CheckMatchingILinkedList(list, { index1.first, index1.second }, { i + 1, index1.second }) == true)
		{
			if (CheckMatchingLLinkedList(list, { i, index1.second }, { index2.first, index2.second }) == true)
			{
				DeleteI({ index1.first, index1.second }, { i, index1.second });
				DeleteLLinkedList(list, { i, index1.second }, { index2.first, index2.second });
				return;
			}
		}
	}
}

//It is the same as Draw L without linkedlist, just change Board** board to Node** list
void DrawLLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2)
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
	if (CheckMatchingILinkedList(list, { index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) + 1 }) == true)
	{
		if (CheckMatchingILinkedList(list, { min(index1.first, index2.first), max(index1.second, index2.second) }, { max(index1.first, index2.first), max(index1.second, index2.second) }) == true)
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
	if (CheckMatchingILinkedList(list, { index, min(index1.second, index2.second) - 1 }, { index, max(index1.second, index2.second) }) == true)
	{
		if (CheckMatchingILinkedList(list, { min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) }) == true)
		{
			DrawI({ index, min(index1.second, index2.second) }, { index, max(index1.second, index2.second) });
			DrawI({ min(index1.first, index2.first), min(index1.second, index2.second) }, { max(index1.first, index2.first), min(index1.second, index2.second) });
			return;
		}
	}
}

//It is the same as Draw U and Z without linkedlist, just change Board** board to Node** list
void DrawUAndZLinkedList(Node** list, pair<int, int>index1, pair<int, int>index2, int numOfRows, int numOfCols)
{
	for (int j = index1.second - 1; j >= 0; j--)
	{
		if (CheckMatchingILinkedList(list, { index1.first, j - 1 }, { index1.first, index1.second }) == true)
		{
			if (CheckMatchingLLinkedList(list, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DrawI({ index1.first, j }, { index1.first, index1.second });
				DrawLLinkedList(list, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}
	for (int j = index1.second + 1; j < numOfCols + 2; j++)
	{
		if (CheckMatchingILinkedList(list, { index1.first, index1.second }, { index1.first, j + 1 }) == true)
		{
			if (CheckMatchingLLinkedList(list, { index1.first, j }, { index2.first, index2.second }) == true)
			{
				DrawI({ index1.first, index1.second }, { index1.first, j });
				DrawLLinkedList(list, { index1.first, j }, { index2.first, index2.second });
				return;
			}
		}
	}

	for (int i = index1.first - 1; i >= 0; i--)
	{
		if (i < index1.first)
		{
			if (CheckMatchingILinkedList(list, { i - 1, index1.second }, { index1.first, index1.second }) == true)
			{
				if (CheckMatchingLLinkedList(list, { i, index1.second }, { index2.first, index2.second }) == true)
				{

					if (i != 0)
					{
						DrawI({ i, index1.second }, { index1.first, index1.second });
						DrawLLinkedList(list, { i, index1.second }, { index2.first, index2.second });
					}
					else
					{
						Controller::PrintLine(7 * (index1.second - 1) + 7, 5 * 0 + 0, abs(5 * index1.first) - 2, Vertical);
						Interface::GotoXY(7 * (index1.second - 1) + 7, 5 * index1.first - 3);
						cout << "v";
						if (index1.second < index2.second)
						{
							if (CheckMatchingILinkedList(list, { 0, index1.second }, { 0, index2.second + 1 }) == true)
							{
								if (CheckMatchingILinkedList(list, { 0, index2.second }, { index2.first, index2.second }) == true)
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
							if (CheckMatchingILinkedList(list, { 0, index2.second - 1 }, { 0, index1.second }) == true)
							{
								if (CheckMatchingILinkedList(list, { 0, index2.second }, { index2.first, index2.second }) == true)
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
	}
	for (int i = index1.first + 1; i < numOfRows + 2; i++)
	{
		if (CheckMatchingILinkedList(list, { index1.first, index1.second }, { i + 1, index1.second }) == true)
		{
			if (CheckMatchingLLinkedList(list, { i, index1.second }, { index2.first, index2.second }) == true)
			{
				DrawI({ index1.first, index1.second }, { i, index1.second });
				DrawLLinkedList(list, { i, index1.second }, { index2.first, index2.second });
				return;
			}
		}
	}
}
//Draw background for linked list
void DrawBackGroundLinkedList(Node** list, int row, int col)
{
	Node* pRes = NULL;
	char background[100][100] =
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
		"                         |",
		"                       \\ _ /",
		"                     -= (_) =-",
		"   .\\/.                /   \\",
		".\\\\//o\\\\                 |      ,~",
		"//o\\\\|,\\/.   ,.,.,               |\\",
		"  |  |//o\\ /###/#\\               /| \\",
		"^^|^^|^~|^^^|' '|:|^\"\"\"(\"~~~~~/_|__\\~~~",
		" .|'' . |  '''\"'\"''\" (\" ~ ~ ~======~~",
		" ^^^^^   ^^^ ^ ^^^ ^( \" ~~~~~~~~~~~" };
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			pRes = GetNode(list, i + 1, j + 1);
			if (pRes->data.key == 0)
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

//It is the same as Check Win without linkedlist, just change Board** board to Node** list
bool IsWinLinkedList(Node** list, int row, int col)
{
	Node* pRes = NULL;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			pRes = GetNode(list, i + 1, j + 1);
			if (pRes->data.key != 0)
			{
				return false;
			}
		}
	}
	return true;
}

//It is the same as Move suggestion without linkedlist, just change Board** board to Node** list
void MoveSuggestionLinkedList(Node** list, int row, int col)
{
	Node* pCurr1 = NULL;
	Node* pCurr2 = NULL;
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
						pCurr1 = GetNode(list, i, j);
						pCurr2 = GetNode(list, k, l);
						if (pCurr1->data.key != 0 && pCurr2->data.key != 0 && pCurr1->data.c == pCurr2->data.c)
						{
							if (IsMatchingLinkedList(list, pCurr1->data.index, pCurr2->data.index, row, col))
							{
								Controller::PrintRectangleWithBackgroundColor(7 * (j - 1) + 6 - 2, 5 * (i - 1) + 3 - 2, 7, 5, PURPLE);
								Interface::GotoXY(7 * (j - 1) + 7, 5 * (i - 1) + 3);
								Interface::SetConsoleColor(PURPLE, YELLOW);
								cout << pCurr1->data.c;
								Controller::PrintRectangleWithBackgroundColor(7 * (l - 1) + 6 - 2, 5 * (k - 1) + 3 - 2, 7, 5, PURPLE);
								Interface::GotoXY(7 * (l - 1) + 7, 5 * (k - 1) + 3);
								Interface::SetConsoleColor(PURPLE, YELLOW);
								cout << pCurr2->data.c;
								Sleep(500);

								Controller::DeleteRectangleWithBackgroundColorButText(7 * (j - 1) + 6 - 2, 5 * (i - 1) + 3 - 2, 7 * (j - 1) + 7, 5 * (i - 1) + 3, 7, 5);
								Interface::SetConsoleColor(BLACK, YELLOW);
								Controller::PrintRectangle(7 * (j - 1) + 6 - 2, 5 * (i - 1) + 3 - 2, 7, 5);
								Interface::GotoXY(7 * (j - 1) + 7, 5 * (i - 1) + 3);
								cout << pCurr1->data.c << "  ";
								Controller::DeleteRectangleWithBackgroundColorButText(7 * (l - 1) + 6 - 2, 5 * (k - 1) + 3 - 2, 7 * (l - 1) + 7, 5 * (k - 1) + 3, 7, 5);
								Interface::SetConsoleColor(BLACK, YELLOW);
								Controller::PrintRectangle(7 * (l - 1) + 6 - 2, 5 * (k - 1) + 3 - 2, 7, 5);
								Interface::GotoXY(7 * (l - 1) + 7, 5 * (k - 1) + 3);
								cout << pCurr2->data.c << "  ";
								return;
							}
						}
					}
				}
			}
		}
	}
}

//It is the same as Check continue without linkedlist, just change Board** board to Node** list
bool IsContinueLinkedList(Node** list, int row, int col)
{
	Node* pCurr1 = NULL;
	Node* pCurr2 = NULL;
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
						pCurr1 = GetNode(list, i, j);
						pCurr2 = GetNode(list, k, l);
						if (pCurr1->data.key != 0 && pCurr2->data.key != 0 && pCurr1->data.c == pCurr2->data.c)
						{
							if (IsMatchingLinkedList(list, pCurr1->data.index, pCurr2->data.index, row, col))
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

//Most are similar to the same as move cursor game without linkedlist, The different is that changing Board** board to Node** list and shifting all the button existed to the left.
void MoveCursorGameLinkedList(Node**& list, int row, int col, int points)
{
	Controller::ShowCursor(false);
	time_t timeStart;
	time(&timeStart);
	while (true)
	{
		if (IsWinLinkedList(list, row, col) == true)
		{
			Interface::SetMusic(Win);
			break;
		}
		if (IsContinueLinkedList(list, row, col) == false)
		{
			Interface::SetMusic(Lose);
			break;
		}
		time_t timeCurr;
		time(&timeCurr);
		time_t Distance;
		Distance = timeCurr - timeStart;
		tm timeDistance;
		localtime_s(&timeDistance, &Distance);
		Game::PrintTime(timeDistance);
		int i, j;
		bool check = false;
		Node* pRes = NULL;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				pRes = GetNode(list, i + 1, j + 1);
				if (pRes->data.key == 1)
				{
					Interface::GotoXY(7 * j + 7, 5 * i + 3);
					check = true;
				}
				if (check == true) break;
			}
			if (check == true) break;
		}
		Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
		Interface::GotoXY(7 * j + 7, 5 * i + 3);
		Interface::SetConsoleColor(BLUE, YELLOW);
		pRes = GetNode(list, i + 1, j + 1);
		cout << pRes->data.c;
		int choice;
		bool enter = false;
		Board index[2];
		index[0].index = { -1, -1 };
		if (_kbhit())
		{
			for (int cnt = 0; cnt < 2; cnt++)
			{
				while (true)
				{
					time_t timeCurr;
					time(&timeCurr);
					time_t Distance;
					Distance = timeCurr - timeStart;
					tm timeDistance;
					localtime_s(&timeDistance, &Distance);
					Game::PrintTime(timeDistance);
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
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c << "  ";
						}
						else enter = false;
						j--;
						if (j < 0)
						{
							j++;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int left;
						for (left = j; left >= 0; left--)
						{
							pRes = GetNode(list, i + 1, left + 1);
							if (pRes->data.key == 1)
							{
								check = true;
								break;
							}
						}
						if (check == true)
						{
							j = left;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						else
						{
							j++;
							bool CheckPath = false;
							int maxLength = 1000;
							int indexRow = i, indexCol = j;
							for (int tmpRow = 0; tmpRow < row; tmpRow++)
							{
								for (int tmpCol = 0; tmpCol < j; tmpCol++)
								{
									pRes = GetNode(list, tmpRow + 1, tmpCol + 1);
									if (pRes->data.key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
									{
										maxLength = pow(i - tmpRow, 2) + pow(j - tmpCol, 2);
										CheckPath = true;
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
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					else if (choice == RightArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c << "  ";
						}
						else enter = false;
						j++;
						if (j >= col)
						{
							j--;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int right;
						for (right = j; right < col; right++)
						{
							pRes = GetNode(list, i + 1, right + 1);
							if (pRes->data.key == 1)
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
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
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
									pRes = GetNode(list, tmpRow + 1, tmpCol + 1);
									if (pRes->data.key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
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
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					else if (choice == UpArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c << "  ";
						}
						else enter = false;
						i--;
						if (j < 0)
						{
							i++;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c << "  ";
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int up;
						for (up = i; up >= 0; up--)
						{
							pRes = GetNode(list, up + 1, j + 1);
							if (pRes->data.key == 1)
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
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
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
									pRes = GetNode(list, tmpRow + 1, tmpCol + 1);
									if (pRes->data.key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
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
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					else if (choice == DownArrow)
					{
						if (enter == false && !(i == index[0].index.first - 1 && j == index[0].index.second - 1))
						{
							Controller::DeleteRectangleWithBackgroundColorButText(7 * j + 6 - 2, 5 * i + 3 - 2, 7 * j + 7, 5 * i + 3, 7, 5);
							Interface::SetConsoleColor(BLACK, YELLOW);
							Controller::PrintRectangle(7 * j + 7 - 3, 5 * i + 3 - 2, 7, 5);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLACK, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c << "  ";
						}
						else enter = false;
						i++;
						if (j < 0)
						{
							i--;
							Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
							Interface::GotoXY(7 * j + 7, 5 * i + 3);
							Interface::SetConsoleColor(BLUE, YELLOW);
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
							Interface::SetMusic(Move);
							Interface::SetConsoleColor(BLACK, YELLOW);
						}
						bool check = false;
						int down;
						for (down = i; down < row; down++)
						{
							pRes = GetNode(list, down + 1, j + 1);
							if (pRes->data.key == 1)
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
							pRes = GetNode(list, i + 1, j + 1);
							cout << pRes->data.c;
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
									pRes = GetNode(list, tmpRow + 1, tmpCol + 1);
									if (pRes->data.key == 1 && pow(i - tmpRow, 2) + pow(j - tmpCol, 2) < maxLength)
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
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
							else
							{
								Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
								Interface::GotoXY(7 * j + 7, 5 * i + 3);
								Interface::SetConsoleColor(BLUE, YELLOW);
								pRes = GetNode(list, i + 1, j + 1);
								cout << pRes->data.c;
								Interface::SetMusic(Move);
								Interface::SetConsoleColor(BLACK, YELLOW);
							}
						}
					}
					else if (choice == m)
					{
						Interface::SetMusic(Select);
						MoveSuggestionLinkedList(list, row, col);
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						pRes = GetNode(list, i + 1, j + 1);
						cout << pRes->data.c;
						if (points >= 2)
						{
							points = points - 2;
							Game::PrintScore(points);

						}
						else if (points < 2)
						{
							points = 0;
							Game::PrintScore(points);
						}
						Sleep(300);
						while (true)
						{
							time_t timeCurr;
							time(&timeCurr);
							time_t Distance;
							Distance = timeCurr - timeStart;
							tm timeDistance;
							localtime_s(&timeDistance, &Distance);
							Game::PrintTime(timeDistance);
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
					else if (choice == e)
					{
						Interface::SetMusic(Select);
						GameExitLinkedList(list, row, col, points, timeDistance);
					}
					if (choice != ENTER)
					{
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						pRes = GetNode(list, i + 1, j + 1);
						cout << pRes->data.c;
						Interface::SetConsoleColor(BLACK, YELLOW);
						while (true)
						{
							time_t timeCurr;
							time(&timeCurr);
							time_t Distance;
							Distance = timeCurr - timeStart;
							tm timeDistance;
							localtime_s(&timeDistance, &Distance);
							Game::PrintTime(timeDistance);
							if (_kbhit())
							{
								choice = _getch();
								break;
							}
						}
					}
					else if (choice == ENTER && cnt == 0)
					{
						enter = true;
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						pRes = GetNode(list, i + 1, j + 1);
						cout << pRes->data.c;
						Interface::SetMusic(Select);
						Interface::SetConsoleColor(BLACK, YELLOW);
						Sleep(300);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						index[0].c = pRes->data.c;
						index[0].coordinate = { 7 * j + 7, 5 * i + 3 };
						index[0].index = { i + 1, j + 1 };
						index[0].key = 1;
						break;
					}
					else if (choice == ENTER && cnt == 1)
					{
						enter = true;
						Controller::PrintRectangleWithBackgroundColor(7 * j + 6 - 2, 5 * i + 3 - 2, 7, 5, BLUE);
						Interface::GotoXY(7 * j + 7, 5 * i + 3);
						Interface::SetConsoleColor(BLUE, YELLOW);
						pRes = GetNode(list, i + 1, j + 1);
						cout << pRes->data.c;
						Interface::SetMusic(Select);
						Interface::SetConsoleColor(BLACK, YELLOW);
						Sleep(300);
						Interface::GotoXY(2, 30);
						index[1].c = pRes->data.c;
						index[1].coordinate = { 7 * j + 7, 5 * i + 3 };
						index[1].index = { i + 1, j + 1 };
						index[1].key = 1;
						break;
					}
				}
			}
			if (index[0].c == index[1].c && index[0].key == 1 && index[1].key == 1 && !(index[0].index.first == index[1].index.first && index[0].index.second == index[1].index.second))
			{
				if (IsMatchingLinkedList(list, index[0].index, index[1].index, row, col) == true)
				{
					if (CheckMatchingILinkedList(list, index[0].index, index[1].index) == true)
					{
						Interface::SetConsoleColor(BLACK, LIGHTRED);
						DrawI(index[0].index, index[1].index);
						Sleep(300);
						DeleteI(index[0].index, index[1].index);
						Interface::SetConsoleColor(BLACK, YELLOW);
					}
					else if (CheckMatchingLLinkedList(list, index[0].index, index[1].index) == true)
					{
						Interface::SetConsoleColor(BLACK, LIGHTRED);
						DrawLLinkedList(list, index[0].index, index[1].index);
						Sleep(300);
						DeleteLLinkedList(list, index[0].index, index[1].index);
						Interface::SetConsoleColor(BLACK, YELLOW);
					}
					else
					{
						Interface::SetConsoleColor(BLACK, LIGHTRED);
						DrawUAndZLinkedList(list, index[0].index, index[1].index, row, col);
						Sleep(300);
						DeleteUAndZLinkedList(list, index[0].index, index[1].index, row, col);
						Interface::SetConsoleColor(BLACK, YELLOW);
					}
					Game::DrawBoard(2, 0, 46, 32);
					Game::DeleteTwoRectangle(index[0].index, index[1].index, 7, 5);
					Node* pTmp1 = GetNode(list, index[0].index.first, index[0].index.second);
					pTmp1->data.key = 0;
					//Update the new data to the list
					UpdateNode(list, pTmp1->data, index[0].index.first, index[0].index.second);
					Node* pTmp2 = GetNode(list, index[1].index.first, index[1].index.second);
					pTmp2->data.key = 0;
					//Update the new data to the list
					UpdateNode(list, pTmp2->data, index[1].index.first, index[1].index.second);

					//Update all the node to shift to the left
					UpdateNodeAfterDelete(list, pTmp1->data.index, pTmp2->data.index);
					//delete button
					DeleteButton(list, row, col);
					//Draw button again
					DrawButtonAgain(list, row, col);
					//draw background linkedlist
					DrawBackGroundLinkedList(list, row, col);
					points = points + 15;
					//Print score
					Game::PrintScore(points);
				}
				else
				{
					Game::DeleteTwoRectangle(index[0].index, index[1].index, 7, 5);
					Game::PrintTwoRectangle(index[0].index, index[1].index, 7, 5);
					Interface::GotoXY(index[0].coordinate.first, index[0].coordinate.second);
					Node* pTmp = GetNode(list, index[0].index.first, index[0].index.second);
					cout << pTmp->data.c;
					Interface::GotoXY(7 * j + 7, 5 * i + 3);
					Interface::SetConsoleColor(BLACK, YELLOW);
					pTmp = GetNode(list, i + 1, j + 1);
					cout << pTmp->data.c;
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
			else
			{
				Game::DeleteTwoRectangle(index[0].index, index[1].index, 7, 5);
				Game::PrintTwoRectangle(index[0].index, index[1].index, 7, 5);
				Interface::GotoXY(index[0].coordinate.first, index[0].coordinate.second);
				Node* pTmp = GetNode(list, index[0].index.first, index[0].index.second);
				cout << pTmp->data.c;
				Interface::GotoXY(7 * j + 7, 5 * i + 3);
				Interface::SetConsoleColor(BLACK, YELLOW);
				pTmp = GetNode(list, i + 1, j + 1);
				cout << pTmp->data.c;
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

	time_t timeCurr;
	time(&timeCurr);
	time_t Distance;
	Distance = timeCurr - timeStart;
	tm timeDistance;
	localtime_s(&timeDistance, &Distance);
	Interface::SetConsoleColor(BLACK, YELLOW);
	system("cls");
	if (IsWinLinkedList(list, row, col) == true)
	{
		Interface::PrintWin(GREEN);
	}
	else if (IsContinueLinkedList(list, row, col) == false)
	{
		Interface::PrintLose(GREEN);
	}
	DeleteNode(list, row, col);
	Game::PrintSaveGame(points, timeDistance);
}
//Delete head of node
void DeleteHead(Node**& list, int indexRow)
{
	if (list[indexRow] == NULL)
	{
		return;
	}
	if (list[indexRow]->next == NULL)
	{
		delete list[indexRow];
		list[indexRow] = NULL;
		return;
	}
	Node* pTmp = list[indexRow];
	list[indexRow] = list[indexRow]->next;
	delete pTmp;
}
//Delete node after playing game to avoid memory leak
void DeleteNode(Node**& list, int row, int col)
{
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			DeleteHead(list, i);
		}
	}
}

//It is the same as GameExit without linkedlist, just change Board** board to Node** list
void GameExitLinkedList(Node**& list, int row, int col, int points, tm timeDistance)
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
		DeleteNode(list, row, col);
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