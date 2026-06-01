#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

//Brayan Daniel Barrios Carranza
// Carné: 9941-15-6843
// Sección:A

using namespace std;

struct Producto{
    int codigo;
    char nombre[30];
    float precio;
    int stock;
    int vendidos;
    bool activo;
};

struct DetalleVenta{
    int codigoProducto;
    char nombre[30];
    int cantidad;
    float precioUnitario;
    float subtotal;
};

struct Venta{
    
    int numeroVenta;
    int dia;
    int mes;
    int año;
    int cantidadArticulos;
    float subtotal;
    float iva;
    float descuento;
    float total;
    };

bool buscarProducto(int codigoBuscado, Producto &producto, int &posicion){

    ifstream archivo("productos.dat", ios::binary);

    if(!archivo){
        return false;
    }

    Producto temp;
    posicion = 0;

    while(archivo.read((char*)&temp, sizeof(Producto))){

        if(temp.codigo == codigoBuscado && temp.activo == true){
            producto = temp;
            archivo.close();
            return true;
        }

        posicion++;
    }

    archivo.close();

    return false;
}

void registrarProducto(){

    Producto p;
    ofstream archivo("productos.dat", ios::binary | ios::app);

    if(!archivo){
        cout << "Error al abrir archivo" << endl;
        return;
    }

    cout << "\nCodigo: ";
    cin >> p.codigo;

    cin.ignore();

    cout << "Nombre: ";
cin.getline(p.nombre,30);

try{

    cout << "Precio: ";
    cin >> p.precio;

    if(cin.fail()){
        throw 1;
    }

    if(p.precio <= 0){
        throw 2;
    }

}
catch(int x){

    cin.clear();
    cin.ignore(1000,'\n');

    if(x == 1){
        cout << "Debe ingresar numeros" << endl;
    }

    if(x == 2){
        cout << "El precio no puede ser negativo" << endl;
    }

    return;
}

try{

    cout << "Stock: ";
    cin >> p.stock;

    if(cin.fail()){
        throw 1;
    }

    if(p.stock < 0){
        throw 2;
    }

}
catch(int x){

    cin.clear();
    cin.ignore(1000,'\n');

    if(x == 1){
        cout << "Debe ingresar numeros" << endl;
    }

    if(x == 2){
        cout << "El stock no puede ser negativo" << endl;
    }

    return;
}

    p.vendidos = 0;
    p.activo = true;

    archivo.write((char*)&p, sizeof(Producto));
    archivo.close();
    cout << "Producto registrado correctamente" << endl;
}

void listarProductos(){

    ifstream archivo("productos.dat", ios::binary);

    if(!archivo){
        cout << "No existe archivo" << endl;
        return;
    }

    Producto p;

    cout << "\n====== PRODUCTOS ======" << endl;
    while(archivo.read((char*)&p, sizeof(Producto))){

        if(p.activo == true){
            cout << "\nCodigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            cout << "Vendidos: " << p.vendidos << endl;
        }
    }

    archivo.close();
}

void buscarProductoCodigo(){

    int codigo;

    cout << "Ingrese codigo: ";
    cin >> codigo;

    Producto p;
    int posicion;

    bool encontrado = buscarProducto(codigo, p, posicion);

    if(encontrado){
        cout << "\nProducto encontrado" << endl;
        cout << "Nombre: " << p.nombre << endl;
        cout << "Precio: Q" << p.precio << endl;
        cout << "Stock: " << p.stock << endl;
    }
    else{
        cout << "Producto no encontrado" << endl;
    }
}

void buscarProductoNombre(){
    char nombreBuscado[30];
    cin.ignore();
    cout << "Ingrese nombre: ";
    cin.getline(nombreBuscado,30);

    ifstream archivo("productos.dat", ios::binary);

    Producto p;
    bool encontrado = false;

    while(archivo.read((char*)&p, sizeof(Producto))){
        if(strcmp(nombreBuscado, p.nombre) == 0 && p.activo == true){
            cout << "\nCodigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            encontrado = true;
        }
    }

    if(!encontrado){

        cout << "Producto no encontrado" << endl;
    }

    archivo.close();
}

