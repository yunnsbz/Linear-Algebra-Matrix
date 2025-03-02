#pragma once

class matrixClass {

private:
	int row, col;//satýr ve sütun
	int** matrix=NULL;
	//unsigned long long int det = 0;
public:
	matrixClass(int r, int c);	//malloc ile matris dizisini oluþtur
	~matrixClass();	//free ile matris dizisini sil
	matrixClass(const matrixClass& oth);	//bulunduðu matrisi parantez içindeki matrise eþitler
	int getRow();
	int getCol();
	void setValue(int r, int c, int value);		//matrisin bir satýr ve sütundaki elemanýn deðerini deðiþtir
	void randomSet();	//matrisin içini rastgele deðerler ile doldur
	void birimMatrisYap();	//matrisi birim matrise çevir 
	void display();
	void addMatris(matrixClass& othmatris);	//iki matrisi topla
	void skalarMultiply(int skaler);	//matrisi bir skaler ile çarp
	void transpoz();	//matrisin transpozunu al
	void matrixMultiply(matrixClass& othmatris);	//iki matrisi kuralýna göre çarp

	//matris çok büyük ise küçükten baþlayarak büyüðe det alýp yap
private:
	int sarrusDeterminant(int** m, int _row, int _col);		//max 3x3 matrislerde geçerli (çaprazlama)
	unsigned long long int calculateMinor(matrixClass* m, int r, int c);	//belirtilen matrisden r ve c satýr ve sütunlarýný kullanarak minor alýr
	unsigned long long int Cofactor(matrixClass* m, int r, int c);
	int calculateDeterminant(matrixClass* m);	//minör ve kofaktor yardýmý ile hesaplama
	void adjMatrisHesapla();	//kofaktörleri yerlerine koy sonra transpozunu al
	matrixClass matrixMinor(matrixClass* m, int r, int c);
public:
	void matrisTersi();		//adj ve det yardýmý ile hesapla (önce det al sonra adj matris kaybolmasýn)
	int determinant();	//mainden ulaþýlabilen fonk. sarrus mu yoksa laplace mi kullanacaðýný belirleyip o fonklarý çaðýrýr
};