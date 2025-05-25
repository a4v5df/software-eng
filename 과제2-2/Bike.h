#pragma once
// Bike.h
#ifndef BIKE_H
#define BIKE_H

#include <string>

class Bike {
private:
    std::string bikeID;
    std::string productName;
    bool rented;

public:
    Bike(std::string bikeID, std::string productName);

    std::string getID() const;
    std::string getProductName() const;
    bool isRented() const;

    void rent();
    void returnBike();
};

#endif 
