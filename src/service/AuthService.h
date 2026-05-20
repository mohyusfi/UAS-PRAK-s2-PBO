#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../model/User.h"


class AuthService {
private:
    std::vector<Customer> listCustomer;
    std::vector<Staff> listStaff;
    User* currentUser; 

public:
    AuthService() : currentUser(nullptr) {
        listStaff.push_back(Staff(1, "Admin Laundry", "admin@laundry.com", "admin123", "08123456789", "STF001"));
    }

    bool registerCustomer(std::string nama, std::string email, std::string password, std::string noHp, std::string alamat) {
        for (const auto& c : listCustomer) {
            if (c.getEmail() == email) {
                std::cout << "Gagal: Email sudah digunakan!" << std::endl;
                return false;
            }
        }

        int newId = listCustomer.size() + 1;
        listCustomer.push_back(Customer(newId, nama, email, password, noHp, alamat));
        std::cout << "Berhasil: Akun customer berhasil dibuat untuk " << nama << std::endl;
        return true;
    }

    bool login(std::string email, std::string password) {
        for (auto& s : listStaff) {
            if (s.getEmail() == email && s.getPassword() == password) {
                currentUser = &s;
                std::cout << "Selamat Datang Staff, " << s.getNama() << "!" << std::endl;
                return true;
            }
        }

        for (auto& c : listCustomer) {
            if (c.getEmail() == email && c.getPassword() == password) {
                currentUser = &c;
                std::cout << "Selamat Datang Customer, " << c.getNama() << "!" << std::endl;
                return true;
            }
        }

        std::cout << "Gagal: Email atau Password salah!" << std::endl;
        return false;
    }

    void logout() {
        if (currentUser != nullptr) {
            std::cout << currentUser->getNama() << " telah logout." << std::endl;
            currentUser = nullptr;
        }
    }

    User* getCurrentUser() const {
        return currentUser;
    }

    const std::vector<Customer>& getListCustomer() const { return listCustomer; }
};
