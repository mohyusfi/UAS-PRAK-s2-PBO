#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "../model/PaketLaundry.h"
#include "../model/MetodeLayanan.h"
#include "../model/Pesanan.h"

class ILaundryService {
public:
    virtual ~ILaundryService() = default;
    virtual void tampilkanPaket() = 0;
    virtual void tampilkanMetode() = 0;
    virtual Pesanan* buatPesananBaru(int customerId, int idAntar, int idAmbil) = 0;
    virtual void tambahDetailPesanan(int pesananId, int paketId, double berat, std::string catatan) = 0;
    virtual double hitungTotal(int pesananId) = 0;
    virtual bool updateStatusPesanan(std::string kode, std::string statusBaru) = 0;
    virtual std::vector<Pesanan> getPesananCustomer(int customerId) = 0;
    virtual const std::vector<Pesanan>& getListPesanan() const = 0;
};

class LaundryService : public ILaundryService {
private:
    std::vector<PaketLaundry> listPaket;
    std::vector<Pengantaran> listPengantaran;
    std::vector<Pengambilan> listPengambilan;
    std::vector<Pesanan> listPesanan;
    std::vector<DetailPesanan> listDetail;

public:
    LaundryService() {
        listPaket.push_back(PaketLaundry(1, "Cuci Kering", 5000, 2, "Cuci dan keringkan saja"));
        listPaket.push_back(PaketLaundry(2, "Cuci Setrika", 7000, 3, "Cuci, kering, dan setrika rapi"));
        listPaket.push_back(PaketLaundry(3, "Express 1 Hari", 10000, 1, "Selesai dalam 24 jam"));

        listPengantaran.push_back(Pengantaran(1, "Bawa Sendiri", 0));
        listPengantaran.push_back(Pengantaran(2, "Jemput ke Rumah", 5000));

        listPengambilan.push_back(Pengambilan(1, "Ambil Sendiri", 0));
        listPengambilan.push_back(Pengambilan(2, "Antar ke Rumah", 5000));
    }

    void tampilkanPaket() override {
        std::cout << "\n=== DAFTAR PAKET LAUNDRY ===" << std::endl;
        std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Nama" << std::setw(15) << "Harga/Kg" << "Estimasi" << std::endl;
        for (const auto& p : listPaket) {
            if (p.getIsActive()) {
                std::cout << std::left << std::setw(5) << p.getId() 
                          << std::setw(20) << p.getNamaPaket() 
                          << std::setw(15) << p.getHargaPerKg() 
                          << p.getEstimasiHari() << " Hari" << std::endl;
            }
        }
    }

    void tampilkanMetode() override {
        std::cout << "\n--- Metode Pengantaran (Ke Laundry) ---" << std::endl;
        for (const auto& m : listPengantaran) {
            std::cout << m.getId() << ". " << m.getMetode() << " (Fee: " << m.getFee() << ")" << std::endl;
        }
        std::cout << "\n--- Metode Pengambilan (Ke Customer) ---" << std::endl;
        for (const auto& m : listPengambilan) {
            std::cout << m.getId() << ". " << m.getMetode() << " (Fee: " << m.getFee() << ")" << std::endl;
        }
    }

    Pesanan* buatPesananBaru(int customerId, int idAntar, int idAmbil) override {
        int newId = listPesanan.size() + 1;
        std::string kode = "ORD-" + std::to_string(1000 + newId);
        
        listPesanan.push_back(Pesanan(newId, kode, customerId, idAntar, idAmbil));
        return &listPesanan.back();
    }

    void tambahDetailPesanan(int pesananId, int paketId, double berat, std::string catatan) override {
        double hargaPaket = 0;
        for (const auto& p : listPaket) {
            if (p.getId() == paketId) {
                hargaPaket = p.getHargaPerKg();
                break;
            }
        }

        int detailId = listDetail.size() + 1;
        listDetail.push_back(DetailPesanan(detailId, pesananId, paketId, berat, hargaPaket, catatan));
    }

    double hitungTotal(int pesananId) override {
        double total = 0;
        Pesanan* pesanan = nullptr;

        for (auto& p : listPesanan) {
            if (p.getId() == pesananId) {
                pesanan = &p;
                break;
            }
        }

        if (!pesanan) return 0;

        for (const auto& d : listDetail) {
            if (d.getPesananId() == pesananId) {
                total += d.getSubtotal();
            }
        }

        for (const auto& m : listPengantaran) {
            if (m.getId() == pesanan->getPengantaranId()) total += m.getFee();
        }
        for (const auto& m : listPengambilan) {
            if (m.getId() == pesanan->getPengambilanId()) total += m.getFee();
        }

        pesanan->setTotalHarga(total);
        return total;
    }

    bool updateStatusPesanan(std::string kode, std::string statusBaru) override {
        for (auto& p : listPesanan) {
            if (p.getKodePesanan() == kode) {
                p.setStatus(statusBaru);
                std::cout << "Berhasil: Status pesanan " << kode << " diubah menjadi " << statusBaru << std::endl;
                return true;
            }
        }
        return false;
    }

    std::vector<Pesanan> getPesananCustomer(int customerId) override {
        std::vector<Pesanan> result;
        for (const auto& p : listPesanan) {
            if (p.getCustomerId() == customerId) {
                result.push_back(p);
            }
        }
        return result;
    }

    const std::vector<Pesanan>& getListPesanan() const override { return listPesanan; }


    const std::vector<PaketLaundry>& getListPaket() const { return listPaket; }

    void tambahPaket(std::string nama, double harga, int estimasi, std::string desc) {
        int newId = listPaket.size() + 1;
        listPaket.push_back(PaketLaundry(newId, nama, harga, estimasi, desc));
        std::cout << "Berhasil: Paket " << nama << " berhasil ditambahkan!" << std::endl;
    }

    bool updatePaket(int id, std::string nama, double harga, int estimasi, std::string desc) {
        for (auto& p : listPaket) {
            if (p.getId() == id) {
                bool active = p.getIsActive();
                p = PaketLaundry(id, nama, harga, estimasi, desc);
                p.setStatus(active);
                std::cout << "Berhasil: Paket dengan ID " << id << " berhasil diperbarui!" << std::endl;
                return true;
            }
        }
        return false;
    }

    bool softDeletePaket(int id) {
        for (auto& p : listPaket) {
            if (p.getId() == id) {
                p.nonaktifkanPaket();
                std::cout << "Berhasil: Paket " << p.getNamaPaket() << " dinonaktifkan!" << std::endl;
                return true;
            }
        }
        return false;
    }
};
