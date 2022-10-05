#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>


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
        void deleteDatabase();
};