void actualizarStock(){

    int codigo;
    int nuevoStock;
    cout << "Codigo producto: ";
    cin >> codigo;

    Producto p;
    int posicion;

    bool encontrado = buscarProducto(codigo, p, posicion);

    if(encontrado){
        try{
    cout << "Nuevo stock: ";
    cin >> nuevoStock;

    if(cin.fail()){
        throw 1;
    }

    if(nuevoStock < 0){
        throw 2;
    }

}
catch(int x){

    cin.clear();
    cin.ignore(1000,'\n');

    if(x == 1){
        cout << "Debe ingresar numeros" << endl;
    }

    if(x == 2){
        cout << "Stock invalido" << endl;
    }

    return;
}

p.stock = nuevoStock;

        fstream archivo("productos.dat", ios::binary | ios::in | ios::out);
        archivo.seekp(posicion * sizeof(Producto), ios::beg);
        archivo.write((char*)&p, sizeof(Producto));
        archivo.close();
        cout << "Stock actualizado" << endl;
    }
    else{
        cout << "Producto no encontrado" << endl;
    }
}

void modificarPrecio(){

    int codigo;
    float nuevoPrecio;

    cout << "Codigo: ";
    cin >> codigo;

    Producto p;
    int posicion;

    bool encontrado = buscarProducto(codigo, p, posicion);

    if(encontrado){
        try{

    cout << "Nuevo precio: ";
    cin >> nuevoPrecio;

    if(cin.fail()){
        throw 1;
    }

    if(nuevoPrecio <= 0){
        throw 2;
    }

}
catch(int x){

    cin.clear();
    cin.ignore(1000,'\n');

    if(x == 1){
        cout << "Debe ingresar numeros" << endl;
    }

    if(x == 2){
        cout << "Precio invalido" << endl;
    }

    return;
}

p.precio = nuevoPrecio;

        fstream archivo("productos.dat", ios::binary | ios::in | ios::out);
        archivo.seekp(posicion * sizeof(Producto), ios::beg);
        archivo.write((char*)&p, sizeof(Producto));
        archivo.close();
        cout << "Precio actualizado" << endl;
    }
    else{
        cout << "Producto no encontrado" << endl;
    }
}

void eliminarProducto(){

    int codigo;
    cout << "Codigo a eliminar: ";
    cin >> codigo;

    Producto p;
    int posicion;

    bool encontrado = buscarProducto(codigo, p, posicion);

    if(encontrado){
        p.activo = false;

        fstream archivo("productos.dat", ios::binary | ios::in | ios::out);
        archivo.seekp(posicion * sizeof(Producto), ios::beg);
        archivo.write((char*)&p, sizeof(Producto));
        archivo.close();
        cout << "Producto eliminado" << endl;
    }
    else{
        cout << "Producto no encontrado" << endl;
    }
}

float calcularIVA(float subtotal){

    return subtotal * 0.12;
}

float calcularDescuento(float subtotal, int cantidadArticulos){

    float descuento = 0;

    if(subtotal > 500){

        descuento += subtotal * 0.05;
    }

    if(cantidadArticulos % 5 == 0){

        descuento += 25;
    }

    return descuento;
}

