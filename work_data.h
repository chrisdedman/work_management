#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


template <class T> 
class MyWork
{
    private:
        std::string day;
        std::string task;
        int hours;
        
    public:
        int getHours() const {return hours; }
        std::string getDay() const { return day; }
        std::string getTask() const { return task; }
        
        void getData();
        void setDay(std::string d) { day = d; }
        void setTask(std::string t) { task = t; }
        void setHours(int h) { hours = h; }

        std::fstream spreadsheet;
        int totalHours;
        void makeDatabase(std::fstream &spreadsheet);
        void readData(std::fstream &spreadsheet);
        void showDatabase();
        void delete_database();
};

template <class T>
void MyWork<T>::showDatabase()
{
    // This function is printing the data recorded from the file
    
    totalHours += getHours();
        
    std::cout << std::setw(15) << std::left << std::setfill(' ') << getDay()
            << std::setw(10) << std::right << std::setfill(' ') << (getHours() / 60)
            << std::setw(1) << std::left << ':'
            << std::setw(2) << std::left << std::setfill('0') << (getHours() % 60)
            << std::setw(4) << std::left << std::setfill(' ') << " "
            << std::setw(20) << std::left << std::setfill(' ') << getTask() << std::endl;
}

template <class T>
void MyWork<T>::readData(std::fstream &spreadsheet)
{
    // This function gather data from file.

    MyWork work;
    spreadsheet.open("database.dat", std::ios::in);
    if (!spreadsheet)
    {
        std::cout << "Database No Found!" << std::endl;
        exit(1);
    }
    
    std::string myDay;
    std::string myTask;
    int myHour;

    std::cout << std::setw(15) << std::left << "\x1B[36mDATE WORKED\033[0m\t" 
                << std::setw(15) << std::left << "\x1B[36mHOURS WORKED\033[0m\t" 
                << std::setw(15) << std::left << "\x1B[36mTASK PERFORMED\033[0m\t" << std::endl;
                
    while (getline(spreadsheet, myDay))
    {
        spreadsheet >> myHour;
        spreadsheet.ignore();
        getline(spreadsheet, myTask);
    
        work.setDay(myDay);
        work.setHours(myHour);
        work.setTask(myTask);

        work.showDatabase();    // Show the data collected above
    }

    // Calculate the total hours worked according to the recorded data
    std::cout << "\n\x1B[35mTOTAL HOURS WORKED:\033[0m " << (work.totalHours / 60) 
                << ":" << std::setw(2) << std::setfill('0') << (work.totalHours % 60) << std::endl;

    spreadsheet.close();
}

template <class T>
void MyWork<T>::getData()
{   
    // This function is gathering the data to be recorded to file.

    std::string myDay;
    std::string myTask;
    int myHour;

    std::cout << "Enter Work Information \x1B[31m[xxx to end]\033[0m" << std::endl;
    while (true)
    {
        std::cin.ignore();
        
        std::cout << "Enter the date worked \x1B[94m[mm/dd/yyyy]\033[0m: ";
        getline(std::cin, myDay);
        if (myDay == "xxx") break;
        setDay(myDay);

        std::cout << "Enter the task accomplished: ";
        getline(std::cin, myTask);
        setTask(myTask);

        std::cout << "Enter the number of hours worked \x1B[94m[in minutes]\033[0m: ";
        std::cin >> myHour;
        setHours(myHour);

        makeDatabase(spreadsheet);
    }
}

template <class T>
void MyWork<T>::makeDatabase(std::fstream &spreadsheet)
{
    // This function is recording data into file.
    
    spreadsheet.open("database.dat", std::ios::app);
    if (!spreadsheet)
    {
        std::cout << "Database No Found!" << std::endl;
        exit(1);
    }

    spreadsheet << getDay() << std::endl
                 << getHours() << std::endl
                 << getTask() << std::endl;

    spreadsheet.close();
}

template <class T>
void MyWork<T>::delete_database()
{
    // This function is giving the option to delete the database.
    
    char deleteDatabase;

    std::cout << "Do you want to delete all records? [Y/n] ";
    std::cin >> deleteDatabase;
    if (deleteDatabase == 'y' || deleteDatabase == 'Y')
    {
        remove("database.dat");
        std::cout << "Database Deleted!\n" << std::endl;
    }
    else return;
}
