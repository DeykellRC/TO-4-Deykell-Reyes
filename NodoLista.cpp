#include "NodoLista.hpp"

NodoLista::NodoLista(Producto* pProducto) : apProducto(pProducto), apSiguiente(nullptr){}

Producto* NodoLista::getProducto(){
    return apProducto;
}

NodoLista* NodoLista::getSiguiente(){
    return apSiguiente;
}

void NodoLista::setSiguiente(NodoLista* pSiguiente){
    apSiguiente = pSiguiente;
}
