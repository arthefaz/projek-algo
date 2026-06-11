#include <iostream>
#include <string>

using namespace std;

/*==================================================
    LINKED LIST FILE REPOSITORY
==================================================*/

struct FileNode
{
    int idFile;
    string namaFile;
    int ukuranFile;

    // File berada di folder mana
    string namaFolder;

    FileNode *next;
};

// Head Linked List
FileNode *head = NULL;

/*==================================================
    STACK UNDO
==================================================*/

struct UndoNode
{
    string aktivitas;

    // Data file yang disimpan untuk undo
    int idFile;
    string namaFile;
    int ukuranFile;
    string namaFolder;

    // Khusus rename
    string namaLama;
    string namaBaru;

    UndoNode *next;
};

// Top Stack
UndoNode *top = NULL;

/*==================================================
    TREE FOLDER
==================================================*/

struct Folder
{
    string namaFolder;

    Folder *left;
    Folder *right;
};

// Root Tree
Folder *root = NULL;

/*==================================================
    FUNGSI STACK
==================================================*/

// Push ke Stack
void pushUndo(UndoNode *data)
{
    data->next = top;
    top = data;
}

/*==================================================
    CEK FOLDER ADA ATAU TIDAK
==================================================*/

bool cariFolder(Folder *node, string nama)
{
    if (node == NULL)
    {
        return false;
    }

    if (node->namaFolder == nama)
    {
        return true;
    }

    if (nama < node->namaFolder)
    {
        return cariFolder(node->left, nama);
    }

    return cariFolder(node->right, nama);
}

/*==================================================
    TAMBAH FILE
==================================================*/

void tambahFile()
{
    FileNode *baru = new FileNode();

    cout << "ID File : ";
    cin >> baru->idFile;

    cout << "Nama File : ";
    cin >> baru->namaFile;

    cout << "Ukuran File (KB) : ";
    cin >> baru->ukuranFile;

    cout << "Folder : ";
    cin >> baru->namaFolder;

    // Folder harus ada terlebih dahulu
    if (!cariFolder(root, baru->namaFolder))
    {
        cout << "Folder tidak ditemukan!\n";
        delete baru;
        return;
    }

    baru->next = NULL;

    if (head == NULL)
    {
        head = baru;
    }
    else
    {
        FileNode *cur = head;

        while (cur->next != NULL)
        {
            cur = cur->next;
        }

        cur->next = baru;
    }

    // Simpan ke stack untuk undo
    UndoNode *undoBaru = new UndoNode();

    undoBaru->aktivitas = "TAMBAH";
    undoBaru->namaFile = baru->namaFile;

    pushUndo(undoBaru);

    cout << "File berhasil ditambahkan\n";
}

/*==================================================
    TAMPIL FILE
==================================================*/

void tampilFile()
{
    if (head == NULL)
    {
        cout << "Belum ada file\n";
        return;
    }

    FileNode *cur = head;

    while (cur != NULL)
    {
        cout << "\nID File      : " << cur->idFile;
        cout << "\nNama File    : " << cur->namaFile;
        cout << "\nUkuran File  : " << cur->ukuranFile << " KB";
        cout << "\nFolder       : " << cur->namaFolder;
        cout << "\n------------------------\n";

        cur = cur->next;
    }
}

/*==================================================
    CARI FILE
==================================================*/

void cariFile()
{
    string nama;

    cout << "Nama File : ";
    cin >> nama;

    FileNode *cur = head;

    while (cur != NULL)
    {
        if (cur->namaFile == nama)
        {
            cout << "\nFile ditemukan\n";

            cout << "ID      : " << cur->idFile << endl;
            cout << "Nama    : " << cur->namaFile << endl;
            cout << "Ukuran  : " << cur->ukuranFile << endl;
            cout << "Folder  : " << cur->namaFolder << endl;

            return;
        }

        cur = cur->next;
    }

    cout << "File tidak ditemukan\n";
}

/*==================================================
    RENAME FILE
==================================================*/

void renameFile()
{
    string namaLama;
    string namaBaru;

    cout << "Nama Lama : ";
    cin >> namaLama;

    FileNode *cur = head;

    while (cur != NULL)
    {
        if (cur->namaFile == namaLama)
        {
            cout << "Nama Baru : ";
            cin >> namaBaru;

            UndoNode *undoBaru = new UndoNode();

            undoBaru->aktivitas = "RENAME";
            undoBaru->namaLama = namaLama;
            undoBaru->namaBaru = namaBaru;

            pushUndo(undoBaru);

            cur->namaFile = namaBaru;

            cout << "Rename berhasil\n";
            return;
        }

        cur = cur->next;
    }

    cout << "File tidak ditemukan\n";
}

