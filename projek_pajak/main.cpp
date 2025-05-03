#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Struktur untuk menyimpan data kendaraan
struct Kendaraan {
    string nama;
    string plat;
    string jenis; // mobil / motor
    int tahun;
    int harga;
    int pkb;
    int bbnkb;
    int swdkllj;
    int total;
    bool status = false; // Default: belum membayar pajak
    string invoice_id;    // Tambahkan member untuk Invoice ID
};

// Daftar kendaraan (sebagai database sementara)
vector<Kendaraan> daftar_kendaraan;

// Fungsi untuk menghitung pajak dan simpan data
void tambahkan_data() {
    // Alokasikan memori untuk objek Kendaraan menggunakan pointer
    Kendaraan* k = new Kendaraan;

    cout << "Masukkan nama pemilik:  ";
    cin.ignore();
    getline(cin, k->nama); // Gunakan -> untuk mengakses member melalui pointer

    cout << "Masukkan plat nomor: ";
    getline(cin, k->plat);

    cout << "Masukkan jenis kendaraan (mobil/motor): ";
    getline(cin, k->jenis);

    cout << "Masukkan tahun kendaraan: ";
    cin >> k->tahun;

    cout << "Masukkan harga kendaraan: ";
    cin >> k->harga;

    // Hitung pajak
    k->pkb = k->harga * 12 / 1000;
    k->bbnkb = k->harga * 12 / 100;
    k->swdkllj = 34000;
    k->total = k->pkb + k->bbnkb + k->swdkllj;

    // Status default: false (belum membayar pajak)
    k->status = false;
    k->invoice_id = ""; // Inisialisasi invoice_id

    // Simpan alamat memori (pointer) ke dalam vector
    daftar_kendaraan.push_back(*k); // Kita dereference pointer saat memasukkan ke vector
    delete k; // Penting untuk membebaskan memori yang dialokasikan dengan new
    k = nullptr; // Praktik yang baik untuk mengatur pointer menjadi nullptr setelah dihapus

    cout << "Data berhasil ditambahkan!\n";
}

// Tampilkan semua data
void lihat_semua_data() {
    if (daftar_kendaraan.empty()) {
        cout << "Belum ada data kendaraan.\n";
        return;
    }

    cout << "\n=== DAFTAR KENDARAAN ===\n";
    for (size_t i = 0; i < daftar_kendaraan.size(); i++) {
        Kendaraan* k = &daftar_kendaraan[i]; // Dapatkan alamat memori elemen vector
        cout << i + 1 << ". Nama: " << k->nama
             << ", Plat: " << k->plat
             << ", Jenis: " << k->jenis
             << ", Tahun: " << k->tahun
             << ", Pajak: " << k->total
             << ", Status: " << (k->status ? "Sudah membayar pajak" : "Belum membayar pajak");
        if (!k->invoice_id.empty()) {
            cout << ", Invoice ID: " << k->invoice_id;
        }
        cout << endl;
    }
}

// Cari kendaraan berdasarkan plat
void cari_data() {
    if (daftar_kendaraan.empty()) {
        cout << "Belum ada data kendaraan.\n";
        return;
    }

    string cari_plat;
    cout << "Masukkan plat nomor yang ingin dicari: ";
    cin.ignore();
    getline(cin, cari_plat);

    bool ditemukan = false;
    for (auto& k_ref : daftar_kendaraan) {
        Kendaraan* k = &k_ref; // Dapatkan alamat memori elemen vector
        if (k->plat == cari_plat) {
            cout << "\nData ditemukan:\n";
            cout << "Nama: " << k->nama
                 << "\nPlat: " << k->plat
                 << "\nJenis: " << k->jenis
                 << "\nTahun: " << k->tahun
                 << "\nTotal Pajak: " << k->total
                 << "\nStatus: " << (k->status ? "Sudah membayar pajak" : "Belum membayar pajak");
            if (!k->invoice_id.empty()) {
                cout << "\nInvoice ID: " << k->invoice_id;
            }
            cout << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data dengan plat " << cari_plat << " tidak ditemukan.\n";
    }
}

// Hapus data berdasarkan plat
void hapus_data() {
    if (daftar_kendaraan.empty()) {
        cout << "Belum ada data kendaraan.\n";
        return;
    }

    string plat_hapus;
    cout << "Masukkan plat nomor yang ingin dihapus: ";
    cin.ignore();
    getline(cin, plat_hapus);

    for (size_t i = 0; i < daftar_kendaraan.size(); i++) {
        if (daftar_kendaraan[i].plat == plat_hapus) {
            daftar_kendaraan.erase(daftar_kendaraan.begin() + i);
            cout << "Data berhasil dihapus.\n";
            return;
        }
    }

    cout << "Data dengan plat " << plat_hapus << " tidak ditemukan.\n";
}

// Perbarui status pembayaran pajak
void perbarui_status() {
    string plat_update;
    int metode_pembayaran;
    string invoice_id = ""; // Menyimpan invoice ID

    if (daftar_kendaraan.empty()) {
        cout << "Belum ada data kendaraan.\n";
        return;
    }

    cout << "Masukkan plat nomor untuk memperbarui status pajak: ";
    cin.ignore();
    getline(cin, plat_update);

    do {
        cout << "silahkan pilih metode pembayaran: \n";
        cout << "1.Alfamart \n";
        cout << "2.Indomaret \n";
        cout << "3.Briva (Bri virtual account) \n";
        cout << "4.BCA \n";
        cin >> metode_pembayaran;

        switch (metode_pembayaran) {
            case 1:
                invoice_id = "INV-001";
                break;
            case 2:
                invoice_id = "INV-002";
                break;
            case 3:
                invoice_id = "INV-003";
                break;
            case 4:
                invoice_id = "INV-004";
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (metode_pembayaran < 1 || metode_pembayaran > 4);

    bool ditemukan = false;
    for (int i = 0; i < daftar_kendaraan.size(); ++i) {
        Kendaraan* k = &daftar_kendaraan[i]; // Dapatkan alamat memori elemen vector
        if (k->plat == plat_update) {
            k->status = true;
            k->invoice_id = invoice_id;
            cout << "Status pajak kendaraan dengan plat " << plat_update << " telah diperbarui menjadi 'Sudah membayar pajak' dengan Invoice ID: " << invoice_id << ".\n";
            cout << "Data anda akan diproses 7×24 jam kerja\n";
            cout << "Terimakasih sudah membayar pajak\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data dengan plat " << plat_update << " tidak ditemukan.\n";
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n=== MENU PAJAK KENDARAAN ===\n";
        cout << "1. Tambahkan Data Kendaraan\n";
        cout << "2. Lihat Semua Data\n";
        cout << "3. Cari Data Kendaraan\n";
        cout << "4. Hapus Data Kendaraan\n";
        cout << "5. Perbarui Status Pajak\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahkan_data();
                break;
            case 2:
                lihat_semua_data();
                break;
            case 3:
                cari_data();
                break;
            case 4:
                hapus_data();
                break;
            case 5:
                perbarui_status();
                break;
            case 6:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 6);

    return 0;
}
