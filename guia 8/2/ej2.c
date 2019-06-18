/*EJERCICIO 2 GUIA 8 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSJ_NULL "Null pointer"

/*PROTOTIPOS*/

char *left_trim(const char *);

/************/

 int main(int argc, char const *argv[])
 {
   char * string="  hola";
   char* clean_string;

   if((clean_string=left_trim(string))==NULL)
   {
     fprintf(stderr, "%s\n",MSJ_NULL );
     return 1;
   }

   printf("%s\n",clean_string);

   return 0;
 }

 char * left_trim(const char * string)
 {
   size_t i=0,j;

   char * aux;

   if(string==NULL)
      return NULL;

   /*Cuento la cantidad de espacios*/
   while(*(string+i)==' ') i++;

   /*Pido memoria para la variable auxiliar*/
   if((aux=malloc((strlen((string)+1))*sizeof(char)))==NULL)
      return NULL;

   /*Armo la cadena limpia*/
   for(j=0;i<strlen(string);j++,i++)
   {
     aux[j]=string[i];
   }
   return aux;


 }
