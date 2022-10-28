#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CVehiculo
{
    private:
        string placa, marca;
        int fabricacion;
    public:
        CVehiculo(string placa, string modelo, int fabricacion);
        ~CVehiculo(){};
        string getPlaca(){return this->placa;};
        string getMarca(){return this->marca;};
        int getFabricacion(){return this->fabricacion;};
};

CVehiculo::CVehiculo(string placa, string modelo, int fabricacion)
{
    this->fabricacion = fabricacion;
    this->marca = modelo;
    this->placa = placa;
}


class CTaxi
{
    private:
        string nombre;
        vector<CVehiculo*> vehiculos;
    public:
        CTaxi(string nombre){this->nombre = nombre;};
        ~CTaxi(){};
        string getNombre(){return this->nombre;};
        int getCantidadVehiculos(){return this->vehiculos.size();};
        CVehiculo getVehiculo(int pos){return *vehiculos[pos];};
        void adicionarVehiculo(CVehiculo* vehiculo){this->vehiculos.push_back(vehiculo);};
};


int main()
{
    int n, year;
    string nombre, placa, marca;
    getline(cin, nombre);
    CTaxi* empresa = new CTaxi(nombre);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> placa;
        cin >> marca;
        cin >> year;
        CVehiculo* taxi = new CVehiculo(placa, marca, year);
        empresa->adicionarVehiculo(taxi);
    }

    // mostrar entidades guardadas
    n = empresa->getCantidadVehiculos();
    for (size_t i = 0; i < n; i++)
    {
        // codigo aqui
    }
    
    return 0;
}