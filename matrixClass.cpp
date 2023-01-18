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


matris::matris(int r, int c) {	//matrix[sat�r][s�tun]
	row = r;
	col = c;
	
	//yer ay�rma
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

	//yer ay�rma
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}

	//e�itleme
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

	//matrix 'i ba�ka bir matrise ge�ici olarak kopyal�yorum
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

	//transpoz i�lemi
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

	//matrix 'i ba�ka bir matrise ge�ici olarak kopyal�yorum
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

	//�arpma i�lemi
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//komple hatal�
			/*
			tempMatrix[i][0] += matrix[i][j] * othMatris.matrix[j][i];
			tempMatrix[i][1] += matrix[i][j] * othMatris.matrix[j][i ];
			tempMatrix[i][2] += matrix[i][j] * othMatris.matrix[j][i ];
			*/
			cout << "hatal� fonk �al��t�" << endl;
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
		int a = 0, b = 0;	//ge�ici matrisin boyutlar�
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
	int yon = 0;	//�arp�mlar�n y�n�n� de�i�tirecek

	// g = 1 det'in ilk par�as� i�in, a�a��daki d�ng� ikinci defa �al��t���nda g -1 olur det'in ikinci par�as� i�in
	int g;	//k de�erini tek tek artt�rmak yada azaltmak (de�eri -1'e e�itlenirse) i�in a�a��daki for d�ng�s�nde kullan�l�r
	for (g = 1; g > -2; g -= 2 )	//determinant iki ifadenin fark� ile yap�l�r
	{
		for (int j = 0; j < _row; j++)
		{
			i++;
			k = yon;	//k de�eri s�f�r yada iki

			//i de�eri sat�rlar� a�a�� ve yetmiyorsa tekrar yukar� ��kar�r k ise s�tunlar� temsil eder ba�tan sona yada sondan ba�a
			for ( ; k < _row && k >= 0; i++, k+=g)	
			{

				//i de�erini tekrar ba�a alma
				if(i>=_row){
					i -= _row;
				}
				
				carpimlar *= m[i][k];
			}
			d1 += carpimlar;
			carpimlar = 1;
		}

		det += d1 * g;	//g, ikinci k�s�mda -1 de�erini al�p determinant i�in aradaki fark i�lemini yapm�� olur
		d1 = 0;	//det fark�n�n ikinci k�sm� i�in s�f�rland�
		//�st scope'da determinant�n ilk par�as� yap�lyor 'yon' ve 'g' de�i�ti�inde ikinci par�as� yap�l�r (-'den sonra)		
		yon = _row-1;
	}
	return det;
}

unsigned long long int matris::minorHesapla(matris* m, int r, int c) {
	
	//s�ra ile recursive yap�p �st s�ra min�rlerini bul min�r yard�m� ile det hesapla
	matris tempMat(m->row-1,m->row-1);
	tempMat=matrisMinor(m, r, c);
	if (tempMat.row == 3)	return sarrusDetHesapla(tempMat.matrix,3,3);	//matris 3x3 kald�ysa direk sarrus ile det hesaplay�p return eder

	// matris a�a��daki fonksiyona geldi�inde o da min�r hesaplamak i�in tekrar bu fonksiyona (minorHesapla) g�ndericek ama bir boy daha k���k olucak
	else {
		return determinantHesapla(&tempMat);
	}
}


/*TODO:

[]this pointer'�n� kullanabilirsin.

*/


matris matris::matrisMinor(matris* m, int r, int c) {
	
	//bir boy k���k matris nesnesi olu�turuyoruz bu sayede matris'in t�m �zelliklerine ula�abiliyoruz
	matris* tempMat2 = new matris(m->row - 1, m->row - 1);	
	int a = 0, b = 0;	//ge�ici matrisin boyutlar�
	
	for (int i = 0; i < tempMat2->row; i++)
	{
		for (int j = 0; j < tempMat2->row; j++)
		{
			if (i != r && j != c) {	//belirtilen sat�r ve s�tunlar� kald�r�yoruz
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

