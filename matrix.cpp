

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "matrixClass.h"
using namespace std;

int main()
{
    
    MatrixCalculations m1(5,5);
    MatrixCalculations m2(3, 3);
    m2.FillRandomValues();
    m1.FillRandomValues();
    m1.display();
    m2.display();
    cout << "determinant m1: " << m1.Determinant() << endl;
    cout << "determinant m2: " << m2.Determinant() << endl;

    



}


