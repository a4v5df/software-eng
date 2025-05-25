#pragma once
// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
private:
    std::string id;
    std::string password;

public:
    Admin(std::string id, std::string password);

    std::string getID() const;
    bool checkPassword(const std::string& pw) const;
    bool isAdmin() const;
};

#endif 