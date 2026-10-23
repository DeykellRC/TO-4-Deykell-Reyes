#ifndef NODOLISTA_HPP
#define NODOLISTA_HPP

#include "Producto.hpp"


class NodoLista{
private:
    Producto* apProducto;
    NodoLista* apSiguiente;

public:
    NodoLista(Producto* pProducto);

    Producto* getProducto();
    NodoLista* getSiguiente();

    void setSiguiente(NodoLista* pSiguiente);
};

#endif
