#pragma once
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Calender
{
public:
	void SetDate(); // called first to set the local date and day of the week
	int CheckNextSun(int day);
	void SetRawNextSunday();
	int GetCurrentMonth();
	int GetCurrentWeekDay();
	int GetCurrentDayNumber();
	int GetFirstSun();
	int GetSecondSun();
	int GetRawNextSunday();
	string GenerateFilename();

private:
	//Constants

	const int numOfDaysInEachMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	//Regular variables
	int current_day_num = 0;
	int current_month = 0;
	int next_month = 0;
	int current_week_day = 99;
	int next_sunday = 0;
	int raw_next_sun = 0;
	int last_schedule_day = 0;

};