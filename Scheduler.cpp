/*
* File: Scheduler.cpp
* Name : Sedick Webb
* Date : 5 - 8 - 21
* / callender.cpp : This file contains the 'main' function. Program execution begins and ends there.

//ToDo: 
//if possible i would like to add in a ui for the program to run on
*/

/*Libraries*/
#include <iostream>
#include <ctime>/*RandomNum*/
#include <cstdlib>/*RandomNum*/
#include <iomanip> /*main*/
#include <fstream>/*WorkerSetup,GenerateOutputFile*/
#include <sstream>/*GenerateOutputFile*/

/*Header files*/
#include "Calender.h"
#include "Worker.h"


using namespace std;

void MakeSchedule(vector<Worker>& team, Calender& calender, int number_of_workers);
void WorkerSetup(vector<Worker>& employees);// needs to be updated for setting availibility and schedule
void GenerateOutputFile(vector<Worker>& employees, Calender& calender);
int RandomNum(int highest, int lowest);

int main()
{
    srand(time(0));
     
   

    int number_of_workers = 1;

    //creates calender and calculates nessisary dates.
    Calender schedule_calender;
    schedule_calender.SetDate();

    std::cout << "How many workers are stored in workerInfo.txt?(Including manager)" << endl;

    std::cin >> number_of_workers;
    vector<Worker> team(number_of_workers);
    WorkerSetup(team);

    
    int program_state = -1; //Menu = -1, Exit = 0, Generate full schedule = 1, view worker shift = 2 ChangeShift = 3;
    
    // MainMenu
    do
    {
        if (program_state == -1)
        {
            system("cls");
            std::cout << setw(2) << "1...Generate full schedule." << endl
                << "2...View worker's schedule." << endl
                << "3...Change a worker's shift." << endl
                << "0...Output the file and exit program." << endl
                << "What would you like to do?" << endl;

            std::cin >> program_state;
            std::cout << endl;
        }
        else if (program_state == 1)
        {
            system("cls");
            MakeSchedule(team, schedule_calender, number_of_workers);
            std::cout << endl;
            program_state = -1;
            system("pause");
        }
        else if (program_state == 2)
        {
            int worker = 0;
           

            for (int i = 0; i < number_of_workers; i++)
            {
                cout << "worker #" << i << " " << team[i].GetName() << endl;
            }
            std::cout << "What worker's schedule would you like to view?" << endl;
            std::cin >> worker;
            std::cout << endl;

            for (int i = 0; i <= 13; i++)
            {
                std::cout << "Day # " << i << ": " << right << team[worker].GetSchedule(i) << endl;
            }
            program_state = -1;
            system("pause");
        }
        else if (program_state == 3)
        {
            system("cls");
            int worker = 0;
            int day = 0;
            int shift = 0;

            for (int i = 0; i < number_of_workers; i++)
            {
                cout << "worker #" << i <<" " << team[i].GetName() << endl;
            }
            std::cout << "What worker would you like to change?" << endl;
            std::cin >> worker;
            std::cout << endl;

            for (int i = 0; i <= 13; i++)
            {
                std::cout << "Day # "  << i <<": " << right << team[worker].GetSchedule(i) << endl;
            }
            std::cout << "What day are you trying to change?" << endl;
            std::cin >> day;

            std::cout << "1: 1st shift" << endl << "2: 2nd shift" << endl << "3: 3rd shift" << endl << "4: Off" << endl;
            std::cin >> shift;

            team[worker].SetSchedule(shift, day);
            std::cout << "The schedule has been changed." << endl;
            program_state = -1;

            system("pause");
        }

    } while (program_state != 0);
    GenerateOutputFile(team, schedule_calender);
    std::cout << "Program completed.";
    return 0;
}
void MakeSchedule(vector<Worker>& team, Calender& calender, int number_of_workers)
{
    //Fills the schedule for each worker(WIP)
    for (int i = 0; i < number_of_workers; i++)
    {
        for (int a = 0; a < 14; a++)
        {
            std::cout << "we are on day " << a << endl;
            if (a <= 6)
            {
                if (team[i].GetAvailiblty(a) == true)
                {
                    switch (team[i].GetSchedule(a - 1))
                    {
                    case '3':
                        team[i].SetSchedule(RandomNum(2, 3), a);
                        break;
                    default:
                        team[i].SetSchedule(RandomNum(1, 3), a);
                        break;
                    }
                }
            }
            else
            {
                if (team[i].GetAvailiblty(a - 7) == true)
                {
                    switch (team[i].GetSchedule(a - 1))
                    {
                    case '3':
                        team[i].SetSchedule(RandomNum(2, 3), a);
                        break;
                    default:
                        team[i].SetSchedule(RandomNum(1, 3), a);
                        break;
                    }
                }
            }
            team[i].SetSchedule(4, 0);
            team[i].SetSchedule(4, 7);
        }
    }
}

