#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Calender.h"



class Worker
{
public:
    Worker();
    Worker(int& ID, std::string& name, bool availability[], int scheduled_days[]);
 
    void initialize(int& ID, std::string& name, bool availability[], int scheduled_days[]);
   
    void SetAvailiblty(bool availability,int day);
    void SetSchedule(int schedule, int day);
    const int GetSchedule(int day);
    const std::string GetName();
    const int GetID();
    const bool GetAvailiblty(int day);

private:
    int employee_ID = 9999;
    std::string employee_name = "John";
    bool employee_availiblty[7] = { true,true,true,true,true,true,true };
    int employee_scheduled_days[14] = {4,4,4,4,4,4,4,4,4,4,4,4,4,4 }; /*(sunday - saturday) will be filled with e*/
    std::vector<char> employee_requested_days_off;// deal with later
};