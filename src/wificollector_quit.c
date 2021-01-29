/**CFile***********************************************************************

  FileName    wificollector_quit.c

  Synopsis    The program ends.

  Description Ask for the list and delete it (All the information about the stored 
  			  WiFi cells are destroyed). 
  			  Return the pointer and close the program.

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
//1. QUIT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "data_read_L.h"
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

char *salir(struct Lista *lista){
    char *ptr = NULL;
    struct Lista *aux = NULL;
	
	do{
	    free(ptr);
	    #ifdef DEBUG
		puts("Â¿Esta seguro de que quiere salir el programa? [S/N] \n");
	    #endif
		ptr = data_read_L();
	    
		if((strcmp(ptr,"S") != 0 ) && (strcmp(ptr,"s") != 0 ) && (strcmp(ptr,"N") != 0 ) && (strcmp(ptr,"n") != 0 )){
	        #ifdef DEBUG
			puts("El valor introducido es incorrecto!!\n");
			#endif
		}
		
	}while ((strcmp(ptr,"S") != 0 ) && (strcmp(ptr,"s") != 0 ) && (strcmp(ptr,"N") != 0 ) && (strcmp(ptr,"n") != 0 ));
	
	if(strcmp(ptr,"S")==0 || strcmp(ptr, "s") == 0){
	
		while(lista != NULL){
	        
	        aux = lista;
	        lista = lista->sig;
	        free(aux->pda.MAC);
			free(aux->pda.ESSID);
	        free(aux);
		}
		
	}
	
	return ptr;
}
