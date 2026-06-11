/*
================================================================================
                    SISTEM MANAJEMEN REPOSITORY SOURCE CODE
                     Simple Version Control System (VCS)
================================================================================

KOMPONEN ADT YANG DIGUNAKAN:
  1. Linked List  - Untuk menyimpan daftar file dalam setiap folder
  2. Stack        - Untuk menyimpan riwayat perubahan (Undo dengan snapshot)
  3. Binary Tree  - Untuk menyimpan struktur folder (BST)

STRUKTUR DATA:
  - FileNode: Menyimpan informasi file (ID, nama, konten, ukuran)
  - Folder: Node BST untuk menyimpan folder dan daftar file di dalamnya
  - Snapshot: Menyimpan snapshot lengkap dari seluruh folder tree untuk undo

FITUR MINIMAL (SESUAI REQUIREMENT):
  1. Tambah File         - Tambah file baru ke dalam folder
  2. Hapus File          - Hapus file dari folder
  3. Rename File         - Ubah nama file
  4. Undo Aktivitas      - Kembalikan state ke snapshot sebelumnya
  5. Tampilkan Folder    - Tampilkan struktur folder (tree structure)
  6. Cari File           - Cari file berdasarkan nama di dalam folder

FITUR TAMBAHAN:
  - Tambah Folder        - Tambah folder baru (BST insert)
  - Tampilkan Semua File - Tampilkan semua file di semua folder
  - Edit Konten File     - File konten disimpan dan otomatis kalkulasi size

KARKTERISTIK:
  - Ukuran file otomatis dihitung dari panjang konten (dalam KB)
  - Setiap operasi modifikasi membuat snapshot untuk undo
  - Deep copy digunakan untuk snapshot integrity
  - Memory management dengan proper cleanup

================================================================================
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct FileNode
{
    int idFile;
    string namaFile;
    string isiFile;  // File contents
    int ukuranFile;  // Automatically calculated from contents
    FileNode *next;
};

struct Folder
{
    string namaFolder;
    FileNode *files;
    Folder *left;
    Folder *right;
};

// Snapshot structure to store complete state
struct Snapshot
{
    Folder *folderTree;
    Snapshot *next;
};

Folder *root = NULL;
Snapshot *undoStack = NULL;

// Calculate file size based on content length
int hitungUkuranFile(const string &konten)
{
    // Size in bytes (assume 1 byte per character)
    // Convert to KB by dividing by 1024
    int sizeInBytes = konten.length();
    return max(1, sizeInBytes / 1024);  // Minimum 1 KB
}

// Helper function to deep copy a file linked list
FileNode *copyFileList(FileNode *head)
{
    if (head == NULL)
        return NULL;

    FileNode *newHead = new FileNode();
    newHead->idFile = head->idFile;
    newHead->namaFile = head->namaFile;
    newHead->isiFile = head->isiFile;
    newHead->ukuranFile = head->ukuranFile;
    newHead->next = copyFileList(head->next);

    return newHead;
}

// Helper function to deep copy a folder tree
Folder *copyFolderTree(Folder *node)
{
    if (node == NULL)
        return NULL;

    Folder *newNode = new Folder();
    newNode->namaFolder = node->namaFolder;
    newNode->files = copyFileList(node->files);
    newNode->left = copyFolderTree(node->left);
    newNode->right = copyFolderTree(node->right);

    return newNode;
}

// Helper function to delete a file linked list
void deleteFileList(FileNode *head)
{
    while (head != NULL)
    {
        FileNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper function to delete a folder tree
void deleteFolderTree(Folder *node)
{
    if (node != NULL)
    {
        deleteFolderTree(node->left);
        deleteFolderTree(node->right);
        deleteFileList(node->files);
        delete node;
    }
}

// Create a snapshot of the current state
void createSnapshot()
{
    Snapshot *newSnapshot = new Snapshot();
    newSnapshot->folderTree = copyFolderTree(root);
    newSnapshot->next = undoStack;
    undoStack = newSnapshot;
}

// Undo to the previous snapshot
void undo()
{
    if (undoStack == NULL)
    {
        cout << "Tidak ada aktivitas untuk di-undo" << endl;
        return;
    }

    Snapshot *oldSnapshot = undoStack;
    undoStack = undoStack->next;

    deleteFolderTree(root);
    root = oldSnapshot->folderTree;

    cout << "Undo berhasil" << endl;

    delete oldSnapshot;
}

// Find a folder in the tree
Folder *cariFolderHelper(Folder *node, string nama)
{
    if (node == NULL)
        return NULL;

    if (node->namaFolder == nama)
        return node;

    Folder *left = cariFolderHelper(node->left, nama);
    if (left != NULL)
        return left;

    return cariFolderHelper(node->right, nama);
}

Folder *cariFolder(string nama)
{
    return cariFolderHelper(root, nama);
}

// Find a file in a folder
FileNode *cariFolderFile(Folder *folder, string nama)
{
    if (folder == NULL)
        return NULL;

    FileNode *cur = folder->files;
    while (cur != NULL)
    {
        if (cur->namaFile == nama)
            return cur;
        cur = cur->next;
    }

    return NULL;
}

void tambahFile()
{
    string namaFolder;
    cout << "Nama Folder : ";
    cin >> namaFolder;

    Folder *folder = cariFolder(namaFolder);

    if (folder == NULL)
    {
        cout << "Folder tidak ditemukan" << endl;
        return;
    }

    FileNode *baru = new FileNode();

    cout << "ID File : ";
    cin >> baru->idFile;

    cout << "Nama File : ";
    cin >> baru->namaFile;
    cin.ignore();  // Clear newline

    cout << "Isi File (masukkan konten, gunakan . di awal baris untuk selesai):" << endl;
    string konten = "";
    string baris;
    while (getline(cin, baris))
    {
        if (baris == ".")
            break;
        konten += baris + "\n";
    }

    baru->isiFile = konten;
    baru->ukuranFile = hitungUkuranFile(konten);  // Automatically calculate size
    baru->next = NULL;

    if (folder->files == NULL)
    {
        folder->files = baru;
    }
    else
    {
        FileNode *cur = folder->files;

        while (cur->next != NULL)
        {
            cur = cur->next;
        }

        cur->next = baru;
    }

    cout << "File berhasil ditambahkan (Ukuran: " << baru->ukuranFile << " KB)" << endl;

    createSnapshot();
}

void tampilFile()
{
    string namaFolder;
    cout << "Nama Folder : ";
    cin >> namaFolder;

    Folder *folder = cariFolder(namaFolder);

    if (folder == NULL)
    {
        cout << "Folder tidak ditemukan" << endl;
        return;
    }

    if (folder->files == NULL)
    {
        cout << "Folder kosong" << endl;
        return;
    }

    FileNode *cur = folder->files;

    while (cur != NULL)
    {
        cout << "ID     : " << cur->idFile << endl;
        cout << "Nama   : " << cur->namaFile << endl;
        cout << "Ukuran : " << cur->ukuranFile << " KB" << endl;
        cout << "------------------" << endl;

        cur = cur->next;
    }
}

void cariFile()
{
    string namaFolder;
    cout << "Nama Folder : ";
    cin >> namaFolder;

    string nama;
    cout << "Masukkan nama file : ";
    cin >> nama;

    Folder *folder = cariFolder(namaFolder);

    if (folder == NULL)
    {
        cout << "Folder tidak ditemukan" << endl;
        return;
    }

    FileNode *file = cariFolderFile(folder, nama);

    if (file != NULL)
    {
        cout << "\nFile ditemukan" << endl;
        cout << "ID     : " << file->idFile << endl;
        cout << "Nama   : " << file->namaFile << endl;
        cout << "Ukuran : " << file->ukuranFile << " KB" << endl;
        cout << "Isi :" << endl;
        cout << "---" << endl;
        cout << file->isiFile << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << "File tidak ditemukan" << endl;
    }
}

void renameFile()
{
    string namaFolder;
    cout << "Nama Folder : ";
    cin >> namaFolder;

    string lama;
    cout << "Nama lama : ";
    cin >> lama;

    Folder *folder = cariFolder(namaFolder);

    if (folder == NULL)
    {
        cout << "Folder tidak ditemukan" << endl;
        return;
    }

    FileNode *file = cariFolderFile(folder, lama);

    if (file != NULL)
    {
        cout << "Nama baru : ";
        cin >> file->namaFile;

        cout << "Rename berhasil" << endl;

        createSnapshot();
    }
    else
    {
        cout << "File tidak ditemukan" << endl;
    }
}

void hapusFile()
{
    string namaFolder;
    cout << "Nama Folder : ";
    cin >> namaFolder;

    string nama;
    cout << "Nama file : ";
    cin >> nama;

    Folder *folder = cariFolder(namaFolder);

    if (folder == NULL)
    {
        cout << "Folder tidak ditemukan" << endl;
        return;
    }

    FileNode *cur = folder->files;
    FileNode *prev = NULL;

    while (cur != NULL)
    {
        if (cur->namaFile == nama)
        {
            if (prev == NULL)
            {
                folder->files = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            delete cur;

            cout << "File berhasil dihapus" << endl;

            createSnapshot();

            return;
        }

        prev = cur;
        cur = cur->next;
    }

    cout << "File tidak ditemukan" << endl;
}

Folder *tambahFolder(Folder *node, string nama)
{
    if (node == NULL)
    {
        Folder *baru = new Folder();

        baru->namaFolder = nama;
        baru->files = NULL;
        baru->left = NULL;
        baru->right = NULL;

        return baru;
    }

    if (nama < node->namaFolder)
    {
        node->left = tambahFolder(node->left, nama);
    }
    else if (nama > node->namaFolder)
    {
        node->right = tambahFolder(node->right, nama);
    }
    else
    {
        cout << "Folder sudah ada" << endl;
        return node;
    }

    return node;
}

void tampilFolder(Folder *node, int depth = 0)
{
    if (node != NULL)
    {
        tampilFolder(node->left, depth);

        for (int i = 0; i < depth; i++)
            cout << "  ";

        cout << "[" << node->namaFolder << "]";

        if (node->files != NULL)
        {
            cout << " (";
            int count = 0;
            FileNode *cur = node->files;
            while (cur != NULL)
            {
                count++;
                cur = cur->next;
            }
            cout << count << " files)";
        }

        cout << endl;

        tampilFolder(node->right, depth);
    }
}

void tampilSemuaFile(Folder *node)
{
    if (node != NULL)
    {
        tampilSemuaFile(node->left);

        cout << "\n[" << node->namaFolder << "]" << endl;
        cout << "-------------------" << endl;

        if (node->files == NULL)
        {
            cout << "Folder kosong" << endl;
        }
        else
        {
            FileNode *cur = node->files;
            while (cur != NULL)
            {
                cout << "  ID " << cur->idFile << ": " << cur->namaFile << " (" << cur->ukuranFile << " KB)" << endl;
                cur = cur->next;
            }
        }

        tampilSemuaFile(node->right);
    }
}

int main()
{
    int pilih;

    do
    {
        cout << "\n===== SISTEM MANAJEMEN REPOSITORY SOURCE CODE =====" << endl;
        cout << "ADT: Linked List (Files), Stack (Undo), Tree (Folder)" << endl;

        cout << "\n--- Fitur Minimal ---" << endl;
        cout << "1. Tambah File" << endl;
        cout << "2. Hapus File" << endl;
        cout << "3. Rename File" << endl;
        cout << "4. Undo Aktivitas Terakhir" << endl;
        cout << "5. Tampilkan Struktur Folder" << endl;
        cout << "6. Cari File berdasarkan Nama" << endl;

        cout << "\n--- Fitur Tambahan ---" << endl;
        cout << "7. Tampilkan File di Folder" << endl;
        cout << "8. Tampilkan Semua File" << endl;
        cout << "9. Tambah Folder" << endl;
        cout << "0. Keluar" << endl;

        cout << "\nMasukkan Pilihan (ANGKA) : ";
        cin >> pilih;
        cin.ignore();  // Clear newline from input buffer

        switch (pilih)
        {
        case 1:
            tambahFile();
            break;

        case 2:
            hapusFile();
            break;

        case 3:
            renameFile();
            break;

        case 4:
            undo();
            break;

        case 5:
            cout << "\nStruktur Folder:" << endl;
            if (root == NULL)
                cout << "Belum ada folder" << endl;
            else
                tampilFolder(root);
            break;

        case 6:
            cariFile();
            break;

        case 7:
            tampilFile();
            break;

        case 8:
            cout << "\nSemua File:" << endl;
            if (root == NULL)
                cout << "Belum ada folder" << endl;
            else
                tampilSemuaFile(root);
            break;

        case 9:
        {
            string nama;

            cout << "Nama Folder : ";
            getline(cin, nama);

            root = tambahFolder(root, nama);

            createSnapshot();

            break;
        }

        case 0:
            cout << "Terima kasih telah menggunakan Sistem Manajemen Repository!" << endl;
            break;

        default:
            cout << "Pilihan tidak valid" << endl;
        }

    } while (pilih != 0);

    // Cleanup
    deleteFolderTree(root);
    while (undoStack != NULL)
    {
        Snapshot *temp = undoStack;
        undoStack = undoStack->next;
        deleteFolderTree(temp->folderTree);
        delete temp;
    }

    return 0;
}
