// License LGPL: https://www.gnu.org/licenses/lgpl.html

/**
  * @file arreglo.h
  * @version 1.0
  * @date 08/06/2014
  * @author DuarteCorporation
  * @title Clase plantilla Arreglo
  * @brief Clase para el manejo estadístico de datos
  * @code
    int main() {
        const double valores[] = { 1, 2, 3, 4, 5, 6, 7, 8, 8 };
        Arreglo<double> A(valores, sizeof(valores) / sizeof(double));
        cout << "Valores: " << A           << endl;
        cout << "Media: "   << A.media()   << endl;
        cout << "Mediana: " << A.mediana() << endl;
        cout << "Moda: "    << A.moda()    << endl;
        return 0;
    }
  * @endcode
  */

#ifndef ARREGLO_H
#define ARREGLO_H

#include "funciones.h"
#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @brief Estructura auxiliar de la estructura Moda
 */
template<typename Tipo> struct Mayor
{
    // estructura plantilla Mayor
    Tipo valor;
    int ocurrencias;
};

/**
 * @brief Estructura auxiliar de la clase Arreglo
 */
template<typename Tipo> struct Moda
{
    // estructura plantilla Moda
    Tipo valor;
    bool hay_moda;

    Moda(const Mayor<Tipo> &ma) : valor(ma.valor), hay_moda(true)
    {
        if (ma.ocurrencias == 1) {
            hay_moda = false;
        }
    }
};

/**
 * @brief Operador de inserción de la estructura Moda
 * @param o ostream de salida
 * @param mo Moda de entrada
 * @return ostream&
 */
template<typename Tipo> std::ostream &operator<<(std::ostream &o,
                                                 const Moda<Tipo> &mo)
{
    // Hay moda para mostrar
    if (mo.hay_moda) {
        return o << mo.valor;
    }
    return o;
}

/**
 * @brief Enumeración para elegir la forma de ordenar el Arreglo
 */
enum Ordenamiento
{
    // enumeración de ordenamiento
    ASCENDENTE  = 0,
    DESCENDENTE = 1
};

/**
 * @brief Clase para almacenar datos y hacer operaciones estadísticas
 */
template<typename Tipo> class Arreglo
{
    // clase plantilla Arreglo
public:
    /**
     * @brief Constructor de Arreglo
     * @param valores Representa el arreglo de valores
     * @param tam Tamaño del arreglo
     */
    Arreglo(const Tipo *valores, int tam);

    /**
     * @brief Constructor de copia de Arreglo
     * @param otro Otro arreglo
     */
    Arreglo(const Arreglo &otro);

    /**
      * @brief Destructor de la clase Arreglo
      */
    ~Arreglo() {
        delete[] _valores;
    }

    /**
     * @brief media Obtiene el valor de la media aritmética
     * @return Valor calculado
     */
    double media() const;

    /**
     * @brief mediana Obtiene el valor intermedio de la serie de valores
     * @return El valor intermedio
     */
    Tipo mediana() const;

    /**
     * @brief moda Obtiene el valor con mayor número de ocurrencias
     * @return Moda
     */
    Moda<Tipo> moda() const;

    /**
     * @brief ordena Ordena el contenido del Arreglo
     * @param ord Forma de ordenamiento
     */
    void ordena(Ordenamiento ord = ASCENDENTE);

    /**
     * @brief Operador de inserción de la clase Arreglo
     * @param o ostream&
     * @param A Referencia constante a un Arreglo
     * @return ostream&
     */
    template<typename Type> friend std::ostream &operator<<(std::ostream &o,
                                                     const Arreglo<Type> &A);
private:
    void copia(std::vector<Tipo> &v) const;
    void asigna(const std::vector<Tipo> &v);

    Tipo *_valores;
    int _tam;
};

template<typename Tipo> Arreglo<Tipo>::Arreglo(const Tipo *valores, int tam)
    : _valores(new Tipo[tam])
    , _tam(tam)
{
    // copia valores
    for (int i = 0; i < tam; ++i) {
        _valores[i] = valores[i];
    }
}

template<typename Tipo> Arreglo<Tipo>::Arreglo(const Arreglo &otro)
    : _valores(new Tipo[otro._tam])
    , _tam(otro._tam)
{
    // copia valores
    for (int i = 0; i < _tam; ++i) {
        _valores[i] = otro._valores[i];
    }
}

template<typename Tipo> double Arreglo<Tipo>::media() const
{
    // obtiene la media de los valores (promedio)
    double S = 0; // suma
    for (int i = 0; i < _tam; ++i) {
        S += _valores[i];
    }
    return S / _tam; // resultado
}

template<typename Tipo> Tipo Arreglo<Tipo>::mediana() const
{
    // obtiene la mediana de los valores (valor intermedio)
    Arreglo A(*this); // copia
    A.ordena();
    // si el tamaño es par:
    if (es_par(A._tam)) {
        const int pos1 = A._tam / 2;
        const int pos2 = pos1 - 1;
        const double S = A._valores[pos1] + A._valores[pos2];
        return S / 2; // resultado
    }
    // si el tamaño es impar:
    return A._valores[A._tam / 2]; // resultado
}

template<typename Tipo> Moda<Tipo> Arreglo<Tipo>::moda() const
{
    // obtiene el valor más frecuente
    using namespace std;
    vector<Tipo> valores, clases;
    copia(valores); // copia valores
    // llena clases
    int i;
    for (i = 0; i < _tam; ++i) {
        const int cnt = count(clases.begin(), clases.end(), _valores[i]);
        if (cnt == 0) {
            clases.push_back(_valores[i]);
        }
    }
    // Busca la mayor ocurrencia
    const int tamcss = clases.size();
    Mayor<Tipo> ma;
    ma.valor = clases[0];
    ma.ocurrencias = count(valores.begin(), valores.end(), clases[0]);
    for (i = 1; i < tamcss; ++i) {
        const int cnt = count(valores.begin(), valores.end(), clases[i]);
        if (ma.ocurrencias < cnt) {
            ma.ocurrencias = cnt;
            ma.valor = clases[i];
        }
    }
    return Moda<Tipo>(ma);
}

template<typename Tipo> void Arreglo<Tipo>::ordena(Ordenamiento ord)
{
    // ordena arreglo
    using namespace std;
    vector<Tipo> valores;
    copia(valores);
    sort(valores.begin(), valores.end(), ord == ASCENDENTE ? menor : mayor);
    asigna(valores);
}

template<typename Tipo> void Arreglo<Tipo>::copia(std::vector<Tipo> &v) const
{
    // operación contraria de asigna
    const int tam = v.size();
    if (tam < _tam) {
        v.resize(_tam);
    }
    for (int i = 0; i < _tam; ++i) {
        v[i] = _valores[i];
    }
}

template<typename Tipo> void Arreglo<Tipo>::asigna(const std::vector<Tipo> &v)
{
    // operación contraria de copia
    for (int i = 0; i < _tam; ++i) {
        _valores[i] = v[i];
    }
}

template<typename Type> std::ostream &operator<<(std::ostream &o,
                                                 const Arreglo<Type> &A)
{
    // muestra arreglos
    o << A._valores[0];
    for (int i = 1; i < A._tam; ++i) {
        o << ", " << A._valores[i];
    }
    return o;
}

#endif // ARREGLO_H
