#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

// dugum struct'ı ağaç yapısı için kullanılmaktadır.
struct dugum
{
    char ogrno[15], ad[30], soyad[30];
    dugum *sol;
    dugum *sag;
};

// Ağaç yapısı içerisinde yer alan temel argumanlar yer almaktadır.
struct agac
{
    dugum *kok;
    void agacolustur();
    void ekle(dugum *);
    void yazdir();
    void preorder(dugum *);
    void inorder(dugum *);
    void postorder(dugum *);
} kayit;

// preorder listeleme yapmaktadır ağaç içeriğini
void agac::preorder(dugum *p)
{
    if (p)
    {
        cout << p->ogrno << "  " << p->ad << " " << p->soyad << "\n";
        preorder(p->sol);
        preorder(p->sag);
    }
}

// inorder listeleme yapmaktadır ağaç içeriğini
void agac::inorder(dugum *p)
{
    if (p)
    {
        inorder(p->sol);
        cout << p->ogrno << "  " << p->ad << " " << p->soyad << "\n";
        inorder(p->sag);
    }
}

// postorder listeleme yapmaktadır ağaç içeriğini
void agac::postorder(dugum *p)
{
    if (p)
    {
        postorder(p->sol);
        postorder(p->sag);
        cout << p->ogrno << "  " << p->ad << " " << p->soyad << "\n";
    }
}

// İstenen ağacı oluşturur.
void agac::agacolustur()
{
    kok = NULL;
    cout << "Agac olusturuldu ;) " << endl;
}

// dosyadan okunan veriler bu fonksiyon ile ağaca eklenir.
void agac::ekle(dugum *eklenecek)
{
    bool eklendi = false;
    dugum *tara;
    dugum *yeni = new dugum;
    tara = kok;
    *yeni = *eklenecek;
    yeni->sol = NULL;
    yeni->sag = NULL;

    if (kok == NULL)
    {
        kok = yeni;
        return;
    }
    while ((tara != NULL) && (!eklendi))
    {
        if ((yeni->ogrno < tara->ogrno))
        {
            if (tara->sol != NULL)
            {
                tara = tara->sol;
            }
            else
            {
                tara->sol = yeni;
                eklendi = true;
            }
        }
        else if (yeni->ogrno > tara->ogrno)
        {
            if (tara->sag != NULL)
                tara = tara->sag;
            else
            {
                tara->sag = yeni;
                eklendi = true;
            }
        }
    }
}

// dosya okuma işlemi gerçekleşir.
int dosyaOku(string dosyaAdi)
{
    char satirAl[75];
    dugum yenikayit;
    kayit.agacolustur();

    char *ptr;
    ifstream dosya(dosyaAdi);
    dosya.getline(satirAl, 75);
    for (int i = 0; i < 75; i++)
    {
        if (satirAl[i] == '\r')
            satirAl[i] = '\0';
    }
    while (dosya)
    {
        ptr = strtok(satirAl, "\t");
        int j = 0;
        while (ptr != NULL)
        {
            if (j == 0)
                strcpy(yenikayit.ogrno, ptr);
            if (j == 1)
                strcpy(yenikayit.ad, ptr);
            if (j == 2)
                strcpy(yenikayit.soyad, ptr);
            if (j == 3)
            {
                strcat(yenikayit.ad, " ");
                strcat(yenikayit.ad, yenikayit.soyad);
                strcpy(yenikayit.soyad, ptr);
            }
            ptr = strtok(NULL, " ");
            j++;
        }
        dosya.getline(satirAl, 75);
        for (int i = 0; i < 75; i++)
        {
            if (satirAl[i] == '\r')
                satirAl[i] = '\0';
        }

        kayit.ekle(&yenikayit);
    }
    dosya.close();
    return 0;
}

// kullanıcının okuması gerekn dosya seçilir.
void dosyaSec()
{
    int islemNumarası;
    cout << "\n\n1. data1.txt dosyası için\n";
    cout << "2. data2.txt dosyası için\n";
    cout << "3. data3.txt dosyası için\n";
    cout << "Bir dosya seciniz: ";
    cin >> islemNumarası;

    switch (islemNumarası)
    {
    case 1:
        dosyaOku("data1.txt");
    case 2:
        dosyaOku("data2.txt");
        break;
    case 3:
        dosyaOku("data3.txt");
        break;
    default:
        cout << "Lutfen dogru islem numarası girin.\n\n";
        break;
    }
}

// listeleme işlemi türü bu fonksiyon ile seçilir.
void listele()
{
    int islemNumarası;
    while (1)
    {
        cout << "\n\n1. Preorder Listeleme\n";
        cout << "2. Inorder Listeleme\n";
        cout << "3. Postorder Listeleme\n";
        cout << "4. Geri\n\n";
        cout << "Bir islem seciniz: ";
        cin >> islemNumarası;

        dosyaSec();

        switch (islemNumarası)
        {
        case 1:
            kayit.preorder(kayit.kok);
        case 2:
            kayit.inorder(kayit.kok);
            break;
        case 3:
            kayit.postorder(kayit.kok);
            break;
        case 4:
            return;
            break;
        default:
            cout << "Lutfen dogru islem numarası girin.\n\n";
            break;
        }
    }
}

int main()
{
    int islemNumarası;
    while (1)
    {
        cout << "\n1. Arama Yapma\n";
        cout << "2. Listeleme Yapma\n";
        cout << "3. Ogrenci Sil\n";
        cout << "4. Cikis\n\n";
        cout << "Bir islem seciniz: ";
        cin >> islemNumarası;

        switch (islemNumarası)
        {
        case 1:
            break;
        case 2:
            listele();
            break;
        case 3:
            break;
        case 4:
            return 0;
            break;
        default:
            cout << "Lutfen dogru islem numarası girin.\n\n";
            break;
        }
    }
}