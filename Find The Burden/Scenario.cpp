#include <iostream>
#include "Scenario.h"

Scenario::Scenario()
{
	Scenario(0);
}

Scenario::Scenario(int prev)
{
	// set scene to next (linear stages) set prevS in main.cpp to -1
	scene = prev + 1;

	// set scene to random (random stages) set prevS in main.cpp to 0
	/*
	scene = rand() % totalScenarios;

	while (scene == prev)
	scene = rand() % totalScenarios;
	*/

	SetScenario(scene);

}

void Scenario::SetScenario(int sc)
{
	if (sc == 0)
	{
		numLines = 3;
		scenarioLines = new string[3];
		scenarioLines[0] = "             Jake did 18 slides. Mandy did 19 slides. Paul did";
		scenarioLines[1] = "              16 slides. Carmen did 6 slides. Mariana did 21";
		scenarioLines[2] = "                         slides. Find The Burden.";
		answer = "Carmen";
	}
	else if (sc == 1)
	{
		numLines = 3;
		scenarioLines = new string[3];
		scenarioLines[0] = "             Meeting is at 3pm. Adam reach at 2:30pm. Aria reach";
		scenarioLines[1] = "              at 3:02pm. Leonarda reach at 2:50pm. Isla reach at";
		scenarioLines[2] = "                         4:05pm. Find The Burden.";
		answer = "Isla";
	}
}

string Scenario::GetLines(int n)
{
	return scenarioLines[n];
}

string Scenario::GetAnswer()
{
	return answer;
}

int Scenario::GetNumLines()
{
	return numLines;
}

int Scenario::GetScene()
{
	return scene;
}

bool Scenario::CheckLast()
{
	if (scene == totalScenarios - 1)
		return true;

	return false;
}

void Scenario::ClearScenario()
{
	delete[] scenarioLines;
}