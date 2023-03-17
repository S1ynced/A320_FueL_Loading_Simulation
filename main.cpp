#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() {

    srand(time(NULL));
    int fuel, target, limit, totalFuel, timeRemaining;

    fuel = rand() % 500+ 2200;

    cout << "Current Fuel: " << fuel << "kg" << endl;
    cout << "Enter Target: ";
    cin >> target;

    system("cls");
    
    limit = (target - fuel) / 20;
    
//  Time in Seconds(s)
    timeRemaining = ((target - fuel) / 20);

    for (int i = 0; i < limit; i++) {
        fuel += 20;
        cout << "Target Fuel: " << target << "kg" << endl;
        cout << "Refuelling: " << fuel << "kg" << endl;
        timeRemaining--;
        cout << "Estimated Time: " << timeRemaining <<"s";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("cls");
    }
    totalFuel = fuel;
    cout << "Target Fuel: " << target << "kg" << endl;
    cout << "Total Fuel: " << totalFuel << "kg" << endl << endl;
    cout << "Target Reached! Refuelling Completed...";
    cout << endl;
    system("pause>0");
}