#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef filedata_h
#include "filedata.h"
#endif

// Membersihkan buffer stdin (wajib setelah scanf)
void bersihkanBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Inisialisasi file: Cek jika file ada. Jika tidak, buat dengan header.
void inisialisasiFile(const char *namaFile, const char *header) {
    FILE *fp = fopen(namaFile, "r"); // Coba baca dulu
    if (fp == NULL) {
        // File tidak ada, buat baru dengan mode "w" (write)
        fp = fopen(namaFile, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error: Gagal membuat file '%s'.\n", namaFile);
            exit(1);
        }
        fprintf(fp, "%s", header); // Tulis header
        printf("Info: File '%s' tidak ditemukan, file baru dibuat dengan header.\n", namaFile);
    }
    // Jika file ada (fp != NULL), tidak perlu melakukan apa-apa.
    fclose(fp);
}


// Cek duplikat data pada kolom tertentu (0 = kolom pertama)
// Mengembalikan 1 jika duplikat ditemukan, 0 jika tidak.
int cekDuplikat(const char *namaFile, const char *key, int kolom) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        return 0; // File tidak ada, pasti tidak duplikat
    }

    char baris[512];
    fgets(baris, sizeof(baris), fp); // Lewati baris header

    while (fgets(baris, sizeof(baris), fp)) {
        baris[strcspn(baris, "\n")] = '\0'; // Hapus newline
        char temp_baris[512];
        strcpy(temp_baris, baris);

        char *token = strtok(temp_baris, ",");
        int i = 0;
        while (token != NULL) {
            if (i == kolom && strcmp(token, key) == 0) {
                fclose(fp);
                return 1; // Duplikat ditemukan
            }
            token = strtok(NULL, ",");
            i++;
        }
    }
    fclose(fp);
    return 0; // Tidak ada duplikat
}

// Cek duplikat khusus untuk file KRS (pasangan NIM & ID_MK)
int cekDuplikatKRS(const char *nim, const char *id_mk) {
    FILE *fp = fopen("krs.csv", "r");
    if (!fp) return 0;

    char baris[256];
    fgets(baris, sizeof(baris), fp); // Lewati header

    while (fgets(baris, sizeof(baris), fp)) {
        baris[strcspn(baris, "\n")] = '\0';
        char temp_baris[256];
        strcpy(temp_baris, baris);

        char *nim_csv = strtok(temp_baris, ",");
        char *id_mk_csv = strtok(NULL, ",");

        if (nim_csv && id_mk_csv) {
            if (strcmp(nim_csv, nim) == 0 && strcmp(id_mk_csv, id_mk) == 0) {
                fclose(fp);
                return 1; // Duplikat ditemukan
            }
        }
    }
    fclose(fp);
    return 0;
}


// Fungsi untuk menampilkan isi file
void tampilkanDataFile(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        fprintf(stderr, "Gagal membaca file '%s'.\n", namaFile);
        return;
    }

    char baris[512];
    printf("\n=== Data dari File '%s' ===\n", namaFile);
    while (fgets(baris, sizeof(baris), fp)) {
        printf("%s", baris); 
    }
    printf("===================================\n");
    fclose(fp);
}

// Fungsi REVISI: Tambah Matakuliah (Batch input)
void tambahDataMatakuliah() {
    int jumlah;
    printf("Masukkan jumlah matakuliah yang ingin diinput: ");
    scanf("%d", &jumlah);
    bersihkanBufferInput();

    FILE *fp = fopen("matakuliah.csv", "a"); 
    if (!fp) {
        printf("Gagal membuka file matakuliah.csv untuk menulis!\n");
        return;
    }

    int sukses = 0;
    for (int i = 0; i < jumlah; i++) {
        Matakuliah mk;
        printf("\n--- Matakuliah #%d ---\n", i + 1);
        
        printf("ID MK  : ");
        fgets(mk.id_mk, MAX_MK_ID_LEN, stdin);
        mk.id_mk[strcspn(mk.id_mk, "\n")] = '\0'; 

        // Cek Duplikat
        if (cekDuplikat("matakuliah.csv", mk.id_mk, 0)) {
            printf("Error: ID Matakuliah '%s' sudah terdaftar. Data #%d dibatalkan.\n", mk.id_mk, i + 1);
            continue; // Lanjut ke data berikutnya
        }

        printf("Nama   : ");
        fgets(mk.nama, MAX_NAME_LEN, stdin);
        mk.nama[strcspn(mk.nama, "\n")] = '\0'; 

        printf("SKS    : ");
        scanf("%d", &mk.sks);
        bersihkanBufferInput();

        fprintf(fp, "%s,%s,%d\n", mk.id_mk, mk.nama, mk.sks);
        sukses++;
    }

    fclose(fp);
    printf("\nProses selesai. Berhasil menambahkan %d dari %d data matakuliah.\n", sukses, jumlah);
}

