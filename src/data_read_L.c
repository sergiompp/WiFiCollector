#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
/**Funci�n********************************************************************

  Resumen      Funci�n para leer una cadena de car�cteres.

  Descripci�n  Crea una funci�n que permite leer una cadena de car�cteres.

  Par�metros   No hay
  
******************************************************************************/
//0. DATA_READ_L

char *data_read_L(){
  char *c = NULL;
  size_t numero_bytes;
  ssize_t bytes_leidos;
  int i;

  numero_bytes = 0 ;
  
  
  bytes_leidos = getline(&c, &numero_bytes, stdin);

  if(bytes_leidos == -1){
      puts("error");
	  free(c);
  }

 for(i = 0; i < strlen(c); i++){
	if(c[i] == '\n'){
		c[i] = '\0';	
	}
 }
  
return c;
  
  
}
