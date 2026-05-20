#pragma once

#include <string>
#include <chrono>


class Transaksi {
private:
    int id;
    int pesananId;
    std::chrono::system_clock::time_point tanggal;
    double totalTagihan;
    std::string statusTransaksi;
    std::string deskripsi;

public:
    Transaksi(int id, int pesananId, double total, std::string desc)
        : id(id), pesananId(pesananId), totalTagihan(total), 
          statusTransaksi("Unpaid"), deskripsi(desc) {
        tanggal = std::chrono::system_clock::now();
    }

    int getId() const { return id; }
    int getPesananId() const { return pesananId; }
    double getTotalTagihan() const { return totalTagihan; }
    std::string getStatusTransaksi() const { return statusTransaksi; }
    std::string getDeskripsi() const { return deskripsi; }

    void setStatus(std::string status) { statusTransaksi = status; }
};

class Pembayaran {
private:
    int id;
    int transaksiId;
    std::string metode; 
    double nominal;
    std::string statusPembayaran; 

public:
    Pembayaran(int id, int transaksiId, std::string metode, double nominal)
        : id(id), transaksiId(transaksiId), metode(metode), 
          nominal(nominal), statusPembayaran("Pending") {}

   
    int getTransaksiId() const { return transaksiId; }
    double getNominal() const { return nominal; }
    std::string getMetode() const { return metode; }
    std::string getStatusPembayaran() const { return statusPembayaran; }

    void setStatus(std::string status) { statusPembayaran = status; }
};
