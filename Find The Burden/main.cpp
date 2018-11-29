#include <iostream>
#include <string>
#include <Windows.h>
#include "Scenario.h"
using namespace std;

HANDLE hStdout;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

enum Screens { MAIN, START, END };
enum EndState { OVER, COMPLETE };

Screens currentScreen;
static int windowWidth = 70;

bool gameExit = false;
int score;
int prevS = -1; // set to 0 when doing random scenes
EndState endState;
string input;
string inputAns;
Scenario currentScenario;

void Init()
{
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	currentScreen = MAIN;
	score = 0;
}

void Draw()
{
	system("cls");

	if (currentScreen == MAIN) // main menu
	{
		for (int i = 0; i < windowWidth; i++)
			cout << "#";
		cout << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		cout << "                     Welcome to Find The Burden!" << endl;
		cout << "                  Disclaimer: Dis game iz just joke" << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		cout << "                   'start' to start 'exit' to exit" << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		for (int i = 0; i < windowWidth; i++)
			cout << "#";

		cout << endl;

		cout << "  Input: ";
	}
	else if (currentScreen == START) // game screen
	{
		for (int i = 0; i < windowWidth; i++)
			cout << "#";
		cout << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		for (int i = 0; i < currentScenario.GetNumLines(); i++)
			cout << currentScenario.GetLines(i) << endl;


		for (int i = 0; i < 2; i++)
			cout << endl;


		for (int i = 0; i < windowWidth; i++)
			cout << "#";

		cout << endl;
		csbiInfo.dwCursorPosition.X = 20;
		csbiInfo.dwCursorPosition.Y -= 10;
		SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
		cout << "  Burden = ";
	}
	else if (currentScreen == END) // game over screen
	{
		for (int i = 0; i < windowWidth; i++)
			cout << "#";
		cout << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		if (endState == OVER)
			cout << "                              Game Over!" << endl;
		else if (endState == COMPLETE)
			cout << "                       You Found ALL The Burdens!" << endl;

		cout << "                           Your Final Score: " << score << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		cout << "                   'main' to go back 'exit' to exit" << endl;

		for (int i = 0; i < 2; i++)
			cout << endl;

		for (int i = 0; i < windowWidth; i++)
			cout << "#";

		cout << endl;

		cout << "  Input: ";
	}

}

void Input()
{
	getline(cin, input);
	if (currentScreen == START)
	{
		// let Logic() check correct answer
		inputAns = input;
	}
}

void GenerateScenario()
{
	// clear memory for scene array
	currentScenario.ClearScenario();

	//generate new scenario
	currentScenario = Scenario(prevS);

	// set new previous
	prevS = currentScenario.GetScene();
}

void Logic()
{
	if (currentScreen == MAIN)
	{
		if (input == "exit")
			gameExit = true;
		else if (input == "start")
		{
			currentScreen = START;
			GenerateScenario();
		}
	}
	else if (currentScreen == START)
	{
		if (inputAns == currentScenario.GetAnswer()) // correct answer
		{
			score++;
			cout << "      That's correct! " << inputAns << " is burden!" << endl;
			cout << "      Your Current Score: " << score << endl;
			Sleep(2000);
			if (currentScenario.CheckLast())
			{
				currentScreen = END;
				endState = COMPLETE;
			}
		}
		else // wrong answer
		{
			cout << "      That's wrong! " << inputAns << " is not burden!" << endl;
			cout << "      Your Final Score: " << score << endl;
			Sleep(3000);
			currentScreen = END;
			endState = OVER;
		}

		GenerateScenario();
	}
	else if (currentScreen == END)
	{
		if (input == "exit")
			gameExit = true;
		else if (input == "main")
		{
			currentScreen = MAIN;
			Init();
		}
	}

}

int main()
{
	Init();
	while (!gameExit)
	{
		Draw();
		Input();
		Logic();
	}

	return 0;
}