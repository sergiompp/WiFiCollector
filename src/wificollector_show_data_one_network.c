/**CFile***********************************************************************

  FileName    wificollector_show_data_one_network.c

  Synopsis    Show a specific cell from the list.

  Description Ask for the list and the ESSID name of the WiFi cell will be displayed
  			  Return the Wifi cell.

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
//3. SHOW_DATA_ONE_NETWORK


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "structWifi.h"
#include "data_read.h"

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



void showData(struct Lista *lista, char *ESSID){
	struct Lista *aux = lista;
	struct Lista *auxMostrar = (struct Lista*)malloc(sizeof(struct Lista));
	
	if(aux == NULL){
		#ifdef DEBUG
		printf("\nNo hay ninguna red WiFi para mostrar, la lista esta vacia\n");
		#endif
	} else {
		do{
			if(strcmp(aux->pda.ESSID, ESSID)==0){
	        	auxMostrar = aux;
	        	auxMostrar->sig = aux->sig;
	        	
				//IMPRESION DE FICHERO LEIDO
				printf("\n\n\n===== Informacion completa de red Wifi =====\n");
					
				printf("\t\t= id: %d\n", auxMostrar->pda.identificador);
				printf("\t\t= Address - MAC: %s\n", auxMostrar->pda.MAC);
				printf("\t\t= ESSID: \"%s\"\n", auxMostrar->pda.ESSID);
				printf("\t\t= Mode: ");
				switch(auxMostrar->pda.modo){
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
				printf("\t\t= Channel: %d\n", auxMostrar->pda.canal);
				printf("\t\t= Encryption: %s\n", (auxMostrar->pda.cifrado==0)?"OFF":"ON");
				printf("\t\t= Quality: %d / %d\n", auxMostrar->pda.calidad_medida, auxMostrar->pda.calidad_maxima);		
				printf("\t\t= Frequency: %.3f GHz\n", auxMostrar->pda.frecuencia);
				printf("\t\t= Signal Level: -%d dBm\n", auxMostrar->pda.nivelSenal);
				printf("\n\n\n");	
				
				break;
			}else{
				aux = aux->sig;	
			}
				
		} while(aux->sig != NULL);
		
		#ifdef DEBUG
		printf("\nFinal de la lista de redes\n"); 
		#endif
	}
}

