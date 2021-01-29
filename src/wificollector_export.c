/**CFile***********************************************************************

  FileName    wificollector_export.c

  Synopsis    Save info in a binary file. 

  Description Ask for the list and save the info in a binary file with a name
  			  that user choose.
  			  Return the binary file.

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
//7. EXPORT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

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

void wificollector_export(struct Lista *lista, char *nombreFichero){
	FILE *fichero = fopen(nombreFichero,"wb");
    fflush(fichero);
	
    struct Lista *aux = lista;
    
    pthread_t hilo1;
	
	pthread_create(&hilo1, NULL, (void*) detectarEOF, NULL);
	pthread_join(hilo1, NULL);

    
	if(fichero == NULL){
		#ifdef DEBUG
		printf("Error de fichero");
		#endif
	} else {
		
        while(aux->sig!=NULL){
            
            assert(fwrite(&aux->pda.identificador, sizeof(int), 1, fichero) == 1);
			assert(fwrite(&aux->pda.MAC, sizeof(char),1, fichero) ==1 );
			assert(fwrite(&aux->pda.ESSID, sizeof(char), 1, fichero) == 1);
			assert(fwrite(&aux->pda.modo, sizeof(aux->pda.modo),1, fichero) ==1 );
            assert(fwrite(&aux->pda.canal, sizeof(int), 1, fichero) == 1);
			assert(fwrite(&aux->pda.cifrado, sizeof(aux->pda.cifrado),1, fichero) ==1 );
			assert(fwrite(&aux->pda.calidad_medida, sizeof(int), 1, fichero) == 1);
			assert(fwrite(&aux->pda.calidad_maxima, sizeof(int), 1, fichero) == 1);
			assert(fwrite(&aux->pda.frecuencia, sizeof(float), 1, fichero) == 1);
			assert(fwrite(&aux->pda.nivelSenal, sizeof(int),1, fichero) ==1 );
			
            aux = aux->sig;
        }
        fflush(fichero);
		fclose(fichero);
		#ifdef DEBUG
		printf("\n\n\t\tFichero Exportado Correctamente!\n\n");
		#endif
	}
}
