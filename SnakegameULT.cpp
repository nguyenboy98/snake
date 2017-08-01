#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
//VARIABLE
struct coordinate
{
	int x, y;
};
char map[100][100];
int room_width = 62, room_height = 25, food = 0;
int food_x = 0, food_y = 0, delay = 100, ax = 2, ay = 0, point = 3, tmpnum, score[100];
bool gameplay = true;
string name, player[100], tmpstr;
coordinate snake[100];


//LIBRARY
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle
	(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

//Sub
void xytext(int x, int y, int color, string str)
{
	gotoxy(x, y);
	textcolor(color);
	cout << str;
	textcolor(7);
	gotoxy(0, 0);
}
void xypoint(int x, int y, int color, string str, int point)
{
	gotoxy(x, y);
	textcolor(color);
	cout << str;
	cout << point;
	textcolor(7);
	gotoxy(0, 0);
}
void xyobject(int x, int y, int color, char input)
{
	gotoxy(x, y);
	textcolor(color);
	printf("%c", input);
	textcolor(7);
	gotoxy(0, 0);
}

//MENU
void menugame()
{
	{
		gotoxy(0, 7);
		printf("         ____              _ \n");
		printf("        / ___| _ __   __ _| | _____ \n");
		printf("        \\___ \\| '_ \\ / _` | |/ / _ \\  \n");
		printf("         ___) | | | | (_| |   <  __/ \n");
		printf("        |____/|_|_|_|\\__,_|_|\\_\\___|  ___  \n");
		printf("               / _` |/ _` | '_ ` _ \\ / _ \\ \n");
		printf("              | (_| | (_| | | | | | |  __/  \n");
		printf("               \\__, |\\__,_|_| |_| |_|\\___| \n");
		printf("               |___/ \n");
		printf("\n\n\t\t_______________________________\n\n");
		printf("     Made by: \n");
		printf("  \t* Vu Nhat Thanh\t\t   Phan Tran Phong Nguyen \n");
		printf("   \t  Nguyen Do Cuong");
		gotoxy(0, 0);
	}
	int key;
	while (true)
	{
		xytext(47, 12, 7, "START GAME");
		xytext(47, 14, 7, "EXIT");
		if (GetAsyncKeyState(VK_UP))
		{
			key = 1;
			xytext(45, 12, 7, ">");
			xytext(45, 14, 7, " ");
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			key = 0;
			xytext(45, 12, 7, " ");
			xytext(45, 14, 7, ">");
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			if (key == 1) break;
			else exit(0);
		}
	}
}
void pause() {
	xytext(32, 12, 15, "3");
	Sleep(700);
	xytext(32, 12, 15, "2");
	Sleep(700);
	xytext(32, 12, 15, "1");
	Sleep(700);
	xytext(32, 12, 15, " ");
}

//OBJECT
void obj_snake()
{
	xyobject(snake[0].x, snake[0].y, 12, (char)254);
	for (int i = 1; i < point; i++)
	{
		xyobject(snake[i].x, snake[i].y, 14, (char)254);
	}
	xyobject(snake[point].x, snake[point].y, 0, (char)254);
	for (int i = 0; i < point; i++)
	{
		snake[point - i].x = snake[point - i - 1].x;
		snake[point - i].y = snake[point - i - 1].y;
	}
	snake[0].x += ax; snake[0].y += ay;
	Sleep(delay);
}
void obj_tail()
{
	snake[0].x = 37; snake[0].y = 15;
	snake[1].x = 35; snake[1].y = 15;
	snake[2].x = 33; snake[2].y = 15;
	snake[3].x = 32; snake[3].y = 15;
}
void obj_food()
{
	if (food == 0)
	{
		int check = 0;
		do
		{
			check = 0;
			food_x = 2 + (rand() % (room_width - 2));
			food_y = 1 + (rand() % (room_height - 2));
			for (int i = 0; i <= point; i++)
			{
				if (snake[i].x == food_x && snake[i].y == food_y)
				{
					check = 1;
				}
			}
		} while (food_x % 2 == 0 || check == 1);
		xyobject(food_x, food_y, 10, (char)120);
		food = 1;
	}
}



//MAPCREATOR
void GUImap()
{
	for (int i = 0; i < room_height; i++)
	{
		map[i][0] = (char)219;
		map[i][room_width - 1] = (char)219;
		for (int j = 0; j < room_width; j++)
		{
			map[0][j] = (char)220;
			map[room_height - 1][j] = (char)223;
		}
	}
}
void printGUI()
{
	textcolor(15);
	for (int i = 0; i < room_height; i++)
	{
		printf(" ");
		for (int j = 0; j < room_width; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}
void GUItext()
{
	xytext(5, 0, 15, " SNAKE GAME Ver1.0 ");
	xypoint(50, 25, 15, "Point: ", point - 3);

}
void processing()
{
	//Point
	if ((food_x == snake[0].x) && (food_y == snake[0].y))
	{
		point += 1;
		food = 0;
	}
	//Endgame
	bool lose = false;
	for (int i = 2; i <= point; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			lose = true;
		}
	}
	if (snake[0].x > (room_width - 1) || snake[0].x == 1 || snake[0].y > (room_height - 2) || snake[0].y == 0 || lose == true)
	{
		xytext(28, 12, 13, "GAME OVER!");
		system("pause>nul");
		system("cls");
		gotoxy(15, 12);
		ShowConsoleCursor(true);
		fstream scrlist; fstream plrlist;
		scrlist.open("score.dat", ios::app|ios::out);
		plrlist.open("player.dat", ios::app|ios::out);
		cout << "Player name: ";
		getline(cin, name);
		scrlist << point-3 << endl;
		plrlist << name << endl;
		scrlist.close();
		plrlist.close();
		gameplay = false;
	}
}
void control()
{
	if (GetAsyncKeyState(VK_UP) && ((snake[0].y - 1) != snake[1].y))
	{
		ay = -1; ax = 0;
	}
	if (GetAsyncKeyState(VK_DOWN) && ((snake[0].y + 1) != snake[1].y))
	{
		ay = +1; ax = 0;
	}
	if (GetAsyncKeyState(VK_LEFT) && ((snake[0].x - 2) != snake[1].x))
	{
		ax = -2; ay = 0;
	}
	if (GetAsyncKeyState(VK_RIGHT) && ((snake[0].x + 2) != snake[1].x))
	{
		ax = +2; ay = 0;
	}
}
void showScore()
{
	//Sort
	system("cls");
	int n = 0, m = 0;
	ifstream scrlist;
	scrlist.open("score.dat");
	ifstream plrlist;
	plrlist.open("player.dat");
	while(getline(plrlist, player[m])) m += 1;
	while(scrlist >> score[n])
	{
		for(int i = 0; i <= n; i++)
		{
			for(int j = 0; j < n; j++)
				if(score[j] < score[j+1])
				{
					tmpnum = score[j];
					score[j] = score[j+1];
					score[j+1] = tmpnum;
					tmpstr = player[j];
					player[j] = player[j+1];
					player[j+1] = tmpstr;
				}
		}
		n++;
	}
	plrlist.close();
	scrlist.close();
	//Show score
	xytext(20,11,11,"Top 5 depzai: ");
	for(int i = 0; i < 5; i++)
	{
		gotoxy(25,12+i);
		cout << score[i]<< "\t" << player[i] <<endl;
	}

}
//THIS IS SPARTA!
int main()
{
	resizeConsole(500, 460);
	ShowConsoleCursor(false);
	menugame();
	GUImap();
	printGUI();
	obj_tail();
	pause();
	while (gameplay)
	{
		//Load information
		ShowConsoleCursor(false);
		obj_snake();
		obj_food();
		processing();
		GUItext();
		control();
	}
	showScore();
	system("pause>nul");
	return 0;
}
