#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void drawingAircraft(int totalFuel, int maxTotalFuel, int centerTank, int leftInnerTank, int rightInnerTank, int leftOuterTank, int rightOuterTank, int maxLeftOuter, int maxRightOuter) {
    
    cout << endl;
    cout << setw(63) <<"Total Fuel " << totalFuel << "/"<< maxTotalFuel <<" KG" << endl;
    cout << setw(64) << endl << endl <<"Center Tank " << centerTank << "/6622 KG " << endl <<"\n";
    cout << setw(28) <<"Left Inner Tank " << setw(90) <<"Right Inner Tank "<< endl;
    cout << setw(17) << leftInnerTank <<"/5519 KG" << setw(82) << rightInnerTank << "/5519 KG" << endl;
    cout << setw(59) << "|" << setw(12) << "|" << endl; 

    // Drawing the Engines
    cout << setw(45) <<"__" << setw(4) << "__" << setw(33) << "__" << setw(4) << "__" << endl; 
    cout << setw(42) << "|" <<setw(9) << "|" << setw(8) << "|" << setw(12) << "|" << setw(8) << "|"  << setw(9) << "|" << endl;
    cout << setw(27) << "Left Outer Tank" <<setw(30) << "/" << setw(16) << "\\" <<setw(44) << "Right Outer Tank" << endl;
    cout <<setw(18) << leftOuterTank << "/" << maxLeftOuter << " KG" <<setw(17) << "|" <<setw(9) << "|" << setw(2) << "/" << setw(6);
    cout << "|"  << setw(12) << "|" << setw(6) << "\\" << setw(2) << "|" << setw(9) << "|" << setw(19) << rightOuterTank;
    cout << "/" << maxRightOuter << " KG"<< endl;
    cout << setw(49) << "/" << setw(32) << "\\" << endl;
    cout << setw(42) << "|" <<setw(3) << "/" << setw(14) << "|"  << setw(12) << "|" << setw(14) << "\\" <<setw(3) << "|" << endl;
    cout << setw(41) << "/" << setw(48) << "\\" << endl;
    cout << setw(37) << "/" << setw(22) << "|"  << setw(12) << "|" << setw(22) << "\\" << endl;
    cout << setw(33) << "/" << setw(64) << "\\" << endl;
    cout << setw(29) << "/" << setw(18) << "__" <<setw(4) << "__" <<setw(4) << "__" <<setw(4); 
    cout << "|"  << setw(12) << "|" << setw(4) << "__" << setw(4) << "__" << setw(4) << "__";
    cout <<setw(18) << "\\" << endl;
    cout << setw(25) << "/" << setw(17) << "/" << setw(45) << "\\" <<setw(18) <<"\\" << endl;
    cout << setw(21) << "/" << setw(16) << "/" <<setw(22) << "|"  << setw(12) << "|" << setw(21) << "\\";
    cout << setw(17) << "\\" << endl;
    cout << setw(17) << "/" << setw(14) << "/" << setw(67) << "\\" << setw(15) << "\\" << endl;
    cout << setw(13) << "/" << setw(11) << "/" << setw(35) << "|" << setw(12) << "|" << setw(34);
    cout << "\\" << setw(12) << "\\" << endl;
    cout << setw(9) << "/" <<setw(7) << "/" << setw(97) << "\\" << setw(8) << "\\" << endl;
    cout << setw(8) << "/" << setw(4) << "/" << setw(47) << "|" << setw(12) << "|" << setw(47) << "\\" << setw(4) << "\\" << endl;
    cout << setw(7) << "|" <<setw(116) << "|" << endl;
    cout << setw(59) << "|" << setw(12) << "|" << endl; 
}

