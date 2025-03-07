#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "matrixCalculations.h"

using namespace std;

int factor(int a) {
	int b = 1;
	while (a > 0) {
		b *= a;
		a--;
	}
	return b;
}

MatrixCalculations::MatrixCalculations(int r, int c) {	//matrix[sat�r][s�tun]
	row = r;
	col = c;

	//yer ay�rma
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}
}

MatrixCalculations::~MatrixCalculations() {
	for (int i = 0; i < row; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

MatrixCalculations::MatrixCalculations(const MatrixCalculations& oth) {
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

int MatrixCalculations::getRow() { return row; }

int MatrixCalculations::getCol() { return col; }

void MatrixCalculations::setValue(int r, int c, int value) {
	matrix[row][col] = value;
}

void MatrixCalculations::FillRandomValues() {
	srand(time(0));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
}

void MatrixCalculations::CreateIdentityMatrix() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == j)matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
}

void MatrixCalculations::display() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//cout << matrix[i][j] << "  ";		//format yok
			printf("%-3d", matrix[i][j]);
		}
		cout << "\n";
	}
	cout << endl;
}

void MatrixCalculations::addMatris(MatrixCalculations& othMatrix) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] += othMatrix.matrix[i][j];
		}
	}
}

void MatrixCalculations::skalarMultiply(int skalar) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] *= skalar;
		}
	}
}

void MatrixCalculations::transpoz() {

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

void MatrixCalculations::matrixMultiply(MatrixCalculations& othMatrix) {

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
			tempMatrix[i][0] += matrix[i][j] * othMatrix.matrix[j][i];
			tempMatrix[i][1] += matrix[i][j] * othMatrix.matrix[j][i ];
			tempMatrix[i][2] += matrix[i][j] * othMatrix.matrix[j][i ];
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

unsigned long long int MatrixCalculations::Cofactor(MatrixCalculations* m, int r, int c) {
	return calculateMinor(m, r, c) * pow((-1), r + 1 + c);
}

int MatrixCalculations::Determinant() {
	if (row != col) return -1;
	if (row <= 3) return sarrusDeterminant(matrix, row, col);


	else {
		MatrixCalculations tempMat(row, row);
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
		return calculateDeterminant(&tempMat);

	}
}


int MatrixCalculations::sarrusDeterminant(int** m, int _row, int _col) {

	if (_row > 3 || _col > 3) {
		cout << "sarrus det. error";
		return -1;
	}

	int det = 0, d1 = 0, carpimlar = 1, i = -1, k = 0;
	int yon = 0;	//�arp�mlar�n y�n�n� de�i�tirecek

	// g = 1 det'in ilk par�as� i�in, a�a��daki d�ng� ikinci defa �al��t���nda g -1 olur det'in ikinci par�as� i�in
	int g;	//k de�erini tek tek artt�rmak yada azaltmak (de�eri -1'e e�itlenirse) i�in a�a��daki for d�ng�s�nde kullan�l�r
	for (g = 1; g > -2; g -= 2)	//determinant iki ifadenin fark� ile yap�l�r
	{
		for (int j = 0; j < _row; j++)
		{
			i++;
			k = yon;	//k de�eri s�f�r yada iki

			//i de�eri sat�rlar� a�a�� ve yetmiyorsa tekrar yukar� ��kar�r k ise s�tunlar� temsil eder ba�tan sona yada sondan ba�a
			for (; k < _row && k >= 0; i++, k += g)
			{

				//i de�erini tekrar ba�a alma
				if (i >= _row) {
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
		yon = _row - 1;
	}
	return det;
}

unsigned long long int MatrixCalculations::calculateMinor(MatrixCalculations* m, int r, int c) {

	//s�ra ile recursive yap�p �st s�ra min�rlerini bul min�r yard�m� ile det hesapla
	MatrixCalculations tempMat(m->row - 1, m->row - 1);
	tempMat = MatrixMinor(m, r, c);

	if (tempMat.row == 3)	return sarrusDeterminant(tempMat.matrix, 3, 3);	//matris 3x3 kald�ysa direk sarrus ile det hesaplay�p return eder

	// matris a�a��daki fonksiyona geldi�inde o da min�r hesaplamak i�in tekrar bu fonksiyona (calculateMinor) g�ndericek ama bir boy daha k���k olucak
	else {
		return calculateDeterminant(&tempMat);
	}
}


/*TODO:

[]this pointer'�n� kullanabilirsin.

*/


MatrixCalculations MatrixCalculations::MatrixMinor(MatrixCalculations* m, int r, int c) {

	//bir boy k���k matris nesnesi olu�turuyoruz bu sayede matris'in t�m �zelliklerine ula�abiliyoruz
	MatrixCalculations* tempMat2 = new MatrixCalculations(m->row - 1, m->row - 1);
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
int MatrixCalculations::calculateDeterminant(MatrixCalculations* m) {

	for (int i = 0; i < m->row; i++)
	{
		det += m->Cofactor(m, 0, i) * (m->matrix[0][i]);
	}
	return det;

}