void crearVenta(){

    Venta venta;

    venta.subtotal = 0;
    venta.cantidadArticulos = 0;

    int codigo;
    int cantidad;
    char opcion;

    cout << "\nNumero venta: ";
    cin >> venta.numeroVenta;

    cout << "Dia: ";
    cin >> venta.dia;

    try{

    cout << "Mes: ";
    cin >> venta.mes;

    if(cin.fail()){
        throw 1;
    }

    if(venta.mes < 1 || venta.mes > 12){
        throw 2;
    }

}
catch(int x){

    cin.clear();
    cin.ignore(1000,'\n');

    if(x == 1){
        cout << "Debe ingresar numeros" << endl;
    }

    if(x == 2){
        cout << "Mes invalido" << endl;
    }

    return;
}

    cout << "Año: ";
    cin >> venta.año;
    
    do{

        Producto producto;
        int posicion;

        cout << "\nCodigo producto: ";
        cin >> codigo;

        bool encontrado = buscarProducto(
            codigo,
            producto,
            posicion
        );

        if(!encontrado){

            cout << "Producto no encontrado" << endl;
        }
        else{
            cout << "Nombre: " << producto.nombre << endl;
            cout << "Precio: Q" << producto.precio << endl;
            cout << "Stock: " << producto.stock << endl;
            try{
            cout << "Cantidad: ";
            cin >> cantidad;

    if(cin.fail()){
        throw 1;
    }

    if(cantidad <= 0){
        throw 2;
    }

}
catch(int x){

    cin.clear();
    cin.ignore(1000,'\n');

    if(x == 1){
        cout << "Debe ingresar numeros" << endl;
    }

    if(x == 2){
        cout << "Cantidad invalida" << endl;
    }

    continue;
}
            if(cantidad > producto.stock){

                cout << "Stock insuficiente" << endl;
            }
            else{

                DetalleVenta detalle;
                detalle.codigoProducto = producto.codigo;
                strcpy(detalle.nombre, producto.nombre);
                detalle.cantidad = cantidad;
                detalle.precioUnitario = producto.precio;
                detalle.subtotal =
                    cantidad * producto.precio;

                ofstream detalleArchivo(
                    "detalleVentas.dat",
                    ios::binary | ios::app
                );

                detalleArchivo.write(
                    (char*)&detalle,
                    sizeof(DetalleVenta)
                );

                detalleArchivo.close();
                venta.subtotal += detalle.subtotal;
                venta.cantidadArticulos += cantidad;
                producto.stock -= cantidad;
                producto.vendidos += cantidad;

                fstream archivo(
                    "productos.dat",
                    ios::binary | ios::in | ios::out
                );

                archivo.seekp(
                    posicion * sizeof(Producto),
                    ios::beg
                );

                archivo.write(
                    (char*)&producto,
                    sizeof(Producto)
                );

                archivo.close();

                cout << "Producto agregado" << endl;
            }
        }

        cout << "\nAgregar otro producto? (s/n): ";
        cin >> opcion;

    }while(opcion == 's' || opcion == 'S');

    venta.iva = calcularIVA(venta.subtotal);
    venta.descuento = calcularDescuento(
        venta.subtotal,
        venta.cantidadArticulos
    );

    venta.total =
        venta.subtotal +
        venta.iva -
        venta.descuento;

    venta.total =
        round(venta.total * 100) / 100;

    ofstream archivoVenta(
        "ventas.dat",
        ios::binary | ios::app
    );

    archivoVenta.write(
        (char*)&venta,
        sizeof(Venta)
    );

    archivoVenta.close();

    cout << "\n====== FACTURA ======" << endl;
    cout << "Subtotal: Q" << venta.subtotal << endl;
    cout << "IVA: Q" << venta.iva << endl;
    cout << "Descuento: Q" << venta.descuento << endl;
    cout << "Total: Q" << venta.total << endl;
}
void ordenarPrecioAscendente(){

    Producto productos[100];
    int n = 0;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&productos[n], sizeof(Producto))){
        if(productos[n].activo)
            n++;
    }

    archivo.close();

    for(int i=0; i<n-1; i++){

        for(int j=0; j<n-1-i; j++){

            if(productos[j].precio > productos[j+1].precio){

                Producto aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
        }
    }

    cout << "\n=== PRECIO ASCENDENTE ===\n";

    for(int i=0; i<n; i++){

        cout << productos[i].codigo << " - "
             << productos[i].nombre << " - Q"
             << productos[i].precio << endl;
    }
}
void ordenarPrecioDescendente(){

    Producto productos[100];
    int n = 0;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&productos[n], sizeof(Producto))){
        if(productos[n].activo)
            n++;
    }

    archivo.close();

    for(int i=0; i<n-1; i++){

        for(int j=0; j<n-1-i; j++){

            if(productos[j].precio < productos[j+1].precio){

                Producto aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
        }
    }

    cout << "\n=== PRECIO DESCENDENTE ===\n";

    for(int i=0; i<n; i++){

        cout << productos[i].codigo << " - "
             << productos[i].nombre << " - Q"
             << productos[i].precio << endl;
    }
}

void ordenarStockAscendente(){

    Producto productos[100];
    int n = 0;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&productos[n], sizeof(Producto))){
        if(productos[n].activo)
            n++;
    }

    archivo.close();

    for(int i=0; i<n-1; i++){

        for(int j=0; j<n-1-i; j++){

            if(productos[j].stock > productos[j+1].stock){

                Producto aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
        }
    }

    cout << "\n=== STOCK ASCENDENTE ===\n";

    for(int i=0; i<n; i++){

        cout << productos[i].nombre
             << " - Stock: "
             << productos[i].stock << endl;
    }
}

