#pragma once

class MatrixCalculations {

private:
	int row, col;//sat�r ve s�tun
	int** matrix=NULL;
	//unsigned long long int det = 0;
public:
	MatrixCalculations(int r, int c);	//malloc ile matris dizisini olu�tur
	~MatrixCalculations();	//free ile matris dizisini sil
	MatrixCalculations(const MatrixCalculations& oth);	//bulundu�u matrisi parantez i�indeki matrise e�itler
	int getRow();
	int getCol();
	void setValue(int r, int c, int value);		//matrisin bir sat�r ve s�tundaki eleman�n de�erini de�i�tir
	void FillRandomValues();	//matrisin i�ini rastgele de�erler ile doldur
	void birimMatrisYap();	//matrisi birim matrise �evir 
	void display();
	void addMatris(MatrixCalculations& othmatris);	//iki matrisi topla
	void skalarMultiply(int skaler);	//matrisi bir skaler ile �arp
	void transpoz();	//matrisin transpozunu al
	void matrixMultiply(MatrixCalculations& othmatris);	//iki matrisi kural�na g�re �arp

	//matris �ok b�y�k ise k���kten ba�layarak b�y��e det al�p yap
private:
	int sarrusDeterminant(int** m, int _row, int _col);		//max 3x3 matrislerde ge�erli (�aprazlama)
	unsigned long long int calculateMinor(MatrixCalculations* m, int r, int c);	//belirtilen matrisden r ve c sat�r ve s�tunlar�n� kullanarak minor al�r
	unsigned long long int Cofactor(MatrixCalculations* m, int r, int c);
	int calculateDeterminant(MatrixCalculations* m);	//min�r ve kofaktor yard�m� ile hesaplama
	void CalculateAdjMatrix();	//kofakt�rleri yerlerine koy sonra transpozunu al
	MatrixCalculations MatrixMinor(MatrixCalculations* m, int r, int c);
public:
	void MatrixReversed();		//adj ve det yard�m� ile hesapla (�nce det al sonra adj matris kaybolmas�n)
	int Determinant();	//mainden ula��labilen fonk. sarrus mu yoksa laplace mi kullanaca��n� belirleyip o fonklar� �a��r�r
};