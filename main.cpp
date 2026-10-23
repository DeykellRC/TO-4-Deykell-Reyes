#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include "ArbolSplay.hpp"


std::string leerTexto(const std::string& mensaje, bool permitirVacio) {
    std::string linea;
    while (true) {
        std::cout << mensaje;
        if (!std::getline(std::cin, linea)) return "";   
        if (!linea.empty() || permitirVacio) return linea;
        std::cout << "Este campo no puede quedar vacio." << std::endl;
    }
}

int leerEntero(const std::string& mensaje) {
    while (true) {
        std::string linea = leerTexto(mensaje, false);
        if (!std::cin) return -1;
        std::istringstream ss(linea);
        int numero;
        char sobra;
        if (ss >> numero && !(ss >> sobra)) return numero;
        std::cout << "Debe ingresar un numero entero." << std::endl;
    }
}

bool leerPrecio(const std::string& mensaje, bool permitirVacio, float& precio) {
    while (true) {
        std::string linea = leerTexto(mensaje, permitirVacio);
        if (!std::cin) return false;
        if (linea.empty()) return false;
        std::istringstream ss(linea);
        float numero;
        char sobra;
        if (ss >> numero && !(ss >> sobra) && numero >= 0) {
            precio = numero;
            return true;
        }
        std::cout << "Debe ingresar un precio valido (numero mayor o igual a 0)." << std::endl;
    }
}

void pausa() {
    std::string basura;
    std::cout << "\nPresione Enter para continuar...";
    std::getline(std::cin, basura);
}

void agregarProducto(ArbolSplay& arbol) {
    std::cout << "\n--- Agregar producto ---" << std::endl;
    std::string nombre = leerTexto("Nombre: ", false);
    std::string categoria = leerTexto("Categoria: ", false);
    std::string marca = leerTexto("Marca: ", false);
    float precio = 0;
    leerPrecio("Precio: ", false, precio);
    std::string descripcion = leerTexto("Descripcion: ", false);

    int id = arbol.insertar(nombre, categoria, marca, precio, descripcion);
    std::cout << "Producto agregado con el identificador " << id << std::endl;
}

void eliminarProducto(ArbolSplay& arbol) {
    std::cout << "\n--- Eliminar producto ---" << std::endl;
    int id = leerEntero("Identificador: ");
    if (arbol.eliminar(id)) {
        std::cout << "Producto " << id << " eliminado." << std::endl;
    } else {
        std::cout << "No existe un producto con el identificador " << id << std::endl;
    }
}

void modificarProducto(ArbolSplay& arbol) {
    std::cout << "\n--- Modificar producto ---" << std::endl;
    int id = leerEntero("Identificador: ");

    Producto* p = arbol.obtener(id);  
    if (p == nullptr) {
        std::cout << "No existe un producto con el identificador " << id << std::endl;
        return;
    }

    std::cout << "\nDatos actuales:\n" << p->mostrarDatos() << std::endl;
    std::cout << "\nEscriba el nuevo valor o presione Enter para mantener el actual." << std::endl;

    std::string nombre = leerTexto("Nombre [" + p->getNombre() + "]: ", true);
    if (nombre.empty()) nombre = p->getNombre();

    std::string categoria = leerTexto("Categoria [" + p->getCategoria() + "]: ", true);
    if (categoria.empty()) categoria = p->getCategoria();

    std::string marca = leerTexto("Marca [" + p->getMarca() + "]: ", true);
    if (marca.empty()) marca = p->getMarca();

    float precio = p->getPrecio();
    std::ostringstream os;
    os << p->getPrecio();
    leerPrecio("Precio [" + os.str() + "]: ", true, precio);

    std::string descripcion = leerTexto("Descripcion [" + p->getDescripcion() + "]: ", true);
    if (descripcion.empty()) descripcion = p->getDescripcion();

    arbol.modificar(id, nombre, categoria, marca, precio, descripcion);
    std::cout << "Producto " << id << " modificado." << std::endl;
}

void menuAdministrador(ArbolSplay& arbol) {
    int opcion;
    do {
        std::cout << "\n========== MENU ADMINISTRADOR ==========" << std::endl;
        std::cout << "1. Agregar producto" << std::endl;
        std::cout << "2. Eliminar producto" << std::endl;
        std::cout << "3. Modificar producto" << std::endl;
        std::cout << "4. Visualizar arbol splay" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leerEntero("Opcion: ");
        if (!std::cin) return;

        switch (opcion) {
            case 1: agregarProducto(arbol); pausa(); break;
            case 2: eliminarProducto(arbol); pausa(); break;
            case 3: modificarProducto(arbol); pausa(); break;
            case 4:
                std::cout << "\n--- Arbol splay (" << arbol.getTamano() << " productos) ---" << std::endl;
                std::cout << "(la raiz esta a la izquierda; cada nivel tiene 4 espacios mas)\n" << std::endl;
                arbol.mostrar();
                pausa();
                break;
            case 0: break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    } while (opcion != 0);
}

// ================= Opciones de usuario =================

void consultarPorId(ArbolSplay& arbol) {
    std::cout << "\n--- Consultar por identificador ---" << std::endl;
    int id = leerEntero("Identificador: ");

    std::chrono::steady_clock::time_point inicio = std::chrono::steady_clock::now();
    Producto* p = arbol.buscar(id);
    std::chrono::steady_clock::time_point fin = std::chrono::steady_clock::now();

    long long nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count();

    if (p == nullptr) {
        std::cout << "No existe un producto con el identificador " << id << std::endl;
    } else {
        std::cout << "\n" << p->mostrarDatos() << std::endl;
        std::cout << "\nEl producto " << id << " ahora es la raiz del arbol." << std::endl;
    }
    std::cout << "Tiempo de busqueda: " << nanos << " nanosegundos ("
              << nanos / 1000.0 << " microsegundos)" << std::endl;
}

void consultarPorCategoria(ArbolSplay& arbol) {
    std::cout << "\n--- Consultar por categoria ---" << std::endl;
    std::string categoria = leerTexto("Categoria: ", false);
    std::cout << std::endl;
    arbol.topCategoria(categoria);
}

void menuUsuario(ArbolSplay& arbol) {
    int opcion;
    do {
        std::cout << "\n============ MENU USUARIO ============" << std::endl;
        std::cout << "1. Consultar producto por identificador" << std::endl;
        std::cout << "2. Consultar los 5 mas populares de una categoria" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leerEntero("Opcion: ");
        if (!std::cin) return;

        switch (opcion) {
            case 1: consultarPorId(arbol); pausa(); break;
            case 2: consultarPorCategoria(arbol); pausa(); break;
            case 0: break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    } while (opcion != 0);
}


int main() {
    ArbolSplay arbol;

    int opcion;
    do {
        std::cout << "\n=========================================" << std::endl;
        std::cout << "   SISTEMA DE CONSULTA DE PRODUCTOS" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "1. Opciones administrativas" << std::endl;
        std::cout << "2. Opciones de usuario" << std::endl;
        std::cout << "0. Salir" << std::endl;
        opcion = leerEntero("Opcion: ");
        if (!std::cin) break;

        switch (opcion) {
            case 1: menuAdministrador(arbol); break;
            case 2: menuUsuario(arbol); break;
            case 0: std::cout << "Hasta luego." << std::endl; break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    } while (opcion != 0);

    return 0;
}