// Fungsi REVISI: Tambah Mahasiswa (Batch input)
void tambahDataMahasiswa() {
    int jumlah;
    printf("Masukkan jumlah mahasiswa yang ingin diinput: ");
    scanf("%d", &jumlah);
    bersihkanBufferInput();

    FILE *fp = fopen("mahasiswa.csv", "a");
    if (!fp) {
        printf("Gagal membuka file mahasiswa.csv untuk menulis!\n");
        return;
    }

    int sukses = 0;
    for (int i = 0; i < jumlah; i++) {
        Mahasiswa mhs;
        printf("\n--- Mahasiswa #%d ---\n", i + 1);

        printf("NIM        : ");
        fgets(mhs.nim, MAX_NIM_LEN, stdin);
        mhs.nim[strcspn(mhs.nim, "\n")] = '\0';

        // Cek Duplikat
        if (cekDuplikat("mahasiswa.csv", mhs.nim, 0)) {
            printf("Error: NIM '%s' sudah terdaftar. Data #%d dibatalkan.\n", mhs.nim, i + 1);
            continue;
        }

        printf("Nama       : ");
        fgets(mhs.nama, MAX_NAME_LEN, stdin);
        mhs.nama[strcspn(mhs.nama, "\n")] = '\0';

        printf("Prodi      : ");
        fgets(mhs.prodi, MAX_PRODI_LEN, stdin);
        mhs.prodi[strcspn(mhs.prodi, "\n")] = '\0';

        printf("Fakultas   : ");
        fgets(mhs.fakultas, MAX_FAKULTAS_LEN, stdin);
        mhs.fakultas[strcspn(mhs.fakultas, "\n")] = '\0';

        printf("Thn Masuk  : ");
        scanf("%d", &mhs.tahun_masuk);
        bersihkanBufferInput();

        printf("IPK        : ");
        scanf("%f", &mhs.ipk);
        bersihkanBufferInput();
        
        fprintf(fp, "%s,%s,%s,%s,%d,%.2f\n",
                mhs.nim, mhs.nama, mhs.prodi, mhs.fakultas, mhs.tahun_masuk, mhs.ipk);
        sukses++;
    }
    
    fclose(fp);
    printf("\nProses selesai. Berhasil menambahkan %d dari %d data mahasiswa.\n", sukses, jumlah);
}

// Fungsi REVISI: Tambah KRS (Batch input)
void tambahDataKRS() {
    // Tampilkan data yang ada untuk membantu input (hanya sekali)
    tampilkanDataFile("mahasiswa.csv");
    tampilkanDataFile("matakuliah.csv");

    int jumlah;
    printf("\nMasukkan jumlah entri KRS yang ingin diinput: ");
    scanf("%d", &jumlah);
    bersihkanBufferInput();

    FILE *fp = fopen("krs.csv", "a"); 
    if (!fp) {
        printf("Gagal membuka file krs.csv untuk menulis!\n");
        return;
    }

    int sukses = 0;
    for (int i = 0; i < jumlah; i++) {
        KRS krs;
        printf("\n--- Entri KRS #%d ---\n", i + 1);
        
        printf("NIM Mahasiswa   : ");
        fgets(krs.nim_mahasiswa, MAX_NIM_LEN, stdin);
        krs.nim_mahasiswa[strcspn(krs.nim_mahasiswa, "\n")] = '\0';

        printf("ID Matakuliah   : ");
        fgets(krs.id_matakuliah, MAX_MK_ID_LEN, stdin);
        krs.id_matakuliah[strcspn(krs.id_matakuliah, "\n")] = '\0';

        // Cek duplikat KRS
        if (cekDuplikatKRS(krs.nim_mahasiswa, krs.id_matakuliah)) {
            printf("Error: Entri KRS (NIM: %s, MK: %s) sudah ada. Data #%d dibatalkan.\n", krs.nim_mahasiswa, krs.id_matakuliah, i + 1);
            continue;
        }

        // (Opsional) Cek apakah NIM dan ID_MK benar-benar ada di file master
        if (!cekDuplikat("mahasiswa.csv", krs.nim_mahasiswa, 0)) {
            printf("Warning: NIM '%s' tidak ditemukan di data mahasiswa.\n", krs.nim_mahasiswa);
        }
        if (!cekDuplikat("matakuliah.csv", krs.id_matakuliah, 0)) {
            printf("Warning: ID MK '%s' tidak ditemukan di data matakuliah.\n", krs.id_matakuliah);
        }
        
        fprintf(fp, "%s,%s\n", krs.nim_mahasiswa, krs.id_matakuliah);
        sukses++;
    }
    
    fclose(fp);
    printf("\nProses selesai. Berhasil menambahkan %d dari %d data KRS.\n", sukses, jumlah);
}


