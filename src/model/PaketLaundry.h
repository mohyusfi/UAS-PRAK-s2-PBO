#pragma once
#include <string>


class PaketLaundry {
private:
    int id;
    std::string namaPaket;
    double hargaPerKg;
    int estimasiHari;
    std::string deskripsi;
    bool isActive;

public:
    PaketLaundry(int id, std::string nama, double harga, int estimasi, std::string desc)
        : id(id), namaPaket(nama), hargaPerKg(harga), estimasiHari(estimasi), deskripsi(desc), isActive(true) {}


    int getId() const { return id; }
    std::string getNamaPaket() const { return namaPaket; }
    double getHargaPerKg() const { return hargaPerKg; }
    int getEstimasiHari() const { return estimasiHari; }
    std::string getDeskripsi() const { return deskripsi; }
    bool getIsActive() const { return isActive; }

  
    void setStatus(bool status) { isActive = status; }
};
