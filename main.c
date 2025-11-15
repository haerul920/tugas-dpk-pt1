#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#ifndef filedata_h 
#include "filedata.h"   
#endif

void tampilkanUsage(char *namaProgram) {
    printf("Usage: %s [PILIHAN]\n", namaProgram);
    printf("Pilihan:\n");
    printf("  1 : Menjalankan Modul Input Matakuliah (output: matakuliah.csv)\n");
    printf("  2 : Menjalankan Modul Input Mahasiswa (output: mahasiswa.csv)\n");
    printf("  3 : Menjalankan Modul Input KRS (output: krs.csv)\n");
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Error: Argumen tidak sesuai.\n");
        tampilkanUsage(argv[0]);
        return 1; 
    }

    int pilihan = atoi(argv[1]);
    int jumlah;

    switch (pilihan) {
        case 1:
            printf("--- MODUL INPUT MATAKULIAH ---\n");
            Matakuliah *daftar_mk = inputDataMatakuliah(&jumlah);
            simpanMatakuliahKeCSV(daftar_mk, jumlah);
            free(daftar_mk); 
            bacaDariFileCSV("matakuliah.csv"); 
            break;

        case 2:
            printf("--- MODUL INPUT MAHASISWA ---\n");
            Mahasiswa *daftar_mhs = inputDataMahasiswa(&jumlah);
            simpanMahasiswaKeCSV(daftar_mhs, jumlah);
            free(daftar_mhs);
            bacaDariFileCSV("mahasiswa.csv"); 

        case 3:
            printf("--- MODUL INPUT KRS ---\n");
            KRS *daftar_krs = inputDataKRS(&jumlah);
            simpanKRSKeCSV(daftar_krs, jumlah);
            free(daftar_krs);
            bacaDariFileCSV("krs.csv"); 
            break;

        default:
            fprintf(stderr, "Error: Pilihan '%s' tidak valid.\n", argv[1]);
            tampilkanUsage(argv[0]);
            return 1;
    }

    return 0;

}