// Fungsi REVISI: Hapus Mahasiswa (dengan Konfirmasi)
void hapusDataMahasiswa() {
    char nim_hapus[MAX_NIM_LEN];
    printf("Masukkan NIM mahasiswa yang akan dihapus: ");
    fgets(nim_hapus, MAX_NIM_LEN, stdin);
    nim_hapus[strcspn(nim_hapus, "\n")] = '\0';

    // --- REVISI: Cek dulu datanya ada atau tidak ---
    if (!cekDuplikat("mahasiswa.csv", nim_hapus, 0)) {
        printf("Error: Data mahasiswa dengan NIM '%s' tidak ditemukan.\n", nim_hapus);
        return; // Langsung keluar
    }

    // --- REVISI: Tambahkan Konfirmasi ---
    char konfirmasi;
    printf("\nPERINGATAN: Anda akan menghapus data mahasiswa dengan NIM '%s'.\n", nim_hapus);
    printf("Data KRS yang terkait dengan NIM ini TIDAK akan terhapus otomatis.\n");
    printf("Apakah Anda yakin ingin melanjutkan? (y/t): ");
    scanf("%c", &konfirmasi);
    bersihkanBufferInput();

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        printf("Penghapusan dibatalkan.\n");
        return; // Keluar dari fungsi
    }
    // --- Akhir Revisi ---

    // Lanjutkan proses penghapusan jika konfirmasi 'y'
    FILE *fpIn = fopen("mahasiswa.csv", "r");
    if (!fpIn) {
        printf("Error: Gagal membuka 'mahasiswa.csv'\n");
        return;
    }
    
    FILE *fpOut = fopen("temp_mhs.csv", "w");
    if (!fpOut) {
        printf("Error: Gagal membuat file temporary\n");
        fclose(fpIn);
        return;
    }

    char baris[512];
    
    // Salin header
    fgets(baris, sizeof(baris), fpIn);
    fprintf(fpOut, "%s", baris);

    // Baca dan proses sisa file
    while (fgets(baris, sizeof(baris), fpIn)) {
        char temp_baris[512];
        strcpy(temp_baris, baris); // Salin baris asli untuk ditulis ulang

        char *nim_csv = strtok(baris, ","); 

        if (strcmp(nim_csv, nim_hapus) == 0) {
            // Ini adalah data yang akan dihapus, jadi JANGAN salin
        } else {
            fprintf(fpOut, "%s", temp_baris); // Salin baris yang tidak cocok
        }
    }

    fclose(fpIn);
    fclose(fpOut);

    remove("mahasiswa.csv"); // Hapus file lama
    rename("temp_mhs.csv", "mahasiswa.csv"); // Ubah nama file temp
    
    printf("Data mahasiswa dengan NIM '%s' berhasil dihapus.\n", nim_hapus);
}


// --- FUNGSI UNTUK CARI KRS (TIDAK BERUBAH) ---

