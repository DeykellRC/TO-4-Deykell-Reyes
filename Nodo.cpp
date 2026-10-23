#include "Nodo.hpp"

Nodo::Nodo(Producto pProducto) : apPadre(nullptr), apIzquierda(nullptr), apDerecha(nullptr), aProducto(pProducto){}

Nodo* Nodo::getPadre(){
    return apPadre;
}

Nodo* Nodo::getIzquierda(){
    return apIzquierda;
}

Nodo* Nodo::getDerecha(){
    return apDerecha;
}

Producto& Nodo::getProducto(){
    return aProducto;
}

void Nodo::setPadre(Nodo* pPadre){
    apPadre = pPadre;
}

void Nodo::setIzquierda(Nodo* pIzquierda){
    apIzquierda = pIzquierda;
}

void Nodo::setDerecha(Nodo* pDerecha){
    apDerecha = pDerecha;
}
