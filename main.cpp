#include <iostream>
#include "work_data.h"

void MyFile(std::string file);

int main()
{
    MyWork DatabaseClass;

    int option;

    std::cout << "\033[2J\033[1;1H"; // Clear the screen
    std::cout << "\t\t\x1B[94m====== WARRIOR-TORO WORK DONE ======\033[0m\n" << std::endl;
    std::cout << "\t[1] Record Work Done | [2] Read Work Done | [3] Quit\n\t\t\t[4] Delete Record" << std::endl;
    
    while (true)
    {

        std::cin >> option;
        switch (option)
        {
        case 1:
            char archive;

            printf("Would you like to achieve your file? Y/N ");
            std::cin >> archive;

            if ('n' == archive || 'N' == archive)
            {
                DatabaseClass.getData();
            }
            
            else
            {
                std::string dateArchive;
                printf("Add today's date to your file [mm-yy]: ");
                std::cin >> dateArchive;
                MyFile(dateArchive);
            }
            break;

        case 2:
            DatabaseClass.readData(DatabaseClass.spreadsheet);
            break;

        case 3:
            exit(1);

        case 4:
            DatabaseClass.deleteDatabase();
            break;
        
        default:
            break;
        }
    }
    return 0;
}

void MyFile(std::string file)
{
    // This function will archive the current file.
    std::string newFile = "time_worked_" + file + ".dat";
    std::cout << newFile << std::endl;

    rename("time_worked.dat", newFile.c_str());
    printf("File Achieve!\n");
}