void ordenarStockDescendente(){

    Producto productos[100];
    int n = 0;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&productos[n], sizeof(Producto))){
        if(productos[n].activo)
            n++;
    }

    archivo.close();

    for(int i=0; i<n-1; i++){

        for(int j=0; j<n-1-i; j++){

            if(productos[j].stock < productos[j+1].stock){

                Producto aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
        }
    }

    cout << "\n=== STOCK DESCENDENTE ===\n";

    for(int i=0; i<n; i++){

        cout << productos[i].nombre
             << " - Stock: "
             << productos[i].stock << endl;
    }
}
void ordenarPorVentas(){

    Producto productos[100];
    int n = 0;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&productos[n], sizeof(Producto))){
        if(productos[n].activo)
            n++;
    }

    archivo.close();

    for(int i=0; i<n-1; i++){

        for(int j=0; j<n-1-i; j++){

            if(productos[j].vendidos < productos[j+1].vendidos){

                Producto aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
        }
    }

    cout << "\n=== VENTAS ACUMULADAS ===\n";

    for(int i=0; i<n; i++){

        cout << productos[i].nombre
             << " - Vendidos: "
             << productos[i].vendidos << endl;
    }

}
void productosMenorStock(){

    ifstream archivo("productos.dat", ios::binary);

    Producto p;
    Producto menor;
    bool primero = true;

    while(archivo.read((char*)&p, sizeof(Producto))){

        if(p.activo){

            if(primero){

                menor = p;
                primero = false;
            }
            else if(p.stock < menor.stock){

                menor = p;
            }
        }
    }

    archivo.close();

    cout << "\n===== PRODUCTO CON MENOR STOCK =====" << endl;
    cout << "Codigo: " << menor.codigo << endl;
    cout << "Nombre: " << menor.nombre << endl;
    cout << "Stock: " << menor.stock << endl;
}
void productosMasVendidos(){

    ifstream archivo("productos.dat", ios::binary);

    Producto p;
    Producto mayor;
    bool primero = true;

    while(archivo.read((char*)&p, sizeof(Producto))){

        if(p.activo){

            if(primero){

                mayor = p;
                primero = false;
            }
            else if(p.vendidos > mayor.vendidos){

                mayor = p;
            }
        }
    }

    archivo.close();

    cout << "\n===== PRODUCTO MAS VENDIDO =====" << endl;
    cout << "Codigo: " << mayor.codigo << endl;
    cout << "Nombre: " << mayor.nombre << endl;
    cout << "Vendidos: " << mayor.vendidos << endl;
}
void ventasTotalesDia(){

    int diaBuscado;
    int mesBuscado;
    int añoBuscado;

    cout << "Dia: ";
    cin >> diaBuscado;

    cout << "Mes: ";
    cin >> mesBuscado;

    cout << "Año: ";
    cin >> añoBuscado;

    ifstream archivo("ventas.dat", ios::binary);

    Venta venta;

    float totalDia = 0;

    while(archivo.read((char*)&venta, sizeof(Venta))){

        if(venta.dia == diaBuscado &&
           venta.mes == mesBuscado &&
           venta.año == añoBuscado){

            totalDia += venta.total;
        }
    }

    archivo.close();

    cout << "\nVentas del dia: Q" << totalDia << endl;
}
void ventasPorMes(){

    float matriz[12][1] = {0};

    ifstream archivo("ventas.dat", ios::binary);

    Venta venta;

    while(archivo.read((char*)&venta, sizeof(Venta))){

        if(venta.mes >= 1 && venta.mes <= 12){

            matriz[venta.mes - 1][0] += venta.total;
        }
    }

    archivo.close();

    cout << "\n===== VENTAS POR MES =====" << endl;

    for(int i = 0; i < 12; i++){

        cout << "Mes " << i + 1
             << ": Q" << matriz[i][0]
             << endl;
    }
}
void exportarReporteTXT(){

    ifstream archivo("productos.dat", ios::binary);

    ofstream reporte("reporte.txt");

    Producto p;

    reporte << "====== REPORTE INVENTARIO ======\n\n";

    while(archivo.read((char*)&p, sizeof(Producto))){

        if(p.activo){

            reporte << "Codigo: " << p.codigo << endl;
            reporte << "Nombre: " << p.nombre << endl;
            reporte << "Precio: Q" << p.precio << endl;
            reporte << "Stock: " << p.stock << endl;
            reporte << "Vendidos: " << p.vendidos << endl;
            reporte << "------------------------\n";
        }
    }

    archivo.close();
    reporte.close();

    cout << "Reporte exportado a reporte.txt" << endl;
}
void reiniciarInventario(){

    char opcion;

    cout << "Desea eliminar todos los datos? (s/n): ";
    cin >> opcion;

    if(opcion == 's' || opcion == 'S'){

        ofstream archivo1("productos.dat", ios::binary | ios::trunc);
        ofstream archivo2("ventas.dat", ios::binary | ios::trunc);
        ofstream archivo3("detalleVentas.dat", ios::binary | ios::trunc);

        archivo1.close();
        archivo2.close();
        archivo3.close();

        cout << "Inventario reiniciado correctamente" << endl;
    }
    else{

        cout << "Operacion cancelada" << endl;
    }
}
void estadisticasGenerales(){

    ifstream archivo("productos.dat", ios::binary);

    Producto p;

    int totalProductos = 0;
    int totalStock = 0;
    int totalVendidos = 0;

    float valorInventario = 0;

    while(archivo.read((char*)&p, sizeof(Producto))){

        if(p.activo){

            totalProductos++;
            totalStock += p.stock;
            totalVendidos += p.vendidos;
            valorInventario += p.stock * p.precio;
        }
    }

    archivo.close();

    cout << "\n===== ESTADISTICAS =====" << endl;

    cout << "Productos activos: "
         << totalProductos << endl;

    cout << "Stock total: "
         << totalStock << endl;

    cout << "Productos vendidos: "
         << totalVendidos << endl;

    cout << "Valor inventario: Q"
         << valorInventario << endl;
}