void WorkerSetup(vector<Worker>& employees)
{
    ifstream in_file;
    string filename = "workerInfo.txt";
    int worker_id = 0;
    string worker_name = "N/A";
    int worker_schedule[14] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    char worker_availability_choice = 'w';
    bool worker_availability[7] = { true,true,true,true,true,true,true };


    std::cout << "Pulling information from workerInfo.txt" << endl;
    in_file.open(filename.c_str());

    if (in_file.fail())
    {
        std::cout << "Input file could not be opened." << endl;
        return ;
    }

    for (int i = 0; i < employees.size() ; i++)
    {
        do
        {
            in_file >> worker_id;
            in_file >> worker_name;

            for (int a = 0; a < 7; a++)
            {
                in_file >> worker_availability_choice;

                worker_availability_choice = tolower(worker_availability_choice);
                
                do {
                    switch (worker_availability_choice) {
                    case 't':
                        worker_availability[i] = true;
                        break;

                    case 'f':
                        worker_availability[i] = false;
                        break;
                    default:
                        std::cout << endl << "Not a valid input. Manually input it please.(t/f)" << endl;
                        break;
                    }
                } while (worker_availability_choice != 't' && worker_availability_choice != 'f');
            }
            for (int a = 0; a < 14; a++)
            {
                in_file >> worker_schedule[a];
            }

            employees[i].initialize(worker_id, worker_name, worker_availability, worker_schedule);
        } while (!in_file.end);
    }
    in_file.close();
    std::cout << "Completed..." << endl;
}
void GenerateOutputFile(vector<Worker>& employees, Calender& calender)
{
    stringstream str;
    ofstream out_file;
    string filename = "BuildOutput/" + calender.GenerateFilename();
    
    std::cout << "Opening output file..." << endl;
    
    out_file.open(filename.c_str(), ios::app);
    if(out_file.fail())
    {
        std::cout << "Could not open output file." << endl;
        return;
    }

    //First row
    out_file << calender.GetCurrentMonth()+1 <<"/" <<calender.CheckNextSun(calender.GetRawNextSunday()) << "," << "ID" << "," << "Name" << ',' << ',';
  
    out_file << "Sunday " << calender.GetFirstSun() << ',' << "Monday ," << "Tuesday ," << "Wednsday ," << "Thurseday ," << "Friday ," << "Saturday ," ;
    out_file << "Sunday " << calender.GetSecondSun()  << ',' << "Monday ," << "Tuesday ," << "Wednsday ," << "Thurseday ," << "Friday ," << "Saturday ,";
    out_file << endl;
    
    //Second row
    std::cout << "Filling in manager schedule..." << endl;
    out_file << "Manager," << employees[0].GetID() <<',' <<employees[0].GetName() <<','<<',';
    for (int i = 0; i <= 13; i++)
    {
        out_file << employees[0].GetSchedule(i) << ',';
    }
    out_file << endl;
    std::cout << "Completed." << endl;

    
    //Workers
    std::cout << "Filling workers schedule..." << endl;
    for (int i = 1; i < employees.size(); i++)
    {
        out_file << "Worker " << i <<',' << employees[i].GetID() << ',' << employees[i].GetName() << ',' <<',';
        for (int a = 0; a <= 13; a++)
        {
            out_file << employees[i].GetSchedule(a) << ',';
        }
        out_file << endl;
    }
    out_file.close();
    std::cout << "Schedule completed..." << endl;
}

 int RandomNum(int lowest, int highest)
{
     std::cout << "Generating random number between " << lowest << "-" << highest << endl;
    int randnum;
    
    randnum = (rand() % highest + lowest);
    std::cout << "The number generated is "<< randnum << endl << endl;
    return randnum;
}