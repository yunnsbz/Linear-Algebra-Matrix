#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "matrixClass.h"

using namespace std;

int factor(int a) {
	int b = 1;
	while (a > 0) {
		b *= a;
		a--;
	}
	return b;
}


matris::matris(int r, int c) {	//matrix[satýr][sütun]
	row = r;
	col = c;
	
	//yer ayýrma
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}
}

matris::~matris() {
	for (int i = 0; i < row; i++)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
}

matris::matris(const matris& oth) {
	row = oth.row;
	col = oth.col;

	//yer ayýrma
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}

	//eþitleme
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] = oth.matrix[i][j];
		}
	}
}

int matris::getRow() { return row; }

int matris::getCol() { return col; }

void matris::setValue(int r, int c, int value) {
	matrix[row][col] = value;
}

void matris::randomSet() {
	srand(time(0));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
}

void matris::birimMatrisYap() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(i==j)matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
}

void matris::display() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//cout << matrix[i][j] << "  ";		//format yok
			printf("%-3d", matrix[i][j]);
		}
		cout<<"\n";
	}
	cout << endl;
}

void matris::addMatris(matris& othMatris) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] += othMatris.matrix[i][j];
		}
	}
}

void matris::skalerCarp(int skaler) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] *= skaler;
		}
	}
}

void matris::transpoz() {

	//matrix 'i baþka bir matrise geçici olarak kopyalýyorum
	int** tempMatrix=NULL;
	tempMatrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		tempMatrix[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = matrix[i][j];
		}
	}

	//transpoz iþlemi
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i != j) {
				matrix[i][j] = tempMatrix[j][i];
			}
		}
	}

	//tempMatrix'i bellekten silme
	for (int i = 0; i < row; i++)
	{
		delete[]tempMatrix[i];
	}
	delete[]tempMatrix;
}

void matris::matrisCarp(matris& othMatris) {

	//matrix 'i baþka bir matrise geçici olarak kopyalýyorum
	int** tempMatrix = NULL;
	tempMatrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		tempMatrix[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = matrix[i][j];
		}
	}

	//çarpma iþlemi
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//komple hatalý
			/*
			tempMatrix[i][0] += matrix[i][j] * othMatris.matrix[j][i];
			tempMatrix[i][1] += matrix[i][j] * othMatris.matrix[j][i ];
			tempMatrix[i][2] += matrix[i][j] * othMatris.matrix[j][i ];
			*/
			cout << "hatalý fonk çalýþtý" << endl;
		}
	}

	//tempMatrix'i bellekten silme
	for (int i = 0; i < row; i++)
	{
		delete[]tempMatrix[i];
	}
	delete[]tempMatrix;
}

unsigned long long int matris::kofaktorHesapla(matris* m, int r, int c) {
	return minorHesapla(m, r, c) * pow((-1), r+1 + c);
}

int matris::determinant() {
	if (row != col) return -1;
	if (row <= 3) return sarrusDetHesapla(matrix, row, col);


	else {
		matris tempMat(row, row);
		int a = 0, b = 0;	//geçici matrisin boyutlarý
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				tempMat.matrix[a][b++] = matrix[i][j];
			}
		a++;
		if (b >= row)b = 0;
		}
		return determinantHesapla(&tempMat);
	}
}


int matris::sarrusDetHesapla(int** m, int _row, int _col) {

	if (_row > 3 || _col > 3) {
		cout << "sarrus det. error";
		return -1;
	}

	int det = 0, d1 = 0, carpimlar = 1, i = -1, k = 0;
	int yon = 0;	//çarpýmlarýn yönünü deðiþtirecek

	// g = 1 det'in ilk parçasý için, aþaðýdaki döngü ikinci defa çalýþtýðýnda g -1 olur det'in ikinci parçasý için
	int g;	//k deðerini tek tek arttýrmak yada azaltmak (deðeri -1'e eþitlenirse) için aþaðýdaki for döngüsünde kullanýlýr
	for (g = 1; g > -2; g -= 2 )	//determinant iki ifadenin farký ile yapýlýr
	{
		for (int j = 0; j < _row; j++)
		{
			i++;
			k = yon;	//k deðeri sýfýr yada iki

			//i deðeri satýrlarý aþaðý ve yetmiyorsa tekrar yukarý çýkarýr k ise sütunlarý temsil eder baþtan sona yada sondan baþa
			for ( ; k < _row && k >= 0; i++, k+=g)	
			{

				//i deðerini tekrar baþa alma
				if(i>=_row){
					i -= _row;
				}
				
				carpimlar *= m[i][k];
			}
			d1 += carpimlar;
			carpimlar = 1;
		}

		det += d1 * g;	//g, ikinci kýsýmda -1 deðerini alýp determinant için aradaki fark iþlemini yapmýþ olur
		d1 = 0;	//det farkýnýn ikinci kýsmý için sýfýrlandý
		//üst scope'da determinantýn ilk parçasý yapýlyor 'yon' ve 'g' deðiþtiðinde ikinci parçasý yapýlýr (-'den sonra)		
		yon = _row-1;
	}
	return det;
}

unsigned long long int matris::minorHesapla(matris* m, int r, int c) {
	
	//sýra ile recursive yapýp üst sýra minörlerini bul minör yardýmý ile det hesapla
	matris tempMat(m->row-1,m->row-1);
	tempMat=matrisMinor(m, r, c);
	if (tempMat.row == 3)	return sarrusDetHesapla(tempMat.matrix,3,3);	//matris 3x3 kaldýysa direk sarrus ile det hesaplayýp return eder

	// matris aþaðýdaki fonksiyona geldiðinde o da minör hesaplamak için tekrar bu fonksiyona (minorHesapla) göndericek ama bir boy daha küçük olucak
	else {
		return determinantHesapla(&tempMat);
	}
}


/*TODO:

[]this pointer'ýný kullanabilirsin.

*/


matris matris::matrisMinor(matris* m, int r, int c) {
	
	//bir boy küçük matris nesnesi oluþturuyoruz bu sayede matris'in tüm özelliklerine ulaþabiliyoruz
	matris* tempMat2 = new matris(m->row - 1, m->row - 1);	
	int a = 0, b = 0;	//geçici matrisin boyutlarý
	
	for (int i = 0; i < tempMat2->row; i++)
	{
		for (int j = 0; j < tempMat2->row; j++)
		{
			if (i != r && j != c) {	//belirtilen satýr ve sütunlarý kaldýrýyoruz
				tempMat2->matrix[a][b++] = m->matrix[i][j];	
			}
		}
		if (i != r)	a++;
		if (b >= tempMat2->row - 1)b = 0;
	}
	return (*tempMat2);
}
unsigned long long int det = 0;
int matris::determinantHesapla(matris* m) {
	
	for (int i = 0; i < m->row; i++)
	{
		det += m->kofaktorHesapla(m, 0, i) * (m->matrix[0][i]);
	}
	return det;
	
}

