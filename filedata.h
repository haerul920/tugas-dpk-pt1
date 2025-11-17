#ifndef filedata_h
#define filedata_h

#include <stdio.h> // Diperlukan untuk tipe FILE

// Menambahkan konstanta baru untuk bidang baru
#define MAX_NAME_LEN 100
#define MAX_PRODI_LEN 50
#define MAX_FAKULTAS_LEN 50
#define MAX_NIM_LEN 20
#define MAX_MK_ID_LEN 20

// Struct Mahasiswa dimodifikasi
typedef struct {
    char nim[MAX_NIM_LEN];       // Mengganti int id dengan char nim
    char nama[MAX_NAME_LEN];
    char prodi[MAX_PRODI_LEN];
    char fakultas[MAX_FAKULTAS_LEN]; // Bidang baru
    int tahun_masuk;                 // Bidang baru
    float ipk;
} Mahasiswa;

typedef struct {
    char id_mk[MAX_MK_ID_LEN];
    char nama[MAX_NAME_LEN];
    int sks;
} Matakuliah;

// Struct KRS dimodifikasi
typedef struct {
    char nim_mahasiswa[MAX_NIM_LEN]; // Mengganti id_mahasiswa
    char id_matakuliah[MAX_MK_ID_LEN];
} KRS;

// --- Prototipe Fungsi ---

void bersihkanBufferInput();

// Fungsi utilitas file
void inisialisasiFile(const char *namaFile, const char *header);
void tampilkanDataFile(const char *namaFile);
int cekDuplikat(const char *namaFile, const char *key, int kolom);
int cekDuplikatKRS(const char *nim, const char *id_mk);

// Fungsi utama modul
void tambahDataMahasiswa();
void tambahDataMatakuliah();
void tambahDataKRS();
void hapusDataMahasiswa();
void cariKRSMahasiswa();

// Fungsi internal untuk memuat data (digunakan oleh 'cari')
int loadMahasiswa(Mahasiswa **data, int *count);
int loadMatakuliah(Matakuliah **data, int *count);
int loadKRS(KRS **data, int *count);

#endif