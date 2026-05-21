#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "service/AuthService.h"
#include "service/LaundryService.h"
#include "service/PaymentService.h"

using namespace std;

AuthService auth;
LaundryService laundry;
PaymentService payment;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menuCustomer() {
    int pilihan;
    User* user = auth.getCurrentUser();
    
    while (true) {
        cout << "\n=== MENU CUSTOMER (" << user->getNama() << ") ===" << endl;
        cout << "1. Buat Pesanan Laundry" << endl;
        cout << "2. Lihat Status Pesanan" << endl;
        cout << "3. Logout" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            int idAntar, idAmbil, idPaket;
            double berat;

            laundry.tampilkanMetode();
            cout << "\nPilih Metode Pengantaran (ID): "; cin >> idAntar;
            cout << "Pilih Metode Pengambilan (ID): "; cin >> idAmbil;

            Pesanan* p = laundry.buatPesananBaru(user->getId(), idAntar, idAmbil);

            laundry.tampilkanPaket();
            cout << "\nPilih Paket Laundry (ID): "; cin >> idPaket;
            cout << "Input Berat (Kg): "; cin >> berat;

            laundry.tambahDetailPesanan(p->getId(), idPaket, berat, "Pakaian harian");
            double total = laundry.hitungTotal(p->getId());

            cout << "\nTotal yang harus dibayar: Rp" << total << endl;
            
            int metBayar;
            cout << "Pilih Metode Pembayaran (1. COD, 2. Transfer): "; cin >> metBayar;
            
            Transaksi* trx = payment.buatTransaksi(p->getId(), total, p->getKodePesanan());
            
            if (metBayar == 2) {
                double nominal;
                while (true) {
                    cout << "Input Nominal Transfer: "; cin >> nominal;
                    if (payment.prosesPembayaran(trx->getId(), "Transfer", nominal)) {
                        break;
                    }
                }
            } else {
                payment.prosesPembayaran(trx->getId(), "COD", total);
            }

            payment.tampilkanDeskripsi(trx->getId());
            cout << "\n[INFO] Pesanan Berhasil Dibuat!" << endl;

        } else if (pilihan == 2) {
            vector<Pesanan> myOrders = laundry.getPesananCustomer(user->getId());
            cout << "\n=== STATUS PESANAN ANDA ===" << endl;
            if (myOrders.empty()) {
                cout << "Anda belum memiliki pesanan." << endl;
            } else {
                for (const auto& p : myOrders) {
                    cout << "Kode: " << p.getKodePesanan() << " | Total: " << p.getTotalHarga() 
                         << " | Status: [" << p.getStatusPesanan() << "]" << endl;
                }
            }
        } else if (pilihan == 3) {
            auth.logout();
            break;
        }
    }
}

void menuStaff() {
    int pilihan;
    User* user = auth.getCurrentUser();

    while (true) {
        cout << "\n=== MENU STAFF (" << user->getNama() << ") ===" << endl;
        cout << "1. Lihat Semua Pesanan" << endl;
        cout << "2. Update Status Pesanan" << endl;
        cout << "3. Tambah Paket Laundry" << endl;
        cout << "4. Nonaktifkan Paket Laundry" << endl;
        cout << "5. Aktifkan Paket Laundry" << endl;
        cout << "6. Logout" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            const auto& list = laundry.getListPesanan();
            cout << "\n=== DAFTAR SEMUA PESANAN ===" << endl;
            if (list.empty()) cout << "Belum ada pesanan." << endl;
            for (const auto& p : list) {
                cout << "Kode: " << p.getKodePesanan() << " | Customer ID: " << p.getCustomerId() 
                     << " | Total: " << p.getTotalHarga() << " | Status: " << p.getStatusPesanan() << endl;
            }
        } else if (pilihan == 2) {
            string kode, status;
            cout << "Masukkan Kode Pesanan (contoh: ORD-1001): "; cin >> kode;
            cout << "Masukkan Status Baru (Proses/Dicuci/Selesai): "; cin >> status;
            
            if (!laundry.updateStatusPesanan(kode, status)) {
                cout << "Gagal: Kode pesanan tidak ditemukan!" << endl;
            }
        } else if (pilihan == 3) {
            string nama, desc;
            double harga;
            int estimasi;

            cout << "\n=== TAMBAH PAKET LAUNDRY BARU ===" << endl;
            cout << "Nama Paket: "; clearInput(); getline(cin, nama);
            cout << "Harga per Kg: "; cin >> harga;
            cout << "Estimasi Waktu (Hari): "; cin >> estimasi;
            cout << "Deskripsi Paket: "; clearInput(); getline(cin, desc);

            laundry.tambahPaket(nama, harga, estimasi, desc);
        } else if (pilihan == 4) {
            int id;
            laundry.tampilkanSemuaPaketSistem();
            cout << "\nMasukkan ID Paket yang ingin dinonaktifkan: "; cin >> id;
            if (!laundry.softDeletePaket(id)) {
                cout << "Gagal: ID paket tidak ditemukan!" << endl;
            }
        } else if (pilihan == 5) {
            int id;
            laundry.tampilkanSemuaPaketSistem();
            cout << "\nMasukkan ID Paket yang ingin diaktifkan kembali: "; cin >> id;
            if (!laundry.aktifkanPaket(id)) {
                cout << "Gagal: ID paket tidak ditemukan!" << endl;
            }
        } else if (pilihan == 6) {
            auth.logout();
            break;
        }
    }
}

int main() {
    int pilihan;
    string email, pass, nama, noHp, alamat;

    while (true) {
        cout << "\n====================================" << endl;
        cout << "   SELAMAT DATANG DI SMART LAUNDRY" << endl;
        cout << "====================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register Customer" << endl;
        cout << "3. Keluar Aplikasi" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            if (auth.login(email, pass)) {
                if (auth.getCurrentUser()->getRole() == "Staff") {
                    menuStaff();
                } else {
                    menuCustomer();
                }
            }
        } else if (pilihan == 2) {
            cout << "Nama Lengkap: "; clearInput(); getline(cin, nama);
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;
            cout << "No HP: "; cin >> noHp;
            cout << "Alamat: "; clearInput(); getline(cin, alamat);

            auth.registerCustomer(nama, email, pass, noHp, alamat);
        } else if (pilihan == 3) {
            cout << "Terima kasih telah menggunakan Smart Laundry!" << endl;
            break;
        }
    }

    return 0;
}