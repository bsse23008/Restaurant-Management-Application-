#include <iostream>
#include "functions.h"
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
const string attendanceFilename = "Employees_attendance.txt";
const string messagesFilename = "Employees_messages.txt";

struct Info {
    string fullname;   //Struct used to store delivery information
    string delivery;
    double phoneNumber;
};

const string roles[4] = {"user", "chief", "staff", "admin"};
string deliveryRiders[5] = {
        "Ali", "Ahmad", "AKBAR", "Taqi", "Wasif"
};
int rating;
const int noOfUsers = 200;
const int noOfFields = 5;
string usersInfo[noOfUsers][noOfFields];
int activeUser;

int loginData() {

    int i = 0;
    fstream List("data.txt", ios::in);
    if (!List.is_open()) {
        cout << "\tfile is not opened!!!";
        return 0;
    }
    while (!List.eof()) {
        List >> usersInfo[i][0]     //name at 0 index
             >> usersInfo[i][1]    //Username at 1 index
             >> usersInfo[i][2]    //Email at 2 index
             >> usersInfo[i][3]    //Password at 3 index
             >> usersInfo[i][4];    //admin or costumer
        i++;
    }
    List.close();
    return i;
}

template<class T>

bool loginAuth(T userName, T pass) {
    loginData();
    for (int i = 0; i < noOfUsers; ++i) {
        if ((userName == usersInfo[i][1] || userName == usersInfo[i][2]) && pass == usersInfo[i][3]) {
            activeUser = i;
            return true;
        }
    }
    return false;
}

char loginPage() {

    string role;
    cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\t LOGIN HERE... \t\t\t\t   |" << endl;
    cout << " └─────────────────────────────────────────────────────────────────┘" << endl;

    while (true) {
        string logUserName, password;
        cout << "\tEnter Your UserName or Email : ";
        getline(cin, logUserName);
        cout << "\tEnter Password : ";
        getline(cin, password);
        if (loginAuth(logUserName, password)) {
            role = usersInfo[activeUser][4];
            cout << "\nHi " << usersInfo[activeUser][0] << "\nWelcome on the Board !\n";
            break;
        } else {
            cout << "\n\tCredentials didn't match. Please Try Again.\n\n";
        }
    }

    return role[0];
}


int SignupPage() {
    int nUsers = loginData();
    int type, n, count = 0;
//    const int x=1234;
    cout << endl;
    cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\t CREATE YOUR ACCOUNT... \t\t   |" << endl;
    cout << " └─────────────────────────────────────────────────────────────────┘" << endl;

    string fullName, userName, email, password, reTypePass;

    cout << "Which type of account you formed \n1. User \n2. Chef \n3. Staff \n4. Admin\nEnter :";
    cin >> type;
    if (type == 4) {
        while (true) {
            cout << "\n\tTo form admin account \nEnter code :";
            cin >> n;
            count++;
            if (n != 1234) {
                cout << "\n\t\t**Try again wrong Password**";
            } else if (count == 3 || n == 1234) {
                break;
            }
        }
    }
    cout << "\tEnter Full Name: ";
    cin.ignore();
    getline(cin, fullName);
    int itr;
    while (true) {
        itr = 1;
        cout << "\tEnter User Name : ";
        getline(cin, userName);
        for (int i = 0; i < nUsers; ++i) {
            if (userName == usersInfo[i][1]) {
                ++itr;
            }
        }
        if (itr > 1) {
            cout << "\n\tUser Name Already Taken. Try with New One.\n\n";
        } else {
            break;
        }
    }
    while (itr) {
        itr = 1;
        cout << "\tEnter Email: ";
        getline(cin, email);
        for (int i = 0; i < nUsers; ++i) {
            if (email == usersInfo[i][2]) {
                ++itr;
            }
        }

        if (itr > 1) {
            cout << "\n\tEmail Already Taken. Try with New One.\n\n";
        } else {
            break;
        }
    }
    while (true) {
        cout << "\tEnter Password (at least 8 characters) : ";
        getline(cin, password);
        if (password.length() >= 8) {
            break;
        }
        cout << "\n\tPassword must be at least 8 characters.\n\n";
    }
    do {
        cout << "\tConfirm Password : ";
        getline(cin, reTypePass);
        if (reTypePass != password) {
            cout << "\n\tPasswords Must be Same.\n\n";
        }
    } while (reTypePass != password);
    cout << "\n\tYour account has been created successfully.\n";
    ofstream output("data.txt", ios::app);
        if (output.is_open()) {
            output << fullName << " "
                   << userName << " "
                   << email << " "
                   << password << " "
                   << roles[type - 1] << endl;
        }
    return 0;
}

const int nameOfItems = 100;
template<class T, class K>
struct Menu {
    T name;
    K price, discount;
};


