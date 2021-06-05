/*
*File: Worker.cpp
*Name: Sedick Webb
*Date: 5-8-21
*Description: Holds the member functions for the Worker class(Worker.h).
*/

#include <iostream>
#include <string>
#include <vector>

//Header files

#include "Worker.h"

using namespace std;

//class functions
Worker::Worker()
{
    employee_name = "Name";
    employee_ID = 0000;
    for (int i = 0; i <= 6; i++)
    {
        employee_availiblty[i] = true;
        employee_scheduled_days[i] = 4;
        //employee_requested_days_off[i];
    }
}

Worker::Worker(int& ID, string& name, bool availability[], int scheduled_days[])
{
    employee_name = name;
    employee_ID = ID;
    for (int i = 0; i <= 6; i++)
    {
        employee_availiblty[i] = availability[i];
        employee_scheduled_days[i] = scheduled_days[i];
        //employee_requested_days_off[i];
    }
}
void Worker::initialize(int& ID, string& name, bool availability[], int scheduled_days[])
{
   // cout << endl << "here.";
    employee_name = name;
    employee_ID = ID;
    for (int i = 0 ; i <= 6 ; i++)
    {
        employee_availiblty[i] = availability[i];
        employee_scheduled_days[i] = scheduled_days[i];
        //employee_requested_days_off[i];
    }
}

void Worker::SetAvailiblty(bool availability, int day)
{
    employee_availiblty[day] = availability;
    return;
}
void Worker::SetSchedule(int schedule,int day)
{
     employee_scheduled_days[day] = schedule;
     return;
}
bool Worker::GetAvailiblty(int day)
{
    return employee_availiblty[day];
}

int Worker::GetSchedule(int day) 
{
    return employee_scheduled_days[day];
}

string Worker::GetName() 
{
    return employee_name;
}

int Worker::GetID()
{
    return employee_ID;
}