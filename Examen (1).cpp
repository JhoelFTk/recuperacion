#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include <stack>
#include <iostream>
#include<set>
#include"lib/Color.h"
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
using namespace std;

// Definir constantes globales
#define color SetConsoleTextAttribute  
const string JTNOMBRE_COMPLETO = "Jhoel Wladimir Tulcan Caicedo";
const string JTCEDULA = "1725417545";


// Definir estructura Coordenada
struct jtCoordenada {
    int capacidadBelica;
    string geolocalizacion;
    string detalleArsenal;
    jtCoordenada* siguiente;
};

// Crear función para agregar una coordenada a una pila
void jtagregarCoordenada(jtCoordenada** pila, int capacidadBelica, string geolocalizacion, string detalleArsenal) {
    jtCoordenada* nuevaCoordenada = new jtCoordenada;
    nuevaCoordenada->capacidadBelica = capacidadBelica;
    nuevaCoordenada->geolocalizacion = geolocalizacion;
    nuevaCoordenada->detalleArsenal = detalleArsenal;
    nuevaCoordenada->siguiente = *pila;
    *pila = nuevaCoordenada;

  
}


// Crear función para guardar la pila de coordenadas en un archivo de texto
void jtguardarCoordenadas(jtCoordenada* pila) {
    ofstream archivo("coordenadas.txt");
    archivo << "Cap, Geo, Tipo Arsenal" << endl;
    while (pila != nullptr) {
        archivo << pila->capacidadBelica << ", " << pila->geolocalizacion << ", " << pila->detalleArsenal << endl;
        pila = pila->siguiente;
    }
    archivo.close();
}

void jtleerCoordenadas(jtCoordenada** pila) {
    ifstream archivo("coordenadas.txt");
    string linea;
    getline(archivo, linea); // saltar línea de encabezado
    while (getline(archivo, linea)) {

int jtind =0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string jtc= "\\|/-|";
    for(int jti=0; jti<= 100; jti++)
    {  
        //updateBar(i);
        if(jti % 4 ==0)
            jtind =0;
         color(hConsole, 2); 
        cout << "       \r" << jtc[jtind++]  
                << " " << jti << "%";
        usleep(10000);
    }

        //cout << endl;
        stringstream ss(linea);
        string capacidadBelicaStr, geolocalizacion, detalleArsenal;
        cout << "\t";
        getline(ss, capacidadBelicaStr, ',');
        getline(ss, geolocalizacion, ',');
        getline(ss, detalleArsenal);
        
        try {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            int capacidadBelica = stoi(capacidadBelicaStr);
            jtagregarCoordenada(pila, capacidadBelica, geolocalizacion.substr(1), detalleArsenal.substr(1));
            cout << "\033[32m" << linea << "\033[0m" << endl;
            color(hConsole, 2); 
           cout << "PUSH" << endl;
        } catch (...) {
            cout << "\033[31mError: Cordenada Invalida\033[0m" << endl;
        }
    }
}

void jtpresentarDatos(jtCoordenada* pila) {
    // Presenta el nombre
    string nombre = JTNOMBRE_COMPLETO;
    for (int i = 0; i < nombre.length(); i++) {
        if (i == 0 || nombre[i - 1] == ' ') {
            nombre[i] = toupper(nombre[i]);
        } else {
            nombre[i] = tolower(nombre[i]);
        }
    }
    cout << "Developer-Nombre: " << nombre << endl;
    cout << "Developer-Cedula: " << JTCEDULA << endl;

    // Calcular y presentar datos de pila
    int capacidadBelicaTotal = 0;
    int coordenadaTotal = 0;
    while (pila != nullptr) {
        capacidadBelicaTotal += pila->capacidadBelica;
        coordenadaTotal++;
        pila = pila->siguiente;
    }
    cout << "Capacidad Belica: " << capacidadBelicaTotal << endl;
    cout << "Coordenada-Total: " << coordenadaTotal << endl;
}

void jtdesapilarCoordenadas(jtCoordenada** pila) {
    ofstream archivo("tulcanjhoelCoord.txt");
    ofstream archivoBomba("tulcanjhoelCoordBomba.txt");
    while (*pila != nullptr) {
        jtCoordenada* temp = *pila;
        string bomba = "";
        if (temp->detalleArsenal == "BOMBA") {
            bomba = " BOMBA";
            cout << "(POP) " << temp->geolocalizacion << "." << temp->capacidadBelica << " { " << temp->detalleArsenal << bomba << " }" << endl;
            archivoBomba << "(POP) " << temp->geolocalizacion << "." << temp->capacidadBelica << " { " << temp->detalleArsenal << bomba <<" }"  "\n";
        }
        else {
            cout<< "(POP) "<<temp->geolocalizacion<<"."<<temp->capacidadBelica<<" { "<<temp->detalleArsenal<<bomba<<" }"<<endl;
        }
        
        archivo<<"(POP) "<<temp->geolocalizacion<<"."<<temp->capacidadBelica<<" { "<<temp->detalleArsenal<<bomba<<" }"<<"\n";
        
        *pila = (*pila)->siguiente;
        delete temp;
    }
    cout<<"<< PILA VACIA >>"<<endl;
    archivo.close();
    archivoBomba.close();
}

void getCoordenadas() 
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string str;
    fstream f;
    cout << "[+]Apilando coordenadas ... " << endl;
    f.open("datos.txt", ios_base::in); 
    if ( f.is_open() ) 
          while( !f.eof() )
          {
               getline( f, str );
               cout<<str<<endl;
          } 
    else
          color(hConsole, 4); 
          cout << "Error: Cap, Geo, Tipo Arsenal" << endl;
    f.close();
}



int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    getCoordenadas();

    // Inicializar pila de coordenadas
   jtCoordenada* pilaCoordenadas = nullptr;

    // Agregar coordenadas a la pila
    jtagregarCoordenada(&pilaCoordenadas, 1, "GPS1", "bc");
    jtagregarCoordenada(&pilaCoordenadas, 7, "GPS7", "aaabbct");
    jtagregarCoordenada(&pilaCoordenadas, 2, "GPS2", "ac");
    jtagregarCoordenada(&pilaCoordenadas, 5, "GPS5", "bct");
    jtagregarCoordenada(&pilaCoordenadas, 4, "GPS4", "acd");
    jtagregarCoordenada(&pilaCoordenadas, 1, "GPS1", "bc");
    jtagregarCoordenada(&pilaCoordenadas, 7, "GPS7", "aaabbct");
    jtagregarCoordenada(&pilaCoordenadas, 5, "GPS5", "bct");
    jtagregarCoordenada(&pilaCoordenadas, 4, "GPS4", "acd");
    jtagregarCoordenada(&pilaCoordenadas, 5, "GPS1", "bct");


    // Guardar la pila de coordenadas en un archivo de texto
    jtguardarCoordenadas(pilaCoordenadas);

    //leer las coordenadas del archivo de texto
    jtleerCoordenadas(&pilaCoordenadas);
 color(hConsole, 8); 
 system("pause");
 system("cls");
    //Presentar los datos 
    jtpresentarDatos(pilaCoordenadas);
 system("pause");
 system("cls");
   //Mostrar datos 
    jtdesapilarCoordenadas(&pilaCoordenadas);
  
   
    // Liberar memoria de la pila
    while (pilaCoordenadas != nullptr) {
        jtCoordenada* siguiente = pilaCoordenadas->siguiente;
        delete pilaCoordenadas;
        pilaCoordenadas = siguiente;
    }

    return 0;
}