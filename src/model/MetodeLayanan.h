#pragma once
#include <string>


class Pengantaran {
private:
    int id;
    std::string metode;
    double fee;

public:
    Pengantaran(int id, std::string metode, double fee)
        : id(id), metode(metode), fee(fee) {}

    int getId() const { return id; }
    std::string getMetode() const { return metode; }
    double getFee() const { return fee; }
};


class Pengambilan {
private:
    int id;
    std::string metode;
    double fee;

public:
    Pengambilan(int id, std::string metode, double fee)
        : id(id), metode(metode), fee(fee) {}

    int getId() const { return id; }
    std::string getMetode() const { return metode; }
    double getFee() const { return fee; }
};
