#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

struct Tiempo{
	
	public:
		
		int horas;
		int minutos;
		int segundos;
	
};

		bool EsPosterior(Tiempo &t1, Tiempo &t2){
			
			if (t1.horas>t2.horas){
				return true;
				
			} else if (t1.horas==t2.horas) {
				
				if (t1.minutos>t2.minutos){
					return true;
					
				} else if (t1.minutos==t2.minutos){
					return (t1.segundos==t2.segundos);
					
				} else {
					return false;
				}
				
			} else {
				return false;
			}
		}
		
		bool SonIguales(Tiempo &t1, Tiempo &t2){
			return (t1.horas==t2.horas && t1.minutos==t2.minutos && t1.segundos==t2.segundos);
		}
		
		void tiempoEnSegundos(Tiempo &t1){
			t1.segundos=(t1.horas*3600+t1.minutos*60+t1.segundos);
		}
		
		void segundosEnTiempo(Tiempo &t1, int _segundos){
			t1.segundos=_segundos;
			
			t1.horas=t1.segundos/3600;
			t1.minutos=(t1.segundos-t1.horas*3600) / 60;
			t1.segundos%= 60;
		}
		
		void calcularNuevoTiempo(Tiempo &t1, int _segundos){
			t1.segundos+=_segundos;
			
			if (t1.segundos>59){
				t1.minutos+=t1.segundos/60;
				t1.segundos%=60;
			}
			
			if (t1.minutos>59){
				t1.horas+=t1.minutos/60;
				t1.minutos%=60;
			}
			
			if (t1.horas>=24){
				t1.horas%=24;
			}
		}
		
		string toString(Tiempo &t1){ //Hay mucho follon pero es para que quede bonito
			string a_devolver=""; // es decir, que si es a las 5AM no me diga 5:8:9, sino 05:08:09
			
			if (t1.horas <= 9) {
		        a_devolver += '0' + to_string(t1.horas);
		    } else {
		        a_devolver += to_string(t1.horas);
		    }
		    a_devolver += ':';
		
		    if (t1.minutos <= 9) {
		        a_devolver += '0' + to_string(t1.minutos);
		    } else {
		        a_devolver += to_string(t1.minutos);
		    }
		    a_devolver += ':';
		
		    if (t1.segundos <= 9) {
		        a_devolver += '0' + to_string(t1.segundos);
		    } else {
		        a_devolver += to_string(t1.segundos);
		    }
			
			return a_devolver;
		}

struct Registro{
	
	public:
		
		Tiempo entrada;
		Tiempo salida;
		string matricula;
		const float LONG_TRAMO=17.45;
		const int VELOC_LIMITE=90;
	
};

		void copiarRegistro(Registro &a, Registro &b){
			a.entrada=b.entrada;
			a.salida=b.salida;
			a.matricula=b.matricula;
		}
		
		int tiempoEnTramo(Registro &reg){
			int tiempoEntrada = reg.entrada.horas*60 + reg.entrada.minutos;
		    int tiempoSalida = reg.salida.horas*60 + reg.salida.minutos;
		    return abs(tiempoEntrada-tiempoSalida);
		}
		
		double velocidadPromedio(Registro &reg){
			double espacio=reg.LONG_TRAMO;
			double tiempo=tiempoEnTramo(reg);
			return (espacio/tiempo)*60;
		}
		
		void corrigeRegistro(Registro &reg){
			
			if (reg.entrada.segundos>reg.salida.segundos){
				
				tiempoEnSegundos(reg.entrada);
				tiempoEnSegundos(reg.salida);
				
				Tiempo aux=reg.entrada;
				reg.entrada=reg.salida;
				reg.salida=aux;
				
				segundosEnTiempo(reg.entrada, reg.entrada.segundos);
				segundosEnTiempo(reg.salida, reg.salida.segundos);
			}
		}
		
		string controlVehiculo(Registro &reg){
			string mensaje="";
			
			if (velocidadPromedio(reg)>reg.VELOC_LIMITE){
				mensaje="Vehiculo matricula "+reg.matricula+", velocidad promedio "+to_string(velocidadPromedio(reg))+" km/h. MULTA";
				
			} else {
				mensaje="Vehiculo matricula "+reg.matricula+", velocidad promedio "+to_string(velocidadPromedio(reg))+" km/h.";
			}
			
			return mensaje;
		}
		
		string toString(Registro &reg){
			string a_devolver="";
			a_devolver=reg.matricula+", Entra: "+toString(reg.entrada)+" Sale: "+toString(reg.salida);
			
			return a_devolver;
		}
		
struct ControlDiario{
	
	public:
		
