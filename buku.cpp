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

// ---- SORTING 
bool tahunNaik(const Buku &a, const Buku &b)    { return a.tahun < b.tahun; }
bool tahunTurun(const Buku &a, const Buku &b)   { return a.tahun > b.tahun; }
bool ratingNaik(const Buku &a, const Buku &b)   { return a.rating < b.rating; }
bool ratingTurun(const Buku &a, const Buku &b)  { return a.rating > b.rating; }
bool idNaik(const Buku &a, const Buku &b)       { return a.id < b.id; }


Buku bantu[MAX];  

void gabung(int kiri, int tengah, int kanan,
            bool (*lebihDulu)(const Buku &, const Buku &)) {
    int i = kiri, j = tengah + 1, k = kiri;
    while (i <= tengah && j <= kanan) {
        if (lebihDulu(buku[j], buku[i])) bantu[k++] = buku[j++];
        else                             bantu[k++] = buku[i++];
    }
    while (i <= tengah) bantu[k++] = buku[i++];
    while (j <= kanan)  bantu[k++] = buku[j++];
    for (k = kiri; k <= kanan; k++) buku[k] = bantu[k];
}

void mergeSort(int kiri, int kanan,
               bool (*lebihDulu)(const Buku &, const Buku &)) {
    if (kiri >= kanan) return;
    int tengah = (kiri + kanan) / 2;
    mergeSort(kiri, tengah, lebihDulu);
    mergeSort(tengah + 1, kanan, lebihDulu);
    gabung(kiri, tengah, kanan, lebihDulu);
}

void menuSorting() {
    int pilih;
    do {
        cout << "\n=== MENU PENGURUTAN (Merge Sort) ===\n";
        cout << "1. Tahun terbit (terlama -> terbaru)\n";
        cout << "2. Tahun terbit (terbaru -> terlama)\n";
        cout << "3. Rating (terendah -> tertinggi)\n";
        cout << "4. Rating (tertinggi -> terendah)\n";
        cout << "0. Kembali\n";
        pilih = bacaInt("Pilih: ");
        if (pilih == 0) break;
        if (pilih < 1 || pilih > 4) {
            cout << "Pilihan tidak valid.\n";
            continue;
        }

        bool (*cmp)(const Buku &, const Buku &) = tahunNaik;
        if (pilih == 2) cmp = tahunTurun;
        else if (pilih == 3) cmp = ratingNaik;
        else if (pilih == 4) cmp = ratingTurun;

        mergeSort(0, jumlah - 1, cmp);

        cout << "\nHasil pengurutan:\n";
        cetakDaftar(buku, jumlah);
    } while (pilih != 0);
}

// ---- END SORTING

