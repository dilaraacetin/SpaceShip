/******************************************************************************************************************************************************************
**
**				                                              ÖĞRENCİ ADI: Dilara Çetin
**				                                              ÖĞRENCİ NUMARASI: G221210039
**
******************************************************************************************************************************************************************/

#include "GrafikKonsol.hpp"
#include <iostream>
#include <string>

using namespace std;

struct Konum // Konum bilgilerini içeren struct yapısı
{
    int x;
    int y;
};

class UzayMekigi
{
public:

    string karakter;
    int renk;
    Konum konum;

    UzayMekigi()
    {
        karakter = "**    ****  ";
        renk = Grafik::renkOlustur(YAZIRENK_YESIL, YAZIRENK_SIYAH);
        konum = { 0,5 };
    }
    void Hareket() // Uzay mekiğinin hareketini kontrol eden fonksiyon
    {
        if (Grafik::tusBasilimi('D')) // D tuşuna basıldığında x koordinatında değer arttırır
        {
            if (konum.x + 3 < 69)
                konum.x++;
        }

        if (Grafik::tusBasilimi('A')) // A tuşuna basıldığında x koordinatında değer azaltır
        {
            if (konum.x > 0)
                konum.x--;
        }

        if (Grafik::tusBasilimi('S')) // S tuşuna basıldığında y koordinatında değer arttırır ve mekik aşağı doğru hareket eder
        {
            if (konum.y + 2 < 18)
                konum.y++;
        }
        if (Grafik::tusBasilimi('W')) // W tuşuna basıldığında y koordinatında değer azaltır ve mekik yukarı doğru hareket eder
        {
            if (konum.y > 2)
                konum.y--;
        }
    }

    void Ciz() // Uzay mekiğini çizdiren fonksiyon
    {
        for (int satir = 0; satir < 3; satir++)
        {
            for (int sutun = 0; sutun < 4; sutun++)
            {
                int index = satir * 4 + sutun;
                Grafik::karakterYaz(konum.x + sutun, konum.y + satir, karakter[index], renk);
            }
        }
    }
};

UzayMekigi uzayMekigi;

class Mermi
{
public:
    string karakter;
    int renk;
    Konum konum;

    Mermi()
    {
        karakter = "-->";
        konum = { uzayMekigi.konum.x + 4, uzayMekigi.konum.y + 1 };
        renk = Grafik::renkOlustur(YAZIRENK_BEYAZ, ARKARENK_SIYAH);
    }

    void hareketEt() // Merminin hareketini kontrol eden fonksiyon
    {
        if (Grafik::tusBasilimi(32))
        {
            if (konum.x < Grafik::sahneGenisligi() - 3)
                konum.x++;
        }
    }

    void ciz(UzayMekigi u1) // Mermiyi uzay mekiğinin koordinatlarına göre çizdiren fonksiyon
    {
        if (Grafik::tusBasilimi(32))
        {
            if (u1.konum.x < Grafik::sahneGenisligi() - 3)
            {
                Grafik::karakterYaz(u1.konum.x + 4, u1.konum.y + 1, karakter[0], Grafik::renkOlustur(YAZIRENK_KIRMIZI, ARKARENK_SIYAH));
                Grafik::karakterYaz(u1.konum.x + 5, u1.konum.y + 1, karakter[1], Grafik::renkOlustur(YAZIRENK_KIRMIZI, ARKARENK_SIYAH));
                Grafik::karakterYaz(u1.konum.x + 6, u1.konum.y + 1, karakter[2], Grafik::renkOlustur(YAZIRENK_KIRMIZI, ARKARENK_SIYAH));
                Grafik::tusBasilimi(32);
            }
        }
    }
};

Mermi mermi;

class Dusman
{
public:
    int renk;
    Konum konum;
    string karakter;
    int rndmY;
    Dusman()
    {
        renk = Grafik::renkOlustur(YAZIRENK_KIRMIZI, ARKARENK_SIYAH);
        karakter = "****  **  ****";
        konum.x = 66;
        srand(time(NULL));
        rndmY = rand() % 12 + 3;
        konum.y = rndmY; // Düşmanın y koordinatını rastgele atama
    }
    void hareketEt() // Düşmanı sahne sınırları içinde hareket ettiren fonksiyon
    {
        if (konum.x != 1 && konum.y > 2)
        {
            konum.x -= 2;
        }
        else
        {
            konum.x = NULL;
            konum.y = NULL;
        }

    }
    void ciz() // Düşmanı ekrana çizdiren fonksiyon
    {
        for (int satir = 0; satir < 3; satir++)
        {
            for (int sutun = 0; sutun < 4; sutun++)
            {
                int index = satir * 3 + sutun;
                Grafik::karakterYaz(konum.x + sutun, konum.y + satir, karakter[index], renk);
            }
        }
    }
};

