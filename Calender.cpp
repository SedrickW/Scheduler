/*
*File: Calender.cpp 
*Name: Sedick Webb
*Date: 5-8-21
*Description: Holds the member functions for the Calender class (Calender.h)
*/
#include "Calender.h"

#include <string>
#include <sstream>

using namespace std;

void Calender::SetDate()
{
	int range_for_tm_mon = 31;

	// gets todays date 
	time_t rawTime = time(0);
	struct tm timeNow;
	localtime_s(&timeNow, &rawTime);

	current_month = timeNow.tm_mon; // Sets month between 0-11
	next_month = current_month + 2;
	current_day_num = (timeNow.tm_mday * numOfDaysInEachMonth[current_month ]) / range_for_tm_mon; //Sets day of the month
	current_week_day = timeNow.tm_wday ; // Sets current day of the week 0-6
	Calender::SetRawNextSunday();
	next_sunday = Calender::CheckNextSun(raw_next_sun);
	last_schedule_day = Calender::CheckNextSun (next_sunday + 13);
	return;
}
void Calender::SetRawNextSunday()
{
	raw_next_sun = current_day_num + (7 - current_week_day);// does not carry over to the next month
}
int Calender::CheckNextSun(int day)
{
	if (day < numOfDaysInEachMonth[current_month])
	{
		return day;
	}
	else
	{
		return day - numOfDaysInEachMonth[current_month];
	}
	
}
string Calender::GenerateFilename()// shows incorect month for the last schedule day.
{  // Format: Schedule for (start_date - end_date)
	ostringstream filename;
	
	if (raw_next_sun == next_sunday)
	{
		filename << "Schedule for (" << current_month + 1 <<  "-" << next_sunday << " to "<< next_month << "-" << last_schedule_day << ").csv";
	}
	else
	{
		filename << "Schedule (" << next_month << "-" << next_sunday << "_to_" << next_month << "-" << last_schedule_day << ").csv";
	}	
	
	return filename.str();
}

int Calender::GetFirstSun()
{
	return next_sunday;
}

int Calender::GetCurrentMonth()
{
	return current_month ;
}

int Calender::GetCurrentWeekDay()
{
	return current_week_day + 1;
}
int Calender::GetCurrentDayNumber()
{
	return current_day_num;
}
int Calender::GetSecondSun()
{
	return Calender::CheckNextSun(next_sunday+7);
}
int Calender::GetRawNextSunday()
{
	return raw_next_sun;
}