int menuList() {

    string arr[100][3];
    int j = 0;
    ifstream data("menu.txt", ios::in);
    if (data.is_open()) {
        while (!data.eof()) {
            data >> arr[j][0]
                 >> arr[j][1]
                 >> arr[j][2];
            j++;
        }
    } else {
        cout << "\n\t\tNot Open!!!";
    }
    data.close();
    return (j - 1);
}

void viewMenu() {
    Menu<string, int> *menu = new Menu<string, int>[nameOfItems];
    int j = 0;
     char res;
    ifstream data("menu.txt", ios::in);
    if (data.is_open()) {
        while (!data.eof()) {
            data >> menu[j].name >> menu[j].price >> menu[j].discount;
            j++;
        }
        cout << setw(20) << "Food Items" << setw(20) << "\tPrice" << setw(15) << "\tDiscount" << endl;
        for (int i = 0; i < j - 1; i++) {
            cout << setw(2) << i + 1 << ". " << setw(15) << menu[i].name << setw(20) << menu[i].price << " Rs/- only" << setw(15)
                 << menu[i].discount << endl;
        }
       
        cout << " Want a table reservation, press r."
                 "No, press c : ";
        cin >> res;
          if (res == 'r' || res == 'R')
          {
                tableReservation();
          }
          if (res == 'c' || res == 'C')
          {
                cout << " Continuing without making a reservation.\n";
          }
    } else {
        cout << "\n\t\tNot Open!!!";
    }
    data.close();
    delete[] menu; 
}

void addProduct(int noItems) {
    auto *menu = new Menu<string, int>[nameOfItems];
    int n = 1, x;
    int j = 0;
    ifstream data("menu.txt", ios::in);
    if (data.is_open()) {
        while (!data.eof()) {
            data >> menu[j].name
                 >> menu[j].price
                 >> menu[j].discount;
            j++;
        }

        cout << "\nEnter Number of Item you wants to add :";
        cin >> x;
        for (int a = 0; a < x; a++) {
            while (n) {
                n = 1;
                cout << "\nEnter Name of Item (you want to add in list) :";
                cin.ignore();
                getline(cin, menu[a].name);
                for (int i = 0; i < noItems; ++i) {
                    if (menu[i].name == menu[i + 1].name) {
                        ++n;
                    }
                }
                if (n > 1) {
                    cout << "\nItem Name Already Taken. Try with New One.\n";
                } else {
                    break;
                }
            }
            cout << "\nEnter Price of item :";
            cin >> menu[a].price;
            cout << "\nEnter discount on item :";
            cin >> menu[a].discount;
        }
        fstream input("menu.txt", ios::app);
        if (input.is_open()) {
            for (int i = 0; i < x; i++) {
                input << menu[i].name << " ";
                input << menu[i].price << " ";
                input << menu[i].discount << endl;
            }
            input.close();
        }

        cout << "\n\tFood Added Successfully ! " << endl;
        viewMenu();
    }
    delete [] menu;
}

void deleteProduct(int noItems) {
    auto *menu = new Menu<string, int>[nameOfItems];
    int j = 0;
    ifstream input("menu.txt", ios::in);
    if (input.is_open()) {
        while (!input.eof()) {
            input >> menu[j].name
                  >> menu[j].price
                  >> menu[j].discount;
            j++;
        }
    } else {
        cout << "\nNot Open";
    }
    input.close();
    int position;
    cout << "\nEnter Index of item which you wants to remove :";
    cin >> position;
    for (int i = position - 1; i <= noItems; i++) {
        menu[i] = menu[i + 1];
    }

    for (int i = 0; i < noItems - 1; i++) {
        cout << i + 1 << ".  " << menu[i].name << setw(5) << menu[i].price << setw(5) << menu[i].discount << endl;
    }
    ofstream data("menu.txt", ios::out);
    if (data.is_open()) {
        for (int i = 0; i < noItems - 1; i++) {
            data << menu[i].name << " "
                 << menu[i].price << " "
                 << menu[i].discount << endl;
        }
    }
    delete [] menu;
}

template<typename T, typename K>
struct Stock {
    T name;
    K quantity;
};

int stockNumber() {
    int i = 0;
    string name;
    ifstream input("stock.txt", ios::in);
    if (input.is_open()) {
        while (!input.eof()) {
            getline(input, name);
            i++;
        }
    }
    input.close();
    return (i - 1);
}



void viewStock() {
    int i = 0, noOfStock = stockNumber();
    auto *arr2 = new Stock<string, int>[noOfStock];
    ifstream input("stock.txt", ios::in);
    if (input.is_open()) {
        while (!input.eof()) {
            input >> arr2[i].name
                  >> arr2[i].quantity;
            i++;
        }
    }
    for (int j = 0; j < noOfStock; j++) {
        cout << "\n" << j + 1 << " ." << arr2[j].name << "\t\tQuantity :" << arr2[j].quantity << endl;
    }
    input.close();
    delete[] arr2;
}

struct Recipes {
    string name;
    string item[5];
};
Recipes arr[100];

