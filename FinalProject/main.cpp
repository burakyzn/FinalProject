
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>

using namespace std;
const int genislik = 100;
const int yukseklik = 30;
char ekran[genislik][yukseklik];
char tuslar[256];

int uKO[10] = { 1,1,2,2,3,3,2,4,1,5 }; // ucak kordinatlari
int pKO[13] = { 90,91,92,93,94,95,96,1,2,3,4,5,6 }; // anaGemininKordinatlari

char karakter = 219; // sinirlar ve ucak karakteri
char mermiKarakter = 254; // mermi karakteri
char dusmanKarakter = 178; // dusman karakteri
char patronMermiKarakter = 219; // ana gemi mermi karakteri


int uzayliSayisi = 1; // uzayliSayisi baslangic degeri
int kapasite = 10; // mermi kapasitesi
int puan = 0; // puan
int atesSayisi = 0; // ates sayisi baslangic degeri
int kalanUzayliSayisi = 10; // 1.gorev kalan uzayli sayisi
int gorevKosul = 0; // gorevin bitmesinin kontrolu
bool birinciGorevBasarili; // 1.gorev basari kontrolu
bool ikinciGorevBasarili; // 2.gorev basari kontrolu
int anaGemiYukariAsagi = 0; // ana gemi yon
int anaGemiAtesRastgele; // ana gemi ates kontrol
bool anaGemiAtesRastgeleAK; // ana geminin rastgele atis aktif deaktif ozelligi
int anaGemiAtesle = 0; // ateslenen mermi kontrol
int ekrandakiMermiSayisi = 0; // ana geminin atesledigi mermi sayisi
int anaGemiCan = 300; // ana geminin caný
int saldiriyaKalanSure = 100; // ana geminin saldirisina kalan sure
int saldiriyaKalanSureTakip = 0; // kalan sure takip etmek icin 
int asagiSayac = 0; // ana geminin asagi gidip gitmedigini kontrol
int yukariSayac = 0; // ana geminin yukarý gidip gitmedigini kontrol 

void mermiYokEt(int, int);

// dusman sinifi
class Dusman {
public:
	int x;
	int y1;
	int y2;
	int y3;
	int dusmanYer[100][30];
	bool uzayliAktif;


	// bir y2 rastgele sayýsý belirle ve bunun 1 üstüne 1 altýnada dusman karakterinden yerleþtir. bu þekilde dusman random olusmus ve kare olmus olacak.
	void dusmanOlustur() {
		y2 = 3 + rand() % 24;
		x = 96;
		y1 = y2 - 1;
		y3 = y2 + 1;
		dusmanYer[x + 2][y1] = dusmanKarakter;
		dusmanYer[x + 2][y2] = dusmanKarakter;
		dusmanYer[x + 2][y3] = dusmanKarakter;
		dusmanYer[x + 1][y1] = dusmanKarakter;
		dusmanYer[x + 1][y2] = dusmanKarakter;
		dusmanYer[x + 1][y3] = dusmanKarakter;
		dusmanYer[x][y1] = dusmanKarakter;
		dusmanYer[x][y2] = dusmanKarakter;
		dusmanYer[x][y3] = dusmanKarakter;
	}

