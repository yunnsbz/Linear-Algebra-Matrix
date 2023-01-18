

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "matrixClass.h"
using namespace std;

int main()
{
    
    matris m1(5,5);
    matris m2(3, 3);
    m2.randomSet();
    m1.randomSet();
    m1.display();
    m2.display();
    cout << "determinant m1: " << m1.determinant() << endl;
    cout << "determinant m2: " << m2.determinant() << endl;

    



}


