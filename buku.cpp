#include <iostream>
using namespace std;

const int MAX = 100;

int panjang(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}
 
void salin(char *tujuan, const char *asal) {
    int i = 0;
    while (asal[i] != '\0') {
        tujuan[i] = asal[i];
        i++;
    }
    tujuan[i] = '\0';
}

struct Buku {
    int id;
    char judul[50];
    char pengarang[30];
    char kategori[20];
    int tahun;
    double rating;
};
 
Buku buku[MAX];  
int jumlah = 0;   
void tambahData(int id, const char *judul, const char *pengarang, const char *kategori,
                int tahun, double rating) {
    Buku &b = buku[jumlah];
    b.id = id;
    salin(b.judul, judul);
    salin(b.pengarang, pengarang);
    salin(b.kategori, kategori);
    b.tahun = tahun;
    b.rating = rating;
    jumlah++;
}
 
void isiDataAwal() {
    tambahData(1,  "Laskar Pelangi",            "Andrea Hirata",     "Novel",     2005, 4.7);
    tambahData(2,  "Sang Pemimpi",              "Andrea Hirata",     "Novel",     2006, 4.6);
    tambahData(3,  "Bumi",                      "Tere Liye",         "Fantasi",   2014, 4.5);
    tambahData(4,  "Bulan",                     "Tere Liye",         "Fantasi",   2015, 4.4);
    tambahData(5,  "Pulang",                    "Tere Liye",         "Novel",     2015, 4.6);
    tambahData(6,  "Algoritma dan Pemrograman", "Rinaldi Munir",     "Teknologi", 2016, 4.3);
    tambahData(7,  "Struktur Data C++",         "Budi Raharjo",      "Teknologi", 2018, 4.1);
    tambahData(8,  "Dasar Basis Data",          "Budi Raharjo",      "Teknologi", 2019, 4.0);
    tambahData(9,  "Filosofi Teras",            "Henry Manampiring", "Self-Help", 2018, 4.5);
    tambahData(10, "Atomic Habits",             "James Clear",       "Self-Help", 2018, 4.8);
    tambahData(11, "Sejarah Nusantara",         "Slamet Muljana",    "Sejarah",   2008, 4.2);
}
 
void cetakTeksRata(const char *s, int lebar) {
    cout << s;
    int n = panjang(s);
    if (n >= lebar) {
        cout << ' ';
        return;
    }
    for (int i = n; i < lebar; i++) cout << ' ';
}
 
void cetakAngkaRata(int x, int lebar) {
    cout << x;
    int n = 1, t = x;
    if (t < 0) { n++; t = -t; }
    while (t >= 10) { n++; t /= 10; }
    for (int i = n; i < lebar; i++) cout << ' ';
}
 
void cetakRating(double r) {
    int x = (int)(r * 10 + 0.5);  
    cout << x / 10 << '.' << x % 10;
}
 
void cetakGaris() {
    for (int i = 0; i < 85; i++) cout << '-';
    cout << "\n";
}
 
void cetakHeader() {
    cetakTeksRata("ID", 4);
    cetakTeksRata("Judul", 32);
    cetakTeksRata("Pengarang", 22);
    cetakTeksRata("Kategori", 12);
    cetakTeksRata("Tahun", 7);
    cout << "Rating\n";
    cetakGaris();
}
 
void cetakBuku(const Buku &b) {
    cetakAngkaRata(b.id, 4);
    cetakTeksRata(b.judul, 32);
    cetakTeksRata(b.pengarang, 22);
    cetakTeksRata(b.kategori, 12);
    cetakAngkaRata(b.tahun, 7);
    cetakRating(b.rating);
    cout << "\n";
}
 
void cetakDaftar(const Buku data[], int n) {
    cetakHeader();
    for (int i = 0; i < n; i++) cetakBuku(data[i]);
}
 
int bacaInt(const char *prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(1000, '\n');
            return x;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input harus angka.\n";
    }
}
 
void bacaTeks(const char *prompt, char *hasil, int maksPanjang) {
    cout << prompt;
    cin.getline(hasil, maksPanjang);
    if (cin.fail()) {  
        cin.clear();
        cin.ignore(1000, '\n');
    }
}