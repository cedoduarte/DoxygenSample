// License LGPL: https://www.gnu.org/licenses/lgpl.html

/**
  * @file funciones.h
  * @version 1.0
  * @date 08/06/2014
  * @author DuarteCorporation
  * @title Funciones independientes
  * @brief Funciones de utilería
  * @code
    int main() {
        cout << boolalpha;
        cout << es_par(7) << endl;
        cout << menor(1, 2) << endl;
        cout << mayor(1, 2) << endl;
        return 0;
    }
  * @endcode
  */

#ifndef FUNCIONES_H
#define FUNCIONES_H

// funciones independientes

/**
 * @brief es_par Indica si un número es par
 * @param numero Número para evaluar
 * @return Resultado de la evaluación
 */
bool es_par(int numero);

/**
 * @brief menor Indica el número menor
 * @param a Indica el primer número
 * @param b Indica el segundo número
 * @return El número menor
 */
double menor(double a, double b);

/**
 * @brief mayor Indica el número mayor
 * @param a Indica el primer número
 * @param b Indica el segundo número
 * @return El número mayor
 */
double mayor(double a, double b);

#endif // FUNCIONES_H
