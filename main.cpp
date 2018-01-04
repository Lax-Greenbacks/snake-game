#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x;
int y;
int mouseX;
int mouseY;
int score;
int tailX[100];
int tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	mouseX = rand() % width;
	mouseY = rand() % height;
	score = 0;
}

void Draw(){
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "X";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "X";
			if (i == y && j == x)
				cout << "O";
			else if (i == mouseY && j == mouseX)
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "X";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "X";
	cout << endl;
	cout << "Score:" << score << endl;
}

void Controls(){
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'z':
			gameOver = true;
			break;
		}
	}
}

void Logic(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	default:
		break;

	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == mouseX && y == mouseY)
	{
		score += 1;
		mouseX = rand() % width;
		mouseY = rand() % height;
		nTail++;
	}
}

int main(){
	Setup();
	while (!gameOver) {
		Draw();
		Controls();
		Logic();
		Sleep(125);
	}

	return 0;
}