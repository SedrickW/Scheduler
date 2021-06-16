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
#include <random>
#include <iomanip> /*main*/
#include <fstream>/*WorkerSetup,GenerateOutputFile*/
#include <sstream>/*GenerateOutputFile*/

/*Header files*/
#include "Calender.h"
#include "Worker.h"



const void Clear_Screen();
void MakeSchedule(std::vector<Worker>& team, Calender& calender, int number_of_workers);
void WorkerSetup(std::vector<Worker>& employees);// needs to be updated for setting availibility and schedule
void GenerateOutputFile(std::vector<Worker>& employees, Calender& calender);
int RandomNum(int highest, int lowest);

int main()
{
    srand(time(0));
     
   
    
    int number_of_workers = 1;

    //creates calender and calculates nessisary dates.
    Calender schedule_calender;
    schedule_calender.SetDate();

    std::cout << "How many workers are stored in workerInfo.txt?(Including manager)" << '\n';

    std::cin >> number_of_workers;
    std::vector<Worker> team(number_of_workers);
    WorkerSetup(team);

    
    int program_state = -1; //Menu = -1, Exit = 0, Generate full schedule = 1, view worker shift = 2 ChangeShift = 3;
    
    // MainMenu
    do
    {
        if (program_state == -1)
        {
            Clear_Screen();
            std::cout << std::setw(2) << "1...Generate full schedule." << '\n'
                << "2...View worker's schedule." << '\n'
                << "3...Change a worker's shift." << '\n'
                << "0...Output the file and exit program." << '\n'
                << "What would you like to do?" << '\n';

            std::cin >> program_state;
            std::cout << '\n';
        }
        else if (program_state == 1)
        {
            
            Clear_Screen();
            MakeSchedule(team, schedule_calender, number_of_workers);
            std::cout << '\n';
            program_state = -1;
            system("pause");
        }
        else if (program_state == 2)
        {
            int worker = 0;
           

            for (int i = 0; i < number_of_workers; i++)
            {
                std::cout << "worker #" << i << " " << team[i].GetName() << '\n';
            }
            std::cout << "What worker's schedule would you like to view?" << '\n';
            std::cin >> worker;
            std::cout << '\n';

            for (int i = 0; i <= 13; i++)
            {
                std::cout << "Day # " << i << ": " << std::right << team[worker].GetSchedule(i) << '\n';
            }
            program_state = -1;
        }
        else if (program_state == 3)
        {
            Clear_Screen();
            int worker = 0;
            int day = 0;
            int shift = 0;

            for (int i = 0; i < number_of_workers; i++)
            {
                std::cout << "worker #" << i <<" " << team[i].GetName() << '\n';
            }
            std::cout << "What worker would you like to change?" << '\n';
            std::cin >> worker;
            std::cout << '\n';

            for (int i = 0; i <= 13; i++)
            {
                std::cout << "Day # "  << i <<": " << std::right << team[worker].GetSchedule(i) << '\n';
            }
            std::cout << "What day are you trying to change?" << '\n';
            std::cin >> day;

            std::cout << "1: 1st shift" << '\n' << "2: 2nd shift" << '\n' << "3: 3rd shift" << '\n' << "4: Off" << '\n';
            std::cin >> shift;

            team[worker].SetSchedule(shift, day);
            std::cout << "The schedule has been changed." << '\n';
            program_state = -1;

            std::cin.get();
        }

    } while (program_state != 0);
    GenerateOutputFile(team, schedule_calender);
    std::cout << "Program completed.";
    return 0;
}
void MakeSchedule(std::vector<Worker>& team, Calender& calender, int number_of_workers)
{
    //Fills the schedule for each worker(WIP)
    for (auto& worker : team)
    {
        for (int a = 0; a < 14; a++)
        {
            std::cout << "We are on day " << a << '\n';
            if (a <= 6)
            {
                if (worker.GetAvailiblty(a) == true)
                {
                    switch (worker.GetSchedule(a - 1))
                    {
                    case '3':
                        worker.SetSchedule(RandomNum(2, 3), a);
                        break;
                    default:
                        worker.SetSchedule(RandomNum(1, 3), a);
                        break;
                    }
                }
            }
            else
            {
                if (worker.GetAvailiblty(a - 7) == true)
                {
                    switch (worker.GetSchedule(a - 1))
                    {
                    case '3':
                        worker.SetSchedule(RandomNum(2, 3), a);
                        break;
                    default:
                        worker.SetSchedule(RandomNum(1, 3), a);
                        break;
                    }
                }
            }
            worker.SetSchedule(4, 0);
            worker.SetSchedule(4, 7);
        }
    }
}

void WorkerSetup(std::vector<Worker>& employees)
{
    std::ifstream in_file;
    const std::string filename = "workerInfo.txt";
    int worker_id = 0;
    std::string worker_name = "N/A";
    int worker_schedule[14] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    char worker_availability_choice = 'w';
    bool worker_availability[7] = { true,true,true,true,true,true,true };


    std::cout << "Pulling information from workerInfo.txt" << '\n';
    in_file.open(filename.c_str());

    if (in_file.fail())
    {
        std::cout << "Input file could not be opened." << '\n';
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
                        std::cout << '\n' << "Not a valid input. Manually input it please.(t/f)" << '\n';
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
    std::cout << "Completed..." << '\n';
}
void GenerateOutputFile(std::vector<Worker>& employees, Calender& calender)
{
    std::stringstream str;
    std::ofstream out_file;
    std::string filename = "BuildOutput/" + calender.GenerateFilename();
    
    std::cout << "Opening output file..." << '\n';
    
    out_file.open(filename.c_str(), std::ios::app, std::ios::trunc);
    if(out_file.fail())
    {
        std::cout << "Could not open output file." << '\n';
        return;
    }

    //First row
    out_file << calender.GetCurrentMonth()+1 <<"/" <<calender.CheckNextSun(calender.GetRawNextSunday()) << "," << "ID" << "," << "Name" << ',' << ',';
  
    out_file << "Sunday " << calender.GetFirstSun() << ',' << "Monday ," << "Tuesday ," << "Wednsday ," << "Thurseday ," << "Friday ," << "Saturday ," ;
    out_file << "Sunday " << calender.GetSecondSun()  << ',' << "Monday ," << "Tuesday ," << "Wednsday ," << "Thurseday ," << "Friday ," << "Saturday ,";
    out_file << '\n';
    
    //Second row
    std::cout << "Filling in manager schedule..." << '\n';
    out_file << "Manager," << employees[0].GetID() <<',' <<employees[0].GetName() <<','<<',';
    for (int i = 0; i <= 13; i++)
    {
        out_file << employees[0].GetSchedule(i) << ',';
    }
    out_file << '\n';
    std::cout << "Completed." << '\n';

    
    //Workers
    std::cout << "Filling workers schedule..." << '\n';
    for (int i = 1; i < employees.size(); i++)
    {
        out_file << "Worker " << i <<',' << employees[i].GetID() << ',' << employees[i].GetName() << ',' <<',';
        for (int a = 0; a <= 13; a++)
        {
            out_file << employees[i].GetSchedule(a) << ',';
        }
        out_file << '\n';
    }
    out_file.close();
    std::cout << "Schedule completed..." <<'\n';
}

 int RandomNum(int lowest, int highest)
{
    return (rand() % highest + lowest);
}
 
 
const void Clear_Screen()
{
#ifdef _WIN32
     system("cls");
#else
     system("clr");
#endif
     return;
};