	// dusmanýn olustugu kordinatlarý azaltarak ekranda hareket ettir
	void dusmanKontrol() {
		dusmanYer[x - 1][y1] = dusmanYer[x][y1];
		dusmanYer[x - 1][y2] = dusmanYer[x][y2];
		dusmanYer[x - 1][y3] = dusmanYer[x][y3];
		dusmanYer[x][y1] = dusmanYer[x + 1][y1];
		dusmanYer[x][y2] = dusmanYer[x + 1][y2];
		dusmanYer[x][y3] = dusmanYer[x + 1][y3];
		dusmanYer[x + 1][y1] = dusmanYer[x + 2][y1];
		dusmanYer[x + 1][y2] = dusmanYer[x + 2][y2];
		dusmanYer[x + 1][y3] = dusmanYer[x + 2][y3];

		x = x - 1;

		// eger dusman bu kordinatlarda mermi ile karsilasirsa yapilacak islemler


		if (ekran[x - 1][y3] == karakter) {
			uzayliAktif = false;
			birinciGorevBasarili = false;
			gorevKosul = 0;
		}
		if (ekran[x - 1][y1] == karakter) {
			uzayliAktif = false;
			birinciGorevBasarili = false;
			gorevKosul = 0;
		}
		if (ekran[x - 1][y2] == karakter) {
			uzayliAktif = false;
			birinciGorevBasarili = false;
			gorevKosul = 0;
		}

		if (ekran[x - 1][y2] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y2, x - 1);
		}
		else if (ekran[x][y2] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y2, x);
		}
		else if (ekran[x + 1][y2] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y2, x + 1);
		}
		else if (ekran[x - 1][y1] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y1, x - 1);
		}
		else if (ekran[x][y1] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y1, x);
		}
		else if (ekran[x + 1][y1] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y1, x + 1);
		}
		else if (ekran[x - 1][y3] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y3, x - 1);
		}
		else if (ekran[x][y3] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y3, x);
		}
		else if (ekran[x + 1][y3] == mermiKarakter)
		{
			uzayliAktif = false;
			mermiYokEt(y3, x + 1);
		}
		else if (x == 1)
		{
			uzayliAktif = false;
			birinciGorevBasarili = false;
			gorevKosul = 0;
		}


		dusmanKonum();

	}

	// dusmanin konumunu ekrana bas
	void dusmanKonum() {
		ekran[x][y1] = dusmanYer[x][y1];
		ekran[x][y2] = dusmanYer[x][y2];
		ekran[x][y3] = dusmanYer[x][y3];
		ekran[x + 1][y1] = dusmanYer[x + 1][y1];
		ekran[x + 1][y2] = dusmanYer[x + 1][y2];
		ekran[x + 1][y3] = dusmanYer[x + 1][y3];
		ekran[x + 2][y1] = dusmanYer[x + 2][y1];
		ekran[x + 2][y2] = dusmanYer[x + 2][y2];
		ekran[x + 2][y3] = dusmanYer[x + 2][y3];
	}


};

// ayni anda ekranda en fazla 10 uzayli olabilecegi icin 10 tane uzayli nesnesi yeterli
Dusman uzayli[10];

// mermi sinifi
class Mermi {
public:
	int y;
	bool mermiAteslendimi;
	int mermiYer[100];

	Mermi() {
		mermiAteslendimi = false;
	}

	// mermilerin mermiyer dizisinde hareketini kontrol etmek icin 
	void mermiKontrol() {
		for (int i = 99; i > 2; i--)
		{
			mermiYer[i] = mermiYer[i - 1];
		}

		mermiKonumu();

	}
	// mermi atesle methodu cagirilirsa mermiyi olustur
	void mermiAtesle(int ydegeri)
	{
		y = ydegeri;
		mermiAteslendimi = true;
		mermiYer[3] = mermiKarakter;
	}
	// merminin ekrandaki yerini bastir
	void mermiKonumu()
	{
		for (int i = 4; i < 99; i++)
		{
			ekran[i][y] = mermiYer[i];
		}

	}

};

// ekrandaki her satýr icin bir mermi nesnesine ihtiyacimiz var
Mermi mermi[27];

// ana geminin mermi sinifi
class MermiPatron {
public:
	int x;
	int y;
	bool mermiPAteslendimi;

	MermiPatron() {
		mermiPAteslendimi = false;
	}

	// burada dizi kullanmadim cunku ayný satir uzerinde ana gemi cok kez mermi ateslemesi yapmiyor
	void mermiKontrol() {
		x--;

		// eger mermi diger mermi ile yada ucak karakteriyle carpisirsa olacaklar burada tanimlandi
		if (ekran[x][y] == mermiKarakter)
		{
			mermiPAteslendimi = false;
			mermiYokEt(y, x);
		}
		else if (ekran[x - 1][y] == mermiKarakter)
		{
			mermiPAteslendimi = false;
			mermiYokEt(y, x - 1);
		}

		if (ekran[x][y] == karakter)
		{
			gorevKosul = 0;
			ikinciGorevBasarili = false;
		}

		// mermi ekrandan cikarsa mermiyi kapat
		if (x < 2)
		{
			mermiPAteslendimi = false;
		}

		mermiKonumu();
	}

