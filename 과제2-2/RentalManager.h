#pragma once
// RentalManager.h
#ifndef RENTALMANAGER_H
#define RENTALMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "Bike.h"

class RentalManager {
private:
    std::vector<std::pair<std::string, std::string>> rentalList; // memberID, bikeID
    std::map<std::string, Bike*> bikeMap; // bikeID ¡æ Bike*

public:
    void addBike(Bike* bike);

    bool isRented(const std::string& bikeID) const;
    void addRental(const std::string& memberID, const std::string& bikeID);
    std::vector<Bike*> getRentals(const std::string& memberID) const;
};

#endif
