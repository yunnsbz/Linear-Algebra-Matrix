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

matrixClass::matrixClass(int r, int c) {	//matrix[satýr][sütun]
	row = r;
	col = c;
	
	//yer ayýrma
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}
}

matrixClass::~matrixClass() {
	for (int i = 0; i < row; i++)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
}

matrixClass::matrixClass(const matrixClass& oth) {
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

int matrixClass::getRow() { return row; }

int matrixClass::getCol() { return col; }

void matrixClass::setValue(int r, int c, int value) {
	matrix[row][col] = value;
}

void matrixClass::randomSet() {
	srand(time(0));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
}

void matrixClass::birimMatrisYap() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(i==j)matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
}

void matrixClass::display() {
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

void matrixClass::addMatris(matrixClass& othMatris) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] += othMatris.matrix[i][j];
		}
	}
}

void matrixClass::skalarMultiply(int skalar) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] *= skalar;
		}
	}
}

void matrixClass::transpoz() {

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

void matrixClass::matrixMultiply(matrixClass& othMatris) {

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

unsigned long long int matrixClass::Cofactor(matrixClass* m, int r, int c) {
	return calculateMinor(m, r, c) * pow((-1), r+1 + c);
}

int matrixClass::determinant() {
	if (row != col) return -1;
	if (row <= 3) return sarrusDeterminant(matrix, row, col);


	else {
		matrixClass tempMat(row, row);
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
		return calculateDeterminant(&tempMat);
	}
}


int matrixClass::sarrusDeterminant(int** m, int _row, int _col) {

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

unsigned long long int matrixClass::calculateMinor(matrixClass* m, int r, int c) {
	
	//sýra ile recursive yapýp üst sýra minörlerini bul minör yardýmý ile det hesapla
	matrixClass tempMat(m->row-1,m->row-1);
	tempMat=matrixMinor(m, r, c);
	if (tempMat.row == 3)	return sarrusDeterminant(tempMat.matrix,3,3);	//matris 3x3 kaldýysa direk sarrus ile det hesaplayýp return eder

	// matris aþaðýdaki fonksiyona geldiðinde o da minör hesaplamak için tekrar bu fonksiyona (calculateMinor) göndericek ama bir boy daha küçük olucak
	else {
		return calculateDeterminant(&tempMat);
	}
}


/*TODO:

[]this pointer'ýný kullanabilirsin.

*/


matrixClass matrixClass::matrixMinor(matrixClass* m, int r, int c) {
	
	//bir boy küçük matris nesnesi oluþturuyoruz bu sayede matris'in tüm özelliklerine ulaþabiliyoruz
	matrixClass* tempMat2 = new matrixClass(m->row - 1, m->row - 1);	
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
int matrixClass::calculateDeterminant(matrixClass* m) {
	
	for (int i = 0; i < m->row; i++)
	{
		det += m->Cofactor(m, 0, i) * (m->matrix[0][i]);
	}
	return det;
	
}