// 1. Fungsi untuk memuat semua data Mahasiswa ke memory
int loadMahasiswa(Mahasiswa **data, int *count) {
    FILE *fp = fopen("mahasiswa.csv", "r");
    if (!fp) return 0;

    char baris[512];
    *count = 0;
    fgets(baris, sizeof(baris), fp); // Lewati header
    while (fgets(baris, sizeof(baris), fp)) (*count)++; // Hitung jumlah data

    if (*count == 0) {
        fclose(fp);
        return 0; // File kosong
    }

    *data = (Mahasiswa*) malloc(*count * sizeof(Mahasiswa));
    if (!*data) {
        printf("Gagal alokasi memori!\n");
        fclose(fp);
        return 0;
    }

    rewind(fp); // Kembali ke awal file
    fgets(baris, sizeof(baris), fp); // Lewati header lagi
    int i = 0;
    while (fgets(baris, sizeof(baris), fp)) {
        sscanf(baris, "%[^,],%[^,],%[^,],%[^,],%d,%f",
               (*data)[i].nim,
               (*data)[i].nama,
               (*data)[i].prodi,
               (*data)[i].fakultas,
               &(*data)[i].tahun_masuk,
               &(*data)[i].ipk);
        i++;
    }
    fclose(fp);
    return 1;
}

// 2. Fungsi untuk memuat semua data Matakuliah ke memory
int loadMatakuliah(Matakuliah **data, int *count) {
    FILE *fp = fopen("matakuliah.csv", "r");
    if (!fp) return 0;

    char baris[256];
    *count = 0;
    fgets(baris, sizeof(baris), fp); // Header
    while (fgets(baris, sizeof(baris), fp)) (*count)++;

    if (*count == 0) {
        fclose(fp);
        return 0; // File kosong
    }

    *data = (Matakuliah*) malloc(*count * sizeof(Matakuliah));
    if (!*data) {
        printf("Gagal alokasi memori!\n");
        fclose(fp);
        return 0;
    }

    rewind(fp);
    fgets(baris, sizeof(baris), fp); // Header
    int i = 0;
    while (fgets(baris, sizeof(baris), fp)) {
        sscanf(baris, "%[^,],%[^,],%d",
               (*data)[i].id_mk,
               (*data)[i].nama,
               &(*data)[i].sks);
        i++;
    }
    fclose(fp);
    return 1;
}

// 3. Fungsi untuk memuat semua data KRS ke memory
int loadKRS(KRS **data, int *count) {
    FILE *fp = fopen("krs.csv", "r");
    if (!fp) return 0;

    char baris[256];
    *count = 0;
    fgets(baris, sizeof(baris), fp); // Header
    while (fgets(baris, sizeof(baris), fp)) (*count)++;

    if (*count == 0) {
        fclose(fp);
        return 0; // File kosong
    }

    *data = (KRS*) malloc(*count * sizeof(KRS));
    if (!*data) {
        printf("Gagal alokasi memori!\n");
        fclose(fp);
        return 0;
    }

    rewind(fp);
    fgets(baris, sizeof(baris), fp); // Header
    int i = 0;
    while (fgets(baris, sizeof(baris), fp)) {
        sscanf(baris, "%[^,],%[^\n]",
               (*data)[i].nim_mahasiswa,
               (*data)[i].id_matakuliah);
        i++;
    }
    fclose(fp);
    return 1;
}

