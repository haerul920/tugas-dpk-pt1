#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef filedata_h
#include "filedata.h"
#endif

void tampilkanUsage(char *namaProgram) {
    printf("Usage: %s [PILIHAN]\n", namaProgram);
    printf("Pilihan:\n");
    printf("  1 : Tambah Data Matakuliah (matakuliah.csv)\n");
    printf("  2 : Tambah Data Mahasiswa (mahasiswa.csv)\n");
    printf("  3 : Tambah Data KRS (krs.csv)\n");
    printf("  4 : Cari KRS Mahasiswa (berdasarkan NIM atau Nama)\n");
    printf("  5 : Hapus Data Mahasiswa (berdasarkan NIM)\n");
    printf("  6 : Tampilkan isi file (Debug)\n");
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Error: Argumen tidak sesuai.\n");
        tampilkanUsage(argv[0]);
        return 1; 
    }

    int pilihan = atoi(argv[1]);

    inisialisasiFile("matakuliah.csv", "ID_MK,Nama,SKS\n");
    inisialisasiFile("mahasiswa.csv", "NIM,Nama,Prodi,Fakultas,Angkatan,IPK\n");
    inisialisasiFile("krs.csv", "NIM_Mahasiswa,ID_Matakuliah\n");

    switch (pilihan) {
        case 1:
            printf("--- MODUL TAMBAH MATAKULIAH ---\n");
            tambahDataMatakuliah();
            break;

        case 2:
            printf("--- MODUL TAMBAH MAHASISWA ---\n");
            tambahDataMahasiswa();
            break;

        case 3:
            printf("--- MODUL TAMBAH KRS ---\n");
            tambahDataKRS();
            break;

        case 4:
            printf("--- MODUL CARI KRS MAHASISWA ---\n");
            cariKRSMahasiswa();
            break;

        case 5:
            printf("--- MODUL HAPUS MAHASISWA ---\n");
            hapusDataMahasiswa();
            break;
        
        case 6:
            printf("--- MODUL TAMPILKAN DATA FILE ---\n");
            printf("Pilih file untuk ditampilkan:\n");
            printf("  1. mahasiswa.csv\n");
            printf("  2. matakuliah.csv\n");
            printf("  3. krs.csv\n");
            printf("Pilihan: ");
            int pilFile;
            scanf("%d", &pilFile);
            bersihkanBufferInput();
            switch (pilFile) {
                case 1: tampilkanDataFile("mahasiswa.csv"); break;
                case 2: tampilkanDataFile("matakuliah.csv"); break;
                case 3: tampilkanDataFile("krs.csv"); break;
                default: printf("Pilihan tidak valid.\n");
            }
            break;

        default:
            fprintf(stderr, "Error: Pilihan '%s' tidak valid.\n", argv[1]);
            tampilkanUsage(argv[0]);
            return 1;
    }

    return 0;
}