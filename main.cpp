// License LGPL: https://www.gnu.org/licenses/lgpl.html

/**
  * @author Carlos Enrique Duarte Ortiz - DuarteCorporation
  * @version 1.0
  * @date 08/06/2014
  * @file main.cpp
  * @title Función principal
  * @brief Manejo del programa principal
  */

#include "arreglo.h"
#include <iostream>

using namespace std;

int main()
{
    const double valores[] = { 1, 2, 3, 4, 5, 6, 7, 8, 8 };
    Arreglo<double> A(valores, sizeof(valores) / sizeof(double));
    cout << "Valores: " << A << endl;
    cout << "Media: " << A.media() << endl;
    cout << "Mediana: " << A.mediana() << endl;
    cout << "Moda: " << A.moda() << endl;
    return 0;
}