Dusman dusman1;

int skor = 0;

void SinirCiz() //Sahnenin sınırlarını çizdiren fonksiyon
{
    for (int i = 0; i < 69; i++)
    {
        Grafik::karakterYaz(i, 1, ' ', Grafik::renkOlustur(YAZIRENK_MAVI, ARKARENK_MAVI));
    }
    for (int i = 0; i < 69; i++)
    {
        Grafik::karakterYaz(i, 19, ' ', Grafik::renkOlustur(YAZIRENK_MAVI, ARKARENK_MAVI));
    }
}
void SkorKontrol(UzayMekigi u1, Dusman d1, Mermi m1) // Uzay mekiğinin, merminin ve düşmanın koordinatlarına göre skoru kontrol eden fonksiyon
{
    if (u1.konum.x + 3 == d1.konum.x || u1.konum.y + 1 == d1.konum.y) 
        skor--;              
    else if (u1.konum.x + 3 == d1.konum.x || u1.konum.y + 1 == d1.konum.y + 1) 
        skor--;
    else if (u1.konum.x + 3 == d1.konum.x || u1.konum.y + 1 == d1.konum.y + 2)
        skor--;
    else if (u1.konum.x + 2 == d1.konum.x || u1.konum.y + 1 == d1.konum.y)
        skor--;
    else if (u1.konum.x + 2 == d1.konum.x || u1.konum.y + 1 == d1.konum.y + 1)
        skor--;
    else if (u1.konum.x + 2 == d1.konum.x || u1.konum.y + 1 == d1.konum.y)
        skor--;
    else if (m1.konum.x + 2 == d1.konum.x || m1.konum.y == d1.konum.y) {
        skor++;
        d1.konum.x = NULL;
        d1.konum.y = NULL;
        m1.konum.x = NULL;
        m1.konum.y = NULL;
    }  
    else if (m1.konum.x + 2 == d1.konum.x || m1.konum.y == d1.konum.y + 1) {
        skor++;
        d1.konum.x = NULL;
        d1.konum.y = NULL;
        m1.konum.x = NULL;
        m1.konum.y = NULL;
    }
        
    else if (m1.konum.x + 2 == d1.konum.x || m1.konum.y == d1.konum.y + 2) {
        skor++;
        d1.konum.x = NULL;
        d1.konum.y = NULL;
        m1.konum.x = NULL;
        m1.konum.y = NULL;
    }
}
void Skor() // Sahnenin sağ üst köşesine skoru yazdıran fonksiyon
{
    Grafik::karakterYaz(60, 0, 'S', Grafik::renkOlustur(YAZIRENK_MOR, ARKARENK_BEYAZ));
    Grafik::karakterYaz(61, 0, 'K', Grafik::renkOlustur(YAZIRENK_MOR, ARKARENK_BEYAZ));
    Grafik::karakterYaz(62, 0, 'O', Grafik::renkOlustur(YAZIRENK_MOR, ARKARENK_BEYAZ));
    Grafik::karakterYaz(63, 0, 'R', Grafik::renkOlustur(YAZIRENK_MOR, ARKARENK_BEYAZ));
    Grafik::karakterYaz(64, 0, '=', Grafik::renkOlustur(YAZIRENK_MOR, ARKARENK_BEYAZ));
    Grafik::karakterYaz(65, 0, skor, Grafik::renkOlustur(YAZIRENK_MOR, ARKARENK_BEYAZ));
}


int main()
{
    // Sahnenin boyutlarını ayarlama
    Grafik::sahneAyarla(70, 20);

    while (true)
    {
        mermi.konum.x = uzayMekigi.konum.x + 4;
        mermi.konum.y = uzayMekigi.konum.y + 1;

        Grafik::sahneyiTemizle();
        SinirCiz();
        Skor();
        Grafik::klavyeOku();

        // Düşmanların hareketi ve çizimi
        dusman1.hareketEt();
        dusman1.ciz();


        // Uzay mekiği hareketi ve çizimi
        uzayMekigi.Hareket();
        uzayMekigi.Ciz();

        // Mermi hareketi ve çizimi (uzay mekiğine göre)
        mermi.hareketEt();
        mermi.ciz(uzayMekigi);

        // Çarpışmayı kontrol eden fonksiyon
        SkorKontrol(uzayMekigi, dusman1, mermi);

        // Sahneyi çizdirme
        Grafik::sahneyiCizdir();
        Sleep(50);
    }

}
