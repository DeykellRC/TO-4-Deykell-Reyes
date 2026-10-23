#include "ArbolSplay.hpp"
#include <iostream>

ArbolSplay::ArbolSplay() : apRaiz(nullptr), aAsignarId(1), aCantidad(0){}

ArbolSplay::~ArbolSplay(){
    liberar(apRaiz);
}

void ArbolSplay::liberar(Nodo* actual){
    if (actual == nullptr) return;
    liberar(actual->getIzquierda());
    liberar(actual->getDerecha());
    delete actual;
}

void ArbolSplay::rotarIzquierda(Nodo* actual){
    Nodo* padre = actual->getPadre();
    Nodo* abuelo = padre->getPadre();
    Nodo* hijoI = actual->getIzquierda();

    padre->setDerecha(hijoI);
    if (hijoI != nullptr) hijoI->setPadre(padre);

    actual->setIzquierda(padre);
    padre->setPadre(actual);

    actual->setPadre(abuelo);
    if (abuelo == nullptr){
        apRaiz = actual;
    }else if (abuelo->getIzquierda() == padre) {
        abuelo->setIzquierda(actual);
    } else{
        abuelo->setDerecha(actual);
    }
}

void ArbolSplay::rotarDerecha(Nodo* actual){
    Nodo* padre = actual->getPadre();
    Nodo* abuelo = padre->getPadre();
    Nodo* hijoD = actual->getDerecha();

    padre->setIzquierda(hijoD);
    if (hijoD != nullptr) hijoD->setPadre(padre);
    
    actual->setDerecha(padre);
    padre->setPadre(actual);

    actual->setPadre(abuelo);
    if (abuelo == nullptr){
        apRaiz = actual;
    }else if (abuelo->getIzquierda() == padre){
        abuelo->setIzquierda(actual);
    }else{
        abuelo->setDerecha(actual);
    }
}

void ArbolSplay::splay(Nodo* actual){
    if (actual == nullptr) return;

    while (actual->getPadre() != nullptr){
        Nodo* padre = actual->getPadre();
        Nodo* abuelo = padre->getPadre();

        bool actualEsIzq = (padre->getIzquierda() == actual);

        if (abuelo == nullptr){
            if (actualEsIzq) {
                rotarDerecha(actual);
            }else{
                rotarIzquierda(actual);
            }
        }else{
            bool padreEsIzq = (abuelo->getIzquierda() == padre);

            if (actualEsIzq && padreEsIzq){
                rotarDerecha(padre);
                rotarDerecha(actual);
            }else if(!actualEsIzq && !padreEsIzq){
                rotarIzquierda(padre);
                rotarIzquierda(actual);
            }else if(!actualEsIzq && padreEsIzq){
                rotarIzquierda(actual);
                rotarDerecha(actual);
            }else{
                rotarDerecha(actual);
                rotarIzquierda(actual);
            }
        }
    }
}

Nodo* ArbolSplay::buscarNodo(int id){
    Nodo* actual = apRaiz;
    Nodo* ultimo = nullptr;

    while (actual != nullptr){
        ultimo = actual;
        int idActual = actual->getProducto().getId();

        if (id == idActual) return actual;
        if (id < idActual) {
            actual = actual->getIzquierda();
        }else{
            actual = actual->getDerecha();
        } 

    }
    return ultimo;
}

Nodo* ArbolSplay::obtenerNodo(int id){
    if (apRaiz == nullptr) return nullptr;

    Nodo* actual = buscarNodo(id);
    splay(actual);

    if (actual->getProducto().getId() != id) return nullptr;
    return actual;
}

Nodo* ArbolSplay::mayor(Nodo* actual){
    while (actual->getDerecha() != nullptr){
        actual = actual->getDerecha();
    }
    return actual;
}

int ArbolSplay::insertar(const std::string& nombre, const std::string& categoria, const std::string& marca,
                         float precio, const std::string& descripcion){

int id = aAsignarId++;
Nodo* nuevo = new Nodo(Producto(id, nombre, categoria, marca, precio, descripcion));

if (apRaiz == nullptr){
    apRaiz = nuevo;
}else{
    Nodo* actual = apRaiz;
    Nodo* padre = nullptr;

    while (actual != nullptr){
        padre = actual;
        if (id < actual->getProducto().getId()){
            actual = actual->getIzquierda();
        }else{
            actual = actual->getDerecha();
        }
    }
    nuevo->setPadre(padre);
    if (id < padre->getProducto().getId()){
        padre->setIzquierda(nuevo);
    }else{
        padre->setDerecha(nuevo);
    }

    }

    aCantidad++;
    splay(nuevo);
    return id;
}

Producto* ArbolSplay::buscar(int id) {
    Nodo* actual = obtenerNodo(id);
    if (actual == nullptr) return nullptr;

    actual->getProducto().consultado();
    return &actual->getProducto();
}

Producto* ArbolSplay::obtener(int id) {
    Nodo* actual = obtenerNodo(id);
    if (actual == nullptr) return nullptr;
    return &actual->getProducto();
}

bool ArbolSplay::eliminar(int id){
    Nodo* actual = obtenerNodo(id);
    if (actual == nullptr) return false;

    Nodo* izq = actual->getIzquierda();
    Nodo* der = actual->getDerecha();

    if (izq != nullptr) izq->setPadre(nullptr);
    if (der != nullptr) der->setPadre(nullptr);

    delete actual;
    aCantidad--;

    if (izq == nullptr){
        apRaiz = der;
    }else{
        apRaiz = izq;
        Nodo* maximo = mayor(izq);
        splay(maximo);
        maximo->setDerecha(der);
        if (der != nullptr) der->setPadre(maximo);
    }
    return true;
}
                        

bool ArbolSplay::modificar(int id, const std::string& nombre, const std::string& categoria, const std::string& marca,
                         float precio, const std::string& descripcion){

    Nodo* actual = obtenerNodo(id);
    if (actual == nullptr) return false;

    Producto& producto = actual->getProducto();
    producto.setNombre(nombre);
    producto.setCategoria(categoria);
    producto.setMarca(marca);
    producto.setPrecio(precio);
    producto.setDescripcion(descripcion);
    return true;
}

void ArbolSplay::mostrar() {
    if (apRaiz == nullptr) {
        std::cout << "El arbol esta vacio" << std::endl;
        return;
    }
    mostrar(apRaiz, 0);
}

void ArbolSplay::mostrar(Nodo* actual, int nivel) {
    if (actual == nullptr) return;

    mostrar(actual->getDerecha(), nivel + 1);

    for (int i = 0; i < nivel; i++) {
        std::cout << "    ";
    }
    std::cout << actual->getProducto().getId();
    if (nivel == 0) {
        std::cout << " (raiz)";
    }
    std::cout << std::endl;

    mostrar(actual->getIzquierda(), nivel + 1);
}

int ArbolSplay::getTamano() const {
    return aCantidad;
}