	// ucagin ucunun kordinati y degeri olarak aliniyor ve oradan mermi atesleniyo
	void mermiAtesle(int ydegeri)
	{
		y = ydegeri;
		x = 90;
		mermiPAteslendimi = true;
	}
	// uretilen mermiyi ekrana bastiriyor
	void mermiKonumu()
	{
		ekran[x][y] = patronMermiKarakter;
	}

};

MermiPatron mermiP[30];

void gitxy(int x, int y)
{
	COORD kordinat;
	kordinat.X = x;
	kordinat.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kordinat);
}
void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}
void ucakEkranda(int y)
{
	// ucagin gelen parametreye gore nasýl hareket edeceginin tanimlandigi kisim
	if (uKO[1] == 1)
	{
		if (y == 1)
		{
			uKO[1] += y;
			uKO[3] += y;
			uKO[5] += y;
			uKO[7] += y;
			uKO[9] += y;
		}
	}
	else if (uKO[9] == 28)
	{
		if (y == -1)
		{
			uKO[1] += y;
			uKO[3] += y;
			uKO[5] += y;
			uKO[7] += y;
			uKO[9] += y;
		}
	}
	else {
		uKO[1] += y;
		uKO[3] += y;
		uKO[5] += y;
		uKO[7] += y;
		uKO[9] += y;
	}


}
void ucakKonumu()
{
	// ucagin konumunu ekrandaki yerine yazdir
	ekran[uKO[0]][uKO[1]] = karakter;
	ekran[uKO[2]][uKO[3]] = karakter;
	ekran[uKO[4]][uKO[5]] = karakter;
	ekran[uKO[6]][uKO[7]] = karakter;
	ekran[uKO[8]][uKO[9]] = karakter;
}
void mermiYokEt(int y, int x) {
	// carpisan ve ekrandan cikan mermileri yok etme methodu
	mermi[y].mermiYer[x] = ' ';
	puan += 10;
	kalanUzayliSayisi -= 1;
}
void uzayliOlustur() {

	// belli araliklarla uzayli olusturma cagrisi yap
	if (uzayliSayisi == 10) {
		uzayli[1].dusmanOlustur();
		uzayli[1].uzayliAktif = true;
	}
	else if (uzayliSayisi == 20) {
		uzayli[2].dusmanOlustur();
		uzayli[2].uzayliAktif = true;
	}
	else if (uzayliSayisi == 30) {
		uzayli[3].dusmanOlustur();
		uzayli[3].uzayliAktif = true;
	}
	else if (uzayliSayisi == 40) {
		uzayli[4].dusmanOlustur();
		uzayli[4].uzayliAktif = true;
	}
	else if (uzayliSayisi == 50) {
		uzayli[5].dusmanOlustur();
		uzayli[5].uzayliAktif = true;
	}
	else if (uzayliSayisi == 60) {
		uzayli[6].dusmanOlustur();
		uzayli[6].uzayliAktif = true;
	}
	else if (uzayliSayisi == 70) {
		uzayli[7].dusmanOlustur();
		uzayli[7].uzayliAktif = true;
	}
	else if (uzayliSayisi == 80) {
		uzayli[8].dusmanOlustur();
		uzayli[8].uzayliAktif = true;
	}
	else if (uzayliSayisi == 90) {
		uzayli[9].dusmanOlustur();
		uzayli[9].uzayliAktif = true;
	}

	uzayliSayisi++;

	if (uzayliSayisi == 105)
		uzayliSayisi = 1;
}
void uzayliKontrol() {
	// olusan uzaylilarin davranislarini kontrol etme fonksiyonu
	for (int i = 1; i < 10; i++)
	{
		if (uzayli[i].uzayliAktif == true)
		{
			uzayli[i].dusmanKontrol();
		}
	}
}
void sarjorDoldur(int mermi) {
	// sarjor bosaldiginda araya bekleme katmak icin yazdigim fonksiyon
	if (atesSayisi == 25) {
		atesSayisi = 0;
		kapasite = 10;
	}
}
void mermiKontrol()
{
	// ucaktan cikan mermilerin gidis kontrolu
	for (int i = 3; i < 27; i++)
	{
		if (mermi[i].mermiAteslendimi == true) // mermi ateþlenmiþ
		{
			mermi[i].mermiKontrol();
		}
	}

	// 10 mermiden sonra sarjor doldurma istegi yolla
	if (atesSayisi >= 10)
	{
		atesSayisi++;
		sarjorDoldur(atesSayisi);
	}
}
void klavyeKontrol()
{
	// klavyeden okunan verilere gore davranislari belirle
	klavyeOku(tuslar);
	if (tuslar['W'] != 0)
	{
		ucakEkranda(-1);
		ucakKonumu();
	}
	else if (tuslar['S'] != 0)
	{
		ucakEkranda(1);
		ucakKonumu();
	}
	else {
		ucakKonumu();
	}

}
void mermiAtesKontrol() {

	// eger sarjor doluysa ucagin ucundan mermi atesle
	if (tuslar[' '] != 0)
	{
		if (atesSayisi < 10)
		{
			if (uKO[5] == 3)
				mermi[3].mermiAtesle(uKO[5]);
			else if (uKO[5] == 4)
				mermi[4].mermiAtesle(uKO[5]);
			else if (uKO[5] == 5)
				mermi[5].mermiAtesle(uKO[5]);
			else if (uKO[5] == 6)
				mermi[6].mermiAtesle(uKO[5]);
			else if (uKO[5] == 7)
				mermi[7].mermiAtesle(uKO[5]);
			else if (uKO[5] == 8)
				mermi[8].mermiAtesle(uKO[5]);
			else if (uKO[5] == 9)
				mermi[9].mermiAtesle(uKO[5]);
			else if (uKO[5] == 10)
				mermi[10].mermiAtesle(uKO[5]);
			else if (uKO[5] == 11)
				mermi[11].mermiAtesle(uKO[5]);
			else if (uKO[5] == 12)
				mermi[12].mermiAtesle(uKO[5]);
			else if (uKO[5] == 13)
				mermi[13].mermiAtesle(uKO[5]);
			else if (uKO[5] == 14)
				mermi[14].mermiAtesle(uKO[5]);
			else if (uKO[5] == 15)
				mermi[15].mermiAtesle(uKO[5]);
			else if (uKO[5] == 16)
				mermi[16].mermiAtesle(uKO[5]);
			else if (uKO[5] == 17)
				mermi[17].mermiAtesle(uKO[5]);
			else if (uKO[5] == 18)
				mermi[18].mermiAtesle(uKO[5]);
			else if (uKO[5] == 19)
				mermi[19].mermiAtesle(uKO[5]);
			else if (uKO[5] == 20)
				mermi[20].mermiAtesle(uKO[5]);
			else if (uKO[5] == 21)
				mermi[21].mermiAtesle(uKO[5]);
			else if (uKO[5] == 22)
				mermi[22].mermiAtesle(uKO[5]);
			else if (uKO[5] == 23)
				mermi[23].mermiAtesle(uKO[5]);
			else if (uKO[5] == 24)
				mermi[24].mermiAtesle(uKO[5]);
			else if (uKO[5] == 25)
				mermi[25].mermiAtesle(uKO[5]);
			else if (uKO[5] == 26)
				mermi[26].mermiAtesle(uKO[5]);

			atesSayisi++;
			kapasite--;
		}
	}
}
void ekraniCiz()
{
	// ekran matrisine islenen verileri ciz
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << ekran[x][y];
		}
		cout << endl;
	}
}
void ekraniTemizle()
{
	// ekran matrisini bosalt
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			ekran[x][y] = ' ';
		}
	}
}
void sinirlariCiz()
{
	// ekran sinirlarini ciz
	for (int x = 0; x < genislik; x++)
	{
		ekran[x][0] = karakter;
		ekran[x][yukseklik - 1] = karakter;
	}
	for (int y = 0; y < yukseklik; y++)
	{
		ekran[0][y] = karakter;
		ekran[genislik - 1][y] = karakter;
	}
}

