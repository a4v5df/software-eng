#pragma once
#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <vector>
#include <string>
#include "Member.h"
#include "Admin.h"

class UserControl {
private:
    std::vector<Member*> memberList;
    Admin admin; 

public:
    UserControl();

    void joinMember(const std::string& id, const std::string& pw, const std::string& phone);
    Member* loginMember(const std::string& id, const std::string& pw);
    Admin* loginAdmin(const std::string& id, const std::string& pw);
};

#endif
