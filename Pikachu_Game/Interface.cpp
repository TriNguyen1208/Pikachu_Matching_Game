#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<string>
#include<string.h>
#include<conio.h>
#include<vector>
#include"Interface.h"
#include"Controller.h"
#include"Game.h"
using namespace std;

//Global variable, using to change from music and not music, full screen to center window
bool Music = true;
bool FullScreen = false;
//Global variable
HWND window = GetConsoleWindow();

//Set interface for menu
void Interface::SetInterface()
{
	Interface::SetConsoleColor(BLACK, BLACK);
	system("cls");
	Interface::SetConsoleColor(BLACK, BLACK);
	//Disable user resize
	Interface::DisableResize();
	//Set title for console
	Interface::setConsoleTitle();
	Interface::SetConsoleColor(BLACK, BLACK);
	//If full screen is false, the screen will be center
	if (FullScreen == false)
	{
		Interface::CenterWindow();
	}
	else
	{
		Interface::FullScreenWindow();
	}
	//Print pokemon
	Interface::PrintPokemon(YELLOW);
	//Print hcmus
	Interface::PrintHCMUS(BLUE);
	//Print pikachu
	Interface::PrintPikachu(YELLOW);
	//Set menu (Play, rank, setting,..)
	Interface::SetMenu();
	//Set music background
	Interface::SetMusic(BackGround);
	//Move the cursor to choose these options
	Controller::MoveCursor();
}
void Interface::PrintPokemon(int color)
{
	cout << endl << endl << endl;
	//Set color
	SetConsoleColor(BLACK, color);
	//Print pokemon
	cout << R"(                                                                   ,'\ )" << endl;
	cout << R"(                                     _.----.        ____         ,'  _\   ___    ___     ____)" << endl;
	cout << R"(                                 _,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.)" << endl;
	cout << R"(                                 \      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |)" << endl;
	cout << R"(                                  \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |)" << endl;
	cout << R"(                                    \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |)" << endl;
	cout << R"(                                     \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |)" << endl;
	cout << R"(                                      \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |)" << endl;
	cout << R"(                                       \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |)" << endl;
	cout << R"(                                        \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |)" << endl;
	cout << R"(                                         \_.-'       |__|    `-._ |              '-.|     '-.| |   |)" << endl;
	cout << R"(                                                                 `'                            '-._|)" << endl;
}
//Move cursor to specific position
void Interface::GotoXY(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(stdOut, pos);
}
//Set color window
void Interface::SetConsoleColor(int background, int text)
{
	SetConsoleTextAttribute(stdOut, background * 16 + text);
}
//Set center window
void Interface::CenterWindow()
{
	RECT rectClient, rectWindow;
	GetClientRect(window, &rectClient);
	GetWindowRect(window, &rectWindow);
	int width = 1100;
	int height = 700;
	int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 4;
	MoveWindow(window, x, y, width, height, TRUE);
}
//Set full screen window
void Interface::FullScreenWindow()
{
	// Get handle of window console
	HWND console = GetConsoleWindow();

	if (console != NULL) {
		// Get the size of screen
		RECT desktop;
		GetWindowRect(GetDesktopWindow(), &desktop);

		SetWindowPos(console, NULL, 0, 0, desktop.right, desktop.bottom, SWP_NOZORDER);

		// Set maximum of window console
		ShowWindow(console, SW_MAXIMIZE);
	}
}
//Set menu
void Interface::SetMenu()
{
	SetConsoleColor(BLACK, YELLOW);
	string menu[] = { "PLAY", "RANK", "HELP", "SETTING", "EXIT" };
	for (int i = 0; i < 5; i++)
	{
		if (i == 3)
		{
			continue;
		}
		GotoXY(65, 28 + 3 * i);
		cout << menu[i] << endl;
	}
	GotoXY(64, 37);
	cout << menu[3];
}
//Set music
void Interface::SetMusic(int music)
{
	if (Music == true)
	{
		vector<const wchar_t*>sound = { L"LittlerootTown.wav", L"lose.wav", L"error.wav", L"move.wav", L"selected.wav", L"win.wav" };
		PlaySound(sound[music], NULL, SND_FILENAME || SND_SYNC);
	}
}
//Print hcmus
void Interface::PrintHCMUS(int color)
{
	cout << endl << endl << endl;
	SetConsoleColor(BLACK, color);
	cout << R"(                            .·:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':·.)" << endl;
	cout << R"(                            : :  _   _  ____ __  __ _   _ ____    ____  _____  ____ _     ____ ___ _____  : :)" << endl;
	cout << R"(                            : : | | | |/ ___|  \/  | | | / ___|  |___ \|___ / / ___| |   / ___/ _ \___  | : :)" << endl;
	cout << R"(                            : : | |_| | |   | |\/| | | | \___ \    __) | |_ \| |   | |  | |  | | | | / /  : :)" << endl;
	cout << R"(                            : : |  _  | |___| |  | | |_| |___) |  / __/ ___) | |___| |__| |__| |_| |/ /   : :)" << endl;
	cout << R"(                            : : |_| |_|\____|_|  |_|\___/|____/  |_____|____/ \____|_____\____\___//_/    : :)" << endl;
	cout << R"(                            '·:...........................................................................:·')" << endl;
}
//Print Pikachu
void Interface::PrintPikachu(int color)
{
	SetConsoleColor(BLACK, YELLOW);
	GotoXY(0, 28);
	cout << R"(       ,___          .-;'
       `"-.`\_...._/`.`
    ,      \        /
 .-' ',    / ()   ()\
`'._   \  /()    .  (|
    > .' ;,     -'-  /
   / <   |;,     __.;
   '-.'-.|  , \    , \
      `>.|;, \_)    \_)
       `-;     ,    /
          \    /   <
           '. <`'-,_)
            '._)
)";
	int posX = 105;
	int posY = 28;
	GotoXY(posX, posY++);
	cout << R"(`;-.          ___,)";
	GotoXY(posX, posY++);
	cout << R"(  `.`\_...._/`.-"`)";
	GotoXY(posX, posY++);
	cout << R"(    \        /      ,)";
	GotoXY(posX, posY++);
	cout << R"(    /()   () \    .' `-._)";
	GotoXY(posX, posY++);
	cout << R"(   |)  .    ()\  /   _.')";
	GotoXY(posX, posY++);
	cout << R"(   \  -'-     ,; '. <)";
	GotoXY(posX, posY++);
	cout << R"(    ;.__     ,;|   > \)";
	GotoXY(posX, posY++);
	cout << R"(   / ,    / ,  |.-'.-')";
	GotoXY(posX, posY++);
	cout << R"(  (_/    (_/ ,;|.<`)";
	GotoXY(posX, posY++);
	cout << R"(    \    ,     ;-`)";
	GotoXY(posX, posY++);
	cout << R"(     >   \    /)";
	GotoXY(posX, posY++);
	cout << R"(    (_,-'`> .')";
	GotoXY(posX, posY++);
	cout << R"(         (_,')";
}
//Print win
void Interface::PrintWin(int color)
{
	cout << endl << endl << endl;
	Interface::SetConsoleColor(BLACK, color);
	cout << R"(                                   ########################################)" << endl;
	cout << R"(                                   #__   __           __        ___       #)" << endl;
	cout << R"(                                   #\ \ / /__  _   _  \ \      / (_)_ __  #)" << endl;
	cout << R"(                                   # \ V / _ \| | | |  \ \ /\ / /| | '_ \ #)" << endl;
	cout << R"(                                   #  | | (_) | |_| |   \ V  V / | | | | |#)" << endl;
	cout << R"(                                   #  |_|\___/ \__,_|    \_/\_/  |_|_| |_|#)" << endl;
	cout << R"(                                   ########################################)" << endl;
}
//Print lose
void Interface::PrintLose(int color)
{
	cout << endl << endl << endl;
	Interface::SetConsoleColor(BLACK, color);
	cout << R"(                                   #########################################)" << endl;
	cout << R"(                                   #__   __            _                   #)" << endl;
	cout << R"(                                   #\ \ / /__  _   _  | |    ___  ___  ___ #)" << endl;
	cout << R"(                                   # \ V / _ \| | | | | |   / _ \/ __|/ _ \#)" << endl;
	cout << R"(                                   #  | | (_) | |_| | | |__| (_) \__ \  __/#)" << endl;
	cout << R"(                                   #  |_|\___/ \__,_| |_____\___/|___/\___|#)" << endl;
	cout << R"(                                   #########################################)" << endl;
}
//Disable resize
void Interface::DisableResize()
{
	SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}