void puan1Kontrol() {
	gitxy(0, 30);
	cout << char(karakter) << " Puan : " << setw(5) << left << puan << char(karakter) << " Sarjor : " << setw(4) << left << kapasite << char(karakter) <<
		" Oldurulen Dusman Sayisi : " << setw(4) << left << puan / 10 << char(karakter) << " Kalan Uzayli Sayisi : " << setw(4) << kalanUzayliSayisi << char(karakter) <<
		" Gorev 1 " << char(karakter);
	gitxy(0, 31);
	for (int x = 0; x < 100; x++)
	{
		cout << char(karakter);
	}

	if (kalanUzayliSayisi <= 0) {
		gorevKosul = 0;
		birinciGorevBasarili = true;
	}
}
void puan2Kontrol() {

	if (saldiriyaKalanSureTakip % 10 == 0)
	{
		saldiriyaKalanSure--;
	}

	saldiriyaKalanSureTakip++;

	gitxy(0, 30);
	cout << char(karakter) << " Puan : " << setw(6) << left << puan << char(karakter) << " Sarjor : " << setw(5) << left << kapasite << char(karakter) <<
		" Ana Geminin Cani :  " << setw(6) << left << anaGemiCan << char(karakter) << " Saldiriya Kalan Sure : " << setw(5) << saldiriyaKalanSure << char(karakter) <<
		" Gorev 2 " << char(karakter);
	gitxy(0, 31);
	for (int x = 0; x < 100; x++)
	{
		cout << char(karakter);
	}

	if (saldiriyaKalanSure <= 0)
	{
		gorevKosul = 0;
		ikinciGorevBasarili = false;
	}

	if (anaGemiCan <= 0)
	{
		gorevKosul = 0;
		ikinciGorevBasarili = true;
	}
}
void puanSil() {
	gitxy(0, 30);
	for (int i = 0; i < 100; i++)
	{
		cout << ' ';
	}
	gitxy(0, 31);
	for (int x = 0; x < 100; x++)
	{
		cout << ' ';
	}
}

