#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Calender.h"

using namespace std;

class Worker
{
public:
    Worker();
    Worker(int& ID, string& name, bool availability[], int scheduled_days[]);
 
    void initialize(int& ID, string& name, bool availability[], int scheduled_days[]);
    bool GetAvailiblty(int day);
    void SetAvailiblty(bool availability,int day);
    void SetSchedule(int schedule, int day);
    int GetSchedule(int day);
    string GetName(); 
    int GetID();

private:
    int employee_ID = 9999;
    string employee_name = "John";
    bool employee_availiblty[7] = { true,true,true,true,true,true,true };
    int employee_scheduled_days[14] = {4,4,4,4,4,4,4,4,4,4,4,4,4,4 }; /*(sunday - saturday) will be filled with e*/
    vector<char> employee_requested_days_off;// deal with later
};
//60s in american history