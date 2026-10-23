#include "Producto.hpp"

Producto::Producto(int pId, std::string pNombre, std::string pCategoria, std::string pMarca, 
                   float pPrecio, std::string pDescripcion)  : 
                   aId(pId), aNombre(pNombre), aCategoria(pCategoria), 
                   aMarca(pMarca), aPrecio(pPrecio), aDescripcion(pDescripcion), aConsultas(0){}

int Producto::getId() const{
    return aId;
}

std::string Producto::getNombre() const{
    return aNombre;
}

std::string Producto::getCategoria() const{
    return aCategoria;
}

std::string Producto::getMarca() const{
    return aMarca;
}

float Producto::getPrecio() const{
    return aPrecio;
}

std::string Producto::getDescripcion() const{
    return aDescripcion;
}

int Producto::getConsultas() const{
    return aConsultas;
}

void Producto::setNombre(std::string pNombre){
    aNombre = pNombre;
}

void Producto::setCategoria(std::string pCategoria){
    aCategoria = pCategoria;
}

void Producto::setMarca(std::string pMarca){
    aMarca = pMarca;
}

void Producto::setPrecio(float pPrecio){
    aPrecio = pPrecio;
}

void Producto::setDescripcion(std::string pDescripcion){
    aDescripcion = pDescripcion;
}

void Producto::consultado(){
    aConsultas++;
}

std::string Producto::mostrarDatos(){
    std::string msg;
    msg = "";
    msg += "Identificador: " + std::to_string(aId) + "\n";
    msg += "Nombre: " + aNombre + "\n";
    msg += "Categoría: " + aCategoria + "\n";
    msg += "Marca: " + aMarca + "\n";
    msg += "Precio: " + std::to_string(aPrecio) + "\n";
    msg += "Descripción: " + aDescripcion + "\n";
    msg += "Consultas: " + std::to_string(aConsultas);

    return msg;
}