void anaGemiEkranda() {
	// ana geminin ekrandaki baslangic yeri
	ekran[pKO[0]][pKO[8]] = karakter;
	ekran[pKO[1]][pKO[7]] = karakter;
	ekran[pKO[2]][pKO[7]] = karakter;
	ekran[pKO[3]][pKO[7]] = karakter;
	ekran[pKO[4]][pKO[7]] = karakter;
	ekran[pKO[6]][pKO[7]] = karakter;
	ekran[pKO[4]][pKO[8]] = karakter;
	ekran[pKO[5]][pKO[8]] = karakter;
	ekran[pKO[3]][pKO[9]] = karakter;
	ekran[pKO[4]][pKO[9]] = karakter;
	ekran[pKO[6]][pKO[9]] = karakter;
	ekran[pKO[3]][pKO[10]] = karakter;
	ekran[pKO[4]][pKO[10]] = karakter;
	ekran[pKO[6]][pKO[10]] = karakter;
	ekran[pKO[0]][pKO[11]] = karakter;
	ekran[pKO[4]][pKO[11]] = karakter;
	ekran[pKO[5]][pKO[11]] = karakter;
	ekran[pKO[1]][pKO[12]] = karakter;
	ekran[pKO[2]][pKO[12]] = karakter;
	ekran[pKO[3]][pKO[12]] = karakter;
	ekran[pKO[4]][pKO[12]] = karakter;
	ekran[pKO[6]][pKO[12]] = karakter;

	// ana geminin on kisimdan yiyebilecegi hasarlar
	if (ekran[pKO[1] - 1][pKO[7]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[7], pKO[1] - 1);
	}

	if (ekran[pKO[0] - 1][pKO[8]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[8], pKO[0] - 1);
	}
	if (ekran[pKO[0] - 1][pKO[11]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[11], pKO[0] - 1);
	}
	if (ekran[pKO[1] - 1][pKO[12]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[12], pKO[1] - 1);
	}
	if (ekran[pKO[3] - 1][pKO[9]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[9], pKO[3] - 1);
	}
	if (ekran[pKO[3] - 1][pKO[10]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[10], pKO[3] - 1);
	}
	if (ekran[pKO[4] - 1][pKO[8]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[8], pKO[4] - 1);
	}
	if (ekran[pKO[4] - 1][pKO[11]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[11], pKO[4] - 1);
	}
	if (ekran[pKO[6] - 1][pKO[9]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[9], pKO[6] - 1);
	}
	if (ekran[pKO[6] - 1][pKO[10]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[10], pKO[6] - 1);
	}
	if (ekran[pKO[6] - 1][pKO[12]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[12], pKO[6] - 1);
	}
	if (ekran[pKO[6] - 1][pKO[7]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[7], pKO[6] - 1);
	}
	if (ekran[pKO[5] + 1][pKO[11]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[11], pKO[5] + 1);
	}
	if (ekran[pKO[5] + 1][pKO[8]] == mermiKarakter) {
		anaGemiCan -= 10;
		mermiYokEt(pKO[8], pKO[5] + 1);
	}

	if (anaGemiYukariAsagi == 1) { // asagi giderken yiyebilecegi hasarlar

		if (ekran[pKO[1]][pKO[12] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] + 1, pKO[1]);
		}
		if (ekran[pKO[2]][pKO[12] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] + 1, pKO[2]);
		}
		if (ekran[pKO[3]][pKO[12] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] + 1, pKO[3]);
		}
		if (ekran[pKO[4]][pKO[12] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] + 1, pKO[4]);
		}
		if (ekran[pKO[6]][pKO[12] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] + 1, pKO[6]);
		}
		if (ekran[pKO[0]][pKO[8] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[8] + 1, pKO[0]);
		}
		if (ekran[pKO[1]][pKO[7] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] + 1, pKO[1]);
		}
		if (ekran[pKO[2]][pKO[7] + 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] + 1, pKO[2]);
		}



	}
	else { // yukari giderken yiyebilecegi hasarlar

		if (ekran[pKO[1]][pKO[7] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] - 1, pKO[1]);
		}
		if (ekran[pKO[2]][pKO[7] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] - 1, pKO[2]);
		}
		if (ekran[pKO[3]][pKO[7] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] - 1, pKO[3]);
		}
		if (ekran[pKO[4]][pKO[7] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] - 1, pKO[4]);
		}
		if (ekran[pKO[6]][pKO[7] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[7] - 1, pKO[6]);
		}
		if (ekran[pKO[1]][pKO[12] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] - 1, pKO[1]);
		}
		if (ekran[pKO[2]][pKO[12] - 1] == mermiKarakter) {
			anaGemiCan -= 10;
			mermiYokEt(pKO[12] - 1, pKO[2]);
		}
	}

}
void anaGemiAsagi() {
	// ana gemi asagi gidiyorsa 3 donuste bir asagý insin
	if (asagiSayac % 3 == 0)
	{
		pKO[7]++;
		pKO[8]++;
		pKO[9]++;
		pKO[10]++;
		pKO[11]++;
		pKO[12]++;
	}
	asagiSayac++;
}
void anaGemiYukari() {
	// ana gemi yukarý gidiyorsa 3 donuste bi yukarý gitsin
	if (yukariSayac % 3 == 0)
	{
		pKO[7]--;
		pKO[8]--;
		pKO[9]--;
		pKO[10]--;
		pKO[11]--;
		pKO[12]--;

	}
	yukariSayac++;
}
void anaGemiKontrol() {
	// ana geminin kordinatlarina gore onu surekli asagi yada yukari yolla
	if (pKO[7] == 1)
	{
		anaGemiYukariAsagi = 1;
	}
	else if (pKO[12] == 28)
	{
		anaGemiYukariAsagi = 2;
	}

	if (anaGemiYukariAsagi == 1)
	{
		anaGemiAsagi();
	}
	else if (anaGemiYukariAsagi == 2)
	{
		anaGemiYukari();
	}

	anaGemiEkranda();
}
void anaGemiAtesKontrol() {

	// ana gemi rastgele zamanlarda (3+(0-15)) ates etsin
	if (anaGemiAtesRastgeleAK == true) {
		anaGemiAtesRastgele = 3 + rand() % 15;
		anaGemiAtesRastgeleAK = false;
	}

	// ekrandakimermisayisiyla nesne numarasini kontrol et
	if (anaGemiAtesle == anaGemiAtesRastgele)
	{
		mermiP[ekrandakiMermiSayisi].mermiAtesle(pKO[9]);
		mermiP[ekrandakiMermiSayisi].mermiPAteslendimi = true;
		anaGemiAtesRastgeleAK = true;
		anaGemiAtesle = 0;
		ekrandakiMermiSayisi++;
	}

	anaGemiAtesle++;

	// toplam ana gemi mermi nesnesi 30 a ulaþýnca eski nesnelerin uzerine yazmak icin sifirla
	if (ekrandakiMermiSayisi >= 30)
	{
		ekrandakiMermiSayisi = 0;
	}




}
void anaGemiMermiKontrol() {

	// ateslenen mermileri kontrol et
	for (int i = 0; i < 30; i++)
	{
		if (mermiP[i].mermiPAteslendimi == true)
		{
			mermiP[i].mermiKontrol();
		}
	}
}

