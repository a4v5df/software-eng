#include "RentalManager.h"

void RentalManager::addBike(Bike* bike) {
    bikeMap[bike->getID()] = bike;
}

bool RentalManager::isRented(const std::string& bikeID) const {
    for (const auto& p : rentalList) {
        if (p.second == bikeID) return true;
    }
    return false;
}

void RentalManager::addRental(const std::string& memberID, const std::string& bikeID) {
    if (bikeMap.count(bikeID)) {
        rentalList.emplace_back(memberID, bikeID); // 순차적으로 저장
        bikeMap[bikeID]->rent();
    }
}


std::vector<Bike*> RentalManager::getRentals(const std::string& memberID) const {
    std::vector<Bike*> result;
    for (const auto& p : rentalList) {
        if (p.first == memberID) {
            const std::string& bikeID = p.second;
            if (bikeMap.count(bikeID)) {
                result.push_back(bikeMap.at(bikeID));
            }
        }
    }
    return result;
}
