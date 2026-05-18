#pragma once
#include <vector>
#include <iostream>
#include "../model/Transaksi.h"


class PaymentService {
private:
    std::vector<Transaksi> listTransaksi;
    std::vector<Pembayaran> listPembayaran;

public:
    Transaksi* buatTransaksi(int pesananId, double total, std::string kodePesanan) {
        int newId = listTransaksi.size() + 1;
        std::string desc = "Tagihan untuk pesanan " + kodePesanan;
        
        listTransaksi.push_back(Transaksi(newId, pesananId, total, desc));
        return &listTransaksi.back();
    }

    bool prosesPembayaran(int transaksiId, std::string metode, double nominal) {
        Transaksi* trx = nullptr;
        for (auto& t : listTransaksi) {
            if (t.getId() == transaksiId) {
                trx = &t;
                break;
            }
        }

        if (!trx) {
            std::cout << "Gagal: Transaksi tidak ditemukan." << std::endl;
            return false;
        }

        if (nominal < trx->getTotalTagihan()) {
            std::cout << "Gagal: Nominal transfer (" << nominal << ") kurang dari total (" << trx->getTotalTagihan() << ")." << std::endl;
            return false;
        }

        int payId = listPembayaran.size() + 1;
        listPembayaran.push_back(Pembayaran(payId, transaksiId, metode, nominal));
        
        listPembayaran.back().setStatus("Success");
        trx->setStatus("Paid");

        std::cout << "Berhasil: Pembayaran diterima. Status Transaksi: PAID." << std::endl;
        return true;
    }

    void tampilkanDeskripsi(int transaksiId) {
        for (const auto& t : listTransaksi) {
            if (t.getId() == transaksiId) {
                std::cout << "\n=== DESKRIPSI TRANSAKSI ===" << std::endl;
                std::cout << "ID Transaksi : " << t.getId() << std::endl;
                std::cout << "Keterangan   : " << t.getDeskripsi() << std::endl;
                std::cout << "Total Tagihan: " << t.getTotalTagihan() << std::endl;
                std::cout << "Status       : " << t.getStatusTransaksi() << std::endl;
                std::cout << "===========================" << std::endl;
                return;
            }
        }
    }
};
