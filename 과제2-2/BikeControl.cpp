#include "BikeControl.h"
#include <iostream>

BikeControl::BikeControl(RentalManager* rentalMgr) : rentalMgr(rentalMgr) {}

void BikeControl::registerBike(const Admin& admin, const std::string& bikeID, const std::string& productName) {
    for (Bike* b : bikeList) {
        if (b->getID() == bikeID) {
            std::cout << "이미 등록된 자전거입니다.\n";
            return;
        }
    }

    Bike* newBike = new Bike(bikeID, productName);
    bikeList.push_back(newBike);
    rentalMgr->addBike(newBike); 
}

Bike* BikeControl::rentBike(const Member& member, const std::string& bikeID) {
    if (rentalMgr->isRented(bikeID)) return nullptr;

    for (Bike* b : bikeList) {
        if (b->getID() == bikeID) {
            b->rent();
            rentalMgr->addRental(member.getID(), bikeID);
            return b;  //  대여된 자전거 반환
        }
    }
    return nullptr;
}

void BikeControl::listUserRentals(const Member& member) const {
    std::vector<Bike*> rentals = rentalMgr->getRentals(member.getID());
    for (Bike* b : rentals) {
        std::cout << b->getID() << " " << b->getProductName() << "\n";
    }
}

RentalManager* BikeControl::getRentalManager() {
    return rentalMgr;
}