		static const int MAX=100;
		Registro conjunto[MAX];
		int util;
		
};

		void extraeDatos(ControlDiario control, ControlDiario &pasados, ControlDiario &no_pasados){
			int contadorp=0, contadornp=0;
			
			for (int i=0; i<control.util; i++){
				
				Registro reg=control.conjunto[i];
				
				if (velocidadPromedio(reg)>reg.VELOC_LIMITE){
					copiarRegistro(pasados.conjunto[contadorp],reg);
					contadorp++;
					
				} else {
					copiarRegistro(no_pasados.conjunto[contadornp],reg);
					contadornp++;
				}	
			}
			pasados.util=contadorp;
			no_pasados.util=contadornp;
		}
		
int main (){
	
	int num_vehiculos, contador=0, sege, segs;
	double porcen_exceso, porcen_sin, vel_promedio;
	ControlDiario control, pasados, no_pasados;
	
	cout << "Introduce el numero de vehiculos a registrar: " << endl;
	cin >> num_vehiculos;
	
	while (contador!=num_vehiculos){
		
		Registro reg;
		
		cout << "Introduce el tiempo de entrada (s): " << endl;
		cin >> sege;
		
		cout << "Introduce el tiempo de salida (s): " << endl;
		cin >> segs;
		
		cout << "Introduce la matricula del vehiculo: " << endl;
		cin >> reg.matricula;

		segundosEnTiempo(reg.entrada, sege);
		segundosEnTiempo(reg.salida, segs);
		
		copiarRegistro(control.conjunto[contador],reg);
		control.util++;
		
		contador++;
	}
	
	extraeDatos(control, pasados, no_pasados);
	
	cout << endl;
	cout << "\033[1;33m-------------------------------------------------------\033[0m" << endl;
    cout << "\033[1;33m           Registro de Velocidades de Vehiculos        \033[0m" << endl;
    cout << "\033[1;33m-------------------------------------------------------\033[0m" << endl;
	cout << endl;
	cout << "\033[1;34m              Made by Marco Calvo Jimenez              \033[0m" << endl << endl << endl << endl;
	
	cout << "\033[1;31m---------- Vehiculos con exceso de velocidad ----------\033[0m" << endl;
	cout << endl << endl;
	
	for (int i=0; i<control.util; i++){
		Registro reg=control.conjunto[i];
		vel_promedio+=velocidadPromedio(reg);
	}
	
	vel_promedio/=num_vehiculos;
	porcen_exceso=((pasados.util*1.0)/num_vehiculos)*100;
	porcen_sin=100-porcen_exceso;
	
	if (pasados.util!=0){
	
	    for (int i=0; i<pasados.util; i++){
	        Registro reg;
	        copiarRegistro(reg, pasados.conjunto[i]);
	        cout << "Vehiculo: " << reg.matricula << endl;
	        cout << "Hora de Entrada:   " << toString(reg.entrada) << "   Hora de Salida:   " << toString(reg.salida) <<"   Velocidad Promedio:  " << velocidadPromedio(reg) << " km/h" << endl;
	        cout << endl;
	    }
    
    } else {
		cout << "          No se ha registrado ningun vehiculo." << endl << endl;
	}
    
	cout << endl;
	
    cout << "\033[1;32m---------- Vehiculos sin exceso de velocidad ----------\033[0m" << endl;
    cout << endl << endl;
    	
    if (no_pasados.util!=0){
    	
	    for (int i=0; i<no_pasados.util; i++){
		    Registro reg;
		    copiarRegistro(reg,no_pasados.conjunto[i]);
		    cout <<  "Vehiculo: " << reg.matricula << endl;
		    cout << "Hora de Entrada:   " << toString(reg.entrada) << "   Hora de Salida:   " << toString(reg.salida) << "   Velocidad Promedio:  " << velocidadPromedio(reg) << " km/h" <<endl;
		    cout << endl;
		}
	
	} else {
		cout << "          No se ha registrado ningun vehiculo." << endl << endl;
	}
	
    cout << endl;
    cout << "\033[1;33m-------------------------------------------------------\033[0m" << endl;
    cout << "\033[1;33m                 Estadisticas Generales                \033[0m" << endl;
    cout << "\033[1;33m-------------------------------------------------------\033[0m" << endl <<  endl;
    cout << "Total de Vehiculos Registrados: " << num_vehiculos << endl << endl;
    cout << "Total de Vehiculos Excedidos: " << pasados.util << endl << endl;
    cout << "Total de Vehiculos sin Exceder: " << no_pasados.util << endl << endl;
    cout << "Velocidad Promedio de todos los Vehiculos: " << vel_promedio << " km/h" << endl << endl;
    cout << "Porcentaje de Vehiculos sin Exceso de Velocidad: " << porcen_sin << endl << endl;
    cout << "Porcentaje de Vehiculos con Exceso de Velocidad: " << porcen_exceso << endl;
    
	return 0;
	
}
