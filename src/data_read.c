#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Funci�n********************************************************************

  Resumen      Funci�n para leer enteros

  Descripci�n  Crea una funci�n que permite leer enteros.

  Par�metros   No hay
  
******************************************************************************/
//0. DATA_READ



long int data_read(){
    
  
  char *ptr = NULL;
  size_t numero_bytes;
  ssize_t bytes_leidos;
  int long datos;
  char *s = NULL;
  numero_bytes = 0 ;
 
  do{
      
	free(s);
  	bytes_leidos = getline(&s, &numero_bytes, stdin);
  
  

    if(bytes_leidos == -1){
        puts("error");
    }
    
    datos = strtol(s, &ptr ,0);
    
    if(datos == 0){
		
        puts("Has introducido un valor invalido. Por favor introduce un numero mayor de 0");
		
    }
    
  }while(datos == 0);
  
  free(s);
  return datos;
  
}