void menu(){

    int op;

    do{

        cout << "\n====== SISTEMA ======" << endl;
        cout << "1. Registrar producto" << endl;
        cout << "2. Listar productos" << endl;
        cout << "3. Buscar por codigo" << endl;
        cout << "4. Buscar por nombre" << endl;
        cout << "5. Actualizar stock" << endl;
        cout << "6. Modificar precio" << endl;
        cout << "7. Eliminar producto" << endl;
        cout << "8. Crear venta" << endl;
        cout << "9. Producto menor stock" << endl;
        cout << "10. Producto mas vendido" << endl;
        cout << "11. Ventas del dia" << endl;
        cout << "12. Ventas por mes" << endl;
        cout << "13. Precio ascendente" << endl;
        cout << "14. Precio descendente" << endl;
        cout << "15. Stock ascendente" << endl;
        cout << "16. Stock descendente" << endl;
        cout << "17. Ventas acumuladas" << endl;
        cout << "18. Exportar reporte TXT" << endl;
        cout << "19. Reiniciar inventario" << endl;
        cout << "20. Estadisticas generales" << endl;
        cout << "21. Salir" << endl;
        cout << "Opcion: ";
        cin >> op;

        switch(op){

            case 1:
                registrarProducto();
                break;

            case 2:
                listarProductos();
                break;

            case 3:
                buscarProductoCodigo();
                break;

            case 4:
                buscarProductoNombre();
                break;

            case 5:
                actualizarStock();
                break;

            case 6:
                modificarPrecio();
                break;

            case 7:
                eliminarProducto();
                break;

            case 8:
                crearVenta();
                break;

            case 9:
                productosMenorStock();
                break;

            case 10:
                productosMasVendidos();
                break;

            case 11:
                ventasTotalesDia();
                break;

            case 12:
                ventasPorMes();
                break;

            case 13:
                ordenarPrecioAscendente();
                break;

            case 14:
                ordenarPrecioDescendente();
                break;

            case 15:
                ordenarStockAscendente();
                break;

            case 16:
                ordenarStockDescendente();
                break;

            case 17:
                ordenarPorVentas();
                break;

            case 18:
                exportarReporteTXT();
                break;

            case 19:
                reiniciarInventario();
                break;

            case 20:
                estadisticasGenerales();
                break;

            case 21:
                cout << "Saliendo..." << endl;
                break;   
        
            default:
                cout << "Opcion invalida" << endl;
        }

    }while(op != 21);
}
int main(){

    menu();

    return 0;
}