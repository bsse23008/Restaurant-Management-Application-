#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

//write functions prototype here

int SignupPage();
char loginPage();
void adminPage();
void chefPage();
void recipe();
void  staffPage();
int userPage();

//float calculateSalesTax(float itemPrice, float taxRate);
template <typename T>
T calculateSalesTax(T itemPrice, T taxRate) ;
void tableReservation();
#endif
