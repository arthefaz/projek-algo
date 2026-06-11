# Sistem Manajemen Repository Source Code

## Deskripsi
Sistem manajemen repository sederhana yang mengimplementasikan struktur data Linked List, Stack, dan Tree untuk version control source code.

## Struktur Data

### 1. FileNode (Linked List)
- **idFile**: ID unik untuk file
- **namaFile**: Nama file
- **isiFile**: Konten file (string)
- **ukuranFile**: Ukuran file dalam KB (auto-calculated dari panjang konten)
- **next**: Pointer ke file berikutnya

### 2. Folder (Binary Search Tree)
- **namaFolder**: Nama folder
- **files**: Pointer ke linked list FileNode
- **left**: Child folder dengan nama lexicographically lebih kecil
- **right**: Child folder dengan nama lexicographically lebih besar

### 3. Snapshot (Stack)
- **folderTree**: Deep copy dari seluruh folder tree
- **next**: Pointer ke snapshot sebelumnya

## Fitur Minimal (Sesuai Requirement)

1. **Tambah File** - Menambahkan file baru ke dalam folder
   - Menerima ID, nama file, dan konten
   - Ukuran file otomatis dihitung dari panjang konten
   - Membuat snapshot setelah operasi

2. **Hapus File** - Menghapus file dari folder
   - Mencari file berdasarkan nama
   - Menghapus dari linked list
   - Membuat snapshot setelah operasi

3. **Rename File** - Mengubah nama file
   - Mencari file dan mengubah namanya
   - Membuat snapshot setelah operasi

4. **Undo Aktivitas Terakhir** - Mengembalikan state ke snapshot sebelumnya
   - Merepresentasikan seluruh folder tree dengan semua file
   - Implementasi menggunakan Stack of Snapshots

5. **Tampilkan Struktur Folder** - Menampilkan struktur BST
   - In-order traversal
   - Menunjukkan jumlah file di setiap folder

6. **Cari File berdasarkan Nama** - Mencari file di dalam folder
   - Input: nama folder dan nama file
   - Output: informasi lengkap file (ID, nama, ukuran, konten)

## Fitur Tambahan

- **Tambah Folder** - Menambahkan folder baru (BST insert)
- **Tampilkan File di Folder** - Menampilkan daftar file dalam satu folder
- **Tampilkan Semua File** - Menampilkan semua file di semua folder dengan in-order traversal

## Karakteristik Implementasi

### Kalkulasi Ukuran File
```cpp
int hitungUkuranFile(const string &konten)
{
    int sizeInBytes = konten.length();
    return max(1, sizeInBytes / 1024);  // Minimum 1 KB
}
```

### Snapshot System
- Setiap perubahan state membuat snapshot otomatis
- Deep copy digunakan untuk menjaga integritas snapshot
- Undo mengembalikan root ke state snapshot sebelumnya

### Memory Management
- Deep copy untuk semua struktur data (FileNode, Folder)
- Proper cleanup saat delete
- Memory deallocation di akhir program

## Kompleksitas

- **Tambah Folder**: O(log n) - BST insertion
- **Cari Folder**: O(n) - Linear search dalam tree
- **Tambah/Hapus/Cari File**: O(m) - m = jumlah file dalam folder
- **Undo**: O(n × m) - deep copy dari semua struktur
- **Tampilkan Folder**: O(n) - In-order traversal

## Cara Penggunaan

### Compile
```bash
g++ -std=c++11 -Wall -Wextra UAS.cpp -o UAS
```

### Run
```bash
./UAS
```

### Input Format File
Saat menambah file, gunakan:
```
Nama Folder: <nama_folder>
ID File: <id>
Nama File: <nama>
Isi File: <konten_baris_1>
          <konten_baris_2>
          ...
          .  (titik untuk selesai)
```

## Contoh Operasi

```
1. Tambah Folder "src"
2. Tambah File dengan ID=1, Nama="main.cpp", Konten="int main() {...}"
3. Cari File "main.cpp" di folder "src"
4. Rename "main.cpp" menjadi "app.cpp"
5. Undo (kembali ke "main.cpp")
6. Tampilkan Struktur Folder
```