int main() {

    SetConsoleTitleA("A320 Fuel Loading Simulation");

    // Set output window's dimesnsions
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 960, 600, TRUE); // 800 width, 100 height

    srand(time(NULL));
    int limit, estimatedTime;
    int currentFuel, targetFuel, totalFuel, maxTotalFuel;
    int centerTank, leftOuterTank, rightOuterTank, leftInnerTank, rightInnerTank;
    int maxLeftInner, maxRightInner, maxLeftOuter, maxRightOuter, maxCenter;
    string refuelStatus, refuelTime;

    // Setting the maximum values of the respective tanks based on manual
    maxCenter = 6622;
    maxLeftInner = maxRightInner = 5519;
    maxLeftOuter = maxRightOuter = 693;
    maxTotalFuel = 19046;

    // Generating a random inital value of the fuel. This range is approximately based on the real-world fuel usage.
    currentFuel = rand() % 700+ 2000;

    totalFuel = currentFuel;

    /*
    - Filling up Outer Tanks 
    - If current fuel is > 1386, set outer tanks to their max
    - If current fuel is < 1386, divide the fuel equally into each tank then fill
    - Fill till respective max capacity is reached then move onto Inner tanks
    */
    leftOuterTank = currentFuel / 2;
    rightOuterTank = currentFuel / 2;

    if (currentFuel >= 1386) {
        leftOuterTank = rightOuterTank = 693;
    }
    else if (currentFuel < 1386) {
        leftOuterTank += 8;
        rightOuterTank += 8;
    }

    /*
    - Filling up Inner Tanks
    - If current fuel is > 11038, set Inner tanks to their max
    - If current fuel is < 11038, divide the fuel equally into each tank then fill
    - Fill till respective max capacity is reached then move onto Inner tanks
    */
    leftInnerTank = (currentFuel / 2) - leftOuterTank;
    rightInnerTank = (currentFuel / 2) - rightOuterTank;

    if (currentFuel >= 12424) {
        leftInnerTank = rightInnerTank = 5519;
    }
    else if (currentFuel < 9653) {
        leftInnerTank += 8;
        rightInnerTank += 8;
    }
    
    /*
      Filling up center tank
    - If current fuel is > 12424, fill center tank till max
    */
    if (currentFuel <= 12424) {
        centerTank = 0;
    }
    if (currentFuel > 12424) {
        centerTank += 16;
    }

    drawingAircraft(totalFuel, maxTotalFuel, centerTank, leftInnerTank, rightInnerTank, leftOuterTank, rightOuterTank, maxLeftOuter, maxRightOuter);

    cout << "\n\n\n";

    if (totalFuel = currentFuel) {
        refuelStatus = "(Ready to Start)";
        estimatedTime = 0;
    }
    else {
        refuelStatus = "(Refuelling...)";
    }

    cout << setw(18) <<"Refuel" << " " << refuelStatus << setw(25);
    cout << "Estimated Time: " << estimatedTime <<" seconds " << "\t" <<endl;

    cout << setw(25) << "Target Fuel: ";
    cin >> targetFuel;
           
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");

    limit = ((targetFuel - currentFuel) / 16) - 1;

    for (int i = 0; i <= limit; i++) {
        refuelTime = "Real";
        currentFuel += 16;
        estimatedTime = (((targetFuel - currentFuel) / 16)) + 1;
        
        /*
          Filling up outer tanks 
        - If current fuel is > 1386, set outer tanks to their max
        - If current fuel is < 1386, divide the fuel equally into each tank then fill
        - Fill till respective max capacity is reached then move onto Inner tanks 
        */
        leftOuterTank = currentFuel / 2;
        rightOuterTank = currentFuel / 2;

        if (currentFuel >= 1386) {
            leftOuterTank = rightOuterTank = 693;
        }
        else if (currentFuel < 1386) {
            leftOuterTank += 8;
            rightOuterTank += 8;
        }

        /*
        - Filling up Inner tanks
        - If current fuel is > 11038, set Inner tanks to their max
        - If current fuel is < 11038, divide the fuel equally into each tank then fill
        - Fill till respective max capacity is reached then move onto Inner tanks
        */
        leftInnerTank = (currentFuel / 2) - leftOuterTank;
        rightInnerTank = (currentFuel / 2) - rightOuterTank;

        if (currentFuel >= 12424) {
            leftInnerTank = rightInnerTank = 5519;
        }
        else if (currentFuel < 9653) {
            leftInnerTank += 8;
            rightInnerTank += 8;
        }

        /*
        - Filling up center tank
        - If current fuel is > 12424, fill center tank till max
        */
        if (currentFuel <= 12424) {
            centerTank = 0;
        }
        if (currentFuel > 12424) {
            centerTank += 16;
        }

        totalFuel = leftOuterTank + rightOuterTank + leftInnerTank + rightInnerTank + centerTank;

        drawingAircraft(totalFuel, maxTotalFuel, centerTank, leftInnerTank, rightInnerTank, leftOuterTank, rightOuterTank, maxLeftOuter, maxRightOuter);

        cout << "\n\n\n";

        if (totalFuel >= targetFuel) {
            refuelStatus = "(Completed....)";
            estimatedTime = 1;
        }
        else {
            refuelStatus = "(Refuelling...)";
        }
        cout << setw(18) <<"Refuel" << " " << refuelStatus << setw(25);

        estimatedTime--;
        cout << "Estimated Time: " << estimatedTime <<" seconds " << endl;

        cout << setw(56) << "Target Fuel: " << targetFuel << " KG" << setw(35);
        cout << "Refuel Time: " << refuelTime << "\t";
            
        std::this_thread::sleep_for(std::chrono::seconds(1));

        COORD cursorPosition;	
        cursorPosition.X = 0;	
        cursorPosition.Y = 0;	
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

        ShowConsoleCursor(false);
    }
    
    drawingAircraft(totalFuel, maxTotalFuel, centerTank, leftInnerTank, rightInnerTank, leftOuterTank, rightOuterTank, maxLeftOuter, maxRightOuter);

    cout << "\n\n\n";

    if (totalFuel >= targetFuel) {
        refuelStatus = "(Completed....)";
        estimatedTime = 1;
    }
    else {
        refuelStatus = "(Refuelling...)";
    }
    cout << setw(18) <<"Refuel" << " " << refuelStatus << setw(25);

    estimatedTime--;
    cout << "Estimated Time: " << estimatedTime <<" seconds " << endl;

    cout << setw(56) << "Target Fuel: " << targetFuel << " KG" << setw(35);
    cout << "Refuel Time: " << refuelTime;

    cout << endl;
    system("pause>0");
    return 0;
}