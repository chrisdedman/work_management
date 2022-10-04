#include <iostream>
#include "work_data.h"

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
            DatabaseClass.getData();
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