// gorev listesi
void gorevEmri1() {
	gitxy(40, 5);
	char gorevEmriCevap[20];
	bool gorevEmriKabul = true;
	string gorev = "Yeni Gorev Emri";
	int x = 0;
	while (gorev[x] != '\0')
	{
		cout << gorev[x];
		if (gorev[x] != ' ' && gorev[x] != '\n')
			Beep(850, 300);

		Sleep(10 + rand() % 30);
		x++;
	};
	cout << "\n\nGunaydin Yuzbasi,\n" <<
		"Gezegenimiz 3 yildir uzayli tehditi altinda. Kaynaklarimizi somurduler. Insanlarimizi oldurduler.\n"
		"Bizi silahsiz ve korumasiz biraktilar. Direnis kuvvetlerinden aldigimiz istihbarata gore bize son \n"
		"bir saldiri yapma pesindeler. Gezegeni kurtarabilmek icin uzaylilarin ana ussunu yok etmeliyiz. \n\n"
		"Yuzbasi, yuksek kurul bu gorev icin en yetenekli pilotumuz olan seni secti. \n"
		"Direnis kuvvetleri ele gecirilmeyen son uzay aracini bize teslim etmeye hazir. Maalesef cok az \n"
		"miktarda nukleer yakitimiz kaldi. Gezegenimizin kaderi senin ellerinde. Gezege sana guveniyor. \n\n"
		"(Gorevi kabul etmek icin 'E' tusuna bas)" << " Cevap : ";
	cin >> gorevEmriCevap;
	kursoruGizle();
	while (gorevEmriKabul)
	{
		gorevEmriKabul = true;
		if (gorevEmriCevap[0] == 'e' || gorevEmriCevap[0] == 'E')
		{
			cout << endl << "\t\t\t\t      Gorev Kabul Edildi." << endl;
			Sleep(2000);
			cout << "\t\t\t\t    Uzay araci hazirlaniyor." << endl;
			Sleep(2000);
			cout << "\t\t\t\t    Savas durumuna geciliyor." << endl;
			Sleep(2000);
			cout << "\t\t\t      Basarilar Yuzbasi. Guc seninle olsun.";
			Sleep(2000);
			gorevEmriKabul = false;
		}
		else {
			cout << endl << "\t\t   -Iyi dusun Yuzbasi. Gezegenin kaderi senin ellerinde. Cevap : ";
			cin >> gorevEmriCevap;
		}
	}
}
void gorevEmri2() {
	gitxy(40, 5);
	string gorev = "Yeni Gorev Emri";
	int x = 0;
	while (gorev[x] != '\0')
	{
		cout << gorev[x];
		/*if (gorev[x] != ' ' && gorev[x] != '\n')
			 Beep(850, 300);*/
		Sleep(300 + rand() % 200);
		x++;
	};
	cout << "\n\nTebrikler Binbasi,\n" <<
		"Oncu birlikleri yok ettin ama ana gemi dunyaya yok edici bir saldiri yapmaya hazirlaniyor.\n"
		"Ana gemi yok edilmeli. Istihbarata gore 100 saniye icerisinde bir saldiriya hazir olacaklar\n"
		"Bunu engellemelisin. Dunyayi kurtarmak senin ellerinde binbasi. Dunya sana guveniyor.\n";
	kursoruGizle();

	cout << endl << endl;
	Sleep(3000);
	cout << "\t\t\t\t    Uzay araci hazirlaniyor." << endl;
	Sleep(2000);
	cout << "\t\t\t\t    Savas durumuna geciliyor." << endl;
	Sleep(2000);
	cout << "\t\t\t      Basarilar Binbasi. Guc seninle olsun.";
	Sleep(2000);
}
void gorev1VerileriniSil() {
	// ekrani bir sonraki gorev icin temizle
	for (int y = 3; y < 27; y++)
	{
		for (int x = 4; x < 99; x++) {
			mermi[y].mermiYer[x] = ' ';
		}
	}

	kapasite = 10;
}

