#include "UserControl.h"
#include <iostream>

UserControl::UserControl() : admin("admin", "admin") {}

void UserControl::joinMember(const std::string& id, const std::string& pw, const std::string& phone) {
    for (Member* m : memberList) {
        if (m->getID() == id) {
            return;
        }
    }
    Member* newMember = new Member(id, pw, phone);
    memberList.push_back(newMember);
}

Member* UserControl::loginMember(const std::string& id, const std::string& pw) {
    for (Member* m : memberList) {
        if (m->getID() == id && m->checkPassword(pw)) {
            return m;
        }
    }
    return nullptr;
}

Admin* UserControl::loginAdmin(const std::string& id, const std::string& pw) {
    if (admin.getID() == id && admin.checkPassword(pw)) {
        return &admin;
    }
    return nullptr;
}
