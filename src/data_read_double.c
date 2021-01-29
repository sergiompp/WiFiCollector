#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Función********************************************************************

  Resumen      Función para leer datos de tipo double

  Descripción  Crea una función que permite leer datos de tipo double

  Parámetros   No hay
  
******************************************************************************/
//0. DATA_READ_DOUBLE


double data_read_double(){
  char *ptr;
  size_t numero_bytes;
  ssize_t bytes_leidos;
  double datos;
  char *s = NULL;
  numero_bytes = 0 ;
 
  do{
      
  	bytes_leidos = getline(&s, &numero_bytes, stdin);
  
  

    if(bytes_leidos == -1){
        puts("error");
    }
    
    datos = strtod(s, &ptr);
    
    if(datos == 0){
		
        puts("Has introducido un valor invalido. Por favor introduce un numero mayor de 0");
		
    }
    
  }while(datos == 0);
  
  free(s);
  return datos;
  
}
