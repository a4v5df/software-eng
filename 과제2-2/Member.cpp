// Member.cpp
#include "Member.h"

Member::Member(std::string id, std::string password, std::string phone)
    : id(id), password(password), phone(phone) {
}

std::string Member::getID() const {
    return id;
}

std::string Member::getPhone() const {
    return phone;
}

bool Member::checkPassword(const std::string& pw) const {
    return password == pw;
}