void recipe() {
    int num, count = 0;
    Stock<string, int> arr1;

    cout << "\nEnter number of items to add: ";
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "\nEnter name of Item first";
        cin >> arr[i].name;
        for (int j = 0; j < 4; j++) {
           cout << "\n Then its "<<j+1<< " recipe items :";
            cin >> arr[i].item[j];
        }
    }
    for (int i = 0; i < num; i++) {
        cout << arr[i].name << " ";
        for (int j = 0; j < 4; j++) {
            cout << arr[i].item[j] << " ";
        }
        cout << endl;
    }
    ofstream data("ingredient.txt", ios::app);
    if (data.is_open()) {
        for (int i = 0; i < num; i++) {
            data << "\n" << arr[i].name << " ";
            for (int j = 0; j < 4; j++) {
                data << arr[i].item[j] << " ";
            }

        }
    } else {
        cout << "\n\tnot open!";
    }
    data.close();
}
void editStock(const string& itemName, int quantity) {
    int noOfStock = stockNumber();
    auto *arr2 = new Stock<string, int>[noOfStock];
    ifstream input("stock.txt", ios::in);
    if (input.is_open()) {
        for (int i = 0; i < noOfStock; i++) {
            input >> arr2[i].name >> arr2[i].quantity;
            if (arr2[i].name == itemName) {
                // Update stock based on the order
                arr2[i].quantity -= quantity;
                if (arr2[i].quantity < 0) {
                    arr2[i].quantity = 0; // Ensure non-negative quantity
                }
            }
        }
        input.close();

        // Rewrite updated stock to the file
        ofstream output("stock.txt", ios::out);
        if (output.is_open()) {
            for (int i = 0; i < noOfStock; i++) {
                output << arr2[i].name << " " << arr2[i].quantity << endl;
            }
            output.close();
        } else {
            cout << "\n\tFile is not open for writing\n";
        }
    } else {
        cout << "\n\tFile is not open\n";
    }

    delete[] arr2;
}
void leaveMessage(const string &employeeName, const string &message) {
    ofstream messagesFile(messagesFilename, ios::app);
    if (messagesFile.is_open()) {
        messagesFile << employeeName << " " << message << endl;
        cout << " Message Store by name " << employeeName << endl;
        messagesFile.close();
    } else {
        cout << "Unable to leave a message for the employee." << endl;
    }
}

//                                                                                            //admin functionality
void adminPage() {
    const int x = 100;
    int totalPri = 0;
    int *total = new int[x];
    int *profitArr = new int[x];
    int num, check;
    string deli[100];
//int pos;
    cout << "\n\t\t*Welcome to Admin page*";
    cout << "\npress 1 to change menu \npress 2 to change stock \npress 3 to see delivery data \npress 4 to check profit \npress 5 to write note to someone ";
    cout << "\nEnter :";
    cin >> check;
    if (check == 1) {
        viewMenu();
        int nItems = menuList(), num1;
        cout << "\n1. to add Product \t\t2. to delete product ";
        cout << "\t\nEnter :";
        cin >> num1;
        if (num1 == 1) {
            addProduct(nItems);
        } else if (num1 == 2) {
            deleteProduct(nItems);
        }

    } else if (check == 2) {
        cout << "\n\n\t**Stock you provide last time**";
        viewStock();
        cout << "\nEnter number of item you wants to add :";
        cin >> num;
        auto *arr1 = new Stock<string, int>[num];
//        stock arr1[num];
        for (int i = 0; i < num; i++) {
            cout << "\nEnter Name of item :";
            cin.ignore();
            getline(cin, arr1[i].name);
            cout << "\nEnter Quantity :";
            cin >> arr1[i].quantity;
        }
        ofstream output("stock.txt", ios::app);
        if (output.is_open()) {
            for (int i = 0; i < num; i++) {
                output << arr1[i].name << "  "
                       << arr1[i].quantity << endl;
            }
        }
        output.close();
        viewStock();
    } else if (check == 3) {
        int i = 0;
        ifstream data("Delivery record.txt", ios::in);
        if (data.is_open()) {
            while (true) {
                getline(data, deli[i]);
                i++;
                if (data.eof()) {
                    break;
                }
            }
        } else {
            cout << "Not open";
        }
        cout << "value " << i;
        cout << "\n\t\tDelivery info " << endl;
        for (int j = 0; j < i - 1; j++) {
            cout << deli[j] << "\n";
        }
        data.close();
    } else if (check == 4) {

        ifstream data("profit.txt", ios::in);
        int num1 = 0;
        if (data.is_open()) {
            while (true) {
                data >> profitArr[num1];
                if (data.eof()) {
                    break;
                }
                num1++;
            }
        }

        for (int j = 0; j < 1; j++) {
            for (int i = 0; i < num1; i++) {
                totalPri += profitArr[i];
                total[j] = profitArr[i];
            }
        }
        cout << "\t\nTotal Profit is given as: " << totalPri;
        data.close();
    }
    if (check == 5) {
        string employeeName,message;
        cout << "Enter the name of employee: ";
        cin.ignore();
        getline(cin, employeeName);
        cout << "Enter the message for the employee: ";
        getline(cin, message);
        leaveMessage(employeeName, message);
    }
//editStock(pos);                                                   //optional thing
delete []total;
    delete []profitArr;
}

