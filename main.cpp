#include <iostream>
#include "functions.h"
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

void App() {
    char choice;
    cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\tWelcome To Food Panda \t\t\t    |" << endl;
    cout << " └─────────────────────────────────────────────────────────────────┘" << endl;
    cout << "Press 'l' to Login. \n";
    cout << "Don't have account? Press 's' to create account : ";
    cin >> choice;
    cin.ignore();

    switch (tolower(choice)) {
        case 's': {
            SignupPage();
            cout << "Now You can Login to Here...\n";
        }
        case 'l': {
            char role = loginPage();
            if(role == 'a'){
                adminPage();
            }
            else if(role=='u'){
                userPage();
            }
            else if(role=='c'){
                chefPage();
            }
            else if(role=='s'){
                staffPage();
            }
            break;
        }
        default: {
            cout << "Invalid Input";
            break;
        }
    }
}

int main() {
    App();
//    adminPage();
//    userPage();
//    chefPage();
//    recipie();

    return 0;
}

