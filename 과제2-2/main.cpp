#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Member.h"
#include "Admin.h"
#include "Bike.h"
#include "RentalManager.h"
#include "BikeControl.h"
#include "UserControl.h"

using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

ifstream in_fp;
ofstream out_fp;

void doTask(UserControl& userCtrl, BikeControl& bikeCtrl);

int main() {
    in_fp.open(INPUT_FILE_NAME);
    out_fp.open(OUTPUT_FILE_NAME);

    if (!in_fp.is_open() || !out_fp.is_open()) {
        cerr << "������ �� �� �����ϴ�." << endl;
        return 1;
    }

    RentalManager rentalMgr;
    BikeControl bikeCtrl(&rentalMgr);
    UserControl userCtrl;

    doTask(userCtrl, bikeCtrl);

    in_fp.close();
    out_fp.close();
    return 0;
}

void doTask(UserControl& userCtrl, BikeControl& bikeCtrl) {
    int menu_level_1 = 0, menu_level_2 = 0;
    bool is_program_exit = false;

    Member* loggedInMember = nullptr;
    Admin* loggedInAdmin = nullptr;

    while (!is_program_exit && (in_fp >> menu_level_1 >> menu_level_2)) {
        switch (menu_level_1) {
        case 1: // ȸ�� ����
            switch (menu_level_2) {
            case 1: { // ȸ������
                string id, password, phone;
                in_fp >> id >> password >> phone;

                out_fp << "1.1. ȸ������\n";
                cout << "1.1. ȸ������\n";
                out_fp << "> " << id << " " << password << " " << phone << "\n";
                cout << "> " << id << " " << password << " " << phone << "\n";

                userCtrl.joinMember(id, password, phone);

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 2: // �α��� / �α׾ƿ�
            switch (menu_level_2) {
            case 1: { // �α���
                string id, password;
                in_fp >> id >> password;

                out_fp << "2.1. �α���\n";
                cout << "2.1. �α���\n";
                out_fp << "> " << id << " " << password << "\n";
                cout << "> " << id << " " << password << "\n";

                if (id == "admin") {
                    loggedInAdmin = userCtrl.loginAdmin(id, password);
                    if (!loggedInAdmin) {
                        out_fp << "> ������ �α��� ����\n";
                        cout << "> ������ �α��� ����\n";
                    }
                }
                else {
                    loggedInMember = userCtrl.loginMember(id, password);
                    if (!loggedInMember) {
                        out_fp << "> ȸ�� �α��� ����\n";
                        cout << "> ȸ�� �α��� ����\n";
                    }
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            case 2: { // �α׾ƿ�
                out_fp << "2.2. �α׾ƿ�\n";
                cout << "2.2. �α׾ƿ�\n";

                if (loggedInAdmin) {
                    out_fp << "> " << loggedInAdmin->getID() << "\n";
                    cout << "> " << loggedInAdmin->getID() << "\n";
                    loggedInAdmin = nullptr;
                }
                else if (loggedInMember) {
                    out_fp << "> " << loggedInMember->getID() << "\n";
                    cout << "> " << loggedInMember->getID() << "\n";
                    loggedInMember = nullptr;
                }
                else {
                    out_fp << "> �α׾ƿ��� ����ڰ� �����ϴ�\n";
                    cout << "> �α׾ƿ��� ����ڰ� �����ϴ�\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 3: // ������ ���
            switch (menu_level_2) {
            case 1: {
                string bikeID, productName;
                in_fp >> bikeID >> productName;

                out_fp << "3.1. ������ ���\n";
                cout << "3.1. ������ ���\n";
                out_fp << "> " << bikeID << " " << productName << "\n";
                cout << "> " << bikeID << " " << productName << "\n";

                if (loggedInAdmin) {
                    bikeCtrl.registerBike(*loggedInAdmin, bikeID, productName);
                }
                else {
                    out_fp << "> ������ �α����� �ʿ��մϴ�\n";
                    cout << "> ������ �α����� �ʿ��մϴ�\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 4: // ������ �뿩
            switch (menu_level_2) {
            case 1: {
                string bikeID;
                in_fp >> bikeID;

                out_fp << "4.1. ������ �뿩\n";
                cout << "4.1. ������ �뿩\n";

                if (loggedInMember) {
                    Bike* bike = bikeCtrl.rentBike(*loggedInMember, bikeID);
                    if (bike != nullptr) {
                        out_fp << "> " << bike->getID() << " " << bike->getProductName() << "\n";
                        cout << "> " << bike->getID() << " " << bike->getProductName() << "\n";
                    }
                    else {
                        out_fp << "> �뿩 ����\n";
                        cout << "> �뿩 ����\n";
                    }
                }
                else {
                    out_fp << "> �α����� ȸ���� �����ϴ�\n";
                    cout << "> �α����� ȸ���� �����ϴ�\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 5: // �뿩 ���� ��ȸ
            switch (menu_level_2) {
            case 1: {
                out_fp << "5.1. ������ �뿩 ����Ʈ\n";
                cout << "5.1. ������ �뿩 ����Ʈ\n";

                if (loggedInMember) {
                    vector<Bike*> rentals = bikeCtrl.getRentalManager()->getRentals(loggedInMember->getID());
                    for (Bike* b : rentals) {
                        out_fp << "> " << b->getID() << " " << b->getProductName() << "\n";
                        cout << "> " << b->getID() << " " << b->getProductName() << "\n";
                    }
                }
                else {
                    out_fp << "> �α����� ȸ���� �����ϴ�\n";
                    cout << "> �α����� ȸ���� �����ϴ�\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 6: // ����
            if (menu_level_2 == 1) {
                out_fp << "6.1. ����\n\n";
                cout << "6.1. ����\n\n";
                is_program_exit = true;
            }
            break;
        }
    }
}
