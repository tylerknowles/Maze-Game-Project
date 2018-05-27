#include "Scores.h"
#include "GameInterface.h"


int Scores::CalculateNumLines(string filename)
{
	int NumberOfLines = 0;
	string line;
	ifstream myfile(filename); //file to be calculated

	while (getline(myfile, line)) //while there is still a line in the file
	{
		++NumberOfLines; //increment number of lines
	}
	myfile.close();
	return NumberOfLines;
}

void Scores::CalculateDateTime()
{
	SYSTEMTIME dt;
	GetLocalTime(&dt); //get the current date and time
	CurrentDay = dt.wDay;
	StringDay = to_string(CurrentDay);
	CurrentMonth = dt.wMonth;
	StringMonth = to_string(CurrentMonth);
	CurrentYear = dt.wYear;
	StringYear = to_string(CurrentYear);
	CurrentHour = dt.wHour;
	StringHour = to_string(CurrentHour);
	CurrentMinute = dt.wMinute;
	StringMinute = to_string(CurrentMinute);
	if (StringDay.length() == 1)
	{
		StringDay = "0" + StringDay; //add a 0 to the front as it is an integer by default
	}
	if (StringMonth.length() == 1)
	{
		StringMonth = "0" + StringMonth;
	}
	if (StringHour.length() == 1)
	{
		StringHour = "0" + StringHour;
	}
	if (StringMinute.length() == 1)
	{
		StringMinute = "0" + StringMinute;
	}
	StringDate = StringDay + "/" + StringMonth + "/" + StringYear; //combine the 3 parts to make up the date
	StringTime = StringHour + ":" + StringMinute; //combine the 2 parts to make up the time
}

void Scores::ReadScores()
{
	ifstream ScoresFile("scores.txt");
	ScoresLines = CalculateNumLines("scores.txt");
	for (int i = 0; i < ScoresLines; i++)
	{
		ScoresFile >> tempName;
		ScoresFile >> tempDay;
		ScoresFile >> tempMonth;
		ScoresFile >> tempYear;
		ScoresFile >> tempHour;
		ScoresFile >> tempMinute;
		tempDate = tempDay + "/" + tempMonth + "/" + tempYear; //combine the 3 parts to make up the date
		tempTime = tempHour + ":" + tempMinute; //combine the 2 parts to make up the time

		scoresVector.push_back({ tempName, tempDate, tempTime, tempDay, tempMonth, tempYear, tempHour, tempMinute }); //push it back onto the scores vector

	}
	ScoresFile.close();
}

void Scores::PrintScores()
{
	ReadScores();
	cout << "\t\t\t\tScores" << endl << "----------------------------------------------------------------------" << endl << "\tName\t\t|\tDate\t\t|\tTime" << endl << "----------------------------------------------------------------------" << endl;
	for (int i = ScoresLines - 1; i >= 0; i--)
	{
		cout << "\t" << scoresVector[i].name << "\t\t|\t" << scoresVector[i].date << "\t|\t" << scoresVector[i].time << endl;
	}
	cout << "----------------------------------------------------------------------" << endl << endl << endl << endl;
}

void Scores::WriteScores()
{
	ReadScores();
	CalculateDateTime();
	cout << "Please enter your name: " << endl;
	cin >> StringName;
	scoresVector.push_back({ StringName, StringDate, StringTime, StringDay, StringMonth, StringYear, StringHour, StringMinute });//add the new score to the scores vector

	ofstream scoresfile("scores.txt");
	for (int i = 0; i < scoresVector.size(); i++)
	{
		scoresfile << scoresVector[i].name << "\t\t" << scoresVector[i].day << "\t" << scoresVector[i].month << "\t" << scoresVector[i].year << "\t" << scoresVector[i].hour << "\t" << scoresVector[i].minute << endl;
		//write all the scores in the scores vector to the text file
	}
}