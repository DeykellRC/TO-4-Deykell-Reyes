#ifndef LISTAPRODUCTOS_HPP
#define LISTAPRODUCTOS_HPP

#include "NodoLista.hpp"

class ListaProductos{
private:
    NodoLista* apCabeza;
    int aCantidad;

public:
    ListaProductos();
    ~ListaProductos();

    void insertarOrdenado(Producto* pProducto);
    void mostrarPrimeros(int n);
    int getCantidad() const;
};

#endif
