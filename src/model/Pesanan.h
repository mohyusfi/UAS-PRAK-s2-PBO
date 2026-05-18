#pragma once
#include <string>
#include <vector>
#include <chrono>

// Model DetailPesanan - Rincian item dalam satu pesanan
class DetailPesanan {
private:
    int id;
    int pesananId;
    int paketId;
    double berat;
    double hargaPerKg;
    double subtotal;
    std::string catatan;

public:
    DetailPesanan(int id, int pesananId, int paketId, double berat, double hargaPerKg, std::string catatan)
        : id(id), pesananId(pesananId), paketId(paketId), berat(berat), hargaPerKg(hargaPerKg), catatan(catatan) {
        this->subtotal = berat * hargaPerKg;
    }

    // Getter
    int getId() const { return id; }
    int getPaketId() const { return paketId; }
    double getBerat() const { return berat; }
    double getSubtotal() const { return subtotal; }
    std::string getCatatan() const { return catatan; }
};

// Model Pesanan - Data utama pesanan laundry
class Pesanan {
private:
    int id;
    std::string kodePesanan;
    int customerId;
    int parentPesananId; // Untuk pesanan tambahan (optional)
    std::string statusPesanan; // Contoh: "Pending", "Proses", "Selesai"
    double totalHarga;
    std::chrono::system_clock::time_point tanggalPesan;
    
    int pengantaranId;
    int pengambilanId;

public:
    Pesanan(int id, std::string kode, int customerId, int pengantaranId, int pengambilanId)
        : id(id), kodePesanan(kode), customerId(customerId), 
          parentPesananId(0), statusPesanan("Pending"), totalHarga(0.0),
          pengantaranId(pengantaranId), pengambilanId(pengambilanId) {
        tanggalPesan = std::chrono::system_clock::now();
    }


    int getId() const { return id; }
    std::string getKodePesanan() const { return kodePesanan; }
    int getCustomerId() const { return customerId; }
    std::string getStatusPesanan() const { return statusPesanan; }
    double getTotalHarga() const { return totalHarga; }
    int getPengantaranId() const { return pengantaranId; }
    int getPengambilanId() const { return pengambilanId; }


    void setTotalHarga(double harga) { totalHarga = harga; }
    void setStatus(std::string status) { statusPesanan = status; }
    void setParentId(int pid) { parentPesananId = pid; }
};
