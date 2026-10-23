#ifndef ARBOLSPLAY_HPP
#define ARBOLSPLAY_HPP

#include <string>
#include "Nodo.hpp"
#include "ListaProductos.hpp"

class ArbolSplay{
private:
    Nodo* apRaiz;
    int aAsignarId;
    int aCantidad;

    void liberar(Nodo* actual);
    void mostrar(Nodo* actual, int nivel);

    void rotarIzquierda(Nodo* actual);
    void rotarDerecha(Nodo* actual);
    void splay(Nodo* actual);

    Nodo* buscarNodo(int pId);
    Nodo* obtenerNodo(int pId);
    Nodo* mayor(Nodo* actual);
    void recolectar(Nodo* actual, const std::string& categoria, ListaProductos& lista);

public:
    ArbolSplay();
    ~ArbolSplay();
    int insertar(const std::string& nombre, const std::string& categoria, const std::string& marca,
                 float precio, const std::string& descripcion);
    Producto* buscar(int id);
    Producto* obtener(int id);
    bool eliminar(int id);
    bool modificar(int id, const std::string& nombre, const std::string& categtoria, const std::string& marca, 
                   float precio, const std::string& descripcion);
    void mostrar();
    int getTamano() const;
    void topCategoria(const std::string& categoria);

};

#endif 