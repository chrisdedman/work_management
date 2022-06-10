#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

struct MyTimeWorked
{
    string day;
    string task;
    int hours;
};

// Prototype
void makeDatabase(fstream &data, vector<MyTimeWorked> &vDB);
void getData(vector<MyTimeWorked> &vDB);
vector<MyTimeWorked> readData(fstream &data);
void showDatabase(vector<MyTimeWorked> vData);

// main function
int main()
{
    vector<MyTimeWorked> vDB;
    fstream data;
    int option;
    cout << "\033[2J\033[1;1H"; // Clear the screen
    cout << "\t\t====== WARRIOR-TORO WORK DONE ======\n"
         << endl;
    cout << "\t\t[1] Record Work Done | [2] Read Work Done" << endl;
    cin >> option;

    if (option == 1)
    {
        getData(vDB);
        makeDatabase(data, vDB);
    }

    else if (option == 2)
    {
        vector<MyTimeWorked> vData = readData(data);
        showDatabase(vData);
    }
    return 0;
}

// Get the dat worked
void getData(vector<MyTimeWorked> &vDB)
{
    MyTimeWorked myWork;
    cout << "Enter Work Information [xxx to end]" << endl;
    while (true)
    {
        cin.ignore();
        cout << "Enter the date worked [mm/dd/yyyy]: ";
        getline(cin, myWork.day);
        if (myWork.day == "xxx")
            break;

        cout << "Enter the task accomplished: ";
        getline(cin, myWork.task);

        cout << "Enter the number of hours worked [in minutes]: ";
        cin >> myWork.hours;
        vDB.push_back(myWork);
    }
}

// Make the database based on the vector data recorded
void makeDatabase(fstream &data, vector<MyTimeWorked> &vDB)
{
    data.open("time_worked.dat", ios::app);
    if (!data)
    {
        cout << "Database No Found!" << endl;
        exit(1);
    }
    for (int index = 0; index < vDB.size(); index++)
    {
        data << vDB[index].day << endl
             << vDB[index].hours << endl
             << vDB[index].task << endl;
    }

    data.close();
}

// Read the database from file
vector<MyTimeWorked> readData(fstream &data)
{
    MyTimeWorked myWork;
    vector<MyTimeWorked> vDB;
    data.open("time_worked.dat", ios::in);
    if (!data)
    {
        cout << "Database No Found!" << endl;
        exit(1);
    }

    while (getline(data, myWork.day))
    {
        data >> myWork.hours;
        data.ignore();
        getline(data, myWork.task);
        vDB.push_back(myWork);
    }
    data.close();

    return vDB;
}

void showDatabase(vector<MyTimeWorked> vData)
{
    int totalWorked = 0;
    cout << setw(15) << left << "DATE WORKED" << setw(15) << left << "HOURS WORKED" << setw(15) << left << "TASK PERFORMED" << endl;
    for (int index = 0; index < vData.size(); index++)
    {
        totalWorked += vData[index].hours;
        if ((vData[index].hours % 60) == 0)
        {
            cout << setw(15) << left << vData[index].day
                 << setw(1) << left << (vData[index].hours / 60)
                 << setw(14) << left << ":00"
                 << setw(15) << left << vData[index].task << endl;
        }

        else
        {
            cout << setw(15) << left << vData[index].day
                 << setw(1) << left << (vData[index].hours / 60)
                 << setw(1) << left << ':'
                 << setw(13) << left << (vData[index].hours % 60)
                 << setw(15) << left << vData[index].task << endl;
        }
    }

    if ((totalWorked % 60) == 0)
    {
        cout << "\nTOTAL HOURS WORKED: " << (totalWorked / 60) << ":00" << endl;
    }
    else
    {
        cout << "\nTOTAL HOURS WORKED: " << (totalWorked / 60) << ':' << (totalWorked % 60) << endl;
    }
}