int main()
{
	system("title Dunyani Kurtar");
	srand(time(0));
	kursoruGizle();

	gorevEmri1();
	gorevKosul = 1;
	while (gorevKosul)
	{
		ekraniTemizle();
		sinirlariCiz();
		uzayliOlustur();
		klavyeKontrol();
		mermiAtesKontrol();
		mermiKontrol();
		uzayliKontrol();
		puan1Kontrol();
		gitxy(0, 0);
		ekraniCiz();
	}

	gitxy(0, 0);
	ekraniTemizle();
	ekraniCiz();
	puanSil();
	gorev1VerileriniSil();

	if (birinciGorevBasarili == true) {
		gitxy(40, 10);
		cout << "Gorev 1 Tamamlandi. ";
	}
	else if (birinciGorevBasarili == false)
	{
		gitxy(37, 10);
		cout << "Gorev 1 Basariz. Kaybettik.";
		Sleep(2000);
		return 0;
	}

	Sleep(2000);
	gitxy(0, 0);
	ekraniTemizle();
	ekraniCiz();
	gorevEmri2();

	gitxy(0, 0);
	ekraniTemizle();
	ekraniCiz();

	gorevKosul = 1;
	anaGemiAtesRastgeleAK = true;
	while (gorevKosul)
	{
		ekraniTemizle();
		sinirlariCiz();
		klavyeKontrol();
		anaGemiKontrol();
		mermiAtesKontrol();
		anaGemiAtesKontrol();
		mermiKontrol();
		anaGemiMermiKontrol();
		anaGemiEkranda();
		puan2Kontrol();
		gitxy(0, 0);
		ekraniCiz();
	}

	gitxy(0, 0);
	ekraniTemizle();
	ekraniCiz();
	puanSil();

	if (ikinciGorevBasarili == true) {
		gitxy(33, 10);
		cout << "Gorev 2 Tamamlandi. Tebrikler Albay.";
		gitxy(40, 11);
		cout << "Dunya Kurtarildi.";
		Sleep(2000);
	}
	else if (ikinciGorevBasarili == false)
	{
		gitxy(37, 10);
		cout << "Gorev 2 Basariz. Kaybettik.";
		Sleep(2000);
		return 0;
	}

	cout << endl << endl;
	system("pause");
}