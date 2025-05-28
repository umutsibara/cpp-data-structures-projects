#include <iostream>
using namespace std;

/*Veri yapısı kullanmamızın avantajları listeye istediğimiz kadar ürün ekleyebilmemiz. 
Elbette dizi genişletirerek de bu işlemler yapılabilirdi.
Dezavantajları ise düğüm kontrolünün zor olması ve belleği dinamik olarak kontrol etmemiz.
    Ayrıca kodlarda da görüldüğü gibi barkod nosuna göre işlem yapması oldukça maliyetli. 
    Aynı fonksiyonu daha az kod ile dizi veri yapısında uygulanabilirdi.*/

struct Liste {
	string urun;
	Liste* sonraki;
	int barkodNo;

	Liste(string urun, int barkodNo) {
		this->barkodNo = barkodNo;
		this->urun = urun;
		this->sonraki = nullptr;
	}
};//Kasa sınıfına ait
struct Sepet { //Stack
    string urun;
    Sepet* sonraki;

    Sepet(string urun) {
        this->urun = urun;
        this->sonraki = nullptr;
    }
};
struct Sira { //Queue
    Sepet* musteri;
    int siraNo;
    Sira* sonraki;

    Sira(int siraNo) {
        this->siraNo = siraNo;
        this->sonraki = nullptr;
        this->musteri = nullptr;
    }
};


