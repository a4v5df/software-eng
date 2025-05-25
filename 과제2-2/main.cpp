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
        cerr << "파일을 열 수 없습니다." << endl;
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
        case 1: // 회원 관련
            switch (menu_level_2) {
            case 1: { // 회원가입
                string id, password, phone;
                in_fp >> id >> password >> phone;

                out_fp << "1.1. 회원가입\n";
                cout << "1.1. 회원가입\n";
                out_fp << "> " << id << " " << password << " " << phone << "\n";
                cout << "> " << id << " " << password << " " << phone << "\n";

                userCtrl.joinMember(id, password, phone);

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 2: // 로그인 / 로그아웃
            switch (menu_level_2) {
            case 1: { // 로그인
                string id, password;
                in_fp >> id >> password;

                out_fp << "2.1. 로그인\n";
                cout << "2.1. 로그인\n";
                out_fp << "> " << id << " " << password << "\n";
                cout << "> " << id << " " << password << "\n";

                if (id == "admin") {
                    loggedInAdmin = userCtrl.loginAdmin(id, password);
                    if (!loggedInAdmin) {
                        out_fp << "> 관리자 로그인 실패\n";
                        cout << "> 관리자 로그인 실패\n";
                    }
                }
                else {
                    loggedInMember = userCtrl.loginMember(id, password);
                    if (!loggedInMember) {
                        out_fp << "> 회원 로그인 실패\n";
                        cout << "> 회원 로그인 실패\n";
                    }
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            case 2: { // 로그아웃
                out_fp << "2.2. 로그아웃\n";
                cout << "2.2. 로그아웃\n";

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
                    out_fp << "> 로그아웃할 사용자가 없습니다\n";
                    cout << "> 로그아웃할 사용자가 없습니다\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 3: // 자전거 등록
            switch (menu_level_2) {
            case 1: {
                string bikeID, productName;
                in_fp >> bikeID >> productName;

                out_fp << "3.1. 자전거 등록\n";
                cout << "3.1. 자전거 등록\n";
                out_fp << "> " << bikeID << " " << productName << "\n";
                cout << "> " << bikeID << " " << productName << "\n";

                if (loggedInAdmin) {
                    bikeCtrl.registerBike(*loggedInAdmin, bikeID, productName);
                }
                else {
                    out_fp << "> 관리자 로그인이 필요합니다\n";
                    cout << "> 관리자 로그인이 필요합니다\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 4: // 자전거 대여
            switch (menu_level_2) {
            case 1: {
                string bikeID;
                in_fp >> bikeID;

                out_fp << "4.1. 자전거 대여\n";
                cout << "4.1. 자전거 대여\n";

                if (loggedInMember) {
                    Bike* bike = bikeCtrl.rentBike(*loggedInMember, bikeID);
                    if (bike != nullptr) {
                        out_fp << "> " << bike->getID() << " " << bike->getProductName() << "\n";
                        cout << "> " << bike->getID() << " " << bike->getProductName() << "\n";
                    }
                    else {
                        out_fp << "> 대여 실패\n";
                        cout << "> 대여 실패\n";
                    }
                }
                else {
                    out_fp << "> 로그인한 회원이 없습니다\n";
                    cout << "> 로그인한 회원이 없습니다\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 5: // 대여 정보 조회
            switch (menu_level_2) {
            case 1: {
                out_fp << "5.1. 자전거 대여 리스트\n";
                cout << "5.1. 자전거 대여 리스트\n";

                if (loggedInMember) {
                    vector<Bike*> rentals = bikeCtrl.getRentalManager()->getRentals(loggedInMember->getID());
                    for (Bike* b : rentals) {
                        out_fp << "> " << b->getID() << " " << b->getProductName() << "\n";
                        cout << "> " << b->getID() << " " << b->getProductName() << "\n";
                    }
                }
                else {
                    out_fp << "> 로그인한 회원이 없습니다\n";
                    cout << "> 로그인한 회원이 없습니다\n";
                }

                out_fp << "\n"; cout << "\n";
                break;
            }
            }
            break;

        case 6: // 종료
            if (menu_level_2 == 1) {
                out_fp << "6.1. 종료\n\n";
                cout << "6.1. 종료\n\n";
                is_program_exit = true;
            }
            break;
        }
    }
}
