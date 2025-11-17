#ifndef filedata_h
#define filedata_h

#include <stdio.h>

#define MAX_NAME_LEN 100
#define MAX_PRODI_LEN 50
#define MAX_FAKULTAS_LEN 50
#define MAX_NIM_LEN 20
#define MAX_MK_ID_LEN 20

typedef struct {
    char nim[MAX_NIM_LEN];
    char nama[MAX_NAME_LEN];
    char prodi[MAX_PRODI_LEN];
    char fakultas[MAX_FAKULTAS_LEN];
    int tahun_masuk;
    float ipk;
} Mahasiswa;

typedef struct {
    char id_mk[MAX_MK_ID_LEN];
    char nama[MAX_NAME_LEN];
    int sks;
} Matakuliah;

typedef struct {
    char nim_mahasiswa[MAX_NIM_LEN];
    char id_matakuliah[MAX_MK_ID_LEN];
} KRS;

void bersihkanBufferInput();

void inisialisasiFile(const char *namaFile, const char *header);
void tampilkanDataFile(const char *namaFile);
int cekDuplikat(const char *namaFile, const char *key, int kolom);
int cekDuplikatKRS(const char *nim, const char *id_mk);

void tambahDataMahasiswa();
void tambahDataMatakuliah();
void tambahDataKRS();
void hapusDataMahasiswa();
void cariKRSMahasiswa();

int loadMahasiswa(Mahasiswa **data, int *count);
int loadMatakuliah(Matakuliah **data, int *count);
int loadKRS(KRS **data, int *count);

#endif