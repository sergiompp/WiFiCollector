#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/**Funci�n********************************************************************

  Resumen      Crea el struct para la celda (punto de acceso) WiFi

  Descripci�n  Crea la estructura de los puntos de acceso con sus parametros

  Par�metros    int identificador - Identificador de la celda WiFi
				char MAC[18] - Direcci�n MAC
				char ESSID[35] - Nombre de la red.
				enum modo{AUTO, AD_HOC, MANAGED, MASTER, REPEATER, SECONDARY, 
				MONITOR, UNKNOWN} modo - Fomra de funcionamiento de la red.
				int canal - Canal donde se encuentra la red.
				enum cifrado{OFF,ON} cifrado - Si la red se encuentra cifrada.
				int calidad_medida - Nivel de Calidad Medida de la red.
				int calidad_maxima - Nivel Maximo de Calidad de la red.
				float frecuencia - Frecuencia de la red.
				int nivelSenal - Nivel de Se�al de la red (-dBm).

******************************************************************************/
//0. STRUCT WiFi


struct PuntoDeAcceso{

	int identificador;
	char MAC[18];
	char ESSID[35];
	enum modo{AUTO, AD_HOC, MANAGED, MASTER, REPEATER, SECONDARY, MONITOR, UNKNOWN} modo;
	int canal;
	enum cifrado{OFF,ON} cifrado;
	int calidad_medida;
	int calidad_maxima;
	float frecuencia;
	int nivelSenal;
};

/**Funci�n********************************************************************

  Resumen      Crea el struct para la lista

  Descripci�n  Crea la estructura de la lista con el struct con parametros y el
  				puntero al siguiente nodo de la lista

  Par�metros    struct PuntoDeAcceso pda - Nodo de la lista con los par�metros
				struct Lista *sig - Puntero al siguente nodo de la lista

******************************************************************************/
struct Lista{
	struct PuntoDeAcceso pda;
	struct Lista *sig;
};



