#include "ListaProductos.hpp"
#include <iostream>

ListaProductos::ListaProductos() : apCabeza(nullptr), aCantidad(0){}

ListaProductos::~ListaProductos(){
    NodoLista* actual = apCabeza;
    while (actual != nullptr){
        NodoLista* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

void ListaProductos::insertarOrdenado(Producto* pProducto){
    NodoLista* nuevo = new NodoLista(pProducto);
    int consultas = pProducto->getConsultas();

    if (apCabeza == nullptr || consultas > apCabeza->getProducto()->getConsultas()){
        nuevo->setSiguiente(apCabeza);
        apCabeza = nuevo;
    }else{
        NodoLista* actual = apCabeza;
        while (actual->getSiguiente() != nullptr && actual->getSiguiente()->getProducto()->getConsultas() >= consultas){
            actual = actual->getSiguiente();
        }
        nuevo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevo);
    }
    aCantidad++;
}

void ListaProductos::mostrarPrimeros(int n){
    NodoLista* actual = apCabeza;
    int posicion = 1;

    while (actual != nullptr && posicion <= n){
        std::cout << "------------- #" << posicion << " -------------" << std::endl;
        std::cout << actual->getProducto()->mostrarDatos() << std::endl;
        actual = actual->getSiguiente();
        posicion++;
    }
}

int ListaProductos::getCantidad() const{
    return aCantidad;
}
