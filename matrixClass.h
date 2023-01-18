#pragma once

class matris {

private:
	int row, col;//sat�r ve s�tun
	int** matrix=NULL;
	//unsigned long long int det = 0;
public:
	matris(int r, int c);	//malloc ile matris dizisini olu�tur
	~matris();	//free ile matris dizisini sil
	matris(const matris& oth);	//bulundu�u matrisi parantez i�indeki matrise e�itler
	int getRow();
	int getCol();
	void setValue(int r, int c, int value);		//matrisin bir sat�r ve s�tundaki eleman�n de�erini de�i�tir
	void randomSet();	//matrisin i�ini rastgele de�erler ile doldur
	void birimMatrisYap();	//matrisi birim matrise �evir 
	void display();
	void addMatris(matris& othMatris);	//iki matrisi topla
	void skalerCarp(int skaler);	//matrisi bir skaler ile �arp
	void transpoz();	//matrisin transpozunu al
	void matrisCarp(matris& othMatris);	//iki matrisi kural�na g�re �arp

	//matris �ok b�y�k ise k���kten ba�layarak b�y��e det al�p yap
private:
	int sarrusDetHesapla(int** m, int _row, int _col);		//max 3x3 matrislerde ge�erli (�aprazlama)
	unsigned long long int minorHesapla(matris* m, int r, int c);	//belirtilen matrisden r ve c sat�r ve s�tunlar�n� kullanarak minor al�r
	unsigned long long int kofaktorHesapla(matris* m, int r, int c);
	int determinantHesapla(matris* m);	//min�r ve kofaktor yard�m� ile hesaplama
	void adjMatrisHesapla();	//kofakt�rleri yerlerine koy sonra transpozunu al
	matris matrisMinor(matris* m, int r, int c);
public:
	void matrisTersi();		//adj ve det yard�m� ile hesapla (�nce det al sonra adj matris kaybolmas�n)
	int determinant();	//mainden ula��labilen fonk. sarrus mu yoksa laplace mi kullanaca��n� belirleyip o fonklar� �a��r�r
};