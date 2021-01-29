/**CFile***********************************************************************

  FileName    wificollector_import.c

  Synopsis    Add the info inside in a binary file to the info of a list. 

  Description Ask for the list and the binary file. If the file has known info 
  			  in the list, it will be ignored. Otherwise, it will be added.
			  Return the list.

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
//7. IMPORT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "structWifi.h"
#include "data_read.h"
#include "data_read_L.h"

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

void wificollector_import(struct Lista *lista){
	printf("Indicar el nombre del fichero: \n");
	char* nombreFichero = data_read_L();
	
	
	FILE *fichero = fopen(nombreFichero, "rb");
    char *nombre = NULL;
    
    pthread_t hilo1;
	
	pthread_create(&hilo1, NULL, (void*)detectarEOF, NULL);
	pthread_join(hilo1, NULL);

    if(fichero == NULL){
        fflush(fichero);
    	#ifdef DEBUG
		printf("\nFichero mal importado\n");
		#endif  
        
	}else{
		while(!feof(fichero)){
			struct Lista *aux = (struct Lista*)malloc(sizeof(struct Lista));

			if(fread(aux, sizeof(lista), 1, fichero) != 1){
           		
				fclose(fichero);
           		free(nombreFichero);
           		free(aux);
           		
           		#ifdef DEBUG
				printf("Archivo importado!. \n");
				#endif
        		return;
       		}
       	 
			if(lista == NULL){
				lista = aux;
				lista -> sig = NULL;
			}else{
				aux -> sig = lista;
				lista = aux;
			}
		}	
        fclose(fichero);  
	} 
}
