#pragma once

class matris {

private:
	int row, col;//satýr ve sütun
	int** matrix=NULL;
	//unsigned long long int det = 0;
public:
	matris(int r, int c);	//malloc ile matris dizisini oluþtur
	~matris();	//free ile matris dizisini sil
	matris(const matris& oth);	//bulunduðu matrisi parantez içindeki matrise eþitler
	int getRow();
	int getCol();
	void setValue(int r, int c, int value);		//matrisin bir satýr ve sütundaki elemanýn deðerini deðiþtir
	void randomSet();	//matrisin içini rastgele deðerler ile doldur
	void birimMatrisYap();	//matrisi birim matrise çevir 
	void display();
	void addMatris(matris& othMatris);	//iki matrisi topla
	void skalerCarp(int skaler);	//matrisi bir skaler ile çarp
	void transpoz();	//matrisin transpozunu al
	void matrisCarp(matris& othMatris);	//iki matrisi kuralýna göre çarp

	//matris çok büyük ise küçükten baþlayarak büyüðe det alýp yap
private:
	int sarrusDetHesapla(int** m, int _row, int _col);		//max 3x3 matrislerde geçerli (çaprazlama)
	unsigned long long int minorHesapla(matris* m, int r, int c);	//belirtilen matrisden r ve c satýr ve sütunlarýný kullanarak minor alýr
	unsigned long long int kofaktorHesapla(matris* m, int r, int c);
	int determinantHesapla(matris* m);	//minör ve kofaktor yardýmý ile hesaplama
	void adjMatrisHesapla();	//kofaktörleri yerlerine koy sonra transpozunu al
	matris matrisMinor(matris* m, int r, int c);
public:
	void matrisTersi();		//adj ve det yardýmý ile hesapla (önce det al sonra adj matris kaybolmasýn)
	int determinant();	//mainden ulaþýlabilen fonk. sarrus mu yoksa laplace mi kullanacaðýný belirleyip o fonklarý çaðýrýr
};