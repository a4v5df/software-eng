// Admin.cpp
#include "Admin.h"

Admin::Admin(std::string id, std::string password)
    : id(id), password(password) {}

std::string Admin::getID() const {
    return id;
}

bool Admin::checkPassword(const std::string& pw) const {
    return password == pw;
}

bool Admin::isAdmin() const {
    return true; 
}
