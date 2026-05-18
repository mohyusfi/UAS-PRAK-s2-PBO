#pragma once
#include <string>


class User {
protected:
    int id;
    std::string nama;
    std::string email;
    std::string password;
    std::string noHp;
    std::string role;

public:
    User(int id, std::string nama, std::string email, std::string password, std::string noHp, std::string role)
        : id(id), nama(nama), email(email), password(password), noHp(noHp), role(role) {}

    virtual ~User() {}

    int getId() const { return id; }
    std::string getNama() const { return nama; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getNoHp() const { return noHp; }
    std::string getRole() const { return role; }
};


class Customer : public User {
private:
    std::string alamat;

public:
    Customer(int id, std::string nama, std::string email, std::string password, std::string noHp, std::string alamat)
        : User(id, nama, email, password, noHp, "Customer"), alamat(alamat) {}

    std::string getAlamat() const { return alamat; }
    void setAlamat(std::string alamatBaru) { alamat = alamatBaru; }
};


class Staff : public User {
private:
    std::string kodeStaff;

public:
    Staff(int id, std::string nama, std::string email, std::string password, std::string noHp, std::string kodeStaff)
        : User(id, nama, email, password, noHp, "Staff"), kodeStaff(kodeStaff) {}

    std::string getKodeStaff() const { return kodeStaff; }
};