class Kasa {
public:
	Kasa() {
		yiyecekBaslangic = nullptr;
		temizlikBaslangic = nullptr;
		evBaslangic = nullptr;
	} 
    void TEST() {
        urunEklemeIslemi("Ekmek", yiyecekBaslangic);
        urunEklemeIslemi("Su", yiyecekBaslangic);
        urunEklemeIslemi("Pirinc", yiyecekBaslangic);
        urunEklemeIslemi("Domates", yiyecekBaslangic);

        urunEklemeIslemi("Sabun", temizlikBaslangic);
        urunEklemeIslemi("Sampiyon Suyu", temizlikBaslangic);
        urunEklemeIslemi("Camasir Suyu", temizlikBaslangic);

        urunEklemeIslemi("Pil", evBaslangic);
        urunEklemeIslemi("Ampul", evBaslangic);
        urunEklemeIslemi("USB", evBaslangic);

    }
    void bilgiEkrani() {
        bool devamEt = true;
        int neYapmakIstiyor = 0;;
        while (devamEt)
        {
            cout << "Ne Yapmak Istiyorsunuz?" <<
                "\n1 - Urun Ekle\n2 - Urun Sil\n3 - Urun Guncelle\n4 - Urunleri Listele\n5 - Cikis Yap" << endl;
            cin >> neYapmakIstiyor;
            cout << endl;
            switch (neYapmakIstiyor){
            case 1:
                urunEklemeEkrani();
                break;
            case 2:
                urunSilmeEkrani();
                break;
            case 3:
                urunGuncellemeEkrani();
                break;
            case 4:
                yazdir();
                break;
            case 5:
                devamEt = false;
                break;
            default:
                cout << "Hatali Islem!\nLutfen Tekrar Deneyiniz..." << endl;
                bilgiEkrani();
                break;
            }
        }
    }
    void urunGuncellemeEkrani() {

        int barkodNo;
        string yeniUrun;
        cout << "Guncellemek Istediginiz Urunun Barkod Numarasini Giriniz..." << endl;
        cin >> barkodNo;
        cout << "Yeni Urunu Yaziniz..." << endl;
        cin >> yeniUrun;
        urunGuncellemeIslemi(barkodNo, yeniUrun);
    }
    void urunGuncellemeIslemi(int barkodNo, string yeniUrun) {
        Liste* guncellenecekUrun = yiyecekBaslangic;

        if (barkodNo >= yiyecekBaslangic->barkodNo && barkodNo < temizlikBaslangic->barkodNo)
        {
            guncellenecekUrun = yiyecekBaslangic;
        }
        else if (barkodNo >= temizlikBaslangic->barkodNo && barkodNo < evBaslangic->barkodNo)
        {
            guncellenecekUrun = temizlikBaslangic;
        }
        else if (barkodNo >= evBaslangic->barkodNo && barkodNo < listeUzunluk)
        {
            guncellenecekUrun = evBaslangic;
        }
        else
        {
            cout << "Gecersiz Barkod Girdiniz.\nLutfen tekrar Deneyiniz..." << endl;
            urunSilmeEkrani();
        }

        while (guncellenecekUrun->barkodNo != barkodNo)
        {
            guncellenecekUrun = guncellenecekUrun->sonraki;
        }
        guncellenecekUrun->urun = yeniUrun;

    }
    void urunSilmeEkrani() {
       
        int barkodNo;
        cout << "Silmek Istediginiz Urunun Barkod Numarasini Giriniz..." << endl;
        cin >> barkodNo;
        urunSilmeIslemi(barkodNo);
        
    }
    void urunSilmeIslemi(int barkodNo) {
        Liste* silinecekUrunOncesi = yiyecekBaslangic;
        Liste* gecici = nullptr;

        if (barkodNo >= yiyecekBaslangic->barkodNo && barkodNo < temizlikBaslangic->barkodNo)
        {
            silinecekUrunOncesi = yiyecekBaslangic;
        }
        else if (barkodNo >= temizlikBaslangic->barkodNo && barkodNo < evBaslangic->barkodNo)
        {
            silinecekUrunOncesi = temizlikBaslangic;
        }
        else if (barkodNo >= evBaslangic->barkodNo && barkodNo < listeUzunluk)
        {
            silinecekUrunOncesi = evBaslangic;
        }
        else
        {
            cout << "Gecersiz Barkod Girdiniz.\nLutfen tekrar Deneyiniz..." << endl;
            urunSilmeEkrani();
        }
        while (silinecekUrunOncesi->sonraki->barkodNo != barkodNo)
        {
            silinecekUrunOncesi = silinecekUrunOncesi->sonraki;
        }
 
        gecici = silinecekUrunOncesi->sonraki->sonraki;
        delete silinecekUrunOncesi->sonraki;
        silinecekUrunOncesi->sonraki = gecici;
        cout << barkodNo << " nolu urun basarili bir sekilde silinmistir." << endl;
    }
    void urunEklemeEkrani() {
    
        int secilenKategori;
        string eklenecekUrun;
        cout << "Lutfen Bir Kategori Secin\n" <<
            "1 - Yiyecekler\n2 - Temizlik Urunleri\n3 - Ev Urunleri" << endl;
        cin >> secilenKategori;

        cout << "Lutfen Eklemek Istediginiz Urunu Yaziniz" << endl;
        cin >> eklenecekUrun;
        switch (secilenKategori){
        case 1: //Yiyecekler İçin
            urunEklemeIslemi(eklenecekUrun, yiyecekBaslangic);
            break;
        case 2: //Temizlik İçin
            urunEklemeIslemi(eklenecekUrun, temizlikBaslangic);
            break;
        case 3: //Ev İçin
            urunEklemeIslemi(eklenecekUrun, evBaslangic);
            break;
        default:
            cout << "Hatali Islem Lutfen Tekrar Deneyin." << endl;
            urunEklemeEkrani();
            break;
        }
    }
	void urunEklemeIslemi(string urun, Liste*& nereyeEklenecek) {

    Liste* eklenecekUrun = new Liste(urun, 0);
    Liste* geciciEleman = nereyeEklenecek;

    if (nereyeEklenecek == nullptr) { //Eklenecek Yer Boşsa 
        nereyeEklenecek = eklenecekUrun;
    }   
    else { //Sona Ekleme İşlemi
        while (geciciEleman->sonraki != nullptr) {
            geciciEleman = geciciEleman->sonraki;
        }
        geciciEleman->sonraki = eklenecekUrun;
    }
}  
    void yazdir(Liste* kategori) {
        Liste* gecici = kategori;
        while (gecici != nullptr) {
            gecici->barkodNo = listeUzunluk++;
            cout << gecici->barkodNo <<"\t" << gecici->urun << endl;
            gecici = gecici->sonraki;
        }
    }
    void yazdir() {
        listeUzunluk = 1;
        cout << "\n***********************\n" << endl;
        cout << "Barkod\tYiyecekler:" << endl;
        yazdir(yiyecekBaslangic);
        cout << "\n***********************\n" << endl;

        cout << "Barkod\tTemizlik Urunleri:" << endl;
        yazdir(temizlikBaslangic);
        cout << "\n***********************\n" << endl;

        cout << "Barkod\tEv Urunleri:" << endl;
        yazdir(evBaslangic);
        cout << "\n***********************\n" << endl;
    }
    
private:
	Liste* yiyecekBaslangic, * temizlikBaslangic, * evBaslangic;
    int listeUzunluk = 1;
};