//struct

//chief functionality
int noOfOrder;

void chefPage() {
    auto *menu = new Menu<string, int>[nameOfItems];
    int k = 0, n;
    string b;
    cout << "\n\t\t*Welcome to chef Page*";
    while (true) {
        cout << "\n1. To add recipe \n2. To review order \n3. To View Stock \n4. To Edit Stock" << endl;
        cout << "From The Above Options Enter The Task Number that you want to execute \n(Enter a negative Value to Stop) :";

        cin >> n;
      if (cin.fail()){
          cin.clear();
          cin.ignore(100,'\n');
          cout << "Invalid input. Please enter a valid number." << endl;
          continue;
      }

        if (n == 1) {
            recipe();
        } else if (n == 2) {
            int arr1[10];
            int k1 = 0;
            ifstream input1("order.txt", ios::in);
            if (input1.is_open()) {
                while (!input1.eof()) {
                    input1 >> arr1[k1];
                    k1++;
                }
            } else {
                cout << "\n\tFile is not open";
            }
            input1.close();
            int j = 0;
            ifstream data("menu.txt", ios::in);
            if (data.is_open()) {
                while (!data.eof()) {
                    data >> menu[j].name
                         >> menu[j].price
                         >> menu[j].discount;
                    j++;

                }
            }
            data.close();
            ifstream input("ingredient.txt", ios::in);
            if (input.is_open()) {
                while (true) {
                    input >> arr[k].name;
                    for (int l = 0; l < 4; l++) {
                        input >> arr[k].item[l];
                    }
                    k++;
                    if (input.eof()) {
                        break;
                    }
                }
            }
            input.close();
            int i = 0;
            while (true) {
                cout << "\n" << i + 1 << "." << "Name :" << menu[arr1[i]].name;
                if (i == (k1 - 2)) {
                    break;
                }
                i++;
            }
            for (int m = 0; m < k1; m++) {
                int index = 0;
                for (int l = 0; l < k - 1; l++) {
                    if (menu[arr1[m]].name == arr[l].name) {
                        index += l;
                        cout << "\nname :" << arr[index].name << "\tRecipe :";
                        for (int o = 0; o < 4; o++)
                            cout << arr[index].item[o] << "  ";
                    }
                }
            }
        } else if (n == 3) {
            viewStock();
        } else if (n == 4) {
            string itemName;
            int quantity;
            cout << "Enter item name to edit: ";
            cin >> itemName;
            cout << "Enter quantity to deduct: ";
            cin >> quantity;
            editStock(itemName, quantity);
            cout << "Stock updated successfully!\n";
        }
        else {
            cout << "Invalid Choice. Please enter a valid option." << endl;
            delete[] menu;
            continue;
        }
    }
}

//Mark attendance for an employee
void mark_Attendance(const string &employee_Name) {
    ofstream attendanceFile(attendanceFilename, ios::app);
    if (attendanceFile.is_open()) {
        attendanceFile << employee_Name << " is present.." << endl;
        cout << "Attendance is marked for " << employee_Name << "." << endl;
        attendanceFile.close();
    } else {
        cout << "Unable to open the employees attendance file." << endl;
    }
}

//Check if there are any messages for an employee
void check_Messages(const string &employeeName) {
    ifstream messagesFile(messagesFilename);
    string line;

    bool found = false;

    if (messagesFile.is_open()) {
        while (getline(messagesFile, line)) {
            size_t foundPos = line.find(employeeName);
            if (foundPos != string::npos) {
                string message = line.substr(foundPos + employeeName.length() + 1);
                cout << "There is a message for " << employeeName << endl;
                cout << message << endl;
                found = true;
            }
        }
        messagesFile.close();
    }

    if (!found) {
        cout << "No messages are found for " << employeeName << "." << endl;
    }
}


//staff or cleaner functionality
void staffPage() {
    cout << "\n\t\t**Welcome to staff page**";
    int choice;
    string employeeName, message;

    while (true) {
        cout << "Employee Attendance and Messaging System" << endl;
        cout << "1. Mark Attendance" << endl;
        cout << "2. Check Messages" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the name of employee: ";
                cin.ignore();
                getline(cin, employeeName);
                mark_Attendance(employeeName);
                break;
            case 2:
                cout << "Enter the name of employee: ";
                cin.ignore();
                getline(cin, employeeName);
                check_Messages(employeeName);
                break;
            case 3:
                cout << "Program is closing.." << endl;
            default:
                cout << "This choice is invalid. Please enter a valid choice." << endl;
        }
    }

}