char hurufKecil(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

bool mengandung(const char *teks, const char *kata) {
    int n = panjang(teks);
    int m = panjang(kata);
    for (int i = 0; i + m <= n; i++) {
        int j = 0;
        while (j < m && hurufKecil(teks[i + j]) == hurufKecil(kata[j])) j++;
        if (j == m) return true;
    }
    return false;
}

void cariJudul() {
    char kata[50];
    bacaTeks("Masukkan judul: ", kata, 50);
    bool ketemu = false;
    for (int i = 0; i < jumlah; i++) {
        if (mengandung(buku[i].judul, kata)) {
            if (!ketemu) cetakHeader();
            cetakBuku(buku[i]);
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Buku tidak ditemukan.\n";
}

void cariPengarang() {
    char kata[50];
    bacaTeks("Masukkan pengarang: ", kata, 50);
    bool ketemu = false;
    for (int i = 0; i < jumlah; i++) {
        if (mengandung(buku[i].pengarang, kata)) {
            if (!ketemu) cetakHeader();
            cetakBuku(buku[i]);
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Buku tidak ditemukan.\n";
}

void menuSearching() {
    int pilih;
    do {
        cout << "\n=== MENU PENCARIAN ===\n";
        cout << "1. Cari berdasarkan Judul\n";
        cout << "2. Cari berdasarkan Pengarang\n";
        cout << "0. Kembali\n";
        pilih = bacaInt("Pilih: ");

        if (pilih == 1) cariJudul();
        else if (pilih == 2) cariPengarang();
        else if (pilih != 0) cout << "Pilihan tidak valid.\n";
    } while (pilih != 0);
}

// ---- GRAPH
struct Edge {
    int tujuan;   
    int bobot;    
};
 
class GrafBuku {
private:
    Buku simpul[MAX];      
    int  jumlahSimpul;
    Edge adj[MAX][MAX];      
    int  derajat[MAX];    
 
    bool samaTeks(const char *a, const char *b) const {
        int n = panjang(a);
        if (n != panjang(b)) return false;
        for (int i = 0; i < n; i++)
            if (hurufKecil(a[i]) != hurufKecil(b[i])) return false;
        return true;
    }
 
    int hitungBobot(const Buku &a, const Buku &b) const {
        int skor = 0;
        if (samaTeks(a.kategori,  b.kategori))  skor += 2;
        if (samaTeks(a.pengarang, b.pengarang)) skor += 1;
        return skor;
    }
 
    void tambahEdge(int dari, int ke, int bobot) {
        adj[dari][derajat[dari]].tujuan = ke;
        adj[dari][derajat[dari]].bobot  = bobot;
        derajat[dari]++;
    }
 
    void urutkanTetangga(int v) {
        for (int i = 1; i < derajat[v]; i++) {
            Edge kunci = adj[v][i];
            int j = i - 1;
            while (j >= 0 && adj[v][j].bobot < kunci.bobot) {
                adj[v][j + 1] = adj[v][j];
                j--;
            }
            adj[v][j + 1] = kunci;
        }
    }
 
public:
    GrafBuku() : jumlahSimpul(0) {
        for (int i = 0; i < MAX; i++) derajat[i] = 0;
    }
 
    int banyakSimpul() const { return jumlahSimpul; }
 
    int tambahBuku(const Buku &b) {
        if (jumlahSimpul >= MAX) return -1;
        simpul[jumlahSimpul] = b;
        derajat[jumlahSimpul] = 0;
        return jumlahSimpul++;
    }
 
    void bangunEdge() {
        for (int i = 0; i < jumlahSimpul; i++) derajat[i] = 0;
 
        for (int i = 0; i < jumlahSimpul; i++) {
            for (int j = i + 1; j < jumlahSimpul; j++) {
                int w = hitungBobot(simpul[i], simpul[j]);
                if (w > 0) {
                    tambahEdge(i, j, w);
                    tambahEdge(j, i, w);
                }
            }
        }
        for (int i = 0; i < jumlahSimpul; i++) urutkanTetangga(i);
    }
 
    int cariIndeksById(int id) const {
        for (int i = 0; i < jumlahSimpul; i++)
            if (simpul[i].id == id) return i;
        return -1;
    }
 
    void tampilkanGraf() const {
        cout << "\n=== GRAF BUKU (Adjacency List) ===\n";
        int totalEdge = 0;
        for (int i = 0; i < jumlahSimpul; i++) {
            cout << "[" << simpul[i].id << "] " << simpul[i].judul << " -> ";
            if (derajat[i] == 0) {
                cout << "(tidak punya hubungan)";
            } else {
                for (int k = 0; k < derajat[i]; k++) {
                    const Buku &t = simpul[adj[i][k].tujuan];
                    cout << "[" << t.id << "] (bobot " << adj[i][k].bobot << ")";
                    if (k < derajat[i] - 1) cout << ", ";
                }
            }
            cout << "\n";
            totalEdge += derajat[i];
        }
        cout << "Jumlah simpul: " << jumlahSimpul
             << ", jumlah edge: " << totalEdge / 2 << "\n";
    }
 
    int rekomendasi(int idAsal, int maks) const {
        int awal = cariIndeksById(idAsal);
        if (awal == -1) {
            cout << "Buku dengan ID " << idAsal << " tidak ditemukan.\n";
            return 0;
        }
 
        int antrian[MAX];
        int level[MAX];                
        for (int i = 0; i < jumlahSimpul; i++) level[i] = -1;   
 
        int depan = 0, belakang = 0;
        antrian[belakang++] = awal;     
        level[awal] = 0;
 
        cout << "\nRekomendasi untuk: " << simpul[awal].judul << "\n";
        int hasil = 0;
 
        while (depan < belakang && hasil < maks) {
            int u = antrian[depan++];   
            if (u != awal) {
                if (hasil == 0) {
                    cetakTeksRata("ID", 4);
                    cetakTeksRata("Judul", 32);
                    cetakTeksRata("Kategori", 12);
                    cout << "Jarak\n";
                    for (int i = 0; i < 55; i++) cout << '-';
                    cout << "\n";
                }
                cetakAngkaRata(simpul[u].id, 4);
                cetakTeksRata(simpul[u].judul, 32);
                cetakTeksRata(simpul[u].kategori, 12);
                cout << level[u] << " langkah\n";
                hasil++;
            }
            for (int k = 0; k < derajat[u]; k++) {
                int v = adj[u][k].tujuan;
                if (level[v] == -1) {   
                    level[v] = level[u] + 1;
                    antrian[belakang++] = v;
                }
            }
        }
        if (hasil == 0) cout << "Tidak ada buku sejenis.\n";
        return hasil;
    }
};
 
GrafBuku graf;   
 
void siapkanGraf() {
    for (int i = 0; i < jumlah; i++) graf.tambahBuku(buku[i]);
    graf.bangunEdge();
}
 
void menuGraf() {
    int pilih;
    do {
        cout << "\n=== MENU GRAF & REKOMENDASI (BFS) ===\n";
        cout << "1. Tampilkan graf buku\n";
        cout << "2. Rekomendasi buku sejenis\n";
        cout << "0. Kembali\n";
        pilih = bacaInt("Pilih: ");
 
        if (pilih == 1) {
            graf.tampilkanGraf();
        } else if (pilih == 2) {
            int id = bacaInt("Masukkan ID buku: ");
            graf.rekomendasi(id, 5);
        } else if (pilih != 0) {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}
// ---- END GRAPH
 
int main() {
    isiDataAwal();
    siapkanGraf();   
 
    int pilih;
    do {
        cout << "\n=== PERPUSTAKAAN DIGITAL ===\n";
        cout << "1. Pengurutan\n";
        cout << "2. Pencarian\n";
        cout << "3. Graf & Rekomendasi\n";
        cout << "0. Keluar\n";
        pilih = bacaInt("Pilih: ");
 
        if (pilih == 1) menuSorting();
        else if (pilih == 2) menuSearching();
        else if (pilih == 3) menuGraf();
        else if (pilih != 0) cout << "Pilihan tidak valid.\n";
    } while (pilih != 0);
 
    return 0;
}