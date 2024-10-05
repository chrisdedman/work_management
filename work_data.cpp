#include "work_data.h"

void Work::showDatabase()
{
    // This function is printing the data recorded from the file
    totalHours += getHours();

    int H = getHours() / 60; // hours
    int M = getHours() % 60; // minutes

    printf("%s\t%02d:%02d\t\t%s\n", getDay().c_str(), H, M, getTask().c_str());
}

void Work::readData(std::fstream &spreadsheet)
{
    // This function gather data from file.
    Work work;
    spreadsheet.open("time_worked.dat", std::ios::in);

    if (!spreadsheet)
    {
        printf("Database No Found!\n");
        exit(1);
    }

    std::string myDay;
    std::string myTask;
    int myHour;

    printf("\x1B[36mDATE WORKED\033[0m\t\x1B[36mHOURS WORKED\033[0m\t\x1B[36mTASK PERFORMED\033[0m\t\n");
    while (getline(spreadsheet, myDay))
    {
        spreadsheet >> myHour;
        spreadsheet.ignore();
        getline(spreadsheet, myTask);

        work.setDay(myDay);
        work.setHours(myHour);
        work.setTask(myTask);

        work.showDatabase(); // Show the data collected above
    }

    // Calculate the total hours worked according to the recorded data
    int totalH = (work.totalHours / 60); // Total hours worked
    int totalM = (work.totalHours % 60); // Total minutes worked

    printf("\n\x1B[35mTOTAL HOURS WORKED:\033[0m %02d:%02d\n", totalH, totalM);

    spreadsheet.close();
}

void Work::getData()
{
    // This function is gathering the data to be recorded to file.
    std::string myDay;
    std::string myTask;
    int myHour;

    printf("Enter Work Information \x1B[31m[xxx to end]\033[0m\n");
    while (true)
    {
        std::cin.ignore();
        printf("Enter the date worked \x1B[94m[mm/dd/yyyy]\033[0m: ");
        getline(std::cin, myDay);

        if ("xxx" == myDay)
        {
            break;
        }

        setDay(myDay);

        printf("Enter the task accomplished: ");
        getline(std::cin, myTask);
        setTask(myTask);

        printf("Enter the number of hours worked \x1B[94m[in minutes]\033[0m: ");
        scanf("%d", &myHour);
        setHours(myHour);

        makeDatabase(spreadsheet);
    }
}

void Work::makeDatabase(std::fstream &spreadsheet)
{
    // This function is recording data into file.
    spreadsheet.open("time_worked.dat", std::ios::app);

    if (!spreadsheet)
    {
        printf("Database No Found!\n");
        exit(1);
    }

    spreadsheet << getDay() << std::endl
                << getHours() << std::endl
                << getTask() << std::endl;

    spreadsheet.close();
}

void Work::deleteDatabase()
{
    // This function is giving the option to delete the database.
    char deleteDatabase;

    printf("Do you want to delete all records? [Y/n] ");
    std::cin >> deleteDatabase;

    if ('y' == deleteDatabase || 'Y' == deleteDatabase)
    {
        remove("time_worked.dat");
        printf("Database Deleted!\n");
    }
}
