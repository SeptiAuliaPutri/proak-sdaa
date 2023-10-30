#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool loginAdmin()
{
    int a;
    string users[] = {"admin"};
    string passwords[] = {"admin"};
    string inputuser, inputpass;

    cout << "-------------------------------------------------------------\n";
    cout << "Selamat datang di Sistem Pendataan Data Nasabah di Pegadaian\n";
    
    cout << "-------------------------------------------------------------\n\n";

    for (a = 1; a <= 3; a++)
    {
        cout << "Silahkan masukkan username dan password Anda untuk masuk ke dalam sistem!\n";
        cout << "Username: ";
        cin >> inputuser;
        cout << "Password: ";
        cin >> inputpass;
        cout << "\n";

        for (int i = 0; i < 1; i++)
        {
            if (inputuser == users[i] && inputpass == passwords[i])
            {
                cout << "Selamat datang, admin " << inputuser << "!\n\n";
                cout << "Silahkan tekan tombol enter untuk melanjutkan ke halaman menu!\n";
                cin.ignore();
                cin.get();
                return true;
            }
        }

        cout << "Username atau password salah. Silakan coba lagi.\n\n";
    }

    cout << "Anda telah mencapai batas maksimal 3x login! Silahkan masukkan username dan password anda yang benar!\n\n";
    return false;
}

bool loginUser()
{
    string username, password;

    cout << "Login Akun\n";

    cout << "Silakan masukkan username dan password Anda untuk login!\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << "\n";

    ifstream file("regis.csv");
    string line;

    while (getline(file, line))
    {
        size_t commaPos = line.find(",");
        if (commaPos == string::npos)
        {
            continue;
        }

        string storedUsername = line.substr(0, commaPos);
        string storedPassword = line.substr(commaPos + 1);

        if (username == storedUsername && password == storedPassword)
        {
            cout << "Selamat datang, user " << username << "!\n\n";
            cout << "Silahkan tekan tombol enter untuk melanjutkan ke halaman menu!\n";
            cin.ignore();
            cin.get();
            return true;
        }
    }

    cout << "Login Gagal. Username atau password salah.\n\n";
    return false;
}

void registerUser()
{
    string username, password;

    cout << "Registrasi Akun\n";

    cout << "Silakan masukkan username dan password baru untuk registrasi!\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << "\n";

    ofstream file("regis.csv", ios::app);
    file << username << ',' << password << '\n';

    cout << "Registrasi berhasil. Anda bisa login dengan username dan password Anda.\n\n";
}

struct paket
{
    string nama_pengirim;
    string nama_penerima;
    string alamat_tujuan;
    string alamat_asal;
    string jenis;
    paket *next = NULL;
    paket *prev = NULL;
};

int lenght(paket *head) // ubah
{
    int jumlah = 0;
    while (head != NULL)
    {
        jumlah++;
        head = head->next;
    }
    return jumlah;
}

int id = 0;

paket *newpaket()
{
    paket *paketbaru = new paket;
    cout << "\t" << endl;
    cout << "Masukkan Nama Pengirim : "; cin >> ws; getline(cin, paketbaru->nama_pengirim);
    cout << "Masukkan Nama Penerima : "; cin >> ws; getline(cin, paketbaru->nama_penerima);
    cout << "Masukkan Alamat Tujuan Paket : "; cin >> ws; getline(cin, paketbaru->alamat_tujuan);
    cout << "Masukkan Alamat Asal : "; cin >> ws; getline(cin, paketbaru->alamat_asal);
    cout << "Jenis Paket : "; cin >> ws; getline(cin, paketbaru->jenis);
    return paketbaru;
}

bool isEmpty(paket *head, paket *tail)
{
    if (head == NULL && tail == NULL)
    {
        return true;
    }
    return false;
}

void displayHead(paket *head, paket *tail)
{
    if (isEmpty(head, tail))
    {
        cout << "Data masih kosong" << endl;
    }
    else
    {
        int i = 1;
        paket *temp = head;
        while (temp != NULL)
        {
            cout << "***********************************************************" << endl;
            cout << "ID Paket : " << i << endl;
            cout << "Nama Pengirim : " << temp->nama_pengirim << endl;
            cout << "Nama Penerima : " << temp->nama_penerima << endl;
            cout << "Alamat Pengiriman : " << temp->alamat_tujuan << endl;
            cout << "Jenis : " << temp->jenis<< " rupiah" << endl;
            cout << "***********************************************************" << endl;
            temp = temp->next;
            i++;
        }
    }
}

void displayTail(paket *head, paket *tail)
{
    if (isEmpty(head, tail))
    {
        cout << "Data masih kosong" << endl;
    }
    else
    {
        int i = 1;
        paket *temp = tail;
        while (temp != NULL)
        {
            cout << "***********************************************************" << endl;
            cout << "ID Paket : " << i << endl;
            cout << "Nama Pengirim : " << temp->nama_pengirim << endl;
            cout << "Nama Penerima : " << temp->nama_penerima << endl;
            cout << "Alamat Pengiriman : " << temp->alamat_tujuan << endl;
            cout << "Jenis : " << temp->jenis<< " rupiah" << endl;
            cout << "***********************************************************" << endl;
            temp = temp->prev;
            i++;
        }
    }
}

void addFirst(paket **head, paket **tail)
{
    paket *paketbaru = newpaket();
    if (isEmpty(*head, *tail))
    {
        *head = paketbaru;
        *tail = paketbaru;
    }
    else
    {
        paketbaru->next = *head;
        (*head)->prev = paketbaru;
        *head = paketbaru;
    }
}

void addLast(paket **head, paket **tail)
{
    if (isEmpty(*head, *tail))
    {
        cout << "\nData Kosong" << endl;
        addFirst(head, tail);
    }
    else
    {
        paket *paketbaru = newpaket();
        paketbaru->prev = *tail;
        (*tail)->next = paketbaru;
        *tail = paketbaru;
    }
}

int main()
{
    paket *head = NULL;
    paket *tail = NULL;

    bool isLoggedIn = false; // Untuk melacak status login

    while (true)
    {
        cout << " --- Menu --- " << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Exit" << endl;
        cout << "Masukkan Pilihan Menu: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            isLoggedIn = loginAdmin();
        }
        else if (choice == 2)
        {
            cout << "1. Login" << endl;
            cout << "2. Registrasi" << endl;
            cout << "Masukkan Pilihan : ";
            cin >> choice;

            if (choice == 1)
            {
                isLoggedIn = loginUser();
                while (true){
                    cout << "1. Tambah Paket" << endl;
                    cout << "2. Tampilkan Semua Paket (Head)" << endl;
                    cout << "3. Tampilkan Semua Paket (Tail)" << endl;
                    cout << "Masukkan Pilihan : ";
                    cin >> choice;

                    if (choice == 1)
                    {
                        addLast(&head, &tail);
                        cout << "Paket berhasil ditambahkan." << endl;
                    }
                    else if (choice == 2)
                    {
                        displayHead(head, tail);
                    }
                    else if (choice == 3)
                    {
                        displayTail(head, tail);
                    }
                }
            }
            else if (choice == 2)
            {
                registerUser();
            }
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            cout << "Menu tidak ditemukan." << endl;
        }
    }

    return 0;
}
