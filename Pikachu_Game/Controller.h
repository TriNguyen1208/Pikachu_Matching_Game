#pragma once
using namespace std;

//Define arrow
#define UpArrow 72
#define DownArrow 80
#define LeftArrow 75
#define RightArrow 77
#define ESC 27                                           //All of references is appeared in our report
#define ENTER 13

#define w 119
#define s 115
#define a 97
#define d 100
#define m 109
#define e 101

#define W 87
#define S 83
#define A 65
#define D 68
#define CapLock 20

//Define type of line
#define Horizontal 1
#define Vertical 2

//Define mode of game
#define EASY 3
#define MEDIUM 4
#define HARD 5
struct Controller
{
	static int PlayMode();
	static void Play();
	static void Rank(int page);
	static void Help();
	static void Exit();
	static void Setting();
	static void MoveCursor();
	static void ShowCursor(bool show);
	static void PrintRectangle(int x, int y, int width, int height);
	static void PrintLine(int x, int y, int size, int type);
	static void PrintRectangleWithBackgroundColor(int x, int y, int width, int height, int backgroundColor);
	static void DeleteRectangleWithBackgroundColor(int x, int y, int width, int height);
	static void DeleteRectangleWithBackgroundColorButText(int x, int y, int xText, int yText, int width, int height);
	static void WriteMenuAgain(int x, int y, int backgroundColor, int textColor);
};