// 
// =========================================================================
// == FUNGSI INI ADALAH SATU-SATUNYA YANG BERUBAH PADA REVISI INI ==
// =========================================================================
// 
// 4. Fungsi utama PENCARIAN KRS (REVISI: Tambah output file)
void cariKRSMahasiswa() {
    // Muat semua data dari 3 file CSV
    Mahasiswa *mhs_data;
    int mhs_count;
    Matakuliah *mk_data;
    int mk_count;
    KRS *krs_data;
    int krs_count;

    // Cek dan muat data (return jika gagal)
    if (!loadMahasiswa(&mhs_data, &mhs_count)) {
        printf("Error: Gagal memuat 'mahasiswa.csv'. File mungkin kosong atau rusak.\n");
        return;
    }
    if (!loadMatakuliah(&mk_data, &mk_count)) {
        printf("Error: Gagal memuat 'matakuliah.csv'.\n");
        free(mhs_data);
        return;
    }
    if (!loadKRS(&krs_data, &krs_count)) {
        printf("Error: Gagal memuat 'krs.csv'.\n");
        free(mhs_data);
        free(mk_data);
        return;
    }

    char searchTerm[MAX_NAME_LEN];
    printf("Masukkan NIM atau Nama Mahasiswa yang dicari: ");
    fgets(searchTerm, MAX_NAME_LEN, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < mhs_count; i++) {
        // Cari berdasarkan NIM (cocok persis) ATAU Nama (cocok sebagian)
        if (strcmp(mhs_data[i].nim, searchTerm) == 0 || strstr(mhs_data[i].nama, searchTerm) != NULL) {
            found = 1;
            
            // --- [REVISI] BUAT NAMA FILE DAN BUKA FILE ---
            char namaFile[256];
            sprintf(namaFile, "KRS_%s.csv", mhs_data[i].nim); // Nama file: KRS_NIM.csv
            
            FILE *fpOut = fopen(namaFile, "w");
            if (fpOut == NULL) {
                printf("Error: Gagal membuat file output '%s'\n", namaFile);
                // (Jangan hentikan program, tampilkan saja di console)
            } else {
                // Tulis info mahasiswa di file
                fprintf(fpOut, "NIM,%s\n", mhs_data[i].nim);
                fprintf(fpOut, "Nama,%s\n", mhs_data[i].nama);
                fprintf(fpOut, "Fakultas,%s\n", mhs_data[i].fakultas);
                fprintf(fpOut, "Prodi,%s\n", mhs_data[i].prodi);
                fprintf(fpOut, "Angkatan,%d\n", mhs_data[i].tahun_masuk);
                fprintf(fpOut, "IPK,%.2f\n", mhs_data[i].ipk);
                fprintf(fpOut, "\n"); // Baris kosong
                // Tulis header KRS
                fprintf(fpOut, "Kode,Nama Matakuliah,SKS\n");
            }
            // --- [AKHIR REVISI] ---


            // --- TAMPILKAN DATA MAHASISWA (di Console) ---
            printf("\n--- Data Mahasiswa Ditemukan ---\n");
            printf("NIM       : %s\n", mhs_data[i].nim);
            printf("Nama      : %s\n", mhs_data[i].nama);
            printf("Fak/Prodi : %s / %s\n", mhs_data[i].fakultas, mhs_data[i].prodi);
            printf("Angkatan  : %d\n", mhs_data[i].tahun_masuk);
            printf("IPK       : %.2f\n", mhs_data[i].ipk);

            // --- TAMPILKAN DATA KRS (di Console) ---
            printf("\n--- Daftar Matakuliah (KRS) ---\n");
            printf("----------------------------------------------------------------------\n");
            printf("%-15s %-40s %s\n", "Kode", "Nama Matakuliah", "SKS");
            printf("----------------------------------------------------------------------\n");

            int total_sks = 0;
            // Cari data KRS yang cocok dengan NIM mahasiswa ini
            for (int j = 0; j < krs_count; j++) {
                if (strcmp(krs_data[j].nim_mahasiswa, mhs_data[i].nim) == 0) {
                    // Jika cocok, cari detail Matakuliah-nya
                    for (int k = 0; k < mk_count; k++) {
                        if (strcmp(mk_data[k].id_mk, krs_data[j].id_matakuliah) == 0) {
                            
                            // Tampilkan di console
                            printf("%-15s %-40s %d\n",
                                   mk_data[k].id_mk,
                                   mk_data[k].nama,
                                   mk_data[k].sks);
                            
                            // --- [REVISI] TULIS KE FILE CSV ---
                            if (fpOut != NULL) {
                                fprintf(fpOut, "%s,%s,%d\n",
                                        mk_data[k].id_mk,
                                        mk_data[k].nama,
                                        mk_data[k].sks);
                            }
                            // --- [AKHIR REVISI] ---

                            total_sks += mk_data[k].sks;
                            break; // Keluar dari loop 'k' (matakuliah)
                        }
                    }
                }
            }
            
            // Tampilkan Total SKS (di Console)
            printf("----------------------------------------------------------------------\n");
            printf("%-56s Total SKS: %d\n", "", total_sks);
            
            // --- [REVISI] TUTUP FILE DAN TULIS TOTAL SKS ---
            if (fpOut != NULL) {
                fprintf(fpOut, "\nTotal SKS,%d\n", total_sks);
                fclose(fpOut);
                printf("\n[Info] Data KRS juga telah disimpan ke file: %s\n", namaFile);
            }
            // --- [AKHIR REVISI] ---
            
            printf("\n"); // Spasi antar mahasiswa jika hasil pencarian > 1
        }
    }

    if (!found) {
        printf("Data mahasiswa dengan NIM atau Nama '%s' tidak ditemukan.\n", searchTerm);
    }

    // Jangan lupa bebaskan memori!
    free(mhs_data);
    free(mk_data);
    free(krs_data);
}