#ifndef NODO_HPP
#define NODO_HPP

#include "Producto.hpp"

class Nodo{
private:
    Nodo* apPadre;
    Nodo* apIzquierda;
    Nodo* apDerecha;
    Producto aProducto;

public:
    Nodo(Producto pProducto);

    Nodo* getPadre();
    Nodo* getIzquierda();
    Nodo* getDerecha();
    Producto& getProducto();

    void setPadre(Nodo* pPadre);
    void setIzquierda(Nodo* pIzquierda);
    void setDerecha(Nodo* pDerecha);


};

#endif 