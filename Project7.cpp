// CRM in C++ Project7.cpp
// EE 312 Project 7 submission by
// Alexis Torres
// at39625
// Slip days used: 0
// Spring 2022

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>
using namespace std;

void readString(UTString&);
void readNum(int&);

UTString wordInv;//to hold inventory item
UTString nameCus;// to hold customer name
int itemCount;// to hold the count of an item



CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    readString(nameCus);
    readString(wordInv);

    readNum(itemCount);

    if (wordInv ==  "Bottles" && itemCount <= num_bottles ){ // using the operator[] creates a new customer so i can only use it when there is enough to sell the item
        num_bottles =  num_bottles - itemCount;
        database[nameCus].bottles = database[nameCus].bottles + itemCount;
    }
    else if (wordInv == "Diapers" && itemCount <= num_diapers){
        num_diapers = num_diapers - itemCount;
        database[nameCus].diapers = database[nameCus].diapers + itemCount;
    }
   else if (wordInv == "Rattles" && itemCount <= num_rattles){
        num_rattles = num_rattles - itemCount;
        database[nameCus].rattles = database[nameCus].rattles + itemCount;
    }
   else{// if i don't have enough to sell then I don't have, put out the sorry message
       if(wordInv ==  "Bottles"){cout<< "Sorry "<< nameCus.c_str() <<", we only have " << num_bottles <<" Bottles\n";}
       else if(wordInv ==  "Diapers"){ cout<< "Sorry "<< nameCus.c_str() <<", we only have " << num_diapers <<" Diapers\n";}
       else if(wordInv ==  "Rattles"){ cout<< "Sorry "<< nameCus.c_str() <<", we only have " << num_rattles <<" Rattles\n";}
   }
}

void processSummarize() {
    Customer* maxRat = findMax("Rattles"); // since findMax returns a pointer make one for each of the values
    Customer* maxBot = findMax("Bottles");
    Customer* maxDia = findMax("Diapers");

    cout << "There are " << num_bottles << " Bottles " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory\n";
    cout<<"We have had a total of " << database.size() << " different customers\n";

    if (findMax("Bottles") != NULL){// a version of the for each item
        cout << maxBot->name.c_str() << " has purchased the most Bottles (" << maxBot->bottles<< ")\n";
    }
    else{cout << "no one has purchased any Bottles\n";}

    if(findMax("Diapers")!= NULL){
        cout << maxDia->name.c_str() << " has purchased the most Diapers (" << maxDia->diapers<< ")\n";
    }
    else{cout << "no one has purchased any Diapers\n";}

    if(findMax("Rattles") != NULL){
        cout << maxRat->name.c_str() << " has purchased the most Rattles (" << maxRat->rattles<< ")\n";
    }
    else{cout << "no one has purchased any Rattles\n";}



}

void processInventory() {
    readString(wordInv);
    readNum(itemCount);
    if (wordInv ==  "Bottles" ){ //since there is only three items
        num_bottles =  num_bottles + itemCount;//and they all start with a different letter then you can
    }                          // compare only the first letter
   else if (wordInv == "Diapers"){
        num_diapers = num_diapers+ itemCount;
    }
   else if (wordInv == "Rattles"){
        num_rattles = num_rattles + itemCount;
    }
   else{
       cout << "ERROR\n";
   }



}
