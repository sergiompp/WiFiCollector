/**CFile***********************************************************************

  FileName    wifiCollector.c

  Synopsis    Main File.

  Description It's the main file. Here's the place where the menu is displayed
              and from all functions are called.

  SeeAlso     structWifi

  Author      Daniel De Vega 
  			  Sergio M. P�rez

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
//0. MAIN


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#include "data_read.h"
#include "data_read_double.h"
#include "data_read_L.h"

#include "structWifi.h"
#include "mostrarMenu.h"
#include "wifiCollector.h"
#include "wificollector_quit.h"
#include "wificollector_collect.h"
#include "wificollector_show_data_one_network.h"
#include "wificollector_select_best.h"
#include "wificollector_delete_net.h"
#include "wificollector_sort.h"
#include "wificollector_export.h"
#include "wificollector_import.h"



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



int main(int arg_count, char *arg_strings[]){
	struct Lista *listaWifi = NULL; 

    int id_aux = 0;
    int opcion = 0;
    char *yesNo = NULL;
	char *ESSIDLeido = NULL;
	char *nombreFichero = NULL;
	int comparar = 0;
    
	while(opcion != 1){

		mostrarMenu();
		opcion = data_read();
		
		switch(opcion){
			case 1:
				//SALIR DEL PROGRAMA
				
				yesNo = salir(listaWifi);
                if(strcmp(yesNo,"S")!=0 && strcmp(yesNo, "s") != 0){
                   // comparar = 1;
                   opcion = 0;
                }
               // free(yesNo);

				break;
			case 2:
				//COLLECT
				
				do{
					puts("\n�Que celda quiere recolectar? (1 - 21): ");
					id_aux = data_read();
					listaWifi =	collectWifi(listaWifi, id_aux);
					// Pedir al teclado
					puts("\nDesea anadir otro punto de acceso? [s/N]: ");
					yesNo = data_read_L();
					if(strcmp(yesNo,"S")==0 || strcmp(yesNo, "s") == 0){
	                   	comparar = 1;
	            	}else{
	            		comparar = 0;
					}
            	
            	}while(comparar == 1);
            	
		
				break;
			case 3:
				//MOSTRAR RED 
				puts("\nIndique el ESSID (entre ��): ");
                ESSIDLeido = data_read_L();
                showData(listaWifi, ESSIDLeido);
				
				break;
			case 4:
				//MOSTRAR MEJOR CALIDAD
				showBest(listaWifi);
				
				break;
			case 5:
				//BORRAR RED
				puts("\nIndique el ESSID (entre ��): ");
                ESSIDLeido = data_read_L();
                deleteNet(listaWifi, ESSIDLeido);
                
                
				break;
			case 6:
				//ORDENAR DECRECIENTE
				wificollector_sort(listaWifi);
				break;
			case 7:
				//EXPORT
				puts("\nIndique el nombre del fichero: ");
				nombreFichero = data_read_L();
				wificollector_export(listaWifi, nombreFichero);
				break;
			case 8:
				//IMPORT
				wificollector_import(listaWifi);
				break;
	
			default:
				printf("\nCaracter no valido. Numero del 1 al 8!\n\n");	
				break;
		}
	}
	
    // Todo ha ido bien y devolvemos un 0
	return 0;
}

