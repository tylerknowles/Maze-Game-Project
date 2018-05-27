#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;



class Scores
{
private:
	int ScoresLines;

	string tempName;
	string tempDay;
	string tempMonth;
	string tempYear;
	string tempHour;
	string tempMinute;
	string tempDate;
	string tempTime;

	string CurrentName;
	string StringName;
	string CurrentDate;
	string StringDate;
	string CurrentTime;
	string StringTime;
	int CurrentDay;
	string StringDay;
	int CurrentMonth;
	string StringMonth;
	int CurrentYear;
	string StringYear;
	int CurrentHour;
	string StringHour;
	int CurrentMinute;
	string StringMinute;
	struct scores
	{
		string name;
		string date;
		string time;
		string day;
		string month;
		string year;
		string hour;
		string minute;
	};
	vector<scores> scoresVector;
public:
	int CalculateNumLines(string filename);
	void ReadScores();
	void PrintScores();
	void WriteScores();
	void CalculateDateTime();
};

