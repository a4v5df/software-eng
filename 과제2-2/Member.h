#pragma once
// Member.h
#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
private:
    std::string id;
    std::string password;
    std::string phone;

public:
    Member(std::string id, std::string password, std::string phone);

    std::string getID() const;
    std::string getPhone() const;
    bool checkPassword(const std::string& pw) const;
};

#endif 
