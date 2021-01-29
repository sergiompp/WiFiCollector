/**CFile***********************************************************************

  FileName    mostrarMenu.c

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
//0. MOSTRAR MENU


#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void mostrarMenu(){
    printf("[2019] SAUCEM S.L. Recolector de redes inalámbricas\n\n");
    
	printf("\t[1] wificollector_quit\n");    
    printf("\t[2] wificollector_collect\n");
    printf("\t[3] wificollector_show_data_one_network\n");
    printf("\t[4] wificollector_select_best\n");
    printf("\t[5] wificollector_delete_net\n");
    printf("\t[6] wificollector_sort\n");
    printf("\t[7] wificollector_export\n");
    printf("\t[8] wificollector_import\n");
	  
    printf("\n\n\t\tOpción elegida: \n");
}
