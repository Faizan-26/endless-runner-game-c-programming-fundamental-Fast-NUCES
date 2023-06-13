#include<iostream>
#include<string>
#include<conio.h>
#include<cstring>
#include<ctime>
#include<Windows.h>
#include<cstdlib>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
float life = 3;
int score = 0;
int i = 2;
void lifeReduction();
void draw_Border(char arr[][14], int row, int col) {
	for (int k = 0; k < row; k++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j == 0 || j == 13)
				arr[k][j] = '|';
			else {
				arr[k][j] = ' ';
			}
		}
	}
}
void Obstacle_Coins(char arr[][14], int row, int col) {
	srand(time(0));
	int randvalue = 0;
	for (int j = 1; j < col - 1; j++)
	{
		randvalue = rand() % 6;
		if (randvalue > 4)
		{
			randvalue = rand() % 12 + 1;
			arr[0][randvalue] = '#';
		}
		else if (randvalue < 1) {
			randvalue = rand() % 12 + 1;
			arr[0][randvalue] = '$';
		}
	}
}
void Draw_character(char arr[][14]) {
	arr[14][6] = '/';
	arr[14][7] = '\\';
}
void Jump_slide(char arr[][14], int row, int col) {
	char tempa = ' ', tempb = ' ';
	bool jumping = false, sliding = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++) {
			if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && GetAsyncKeyState(VK_SPACE) && i > 3 && !jumping && !sliding)// jump
			{
				jumping = true;
				tempa = arr[i][j];
				tempb = arr[i][j + 1];
				arr[i][j] = ' ';
				arr[i][j + 1] = ' ';
				if (arr[i + 1][j] == '{' && arr[i + 1][j + 1] == '}') {
					arr[i + 1][j] = ' ';
					arr[i + 1][j + 1] = ' ';
					arr[(i - 3) + 1][j] = '{'; arr[(i - 3) + 1][j + 1] = '}';
				}
				if (arr[i - 3][j] == '#' || arr[i - 3][j + 1] == '#')
					lifeReduction();
				arr[i - 3][j] = tempa;
				arr[i - 3][j + 1] = tempb;
				Sleep(30);
				break;
			}
			else if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && GetAsyncKeyState(VK_LCONTROL) && i > 3 && !jumping && !sliding)//sliding
			{
				sliding = true;
				tempa = arr[i][j];
				tempb = arr[i][j + 1];
				arr[i][j] = ' ';
				arr[i][j + 1] = ' ';
				if (arr[i + 1][j] == '{' && arr[i + 1][j + 1] == '}') {
					arr[i + 1][j] = ' ';
					arr[i + 1][j + 1] = ' ';
					arr[(i - 2) + 1][j] = '{'; arr[(i - 2) + 1][j + 1] = '}';
				}
				if (arr[i - 2][j] == '#' || arr[i - 2][j + 1] == '#')
					lifeReduction();
				arr[i - 2][j] = tempa;
				arr[i - 2][j + 1] = tempb;
				Sleep(30);
				break;
			}

		}
	}

}
void accident(char arr[][14], int row, int col) {// char with obstacle
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && arr[i][j] != arr[0][j]) {
				if (arr[i - 1][j] == '#' || arr[i - 1][j + 1] == '#')
					lifeReduction();
			}
		}
	}
}
void Display_Game(char arr[][14], int row, int col, int& distance) {
	SetConsoleTextAttribute(h, 15);
	cout << "Life Left: " << life << endl;
	cout << "Scores :" << score << endl;
	cout << "Distance Covered: " << distance << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] == '$')
			{
				SetConsoleTextAttribute(h, 10);
				cout << arr[i][j];
			}
			else if (arr[i][j] == '#' || arr[i][j] == '{' || arr[i][j] == '}') {
				SetConsoleTextAttribute(h, 12);
				cout << arr[i][j];
			}
			else if (arr[i][j] == '/' || arr[i][j] == '\\') {
				SetConsoleTextAttribute(h, 14);
				cout << arr[i][j];
			}
			else {
				SetConsoleTextAttribute(h, 15);
				cout << arr[i][j];
			}
			SetConsoleTextAttribute(h, 15);
			Jump_slide(arr, i, j);
		}
		cout << endl;
	}

}
void ComputerPlayer(char arr[][14], int row, int col) {
	if (score > 15) {
		for (int i = row - 1; i >= 0; i--)
		{
			for (int j = 0; j < col; j++)
			{

				if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && i + 4 < row) {
					arr[i + 1][j] = '{';
					arr[i + 1][j + 1] = '}';
				}
			}
		}


	}
}
void Input(char arr[][14], int row, int col)
{
	char temp1 = ' ', temp2 = ' ';
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			for (int i = 0; i < row; i++)
			{
				for (int j = col - 1; j >= 0; j--)
				{
					if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && arr[i][j - 2] != '|' && arr[i][j - 1] != '|' && arr[i][j - 1] != '#') {
						temp1 = arr[i][j];
						temp2 = arr[i][j + 1];
						arr[i][j] = ' ';
						arr[i][j + 1] = ' ';
						if (arr[i + 1][j] == '{' && arr[i + 1][j + 1] == '}') {
							arr[i + 1][j] = ' ';
							arr[i + 1][j + 1] = ' ';
							arr[i + 1][j - 2] = '{' && arr[i + 1][j - 1] == '}';
						}
						if (arr[i][j - 2] == '#' || arr[i][j - 1] == '#')
							lifeReduction();
						arr[i][j - 2] = '/';
						arr[i][j - 1] = '\\';
						break;
					}
				}
			}
			break;
		case 'd':
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col - 4; j++)
				{
					if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && arr[i][j + 2] != '|' && arr[i][j + 1] != '|' && arr[i][j + 2] != '#')
					{
						temp1 = arr[i][j];
						temp2 = arr[i][j + 1];
						arr[i][j] = ' ';
						arr[i][j + 1] = ' ';
						if (arr[i + 1][j] == '{' && arr[i + 1][j + 1] == '}') {
							arr[i + 1][j] = ' ';
							arr[i + 1][j + 1] = ' ';
							arr[i + 1][j + 2] = '{'; arr[i + 1][j + 3] = '}';
						}
						if (arr[i][j + 2] == '#' || arr[i][j + 3] == '#')
							lifeReduction();
						arr[i][j + 2] = temp1;
						arr[i][j + 3] = temp2;
						break;
					}
				}
			}
			break;

		case 'w':

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && arr[i][j] != arr[0][j]) {
						temp1 = arr[i][j];
						temp2 = arr[i][j + 1];
						arr[i][j] = ' ';
						arr[i][j + 1] = ' ';
						if (arr[i + 1][j] == '{' && arr[i + 1][j + 1] == '}') {
							arr[i + 1][j] = ' ';
							arr[i + 1][j + 1] = ' ';
							arr[i][j] = '{'; arr[i][j + 1] = '}';
						}
						if (arr[i - 1][j] == '#' || arr[i - 1][j + 1] == '#')
							lifeReduction();
						arr[i - 1][j] = temp1;
						arr[i - 1][j + 1] = temp2;
					}
				}
			}
			break;

		case 's':
			for (int i = row - 1; i >= 0; i--)
			{
				for (int j = 0; j < col; j++)
				{
					if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && i + 1 < row && arr[i + 1][j] != '|' && arr[i + 1][j + 1] != '|' && arr[i + 1][j + 1] != '#') {
						temp1 = arr[i][j];
						temp2 = arr[i][j + 1];
						arr[i][j] = ' ';
						arr[i][j + 1] = ' ';
						if (arr[i + 1][j] == '{' && arr[i + 1][j + 1] == '}') {
							arr[i + 1][j] = ' ';
							arr[i + 1][j + 1] = ' ';
							arr[i + 2][j] = '{'; arr[i + 2][j + 2] = '}';
						}
						if (arr[i + 2][j] == '#' || arr[i + 2][j + 1] == '#')
							lifeReduction();
						arr[i + 1][j] = temp1;
						arr[i + 1][j + 1] = temp2;
					}
				}
			}
			break;
		}
	}
}
void Swap(char arr[][14], int row, int col)
{
	char temp = ' ';
	for (int i = row - 1; i >= 0; i--)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] == '#' || arr[i][j] == '$' && i + 1 < row && arr[i + 1][j] != '/' && arr[i + 1][j] != '\\' && arr[i + 1][j] != '#')
			{
				temp = arr[i][j];
				arr[i][j] = ' ';
				arr[i + 1][j] = temp;
				if (i + 1 == row - 1) // Check if the obstacle reaches the bottom row
					arr[i + 1][j] = ' '; // Remove the obstacle at the end position
				break;
			}
		}
	}
}
void Score_Increase(char arr[][14], int row, int col) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++) {
			if (arr[i][j] == '/' && arr[i][j + 1] == '\\' && (arr[i - 1][j] == '$' || arr[i - 1][j + 1] == '$')) {
				score += 5;
				arr[i - 1][j] = ' ';
				arr[i - 1][j + 1] = ' ';
			}
		}
	}
}
void main_Logic() {
	int speed = 85;
	int distance = 0;
	const int row = 15, col = 14;
	char arr[row][col];
	while (1) {
		if (i == 2) {
			draw_Border(arr, row, col);
			Draw_character(arr);
			Sleep(500);
			system("CLS");
		}
		if (i % 5 == 0)
			Obstacle_Coins(arr, row, col);
		distance += 1;
		Display_Game(arr, row, col, distance);
		Jump_slide(arr, row, col);
		Score_Increase(arr, row, col);
		ComputerPlayer(arr, row, col);
		accident(arr, row, col);
		Input(arr, row, col);
		Swap(arr, row, col);
		distance++;
		if (distance % 50 == 0 && speed > 40) {
			speed -= 5;
		}
		Sleep(speed);
		system("CLS");
		i++;
		if (life == 0) {
			cout << "GAME OVER!!!";
			break;
		}
	}
}

int main()
{
	Sleep(5000);
	system("pause");
	system("CLS");
	SetConsoleTextAttribute(h, 15);
	main_Logic();
	system ("start https://github.com/Faizan-26/endless-runner-game-c-programming-fundamental-Fast-NUCES")
	system("pause");

	return 0;

}
void lifeReduction() {
	life -= 1;
	i = 2;
	main_Logic();
}