struct Price {
    string name;
    int price;
};

void profit(const int name[], const int sale[], int item, const int amount[]) {
    int profitArr[100];
    auto *menu = new Menu<string, int>[nameOfItems];
    int j = 0;
    ifstream input("menu.txt", ios::in);
    if (input.is_open()) {
        while (!input.eof()) {
            input >> menu[j].name
                  >> menu[j].price
                  >> menu[j].discount;
            j++;
        }
    } else {
        cout << "\nNot Open";
    }
    input.close();
    int k = 0;
    Price quantity[10];
    ifstream file("orignal_price.txt", ios::in);
    if (file.is_open()) {
        while (true) {
            file >> quantity[k].name
                 >> quantity[k].price;
            k++;
            if (file.eof()) {
                break;
            }
        }
    }
    for (int i = 0; i < item; i++) {
        for (int m = 0; m < k - 1; m++) {
            if (menu[name[i]].name == quantity[m].name) {
                profitArr[i] = sale[i] - (amount[i] * quantity[m].price);
            }
        }
    }
    file.close();
    ofstream data("profit.txt", ios::app);
    if (data.is_open()) {
        for (int i = 0; i < item; i++) {
            data << profitArr[i] << " ";
        }
        data << endl;
    }
    data.close();
    delete[] menu;
}

struct Feedback {
    int foodRating;
    int staffRating;
    int cleanlinessRating;
    int returnVisit;
    int overallExperienceRating;
    string chefComment;
    string customerName;
    string phoneNumber;
    string email;
    string suggestions;
    string complaints;
    int customerPoints;
    int chefPoints;
};

void adjustChefSalary(double chefSalary, int rating) {
    if (rating < 3) {
        // 20% salary decrease
        chefSalary *= 0.8;
        cout << "Chef's salary decreased by 20% due to low rating." << endl;
    }
}

void collectFeedback(Feedback &feedback, double chefSalary) {
    cout << "Please rate the food on a scale of 1 to 5 (1 = Poor, 5 = Excellent): ";
    cin >> feedback.foodRating;
    if (feedback.foodRating == -1) {
        return;
    }
    if (feedback.foodRating < 1 || feedback.foodRating > 5) {
        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
        return;
    }
    cout << "Please rate the staff  (1 = Poor, 5 = Excellent): ";
    cin >> feedback.staffRating;
    if (feedback.staffRating < 1 || feedback.staffRating > 5) {
        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
        return;
    }
    cout << "Please rate the cleanliness.(1 = Poor, 5 = Excellent): ";
    cin >> feedback.cleanlinessRating;
    if (feedback.cleanlinessRating < 1 || feedback.cleanlinessRating > 5) {
        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
        return;
    }

    cout << "Please rate your overall dining experience (1 = Poor, 5 = Excellent): ";
    cin >> feedback.overallExperienceRating;
    if (feedback.overallExperienceRating < 1 || feedback.overallExperienceRating > 5) {
        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
        return;
    }
    cin.ignore();
    cout << "Will you return to our restaurant? (1 for Yes, 0 for No): ";
    cin >> feedback.returnVisit;
    cin.ignore();
    cout << "Please provide any additional suggestions: ";
    getline(cin, feedback.suggestions);
    cout << "Please provide any complaints or areas of improvement: ";
    getline(cin, feedback.complaints);
    cout << "Please rate the food prepared by the chef on a scale of 1 to 5 (1 = Poor, 5 = Excellent): ";
    cin >> feedback.foodRating;
    // Adjust chef's salary based on food rating
    adjustChefSalary(chefSalary, feedback.foodRating);
    double customer_discount_rate = 0.1;
    cin.ignore();
    cout << "Please leave your comments about the food prepared by the chef: ";
    getline(cin, feedback.chefComment);
    feedback.customerPoints = customer_discount_rate * feedback.overallExperienceRating * 100;
}

void saveFeedback(Feedback &feedback) {
    ofstream feedbackFile("restaurant_feedback.txt", ios::app);
    ofstream contactFile("customer_contacts.txt", ios::app);

    feedbackFile << "Customer Name: " << feedback.customerName << endl;
    feedbackFile << "Food Rating: " << feedback.foodRating << endl;
    feedbackFile << "Staff Rating: " << feedback.staffRating << endl;
    feedbackFile << "Cleanliness Rating: " << feedback.cleanlinessRating << endl;

    if (feedback.returnVisit == 1) {
        feedbackFile << "Customer will return to the restaurant." << endl;
    } else {
        feedbackFile << "Customer will not return to the restaurant." << endl;
    }

    feedbackFile << "Overall Experience Rating: " << feedback.overallExperienceRating << endl;
    feedbackFile << "Suggestions: " << feedback.suggestions << endl;
    feedbackFile << "Complaints: " << feedback.complaints << endl;
    feedbackFile << "Chef Points: " << feedback.chefPoints << endl;

    contactFile << "Customer Name: " << feedback.customerName << endl;
    contactFile << "Phone Number: " << feedback.phoneNumber << endl;
    contactFile << "Email: " << feedback.email << endl;

    feedbackFile.close();
    contactFile.close();
}