/*==================================================
    HAPUS FILE
==================================================*/

void hapusFile()
{
    string nama;

    cout << "Nama File : ";
    cin >> nama;

    FileNode *cur = head;
    FileNode *prev = NULL;

    while (cur != NULL)
    {
        if (cur->namaFile == nama)
        {
            // Simpan data ke stack
            UndoNode *undoBaru = new UndoNode();

            undoBaru->aktivitas = "HAPUS";

            undoBaru->idFile = cur->idFile;
            undoBaru->namaFile = cur->namaFile;
            undoBaru->ukuranFile = cur->ukuranFile;
            undoBaru->namaFolder = cur->namaFolder;

            pushUndo(undoBaru);

            if (prev == NULL)
            {
                head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            delete cur;

            cout << "File berhasil dihapus\n";
            return;
        }

        prev = cur;
        cur = cur->next;
    }

    cout << "File tidak ditemukan\n";
}

/*==================================================
    UNDO
==================================================*/

void undo()
{
    if (top == NULL)
    {
        cout << "Tidak ada aktivitas untuk diundo\n";
        return;
    }

    UndoNode *ambil = top;

    /*==============================================
        UNDO TAMBAH FILE
        -> file yang ditambah akan dihapus
    ==============================================*/

    if (ambil->aktivitas == "TAMBAH")
    {
        FileNode *cur = head;
        FileNode *prev = NULL;

        while (cur != NULL)
        {
            if (cur->namaFile == ambil->namaFile)
            {
                if (prev == NULL)
                {
                    head = cur->next;
                }
                else
                {
                    prev->next = cur->next;
                }

                delete cur;
                break;
            }

            prev = cur;
            cur = cur->next;
        }

        cout << "Undo tambah file berhasil\n";
    }

    /*==============================================
        UNDO HAPUS FILE
        -> file yang dihapus dikembalikan
    ==============================================*/

    else if (ambil->aktivitas == "HAPUS")
    {
        FileNode *baru = new FileNode();

        baru->idFile = ambil->idFile;
        baru->namaFile = ambil->namaFile;
        baru->ukuranFile = ambil->ukuranFile;
        baru->namaFolder = ambil->namaFolder;

        baru->next = head;
        head = baru;

        cout << "Undo hapus file berhasil\n";
    }

    /*==============================================
        UNDO RENAME
        -> nama baru dikembalikan ke nama lama
    ==============================================*/

    else if (ambil->aktivitas == "RENAME")
    {
        FileNode *cur = head;

        while (cur != NULL)
        {
            if (cur->namaFile == ambil->namaBaru)
            {
                cur->namaFile = ambil->namaLama;

                cout << "Undo rename berhasil\n";
                break;
            }

            cur = cur->next;
        }
    }

    top = top->next;
    delete ambil;
}

/*==================================================
    TREE FOLDER
==================================================*/

Folder *tambahFolder(Folder *node, string nama)
{
    if (node == NULL)
    {
        Folder *baru = new Folder();

        baru->namaFolder = nama;

        baru->left = NULL;
        baru->right = NULL;

        return baru;
    }

    if (nama < node->namaFolder)
    {
        node->left = tambahFolder(node->left, nama);
    }
    else
    {
        node->right = tambahFolder(node->right, nama);
    }

    return node;
}

/*==================================================
    TAMPIL FOLDER (INORDER)
==================================================*/

void tampilFolder(Folder *node)
{
    if (node != NULL)
    {
        tampilFolder(node->left);

        cout << node->namaFolder << endl;

        tampilFolder(node->right);
    }
}

/*==================================================
    MAIN
==================================================*/

int main()
{
    int pilih;

    do
    {
        cout << "\n===== SISTEM REPOSITORY =====\n";

        cout << "1. Tambah Folder\n";
        cout << "2. Tampilkan Folder\n";

        cout << "3. Tambah File\n";
        cout << "4. Tampilkan File\n";
        cout << "5. Cari File\n";
        cout << "6. Rename File\n";
        cout << "7. Hapus File\n";

        cout << "8. Undo\n";

        cout << "0. Keluar\n";

        cout << "\nPilihan : ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
        {
            string namaFolder;

            cout << "Nama Folder : ";
            cin >> namaFolder;

            root = tambahFolder(root, namaFolder);

            break;
        }

        case 2:
            tampilFolder(root);
            break;

        case 3:
            tambahFile();
            break;

        case 4:
            tampilFile();
            break;

        case 5:
            cariFile();
            break;

        case 6:
            renameFile();
            break;

        case 7:
            hapusFile();
            break;

        case 8:
            undo();
            break;
        }

    } while (pilih != 0);

    return 0;
}