class Musteri {

public:
    Musteri() {
        sonUrun = nullptr;
        siraninBasi = nullptr;
        siraninSonu = nullptr;
    }
    //Bu şekilde yaptığımızda, listedeki ürünler sondan başa doğru tutuluyor.
    void sepetUrunEkle(string urun) {

        Sepet* eklenecekUrun = new Sepet(urun);

        if (sonUrun != nullptr)
            eklenecekUrun->sonraki = sonUrun;

        sonUrun = eklenecekUrun;
    }
    void sepetUrunSil() {
        Sepet* silinecekUrun = sonUrun;
        if (sonUrun != nullptr)
        {
            sonUrun = sonUrun->sonraki;
            delete silinecekUrun;
        }
        else
        {
            cout << "Sepetiniz Bosken Silme Islemi Yapamazsiniz!" << endl;
        }
    }
    void urunleriListele() {    
        Sepet* gecici = sonUrun;
        cout << "Sepetinizdeki Urunler:" << endl;
        while (gecici != nullptr)
        {
            cout << gecici->urun << endl;
            gecici = gecici->sonraki;
        }
    }
    void sirayaEkle() {
        Sira* sira = new Sira(0);
        if (siraninBasi == nullptr)
        {
            sira->siraNo = 1;
            siraninBasi = sira;
            siraninSonu = sira;
        }
        else
        {
            sira->siraNo = siraninSonu->siraNo + 1;
            siraninSonu->sonraki = sira;
            siraninSonu = sira;
        }

        cout << sira->siraNo << ". Musterimiz Hosgeldiniz... " << endl;
    }
    void siradanIslemYap() {
        if (siraninBasi == nullptr )
        {
            cout << "Sira Zaten Bos" << endl;
        }
        else 
        {
            Sira* gecici = siraninBasi;
            cout << gecici->siraNo << ". musterimizin islemi basarili." << endl;
            siraninBasi = gecici->sonraki;
            delete gecici;
            if (siraninBasi == nullptr)
            {
                cout << "Kasamiz Bosalmistir." << endl;
                siraninBasi = siraninSonu = nullptr;
                delete siraninSonu;
            }
        }
    }
      
private:
    Sepet *sonUrun;
    Sira* siraninBasi, *siraninSonu;
};
int main()
{
    /*Kasa kasa;
    kasa.TEST();
    kasa.yazdir();
    kasa.bilgiEkrani();*/


    /*Musteri musteri;
    musteri.sirayaEkle();
    musteri.sirayaEkle();
    musteri.siradanIslemYap();
    musteri.sirayaEkle();
    musteri.sirayaEkle();
    musteri.siradanIslemYap();
    musteri.siradanIslemYap();
    musteri.siradanIslemYap();*/


    /*Musteri musteri;
    musteri.sepetUrunEkle("Ekmek");
    musteri.sepetUrunEkle("Su");
    musteri.sepetUrunEkle("Yumurta");
    musteri.urunleriListele();
    musteri.sepetUrunSil();
    musteri.urunleriListele();*/

}