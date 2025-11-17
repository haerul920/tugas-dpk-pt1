<h1 align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=30&pause=1000&color=33FF33&center=true&vCenter=true&width=500&lines=Sistem+Manajemen+KRS" alt="Typing SVG" />
</h1>

<h3 align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=16&pause=1000&color=00BFFF&center=true&vCenter=true&width=600&lines=Sebuah+proyek+konsol+C+untuk+mengelola+data" alt="Typing SVG" />
</h3>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Language" />
</p>

Proyek ini adalah sistem manajemen akademik sederhana berbasis konsol yang ditulis dalam bahasa C. Program ini memungkinkan pengguna untuk mengelola data master **Mahasiswa** dan **Matakuliah**, serta mencatat **Kartu Rencana Studi (KRS)**. Semua data disimpan secara persisten dalam file `.csv`.

---

## ✨ Fitur Utama

- 👨‍🎓 **Manajemen Mahasiswa:**
  - Tambah data mahasiswa baru (NIM, Nama, Prodi, Fakultas, Angkatan, IPK).
  - Hapus data mahasiswa berdasarkan NIM (dengan konfirmasi).
- 📚 **Manajemen Matakuliah:**
  - Tambah data matakuliah baru (ID MK, Nama, SKS).
- ✍️ **Manajemen KRS:**
  - Tambah data KRS untuk menghubungkan mahasiswa dengan matakuliah yang diambil.
- 🔍 **Pencarian Cerdas:**
  - Cari data KRS lengkap mahasiswa berdasarkan **NIM** atau **Nama**.
  - Menampilkan detail mahasiswa (IPK, Fakultas) dan daftar matakuliah yang diambil (dengan total SKS).
- 📄 **Ekspor ke CSV:**
  - Hasil pencarian KRS secara otomatis diekspor ke file `.csv` terpisah (misal: `KRS_D121251094.csv`) untuk pelaporan.
- 💾 **Penyimpanan Persisten:**
  - Semua data disimpan (mode _append_) di file `mahasiswa.csv`, `matakuliah.csv`, dan `krs.csv`.
- 🛡️ **Validasi Duplikat:**
  - Sistem secara otomatis mencegah data duplikat (NIM, ID MK, dan entri KRS) untuk menjaga integritas data.

---

## 📂 Struktur Proyek

Berikut adalah tampilan struktur file dan file-file `.csv` yang dihasilkan oleh program.

<details>
<summary><b><code>matakuliah.csv</code> (Tampilan File Matakuliah di Excel)</b></summary>

<p align="center">
<img src="public/matakuliah.png" alt="matakuliah">
</p>
</details>

<details>
<summary><b><code>mahasiswa.csv</code> (Tampilan File Mahasiswa di Excel)</b></summary>

<p align="center">
<img src="public/mahasiswa.png" alt="mahasiswa">
</p>
</details>

<details>
<summary><b><code>krs.csv</code> (Tampilan File KRS di Excel)</b></summary>

<p align="center">
<img src="public/matakuliah.png" alt="matakuliah">
</p>
</details>

<details>
<summary><b><code>KRS_D121251094.csv</code> (Tampilan File KRS milik Mahasiswa di Excel)</b></summary>

<p align="center">
<img src="public/d121251094.png" alt="KRS milik Mahasiswa">
</p>
</details>

---

## 🚀 Memulai

Pastikan Anda memiliki compiler C (seperti **gcc**) yang terinstal di sistem Anda.

1.  Buka terminal di direktori utama proyek.
2.  Kompilasi program menggunakan perintah berikut:

    ```bash
    gcc main.c filedata.c -o main.exe
    ```

3.  Setelah perintah di atas berhasil, file `main.exe` akan dibuat di direktori Anda.

---

## ⌨️ Cara Menjalankan

Jalankan program dari terminal dengan perintah `./main.exe` diikuti dengan nomor menu yang diinginkan.

```bash
./main.exe 1  # 📚 Tambah Data Matakuliah
./main.exe 2  # 👨‍🎓 Tambah Data Mahasiswa
./main.exe 3  # ✍️  Tambah Data KRS
./main.exe 4  # 🔍 Cari KRS Mahasiswa (dan Ekspor ke CSV)
./main.exe 5  # ❌ Hapus Data Mahasiswa
./main.exe 6  # 🐞 Tampilkan isi file (Mode Debug)
```

🖼️ Galeri / Contoh Penggunaan
Klik untuk melihat contoh output dari setiap perintah:

<details>
<summary><b><code>./main.exe 1</code> (Tambah Matakuliah)</b></summary>

<p align="center">
<img src="public/1.png" alt="Contoh main.exe 1">
</p>
</details>
<details>
<summary><b><code>./main.exe 2</code> (Tambah Mahasiswa)</b></summary>

<p align="center">
<img src="public/2.png" alt="Contoh main.exe 2">
</p>
</details>
<details>
<summary><b><code>./main.exe 3</code> (Tambah KRS)</b></summary>

<p align="center">
<img src="public/3.png" alt="Contoh main.exe 3">
</p>
</details>
<details>
<summary><b><code>./main.exe 4</code> (Cari KRS & Ekspor .csv)</b></summary>

<p>Perintah ini akan menampilkan data di konsol dan otomatis membuat file laporan CSV seperti <code>KRS_D121251094.csv</code>.</p>
<p align="center">
<img src="public/4.png" alt="Contoh main.exe 4">
</p>
</details>
<details>
<summary><b><code>./main.exe 5</code> (Hapus Mahasiswa)</b></summary>

<p align="center">
<img src="public/5.png" alt="Contoh main.exe 5">
</p>
</details>
<details>
<summary><b><code>./main.exe 6</code> (Tampilkan File Debug)</b></summary>

<p align="center">
<img src="public/6.png" alt="Contoh main.exe 6">
</p>
</details>
<p align="center">
<img src="https://readme-typing-svg.demolab.com?font=Press+Start+2P&size=28&pause=1000&color=00FF00&center=true&vCenter=true&width=435&lines=Thank+You" />
</p>
