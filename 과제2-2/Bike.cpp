// Bike.cpp
#include "Bike.h"

Bike::Bike(std::string bikeID, std::string productName)
    : bikeID(bikeID), productName(productName), rented(false) {}

std::string Bike::getID() const {
    return bikeID;
}

std::string Bike::getProductName() const {
    return productName;
}

bool Bike::isRented() const {
    return rented;
}

void Bike::rent() {
    rented = true;
}

void Bike::returnBike() {
    rented = false;
}