void feedback() {
    const int maxCustomers = 10;
    Feedback feedbackData[maxCustomers];
    int numCustomers = 0;

    double chefSalary = 1000.0;

    cout << "Welcome to the restaurant feedback system!" << endl;

    while (numCustomers < maxCustomers) {
        collectFeedback(feedbackData[numCustomers], chefSalary);

        if (feedbackData[numCustomers].foodRating == -1) {
            break;
        }

        cout << "Please provide your contact information for special offers:" << endl;
        cout << "Name: ";
        getline(cin, feedbackData[numCustomers].customerName);
        cout << "Phone Number: ";
        getline(cin, feedbackData[numCustomers].phoneNumber);
        cout << "Email: ";
        getline(cin, feedbackData[numCustomers].email);

        saveFeedback(feedbackData[numCustomers]);

        numCustomers++;

        cout << "Thank you for your feedback and contact information! It has been recorded." << endl;
        cout << "Enter -1 to finish entering feedback, or continue for the next customer." << endl;
    }

    cout << "Final Chef Salary: $" << chefSalary << endl;

    for (int i = 0; i < numCustomers; ++i) {
        cout << "Customer Points for " << feedbackData[i].customerName << ": " << feedbackData[i].customerPoints
             << endl;
    }

}

//  user Controls
int userPage() {
    auto *menu = new Menu<string, int>[nameOfItems];
    int j = 0;
    float priceAfterTax = 0;
    ifstream input("menu.txt", ios::in);
    if (input.is_open()) {
        while (!input.eof()) {
            input >> menu[j].name
                  >> menu[j].price
                  >> menu[j].discount;
            j++;
        }
    } else {
        cout << "\nNot Open";
    }
    input.close();
    int amount[10];
    int num[100];
    int totalDiscount[100], totalPrice[100], Final = 0;
    int x;
    int y;
    struct Info F;
    cout << "\n\t**Welcome to User page**\t";
    cout << "\n\t\t*Today's Menu*" << endl;
    viewMenu();
    while (true) {
        cout << "\nEnter the Index of the item (or any negative value to finish):";
        cin >> num[noOfOrder];
        if (cin.fail()) {
            cout << "\n*Invalid Input*\n(enter numerical Value)";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        if (num[noOfOrder] < 0) {
            break;
        }
        cout << "\nEnter Quantity :";
        cin >> amount[noOfOrder];
        noOfOrder++;
    }
    for (int a = 0; a < noOfOrder; a++) {
        num[a] = num[a];                                                      //for original index of Items now num[a] has original index
    }
    for (int a = 0; a < noOfOrder; a++) {
        num[a] = num[a] -
                 1;                                                      //for original index of Items now num[a] has original index
    }
    ofstream output("order.txt", ios::out);
    if (output.is_open()) {
        int count = 0;
        while (true) {
            output << num[count] << " ";
            count++;
            if (count == noOfOrder) {
                break;
            }
        }
    }

    for (int a = 0; a < noOfOrder; a++) {
        int price = 0, discount = 0;
        price += menu[num[a]].price;
        discount += menu[num[a]].discount;
        totalDiscount[a] = (price * discount) / 100;                          //find discount amount on item
        totalPrice[a] = menu[num[a]].price - totalDiscount[a];                //final price of item
        cout << "\n amount " << amount[a];
        totalPrice[a] = (totalPrice[a] * amount[a]);
        Final += totalPrice[a];                                               //total bill of user after discount
    }

    float taxRate = 17;
    priceAfterTax = calculateSalesTax<float>(Final, taxRate);

    cout << "\n\t\t\tYour Ordered: "
         << "\n\n";
    cout << "*Products*\t"
         << "   *Discount*\t"
         << "  *Quantity*\t"
         << "  *After Discount*"
         << "\tTax Included(17%)"
         << "\n\n";
    for (int a = 0; a < noOfOrder; a++) {

        float itemPrice = totalPrice[a];
         priceAfterTax  = calculateSalesTax <float> (itemPrice, taxRate);
         

        cout << a + 1 << "."
             << menu[num[a]].name << setw(17)
             << menu[num[a]].discount << "%" << setw(15)
             << amount[a] << setw(17)
             << totalPrice[a] << setw(20)
             << priceAfterTax
             << "\n";
    }
    cout << "\t\tTotal Bill:" << priceAfterTax;

    while (true) {
        cout << "\nPress 1 to select delivery and 0 to dine in (negative value to escape) :  " << endl;
        cin.ignore();
        cin >> y;
        if(y < 0){
            break;
        }
        else if (y == 1) {
            int r;
            cout << "Enter customers  fullname " << endl;
            cin >> F.fullname;
            cout << "Enter customers phone number " << endl;
            cin >> F.phoneNumber;
            cout << "Enter customers full address " << endl;
            cin.ignore();
            getline(cin, F.delivery);
            cout << "\n\t\t\t\t**The delivery information**" << endl;
            cout << "The fullname of the customer is  : " << F.fullname << endl;
            cout << "The address of the customer is  : " << F.delivery << endl;
            cout << "The phone number of the customer is  : " << F.phoneNumber << endl;
            cout << "The selected items and payable amount is  : " << endl;
            for (int a = 0; a < noOfOrder; a++) {
                cout << a + 1 << "."
                     << menu[num[a]].name << "\t\t"
                     << menu[num[a]].discount << "%" << "\t\t"
                     << totalPrice[a] << "\n";

            }
            while (true) {
                cout << "\nEnter the rider rating from (1-5) according to the customer reviews " << endl;
                cin >> rating;
                if (rating >= 1 && rating <= 5) {
                    ofstream deliv("Delivery record.txt", ios::app);
                    if (deliv.is_open()) {
                        deliv << "Rating is " << rating << endl;
                        deliv << "The selected food and total price is " << endl;
                        for (int a = 0; a < noOfOrder; a++) {
                            deliv << a + 1 << "."
                                  << menu[num[a]].name << "\t\t"
                                  << menu[num[a]].discount << "%" << "\t\t"
                                  << totalPrice[a] << "\n";
                        }
                    }
                    break;
                } else {
                    cout << "Invalid input" << endl;
                    continue;
                }
            }
        }
            else if (y == 0) {
            string y;
            cout << "select the avalible table from (1to10) " << endl;
            cin >> x;
            ofstream order("kitchen.txt", ios::app);
            if (order.is_open()) {
                order << "Order for table no " << x << endl;
                order << "The selected food is " << endl;
                for (int a = 0; a < noOfOrder; a++) {
                    order << a + 1 << "."
                          << menu[num[a]].name << "\t\t" << endl;
                }
            }
            cout << "Complete info of order for table num " << x << "has been sent to kitchen department " << endl;
            cout << "Enter the customers review on the food " << endl;
            getline(cin,y);
            ofstream review("Food reviews.txt", ios::app);
            if (review.is_open()) {
                review << "The review from the table no " << x << " is " << endl;
                review << y << endl;
            }
            cout << "Thanks for coming ." << endl;
           
            break;
        }
        else
        {
            cout << " Invalid Input !" << endl;
            continue;
        }
    }
     feedback();

}

// float calculateSalesTax(float itemPrice, float taxRate) {

//     float taxAmount = (taxRate / 100.0) * itemPrice;

//     float priceAfterTax = itemPrice + taxAmount;

//     return priceAfterTax;
// }

template <typename T>
T calculateSalesTax(T itemPrice, T taxRate) 
{
    T taxAmount = (taxRate /(100.0)) * itemPrice;
    T priceAfterTax = itemPrice + taxAmount;
    return priceAfterTax;
}




struct Reservation{
    string name, date, time, phoneNo;
    int    noOfGuests,tableNo;
};

static const int totalTables = 30; 

bool isValidContactNumber(string &phoneNo)
{
    if (phoneNo.length() != 12 || phoneNo[1] != '3'  ||  phoneNo[4] != '-')
    {
        return false;
    }
    else
        return true;
}
bool isValidDate(string &date)
{
        if (date.length() != 10 ||
        date[2] != '-' ||
        date[5] != '-' ||
        date[0] < '0' || date[0] > '1' ||  
        (date[0] == '0' && (date[1] < '1' || date[1] > '9')) ||  
        (date[0] == '1' && (date[1] < '0' || date[1] > '2')) ||  
        date[3] < '0' || date[3] > '3' ||  
        (date[3] == '0' && (date[4] < '1' || date[4] > '9')) ||  
        (date[3] == '3' && (date[4] != '0')) ||  
        date[6] != '2' ||  
        date[7] != '0' ||
        date[8] != '2' ||
        date[9] != '3') {
        return false;
    }
        else 
        {
            return true;
        }
    
}   

bool isValidTime(string &time)
{
    if (time[0] > '2' || (time[0] == '2' && time[1] > '3') || time[2] != ':'|| time[3] > '5' || (time[3] == '5' && time[4] > '9'))
    {
        return false;
    }
    return true;
}

      int noOfExistingRes = 0;
      Reservation existingRes[totalTables];
   
bool checkExistingRes(){
        
        string exist;
       
        ifstream res("Reservation.txt", ios::in);

               if (!res.is_open()){
                    cout << "Error opening the file !";
       }else
            { while(getline(res, exist)) 
            {
                    
                       noOfExistingRes++; 
                
            }  
              
                res.close(); 
              
                if (noOfExistingRes >= totalTables){
                  return false;
            }     
        }
       return true;  
    }

bool dataStore(string date1, string time1, int table1){

        string *name = new string    [noOfExistingRes+1]; 
        string *date    = new string [noOfExistingRes+1];
        string *time    = new string [noOfExistingRes+1];
        int  * tableNo  = new int    [noOfExistingRes+1];

ifstream read("Reservation.txt", ios::in);

if (!read.is_open()){
         cout << "File not opened";
} else

{
        int i=0;
        while(!read.eof() && i < noOfExistingRes+1){

                    
                   read  >> name[i]
                         >> name[i]
                         >> date[i]
                         >> time[i]
                         >> name[i]
                         >> tableNo[i];
                  i++;
} } 


            for (int k=0 ; k < noOfExistingRes+1; k++){
                if (date1 == date[k]  && time1 == time[k] && table1 == tableNo[k]){
                    delete[] name;               
                    delete[] date;
                    delete[] time;
                    delete[] tableNo;
                   return true;
                }           
            }
            delete[] name;
            delete[] date;
            delete[] time;
            delete[] tableNo;
            return false;
      

    }


void showTables(){

    const int rows  = 3;
    const int  cols = 3;
    cout << " \n\n \tAvailable Tables at Food Corner\n"   << endl;
       for (int i=1 ; i <=totalTables; i++){
           cout << "\t Table "<<i << "\t\t";
          if (i%3 == 0){
            cout << endl;
         }
      }
}
void tableReservation(){
   
        cout << endl;
        cout << "\t\t\t =============================\n";
        cout << "\t\t\t | Table Reservation System  |\n";
        cout << "\t\t\t =============================\n";
    
       Reservation n;
       cout << " Enter your full name  : ";
       cin.ignore();
       getline(cin, n.name);

        while(true){

            cout << " \n Enter the no of guests : ";
            if (cin >> n.noOfGuests) {
            if (n.noOfGuests > 10) 
            {
                cout << "Sorry! We can't accommodate more than 10 people at a time." << endl;
            } else 
            {
                break; 
            }
        } else 
        {
            cout << "Invalid input. Please enter a valid number of guests." << endl;
            cin.clear(); 
            cin.ignore(); 
        }
    }
       
        
        while (true){
                   
                    cout << " \n Enter the date (e.g., MM-DD-YYYY): ";
                    cin  >> n.date;

                    if (isValidDate(n.date))
                    {
                        break;
                    }
                    else
                    {
                        cout << "\t Invalid Date Format! Please Try Again." << endl;
                    }
              
        }
    
       while(true){
             
 
             cout << " \n Enter your desired time slot e.g.,(23 : 00) : "; 
             
             cin  >> n.time;

             if(isValidTime(n.time)) 
             {           
                    break;
             }
             else
             {
                     cout << "\tInvalid Time Format! Please try again"<<endl;
             
             }
       }

        while (true) {

                cout << " \n Enter your contact number (e.g., 0300-0000000): ";
                cin.ignore();
                cin  >> n.phoneNo;
                if (isValidContactNumber(n.phoneNo)) 
                {                 
                         break;
                }
                else 
                {
                    cout << "Invalid Number. Please enter a valid number in the format 0300-0000000.\n";
                }
            }

    int itr =0;
        while(true){
retrytable:
            cout << " Enter your desired table : ";
            
            showTables();
            
            cin  >> n.tableNo;
            bool isReserved = dataStore(n.date, n.time, n.tableNo);
            if (isReserved)
            {
                cout << " Sorry the table is already reserved ! "<< endl; 
                continue; 
            } 
          
            else if( n.tableNo > 0 &&  n.tableNo < 31 )
            {
               break;
            } 
            
            else 
            {
                cout << " Invalid Input !" << endl;
            }    
        }

        bool check =  checkExistingRes();

        if(!check){
                 
                 cout << " Sorry, All tables reserved !" << endl;
                 return;
        }
       
         bool isAvailable = dataStore(n.date , n.time, n.tableNo);

        if (!isAvailable)
        {

                ofstream res1("Reservation.txt", ios::app);

                if (!res1.is_open()){
                    cout << " Error opening the file !" ;
       }else
            {
              
                res1   << n.name        << " "
                       << n.noOfGuests  << " " 
                       << n.date        << " "
                       << n.time        << " "
                       << n.phoneNo     << " " 
                       << n.tableNo
                       << endl;
                       res1.flush();
                       res1.close();                       
                       cout << " Reservation Successful! for " << n.name<< endl;

                       int calculateBill = (n.noOfGuests * 1500)-1;
                       cout << "\n\n\t\t===================================\n";
                       cout <<"\t\t  Your Total Amount Due is : " << calculateBill << "\t(1500 each person)" << endl;
                       cout << "\t\t====================================" << endl;
            }
       }
     else 
       {
             cout << "Sorry, the table is already reserved for the desired date and time.\n";
             cout << "Please try for another date or time slot." << endl;
             goto retrytable;         
        } 
   }




//                                      End of Project ! 