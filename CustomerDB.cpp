// CRM in C++ CustomerDB.cpp
// EE 312 Project 7 submission by
// Alexis Torres
// at39625
// Slip days used: 0
// Spring 2022

#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) {
    int i;
    if(!isMember(name)){ // if the customer is not a part of the array then add it to the list of customers

//            this->data = new Customer[this->length+1]; // deletes the data :(
//            this->data[length] = Customer(name);
//            this->length ++;
//            this->capacity ++;

        Customer *databasePlusOne = new Customer[this->capacity+1]; // make a copy of the entire data array plus 1
        for(i = 0; i< length; i++){
            databasePlusOne[i] = data[i];
        }
        delete[] data; // delete the old customer array
        data = databasePlusOne;
        this->capacity++;
        this->data[length] = name; // put the name at the very end of the array, at this point its length before I add 1
        this->length++;
        Customer &custHolder = data[length-1]; // return a reference to the customer looking for
        return custHolder;
    }

    for (i = 0; i < length; i++) { // looking though the array to find said customer
        if (data[i].name == name) {
            Customer &custHolder = data[i]; // putting the for loop at the end so its a bit more efficient
            return custHolder;
        }
    }
}

bool CustomerDB::isMember(UTString name) {
    int i;
    for(i = 0; i<length; i++){
       if(data[i].name == name){ // as you move through the array of customers and you find the one you're looking for then return true
           return true;
       }
    }
    return false; // auto return false
}
