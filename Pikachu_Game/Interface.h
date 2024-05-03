#pragma once
#pragma comment(lib, "winmm.lib")
using namespace std;
#include<Windows.h>
//Define Color
#define BLACK 0
#define BLUE 1
#define GREEN 2                                        //All of references is appeared in our report
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15

//Define music
#define BackGround 0
#define Lose 1
#define Error 2
#define Move 3
#define Select 4
#define Win 5

//Global variable
extern HWND window;
static HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
extern bool FullScreen;
extern bool Music;

struct Interface
{
	static void PrintPokemon(int color);
	static void PrintPikachu(int color);
	static void GotoXY(int x, int y);
	static void SetConsoleColor(int background, int text);
	static void CenterWindow();
	static void SetMenu();
	static void SetMusic(int music);
	static void PrintHCMUS(int color);
	static void DisableResize();
	static void setConsoleTitle();
	static void SetInterface();
	static void FullScreenWindow();
	static void PrintWin(int color);
	static void PrintLose(int color);
};
struct Time
{
	int hour = 0;
	int minute = 0;
	int second = 0;
};
struct Player
{
	string Name;
	string Id;
	string Class;
	Time record;
	int score = 0;
};
struct Account
{
	string username;
	string password;
	string email;
};
void ReadFile(Player x[], int& cnt);
void WriteFile(Player x[], int cnt);
void Swap(Player& x, Player& y);
void SortRank(Player x[], int cnt);
void ChangePassword(Account x[], int cnt);
void ReadFileAccount(Account x[], int& cnt);
void WriteFileAccount(Account x[], int cnt);
void SetInterfaceSignUpLogIn();
void LogIn(Account x[], int cnt);
void SignUp(Account x[], int& cnt);
void ForgotPassword(Account x[], int cnt);

