/**CFile***********************************************************************

  FileName    wificollector_collect.c

  Synopsis    Make an auxiliar struct and copy in all information
  			  that can copy from the files .txt

  Description Ask for the list and identifier of the cell that will be copied 
  			  into the structure that will be created
  			  Return the list with all file's information about WiFi cells.

  SeeAlso     structWifi

  Author      Daniel De Vega 
  			  Sergio M. Pérez

  Copyright   [Copyright (c) 2019 Carlos III University of Madrid
  All rights reserved.

  Permission is hereby granted, without written agreement and without license
  or royalty fees, to use, copy, modify, and distribute this software and its
  documentation for any purpose, provided that the above copyright notice and
  the following two paragraphs appear in all copies of this software.

  IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY 
  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING 
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE CARLOS III
  UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO 
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/
//2. COLLECT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "data_read.h"
#include "data_read_L.h"
#include "data_read_double.h"

#include "structWifi.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/
	
/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/

void detectarEOF(){
	while(!feof){
	}
	
	if(!feof==1){
		printf("\n\n\nCTRL + D detectado!!\n\n\n");
		printf("\n\n\nCerrando....\n\n\n");
		sleep(2);
		
	}
	
}

void imprimirModo(int modo){
	switch(modo){
		case 0:
			printf("Auto\n");
			break;
		case 1:
			printf("Ad_hoc\n");
			break;
		case 2:
			printf("Managed\n");
			break;
		case 3:
			printf("Master\n");
			break;
		case 4:
			printf("Repeater\n");
			break;
		case 5:
			printf("Secondary\n");
			break;
		case 6:
			printf("Monitor\n");
			break;
		case 7:
			printf("Unknown\n");
			break;
		default:
			printf("Error\n");	
			break;
	}
}

struct Lista *collectWifi(struct Lista *lista, int id){
	//Declaración de Auxiliares
	FILE *fichero;
  
    //Declaración Constantes
    const char separador[2] = " ";
	char *token;
	char *linea = NULL;
	
	char buffer[2048]; // Buffer to store data
	char cadena[1024]; 
	char cadenaMAC[18];
	char cadenaESSID[35];
	char *eptr = malloc(sizeof(char *));
	char *pEnd = malloc(sizeof(char *));
	int identificador=0;
	long int num = 0;
	float fnum = 0.0f;
	int count=0;
	int opcionModo = 0;
    int lineaLeida = 0;
		

	//Lectura de Fichero Seleccionado		
    int numFichero = id;
    char nombreFicheroSeleccionado[13];
    sprintf(nombreFicheroSeleccionado,"info_cell_%i.txt", numFichero);
	fichero = fopen(nombreFicheroSeleccionado,"r");
	printf("El archivo seleccionado es el: %s",nombreFicheroSeleccionado);
	
	pthread_t hilo1;
	
	pthread_create(&hilo1, NULL, (void*) detectarEOF, NULL);
	pthread_join(hilo1, NULL);

	
	//Apertura de Fichero
	if(fichero==NULL){
		#ifdef DEBUG
		printf("Error en la lectura del fichero:  %c", fichero);
		#endif
	} else {
	//Lectura de Fichero 
		
		#ifdef DEBUG
		printf("\n\nCOLECTANDO RED WIFI...\n");
		printf("LEYENDO DEL ARCHIVO....\n\n"); 
		#endif
		
		while(feof(fichero)==0)
		{
			char *lineaRecorrida=0;
		    struct Lista *aux = 0; 
		    lineaLeida =0;
			do{
				char* leido = fgets(cadena, 1024,fichero);
				//Si el fichero tiene algo a leer, entra. Si no, es un error
				if(leido != NULL){	
					//Lectura de fichero linea a linea (max. 9)
					switch(lineaLeida){
						case 0:
					 		//IDENTIFICADOR CELDA
					 		aux = (struct Lista*)malloc(sizeof(struct Lista));
					 		strtok(cadena, " ");
					 		token = strtok(NULL, " ");
					 		num = strtol(token, &eptr, 10);
					 	
					 		aux->pda.identificador = num; 
					 		#ifdef DEBUG
							printf("Id Leido: %d\n",aux->pda.identificador);
							#endif
					 			
							break;
						
						case 1:
							//DIRECCION MAC
							
						   	strncpy(cadenaMAC, cadena+sizeof("ddress: "), 17);
						   	cadenaMAC[17] = '\0';
						   	
							strcpy(aux->pda.MAC, cadenaMAC);
							#ifdef DEBUG
							printf("MAC Leida: %s\n", aux->pda.MAC);
							#endif
								
							break;
					 	
						case 2:
					 		//ESSID
					 		strtok(cadena, "\"");
					 		token = strtok(NULL, "\"");
					 	   	
					 		strcpy(aux->pda.ESSID, token);	
							#ifdef DEBUG	
							printf("ESSID Leido: %s\n", aux->pda.ESSID);
							#endif
								
							break;
							
						case 3:
							//MODO
							
							strtok(cadena, ":");
					 		token = strtok(NULL, ":\n");
					 		

							if(strcmp("Auto", token)==0){
					 		//	opcionModo = 0;
								aux->pda.modo = AUTO;
							} else if(strcmp("Ad_hoc", token)==0){
					 		//	opcionModo = 1;
								aux->pda.modo = AD_HOC;
							} else if(strcmp("Managed", token)==0){
					 		//	opcionModo = 2;
								aux->pda.modo = MANAGED;
							} else if(strcmp("Master", token)==0){
							//	opcionModo = 3;
								aux->pda.modo = MASTER;
							} else if(strcmp("Repeater", token)==0){
					 		//	opcionModo = 4;
								aux->pda.modo = REPEATER;
							} else if(strcmp("Secondary", token)==0){
					 		//	opcionModo = 5;
								aux->pda.modo = SECONDARY;
							} else if(strcmp("Monitor", token)==0){
					 		//	opcionModo = 6;
								aux->pda.modo = MONITOR;
							} else if(strcmp("Unknown", token)==0){
					 		//	opcionModo = 7;
								aux->pda.modo = UNKNOWN;
							}
						
							#ifdef DEBUG	
							printf("Modo Leido: %d\n", aux->pda.modo);
							#endif
								
					 		break;
						
						case 4:
							//Canal
							
							strtok(cadena, ":");
					 		token = strtok(NULL, ":");
					 		num = strtol(token, &eptr, 10);
					 		
					 		aux->pda.canal = num;
							
							#ifdef DEBUG	
							printf("Canal Leido: %d\n", aux->pda.canal);
							#endif
								
					 		break;
						case 5:
							//Encriptación
								
							strtok(cadena, ":");
					 		token = strtok(NULL, " \n");
								
					 		if(strcmp("on", token)==0){
					 			aux->pda.cifrado = ON;	
							} else if (strcmp("off", token)==0){
								aux->pda.cifrado = OFF;
							}
							
							#ifdef DEBUG
							printf("Cifrado Leido: %d\n", aux->pda.cifrado);
							#endif
								
							break;
						case 6:
							//CALIDAD
							
							strtok(cadena, "=");
							token = strtok(NULL, "/");
							num = strtol(token, &eptr, 10);
							
							aux->pda.calidad_medida = num;
							num = 0;
							
							token = strtok(NULL, " ");
							num = strtol(token, &eptr, 10);
							aux->pda.calidad_maxima = num;
							
							#ifdef DEBUG
							printf("Calidad Leida: %d / %d\n", aux->pda.calidad_medida, aux->pda.calidad_maxima);
							#endif
																					
					 		break;
						case 7:
							//FRECUENCIA
								
							strtok(cadena,":");
							token = strtok(NULL," \n");
							fnum = atof(token);
							aux->pda.frecuencia = fnum;
							
							#ifdef DEBUG	
							printf("Frecuencia Leida: %.3f GHz holaa\n", aux->pda.frecuencia);
							#endif
								
							break;
							
						case 8:
							//NIVEL SEÑAL
								
					 		strtok(cadena, "-");
							token = strtok(NULL, " ");
							num = strtol(token, &eptr, 10);
							aux->pda.nivelSenal = num;
							
							#ifdef DEBUG	
							printf("Nivel Señal Leido: -%d dBm\n", aux->pda.nivelSenal);
							#endif
								
							break;
					 		
						default:
							#ifdef DEBUG
							printf("Error Case\n"); 	
					 		#endif
					 		
							break;
					}
					lineaLeida++;
				} else {
					#ifdef DEBUG
					printf("\n\n\n\t\t\tFinal de fichero!!\n\n\n");
					#endif
					break;
				}
			}while(lineaLeida<9);
			
						
			if(aux != 0)	{
			
				//LECTURA DE NUEVOS NODOS EN LA LISTA (Si los hay)
				if(lista == NULL){
					lista = aux;
					aux->sig = NULL;
				}else{
					aux->sig= lista;
					lista = aux;
				}
				
				//IMPRESION DE FICHERO LEIDO
				printf("\n\n\n===== Informacion completa de red Wifi =====\n");
				
								
				printf("\t\t= id: %d\n", aux->pda.identificador);
				printf("\t\t= Address - MAC: %s\n", aux->pda.MAC);
				printf("\t\t= ESSID: \"%s\"\n", aux->pda.ESSID);
				printf("\t\t= Mode: ");imprimirModo(aux->pda.modo);
				printf("\t\t= Channel: %d\n", aux->pda.canal);
				printf("\t\t= Encryption: %s\n", (aux->pda.cifrado==0)?"OFF":"ON");
				printf("\t\t= Quality: %d / %d\n", aux->pda.calidad_medida, aux->pda.calidad_maxima);		
				printf("\t\t= Frequency: %.3f GHz\n", aux->pda.frecuencia);
				printf("\t\t= Signal Level: -%d dBm\n", aux->pda.nivelSenal);
				printf("\n\n\n");
			}
		}
	}
	#ifdef DEBUG
	printf("\n\nFIN DE LECTURA DEL ARCHIVO!\n");
	#endif
	
	//CIERRE DE FICHERO
	fclose(fichero);
		
			
	int almancenado = 0;
	struct Lista *tmp = lista;
	while(tmp != NULL){
		almancenado++;
		// if (...)
		tmp = tmp -> sig;
	}
	
	#ifdef DEBUG
	printf("Cantidad nodos: %d\n", almancenado);
    #endif 
     
	return lista;
	
}
	
