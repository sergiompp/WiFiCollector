/**CFile***********************************************************************

  FileName    wificollector_delete_net.c

  Synopsis    Delete a specific cell from the list.

  Description Ask for the list and the ESSID name of the WiFi cell to be deleted
  			  Return the list without that Wifi cell.

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
//5. DELETE NET


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
void deleteNet(struct Lista *lista, char *ESSID){
	struct Lista *aux = lista;
	struct Lista *auxBorrar = (struct Lista*)malloc(sizeof(struct Lista));
	
	if(aux == NULL){
		#ifdef DEBUG
		printf("\nNo hay ninguna red WiFi, la lista esta vacia\n");
		#endif
	} else {
		do{
			if(strcmp(aux->pda.ESSID, ESSID)==0){	
				auxBorrar = aux;
				aux->sig = aux->sig->sig;
	        	
	        	free(auxBorrar);
	        	
				break;
			}else{
				aux = aux->sig;	
			}
				
		} while(aux->sig != NULL);
		#ifdef DEBUG
		printf("\nRed Wifi seleccionada borrada de la lista!\n");
		printf("\nFinal de la lista de redes\n"); 
		#endif
	}
}

