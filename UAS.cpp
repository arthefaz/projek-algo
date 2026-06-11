#include <iostream>
#include <string>

using namespace std;

struct FileNode
{
    int idFile;
    string namaFile;
    int ukuranFile;
    FileNode *next;
};

FileNode *head = NULL;

struct UndoNode
{
    string aktivitas;
    UndoNode *next;
};

UndoNode *top = NULL;

struct Folder
{
    string namaFolder;

    Folder *left;
    Folder *right;
};

Folder *root = NULL;

void pushUndo(string aktivitas)
{
    UndoNode *baru = new UndoNode();

    baru->aktivitas = aktivitas;
    baru->next = top;

    top = baru;
}

void undo()
{
    if (top == NULL)
    {
        cout << "Tidak ada aktivitas\n";
        return;
    }

    UndoNode *hapus = top;

    cout << "Undo : " << top->aktivitas << endl;

    top = top->next;

    delete hapus;
}

void tambahFile()
{
    FileNode *baru = new FileNode();

    cout << "ID File : ";
    cin >> baru->idFile;

    cout << "Nama File : ";
    cin >> baru->namaFile;

    cout << "Ukuran File (KB) : ";
    cin >> baru->ukuranFile;

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

    pushUndo("Tambah File");
}

void tampilFile()
{
    FileNode *cur = head;

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
    string nama;

    cout << "Masukkan nama file : ";
    cin >> nama;

    FileNode *cur = head;

    while (cur != NULL)
    {
        if (cur->namaFile == nama)
        {
            cout << "File ditemukan" << endl;

            cout << cur->idFile << endl;
            cout << cur->namaFile << endl;
            cout << cur->ukuranFile << endl;

            return;
        }

        cur = cur->next;
    }

    cout << "File tidak ditemukan" << endl;
}

void renameFile()
{
    string lama;
    string baru;

    cout << "Nama lama : ";
    cin >> lama;

    FileNode *cur = head;

    while (cur != NULL)
    {
        if (cur->namaFile == lama)
        {
            cout << "Nama baru : ";
            cin >> baru;

            cur->namaFile = baru;

            pushUndo("Rename File");

            cout << "Berhasil" << endl;

            return;
        }

        cur = cur->next;
    }

    cout << "File tidak ditemukan" << endl;
}

void hapusFile()
{
    string nama;

    cout << "Nama file : ";
    cin >> nama;

    FileNode *cur = head;
    FileNode *prev = NULL;

    while (cur != NULL)
    {
        if (cur->namaFile == nama)
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

            pushUndo("Hapus File");

            cout << "File berhasil dihapus" << endl;

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

void tampilFolder(Folder *node)
{
    if (node != NULL)
    {
        tampilFolder(node->left);

        cout << node->namaFolder << endl;

        tampilFolder(node->right);
    }
}

int main()
{
    int pilih;

    do
    {
        cout << "\n===== REPOSITORY =====" << endl;

        cout << "1. Tambah File" << endl;
        cout << "2. Hapus File" << endl;
        cout << "3. Rename File" << endl;
        cout << "4. Undo" << endl;
        cout << "5. Tampilkan Folder" << endl;
        cout << "6. Cari File" << endl;
        cout << "7. Tambah Folder" << endl;
        cout << "0. Keluar" << endl;

        cout << "Masukkan Pilihan (ANGKA) : ";
        cin >> pilih;

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
            tampilFolder(root);
            break;

        case 6:
            cariFile();
            break;

        case 7:
        {
            string nama;

            cout << "Nama Folder : ";
            cin >> nama;

            root = tambahFolder(root, nama);

            break;
        }
        }

    } while (pilih != 0);

    return 0;
}