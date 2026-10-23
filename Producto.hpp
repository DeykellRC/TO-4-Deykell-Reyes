#ifndef PRODUCTO_HPP
#define PRODUCTO_HPP

#include <string>

class Producto{
private:
    int aId;
    std::string aNombre;
    std::string aCategoria;
    std::string aMarca;
    float aPrecio;
    std::string aDescripcion;
    int aConsultas;

public:
    Producto(int pId, std::string pNombre, std::string pCategoria, std::string pMarca, float pPrecio, std::string pDescripcion);

    int getId() const;
    std::string getNombre() const;
    std::string getCategoria() const;
    std::string getMarca() const;
    float getPrecio() const;
    std::string getDescripcion() const;
    int getConsultas() const;

    void setNombre(std::string pNombre);
    void setCategoria(std::string pCategoria);
    void setMarca(std::string pMarca);
    void setPrecio(float pPrecio);
    void setDescripcion(std::string pDescripcion);

    void consultado();

    std::string mostrarDatos();
};

#endif 