//Set console title
void Interface::setConsoleTitle()
{
	SetConsoleTitle(L"Pikachu Game");
}
//Set sign up, log in interface
void SetInterfaceSignUpLogIn()
{
	Interface::CenterWindow();
	Interface::DisableResize();
	//Don't show cursor
	Controller::ShowCursor(false);
	Account x[200];
	int cnt;
	//Read file account
	ReadFileAccount(x, cnt);
	Interface::SetConsoleColor(BLACK, YELLOW);
	//Draw the rectangle
	Game::DrawBoard(20, 15, 70, 15);
	Interface::GotoXY(40, 18);
	cout << "Choose one of three options below";

	//Draw the rectangle with its color
	Controller::PrintRectangleWithBackgroundColor(28, 21, 15, 5, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(32, 23);
	cout << "Sign up";

	Interface::SetConsoleColor(BLACK, YELLOW);
	//Draw the rectangle
	Controller::PrintRectangle(50, 21, 15, 5);
	Interface::GotoXY(55, 23);
	cout << "Log in";

	Interface::SetConsoleColor(BLACK, YELLOW);
	//Draw the rectangle
	Controller::PrintRectangle(70, 21, 15, 5);
	Interface::GotoXY(75, 23);
	cout << "Forgot";

	int pos = 32;
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
		if (pos == 32)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
			}
			else if (choice == RightArrow)
			{
				//Delete rectangle without text
				Controller::DeleteRectangleWithBackgroundColorButText(28, 21, 32, 23, 15, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				//Print rectangle again
				Controller::PrintRectangle(28, 21, 15, 5);
				Interface::GotoXY(32, 23);
				cout << "Sign up";
				pos = 55;
				Interface::SetMusic(Move);
				//Draw rectangle with its color
				Controller::PrintRectangleWithBackgroundColor(50, 21, 15, 5, BLUE);
				Interface::GotoXY(pos, 23);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Log in";
			}
		}
		else if (pos == 55)
		{
			if (choice == LeftArrow)
			{
				//Delete rectangle without text
				Controller::DeleteRectangleWithBackgroundColorButText(50, 21, 55, 23, 15, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				//Print rectangle again
				Controller::PrintRectangle(50, 21, 15, 5);
				Interface::GotoXY(55, 23);
				cout << "Log in";
				pos = 32;
				Interface::SetMusic(Move);
				//Draw rectangle with its color
				Controller::PrintRectangleWithBackgroundColor(28, 21, 15, 5, BLUE);
				Interface::GotoXY(pos, 23);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Sign up";
			}
			else if (choice == RightArrow)
			{
				//Delete rectangle without text
				Controller::DeleteRectangleWithBackgroundColorButText(50, 21, 55, 23, 15, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				//Print rectangle again
				Controller::PrintRectangle(50, 21, 15, 5);
				Interface::GotoXY(55, 23);
				cout << "Log in";
				pos = 75;
				Interface::SetMusic(Move);
				//Draw rectangle with its color
				Controller::PrintRectangleWithBackgroundColor(70, 21, 15, 5, BLUE);
				Interface::GotoXY(pos, 23);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Forgot";
			}
		}
		else if (pos == 75)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(70, 21, 76, 23, 15, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(70, 21, 15, 5);
				Interface::GotoXY(75, 23);
				cout << "Forgot";
				pos = 55;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(50, 21, 15, 5, BLUE);
				Interface::GotoXY(pos, 23);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Log in";
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
			//Pause the screen about 300 miliseconds
			Sleep(300);
		}
	}
	switch (pos)
	{
	case 32:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		SignUp(x, cnt);
		break;
	}
	case 55:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		LogIn(x, cnt);
		break;
	}
	case 75:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		ForgotPassword(x, cnt);
		break;
	}
	}
}
//Read file save game
void ReadFile(Player x[], int& cnt)
{
	ifstream fin;
	fin.open("SaveGame.txt");
	if (!fin.is_open())
	{
		return;
	}
	cnt = 0;
	while (getline(fin, x[cnt].Name))
	{
		getline(fin, x[cnt].Id);
		getline(fin, x[cnt].Class);
		fin >> x[cnt].record.hour;
		fin.ignore();
		fin >> x[cnt].record.minute;
		fin.ignore();
		fin >> x[cnt].record.second;
		fin >> x[cnt].score;
		fin.ignore(2);
		cnt++;
	}
	fin.close();
}
//Write player to file save game
void WriteFile(Player x[], int cnt)
{
	ofstream fout;
	fout.open("SaveGame.txt");
	if (!fout.is_open())
	{
		return;
	}
	for (int i = 0; i < cnt; i++)
	{
		fout << x[i].Name << endl;
		fout << x[i].Id << endl;
		fout << x[i].Class << endl;
		fout << x[i].record.hour << ":" << x[i].record.minute << ":" << x[i].record.second << endl;
		fout << x[i].score << endl << endl;
	}
	fout.close();
}
//Swap two player
void Swap(Player& x, Player& y)
{
	Player tmp = x;
	x = y;
	y = tmp;
}
//Arranges in order of priority, points first, then time.
void SortRank(Player x[], int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		for (int j = i + 1; j < cnt; j++)
		{
			if (x[i].score < x[j].score)
			{
				Swap(x[i], x[j]);
			}
			else if (x[i].score == x[j].score)
			{
				if (x[i].record.hour > x[j].record.hour)
				{
					Swap(x[i], x[j]);
				}
				else if (x[i].record.hour == x[j].record.hour)
				{
					if (x[i].record.minute > x[j].record.minute)
					{
						Swap(x[i], x[j]);
					}
					else if (x[i].record.minute == x[j].record.minute)
					{
						if (x[i].record.second > x[j].record.second)
						{
							Swap(x[i], x[j]);
						}
					}
				}
			}
		}
	}
}
//Sign up your account
void SignUp(Account x[], int& cnt)
{
	//Cursor is showed
	Controller::ShowCursor(true);
	Interface::SetConsoleColor(BLACK, YELLOW);
	Game::DrawBoard(20, 15, 70, 20);
	Interface::GotoXY(50, 18);
	cout << "Sign up account";
	string username, password, email;
	Interface::GotoXY(32, 20);
	cout << "Username: ";
	Interface::GotoXY(32, 22);
	cout << "Password: ";
	Interface::GotoXY(32, 24);
	cout << "Email: ";
	Interface::GotoXY(42, 20);
	getline(cin, username);
	Interface::GotoXY(42, 22);
	getline(cin, password);
	Interface::GotoXY(39, 24);
	getline(cin, email);

	bool IsExist = false;
	for (int i = 0; i < cnt; i++)
	{
		if (x[i].username == username || x[i].email == email)
		{
			IsExist = true;
		}
	}
	//If existed
	if (IsExist == true)
	{
		Interface::GotoXY(44, 26);
		cout << "Your account is existed";
	}
	else
	{
		Interface::GotoXY(44, 26);
		cout << "Sign in successfully";
		x[cnt].username = username;
		x[cnt].password = password;
		x[cnt].email = email;
		cnt++;

	}
	WriteFileAccount(x, cnt);
	Controller::ShowCursor(false);
	Controller::PrintRectangleWithBackgroundColor(40, 29, 10, 5, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(43, 31);
	cout << "Back";

	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(60, 29, 10, 5);
	Interface::GotoXY(63, 31);
	cout << "Exit";

	int pos = 43;
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
		if (pos == 43)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(40, 29, 43, 21, 10, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(40, 29, 10, 5);
				Interface::GotoXY(43, 31);
				cout << "Back";
				pos = 63;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(60, 29, 10, 5, BLUE);
				Interface::GotoXY(pos, 31);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Exit";
			}
		}
		else if (pos == 63)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(60, 29, 63, 31, 10, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(60, 29, 10, 5);
				Interface::GotoXY(63, 31);
				cout << "Exit";
				pos = 43;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(40, 29, 10, 5, BLUE);
				Interface::GotoXY(pos, 31);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Back";
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
	case 43:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		//Return to menu of sign up, log in, forgot password
		SetInterfaceSignUpLogIn();
		break;
	}
	case 63:
	{
		//Exit
		exit(1);
		break;
	}
	}
}
//Log in your account to play game
void LogIn(Account x[], int cnt)
{
	Controller::ShowCursor(true);
	Interface::SetConsoleColor(BLACK, YELLOW);
	Game::DrawBoard(20, 15, 70, 20);
	Interface::GotoXY(50, 18);
	cout << "Log in account";
	string info, password;
	Interface::GotoXY(32, 20);
	cout << "Username or email: ";
	Interface::GotoXY(32, 22);
	cout << "Password: ";
	Interface::GotoXY(51, 20);
	getline(cin, info);
	Interface::GotoXY(42, 22);
	getline(cin, password);

	bool IsLogIn = false;
	for (int i = 0; i < cnt; i++)
	{
		if ((info == x[i].username || info == x[i].email) && password == x[i].password)
		{
			IsLogIn = true;
			break;
		}
	}
	if (IsLogIn == true)
	{
		Interface::GotoXY(32, 24);
		cout << "Log in successfully. Press any key to enter the game";

		Controller::ShowCursor(false);
		Controller::PrintRectangleWithBackgroundColor(50, 29, 10, 5, BLUE);
		Interface::SetConsoleColor(BLUE, YELLOW);
		Interface::GotoXY(51, 31);
		cout << "Continue";
		int choice = _getch();
		Interface::SetConsoleColor(BLACK, YELLOW);
		Interface::SetMusic(Select);
		Sleep(300);
		system("cls");
		Interface::SetInterface();
	}
	else
	{
		Interface::GotoXY(40, 24);
		cout << "Your username or password isn't correct";
		Interface::GotoXY(42, 26);
		cout << "Please choose the following options.";

		Controller::ShowCursor(false);
		Controller::PrintRectangleWithBackgroundColor(50, 29, 10, 5, BLUE);
		Interface::SetConsoleColor(BLUE, YELLOW);
		Interface::GotoXY(53, 31);
		cout << "Back";
		int choice = _getch();
		Interface::SetConsoleColor(BLACK, YELLOW);
		Interface::SetMusic(Select);
		Sleep(300);
		system("cls");
		SetInterfaceSignUpLogIn();
	}
}
//Forgot password in menu of log in, sign up
void ForgotPassword(Account x[], int cnt)
{
	srand(time(NULL));
	Controller::ShowCursor(true);
	Interface::SetConsoleColor(BLACK, YELLOW);
	Game::DrawBoard(20, 15, 70, 20);
	Interface::GotoXY(47, 18);
	cout << "Forgot password";
	string info, password;
	Interface::GotoXY(32, 20);
	cout << "Username or email: ";
	Interface::GotoXY(51, 20);
	getline(cin, info);

	bool IsExist = false;
	int i;
	for (i = 0; i < cnt; i++)
	{
		if (x[i].email == info || x[i].username == info)
		{
			IsExist = true;
			break;
		}
	}
	if (IsExist == true)
	{
		Interface::GotoXY(40, 22);
		x[i].password = x[i].password + to_string(rand() % 100 + 1);
		cout << "This is new password: " << x[i].password;
		WriteFileAccount(x, cnt);
	}
	else
	{
		Interface::GotoXY(40, 22);
		cout << "Your username or email isn't correct!";
	}
	Interface::GotoXY(38, 26);
	cout << "Please choose the following options";

	Controller::ShowCursor(false);
	Controller::PrintRectangleWithBackgroundColor(40, 29, 10, 5, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(43, 31);
	cout << "Back";

	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(60, 29, 10, 5);
	Interface::GotoXY(63, 31);
	cout << "Exit";

	int pos = 43;
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
		if (pos == 43)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(40, 29, 43, 21, 10, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(40, 29, 10, 5);
				Interface::GotoXY(43, 31);
				cout << "Back";
				pos = 63;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(60, 29, 10, 5, BLUE);
				Interface::GotoXY(pos, 31);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Exit";
			}
		}
		else if (pos == 63)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(60, 29, 63, 31, 10, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(60, 29, 10, 5);
				Interface::GotoXY(63, 31);
				cout << "Exit";
				pos = 43;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(40, 29, 10, 5, BLUE);
				Interface::GotoXY(pos, 31);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Back";
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
	case 43:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		SetInterfaceSignUpLogIn();
		break;
	}
	case 63:
	{
		exit(1);
		break;
	}
	}
}
//Read file account
void ReadFileAccount(Account x[], int& cnt)
{
	ifstream fin;
	fin.open("SignUp_Login.txt");
	if (!fin.is_open())
	{
		return;
	}
	cnt = 0;
	while (getline(fin, x[cnt].username))
	{
		getline(fin, x[cnt].password);
		getline(fin, x[cnt].email);
		fin.ignore();
		cnt++;
	}
	fin.close();
}
//Write account to the file account
void WriteFileAccount(Account x[], int cnt)
{
	ofstream fout;
	fout.open("SignUp_Login.txt");
	if (!fout.is_open())
	{
		return;
	}
	for (int i = 0; i < cnt; i++)
	{
		fout << x[i].username << endl;
		fout << x[i].password << endl;
		fout << x[i].email << endl;
		fout << endl;
	}
	fout.close();
}
//Change your password in setting
void ChangePassword(Account x[], int cnt)
{
	ReadFileAccount(x, cnt);
	Controller::ShowCursor(true);
	Interface::SetConsoleColor(BLACK, YELLOW);
	Game::DrawBoard(20, 15, 70, 20);
	Interface::GotoXY(50, 18);
	cout << "Change password";
	string info, password, newPassword;
	Interface::GotoXY(32, 20);
	cout << "Username or Email: ";
	Interface::GotoXY(32, 22);
	cout << "Current Password: ";
	Interface::GotoXY(32, 24);
	cout << "New Password: ";
	Interface::GotoXY(51, 20);
	getline(cin, info);
	Interface::GotoXY(50, 22);
	getline(cin, password);
	Interface::GotoXY(46, 24);
	getline(cin, newPassword);

	bool IsExist = false;
	int index;
	for (int i = 0; i < cnt; i++)
	{
		if ((x[i].username == info || x[i].email == info) && x[i].password == password)
		{
			IsExist = true;
			index = i;
			break;
		}
	}
	if (IsExist == true)
	{
		Interface::GotoXY(40, 26);
		cout << "Change your password successfully";
		x[index].password = newPassword;
	}
	else
	{
		Interface::GotoXY(35, 26);
		cout << "Your username or password isn't correct!";
	}
	WriteFileAccount(x, cnt);

	Controller::ShowCursor(false);
	Controller::PrintRectangleWithBackgroundColor(40, 29, 10, 5, BLUE);
	Interface::SetConsoleColor(BLUE, YELLOW);
	Interface::GotoXY(43, 31);
	cout << "Back";

	Interface::SetConsoleColor(BLACK, YELLOW);
	Controller::PrintRectangle(60, 29, 10, 5);
	Interface::GotoXY(63, 31);
	cout << "Exit";

	int pos = 43;
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
		if (pos == 43)
		{
			if (choice == LeftArrow)
			{
				Interface::SetMusic(Move);
			}
			else if (choice == RightArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(40, 29, 43, 21, 10, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(40, 29, 10, 5);
				Interface::GotoXY(43, 31);
				cout << "Back";
				pos = 63;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(60, 29, 10, 5, BLUE);
				Interface::GotoXY(pos, 31);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Exit";
			}
		}
		else if (pos == 63)
		{
			if (choice == LeftArrow)
			{
				Controller::DeleteRectangleWithBackgroundColorButText(60, 29, 63, 31, 10, 5);
				Interface::SetConsoleColor(BLACK, YELLOW);
				Controller::PrintRectangle(60, 29, 10, 5);
				Interface::GotoXY(63, 31);
				cout << "Exit";
				pos = 43;
				Interface::SetMusic(Move);
				Controller::PrintRectangleWithBackgroundColor(40, 29, 10, 5, BLUE);
				Interface::GotoXY(pos, 31);
				Interface::SetConsoleColor(BLUE, YELLOW);
				cout << "Back";
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
	case 43:
	{
		Interface::SetConsoleColor(BLACK, YELLOW);
		system("cls");
		Controller::Setting();
		break;
	}
	case 63:
	{
		exit(1);
		break;
	}
	}
}