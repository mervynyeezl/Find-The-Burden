#include <iostream>
#include <string>

using namespace std;

class Scenario
{
private:
	int numLines;
	int scene;
	int totalScenarios = 2;
	string answer;
	string * scenarioLines;
	void SetScenario(int sc);
public:
	Scenario();
	Scenario(int prev);
	string GetLines(int n);
	string GetAnswer();
	int GetNumLines();
	int GetScene();
	bool CheckLast();
	void ClearScenario();
};
