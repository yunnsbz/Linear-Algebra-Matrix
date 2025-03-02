#pragma once

class MatrixCalculations {

private:
	int row, col;//satýr ve sütun
	int** matrix=NULL;
	//unsigned long long int det = 0;
public:
	MatrixCalculations(int r, int c);	//malloc ile matris dizisini oluþtur
	~MatrixCalculations();	//free ile matris dizisini sil
	MatrixCalculations(const MatrixCalculations& oth);	//bulunduðu matrisi parantez içindeki matrise eþitler
	int getRow();
	int getCol();
	void setValue(int r, int c, int value);		//matrisin bir satýr ve sütundaki elemanýn deðerini deðiþtir
	void FillRandomValues();	//matrisin içini rastgele deðerler ile doldur
	void birimMatrisYap();	//matrisi birim matrise çevir 
	void display();
	void addMatris(MatrixCalculations& othmatris);	//iki matrisi topla
	void skalarMultiply(int skaler);	//matrisi bir skaler ile çarp
	void transpoz();	//matrisin transpozunu al
	void matrixMultiply(MatrixCalculations& othmatris);	//iki matrisi kuralýna göre çarp

	//matris çok büyük ise küçükten baþlayarak büyüðe det alýp yap
private:
	int sarrusDeterminant(int** m, int _row, int _col);		//max 3x3 matrislerde geçerli (çaprazlama)
	unsigned long long int calculateMinor(MatrixCalculations* m, int r, int c);	//belirtilen matrisden r ve c satýr ve sütunlarýný kullanarak minor alýr
	unsigned long long int Cofactor(MatrixCalculations* m, int r, int c);
	int calculateDeterminant(MatrixCalculations* m);	//minör ve kofaktor yardýmý ile hesaplama
	void CalculateAdjMatrix();	//kofaktörleri yerlerine koy sonra transpozunu al
	MatrixCalculations MatrixMinor(MatrixCalculations* m, int r, int c);
public:
	void MatrixReversed();		//adj ve det yardýmý ile hesapla (önce det al sonra adj matris kaybolmasýn)
	int Determinant();	//mainden ulaþýlabilen fonk. sarrus mu yoksa laplace mi kullanacaðýný belirleyip o fonklarý çaðýrýr
};