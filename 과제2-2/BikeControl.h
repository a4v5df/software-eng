#pragma once
#ifndef BIKCONTROL_H
#define BIKCONTROL_H

#include <vector>
#include <string>
#include "Bike.h"
#include "Member.h"
#include "Admin.h"
#include "RentalManager.h"

class BikeControl {
private:
    std::vector<Bike*> bikeList;
    RentalManager* rentalMgr;

public:
    BikeControl(RentalManager* rentalMgr);

    void registerBike(const Admin& admin, const std::string& bikeID, const std::string& productName);
    Bike* rentBike(const Member& member, const std::string& bikeID); 
    void listUserRentals(const Member& member) const;

    RentalManager* getRentalManager();  
};

#endif
